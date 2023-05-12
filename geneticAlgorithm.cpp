#include<bits/stdc++.h>
using namespace std;
set<vector<int>>st;
// a global population array which will help in maintaining all generations 
vector<vector<int>> population;
// bestDistance _sofar is a variable for getting the best distance in a certain generation 
int bestDistance_sofar=INT_MAX,generation_number=1;
vector<int> thatBestFar;
// a utility function to print the best path so far 
void displayTheBest(int best,vector<int>best_path){
       cout<<endl;
       cout<<"-----------------------------------------------------------"<<endl;
       cout<<"Generation Number "<<generation_number++<<endl;
       cout<<"The Best Distance achieved so far "<<best<<endl;
       for(int it:best_path){
          cout<<it<<"->";
       }
       cout<<endl;
       cout<<"-----------------------------------------------------------"<<endl;
}
vector<int> getPopulationShuffled(int n){
    vector<int>v(n),f(n,0),v1(n+1);
    // INTIALIZE THE VECTOR USING IOTA FUNCTION 
    iota(v.begin(),v.end(),0);
    // now we will apply Fisher Yates algorithm for shuffling the population refer tutorials point article for same 
    int index;
    f[0]=1;
    for(int i=1;i<n;i++){
         do{
           index=rand()%(n);
        }while(f[index]!=0);
        f[index]=1;
        v1[i]=v[index];
    } 
    return v1;
}
// a function to make the intial population 
void make_population(){
    // each population is of size 200
    int times=200;
    while(times--){
        vector<int>tmp;
        // shuffle the array of length 10 
        tmp=getPopulationShuffled(10);
        // we use a set to avoid duplicates at the start 
        st.emplace(tmp);
    }
    for(auto it:st){
        population.push_back(it);
    }
}
// we need to do crossovers on any two parents from a given population 
vector<vector<int>> doCrossOvers(vector<int>&p1,vector<int>&p2){
    vector<vector<int>>container_for_parents;
    // using ordered set so as to maintain the order of elements of the parent array
    unordered_set<int>st_for_p1,st_for_p2;
    int n=p1.size();
    p1.erase(p1.begin());
    p1.pop_back();
    p2.erase(p2.begin());
    p2.pop_back();
    // now the crossover point is index number 2 , we can change this as we want 
    /*
         now what we do in crossover is that we have two parents
         p1-> 1 3 2 4 5 7 6
         p2-> 2 6 7 5 4 1 3
         while we crossover at a given point we keep the elements before the crossover point intact and than follow the order and add elements
         the crossover point is k=2 now when we do crossover we expect or array to look like 
         c1-> 1 3 2 6 7 5 4 
         c2-> 2 6 7 1 3 4 5
         this are cross-overed children please see that 1 3 2 and 2 6 7 where intact because k=2
         and other elements are in sequence of the other parent 
         i.e. 6 7 5 4 in c1 are in order of 6 7 5 4 of p2
    */
    int k=2;
    vector<int>te1(p1.begin()+0,p1.begin()+k);
    vector<int>te2(p2.begin()+0,p2.begin()+k);
    for(int i=0;i<te1.size();i++){
            st_for_p1.insert(te1[i]);
            st_for_p2.insert(te2[i]);
    }

    for(int i=0;i<p1.size();i++){
        if(st_for_p1.count(p2[i])==0){
            te1.push_back(p2[i]);
        }
         if(st_for_p2.count(p1[i])==0){
            te2.push_back(p1[i]);
         }
    }
    // need to add the start point in the begining and since we reach to start point back we push it back 
    // we apply crossover on array and finally we have 0->1->3->4->5->6->2->0 this kinda array
    te1.insert(te1.begin(),0);
    te1.push_back(0);
    te2.insert(te2.begin(),0);
    te2.push_back(0);
    container_for_parents.push_back(te1);
    container_for_parents.push_back(te2);
    // after doing crossover we return the new children
    return container_for_parents;
}
// we perform mutations on certain indexes if certain conditions are satisfied
void mutate(vector<int> &child, double mutationRate)
{
    // we give choice to swap any of the indexes from the below we skip last and first element as we don't want to mess up with start and endpoint 
    vector<int>indexes={1,2,3,4,5,6,7,8,9};
    for (int i = 1; i < child.size()-1; i++)
    {
        if ((float)rand() / RAND_MAX < mutationRate)
        {
            int randIdx = rand() % indexes.size();
            // swap that index with a randomly generate index
            swap(child[i], child[indexes[randIdx]]);
        }
    }
}
// roulette wheel is a way of choosing certain indexes from the cumulative array which fall in a certain range 
int rouletteWheel(vector<float>&cumalative){
  float random_num=(float)rand() / RAND_MAX ;
    int index_for_mutation=0;
    for(int i=0;i<cumalative.size()-1;i++){
    if(cumalative[i]<=random_num && cumalative[i+1]>=random_num){
            index_for_mutation=i;
            return i;
    }
  }
  return 0;
}
// this is the heart function of the program where we will be calling all the other functions
void crossOverAndMutations( vector<vector<int>>&population,vector<float>&cumalative){
/*
 we look at the criterions for crossovers mutations
 will be generating a random floating point number between 0 and 1 for two times separately and on basis of that we will 
 decide whether to mutate and crossover to not 
 For mutations 
      if(random()<mutation_rate) than perform mutations
      mutation_rate here is 1% to 5% 
 For Crossovers
      if(random()<crossover_rate) than perform crossover
      crossover_rate here is 80% to 90%
now iff we perform the above operations than we add the new children in the a new_population array programatically we are going to change the whole
population by mutations and crossovers

*/
  vector<vector<int>> new_population(population.size()); 
  int currIdx=0;
  while(currIdx!=population.size()){
  int index_for_mutation=rouletteWheel(cumalative);
  int index_for_mutation1=rouletteWheel(cumalative);
  vector<int> p1=population[index_for_mutation];
  vector<int>p2=population[index_for_mutation1];
  // we are keeping crossover rate as 85% and mutation rate as 5% as per as instructions by rege mam
  float crossover_rate=0.80,mutation_rate=0.05;
  float value_for_mutation=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 if(value_for_mutation<crossover_rate){
    vector<vector<int>>tmp=doCrossOvers(p1,p2);
      mutate(tmp[0],mutation_rate);
     mutate(tmp[1],mutation_rate);
      new_population[currIdx++]=tmp[0];
      new_population[currIdx++]=tmp[1];
  }
  // else if when the crossover and mutations are not done we add the parents to the population
  else{
   new_population[currIdx++]=p1;
  new_population[currIdx++]=p2;
  }
  }
  population=new_population;
}
// an utility function to get the best so far distance and fitness , we will also normalize things here 
vector<float>getFitnessandNormalized(const vector<vector<int>>&dist){
     vector<int>fitnessVals;
// getting the fitness values by using the original input array 
    for(int i=0;i<population.size();i++){
        int ans=0;
        for(int j=0;j<population[0].size()-1;j++){
            int tmp=dist[population[i][j]][population[i][j+1]];
            ans+=tmp;
        }
        if(ans<bestDistance_sofar){
            bestDistance_sofar=ans;
            thatBestFar=population[i];
        }
        fitnessVals.push_back(ans);
    }
/*
we will be normalizing the fitnesses and further we will be using the normalized array to get the cumulative array which is used in the 
above functions now what do I mean by Normalization of array ? 
its the basic stats which we did in 12th grade
take the sum of reciprocals of fitness values and generate a new array by dividing all values of reciprocals array  now we do have an array which
if taken sum will sum-up to 1 than we will get the cumulative array
fitness vals: 10, 20 ,34 ,89 .......
reciprocals : 1/10, 1/20 ,1/34 ,1/89......(let's sum this up we have a sum lets say x)
normalized : reciprocals[i]/x ,reciprocals[i+1]/x,reciprocals[i+2]/x......
cumulative : normalized[0], normalized[i]+cumulative[i-1],normalized[i+1]+cumulative[i-1]......
the cumulative array which is generated is being used by us for other purposes
*/
    vector<double>nor;
    for(int it:fitnessVals){
        nor.push_back((float)1/it);
    }
    float totalOfnorm=accumulate(nor.begin(),nor.end(),0.0000);
    for(int i=0;i<nor.size();i++){
        nor[i]=(float)nor[i]/(float)totalOfnorm;
    }
    float one=accumulate(nor.begin(),nor.end(),float(0.0000));
    vector<float>cumalative(nor.size());
    cumalative[0]=nor[0];
    for(int i=1;i<nor.size();i++){
        cumalative[i]=nor[i]+cumalative[i-1];
    }
  displayTheBest(bestDistance_sofar,thatBestFar);
  return cumalative;
}
int main(){
    /* 
    The overall flow of the code will be like 
    input will be a matrix just like TSP
    we need to get a population 
      -- make_population()
      -- getShuffled() (for getting elements shuffled)
    fitness calculation of the population
      --getFitnessAndNormalized() (will be printing the best distance so far here )
    get the crossovers and mutations
       crossoversandmutations()---> use rouletteWheel() for selection of children 
        --doCrossovers()
        --mutate()
    */ 
    // this srand fuction helps us to generate random values everytime we need during the runtime of the program
    srand(time(0));
    // we need a population initially we'll generate that using this 
    make_population();
    vector<vector<int>> input = {
        {INT_MAX, 20, 30, 10, 11, 15, 13, 2, 12, 1},
        {15, INT_MAX, 16, 4, 2, 20, 1, 7, 18, 11},
        {3, 5, INT_MAX, 2, 4, 9, 21, 8, 9, 14},
        {19, 6, 18, INT_MAX, 3, 10, 9, 20, 15, 21},
        {16, 4, 7, 16, INT_MAX, 19, 1, 13, 11, 2},
        {1, 14, 8, 12, 20, INT_MAX, 2, 9, 13, 10},
        {5, 12, 9, 4, 8, 22, INT_MAX, 12, 19, 22},
        {19, 13, 5, 13, 11, 31, 8, INT_MAX, 11, 6},
        {13, 29, 17, 6, 9, 15, 7, 13, INT_MAX, 24},
        {6, 14, 9, 26, 29, 13, 3, 21, 12, INT_MAX},

    };
    cout<<endl;
    // we will be generating 300 different generations we change it as per as our requirements
    int maxGenerations=300;
    while(maxGenerations--){
    vector<float>cumalative=getFitnessandNormalized(input);
    crossOverAndMutations(population,cumalative);
    }
}
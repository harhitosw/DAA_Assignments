#include<bits/stdc++.h>
using namespace std;
set<vector<int>>st;
vector<vector<int>> population;
vector<int> getPopulationShuffled(int n){
    vector<int>v(n),f(n,0),v1(n+1);
    // INTIALIZE THE VECTOR USING IOTA FUNCTION 
    iota(v.begin(),v.end(),0);
    // now we will apply Fisher Yates algorithm for shuffling the population
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
void make_population(){
    int times=50;
    while(times--){
        vector<int>tmp;
        tmp=getPopulationShuffled(5);
        st.emplace(tmp);
    }
    for(auto it:st){
        population.push_back(it);
    }
//    for(int i=0;i<population.size();i++){
//         for(int j=0;j<population[0].size();j++){
//             cout<<population[i][j]<<" ";
//         }
//         cout<<endl;
//     } 
}
vector<vector<int>> doMutations(vector<int>&p1,vector<int>&p2){
   cout<<"Parents before mutations"<<endl;
    // for(int it:p1){
    //     cout<<it<<" ";
    // }
    // cout<<endl;
    // for(int it:p2){
    //     cout<<it<<" ";
    // }
    vector<vector<int>>container_for_parents;
    unordered_set<int>st_for_p1,st_for_p2;
    int n=p1.size();
    p1.erase(p1.begin());
    p1.pop_back();
    p2.erase(p2.begin());
    p2.pop_back();
    int k=2;
    vector<int>te1(p1.begin()+0,p1.begin()+k);
    vector<int>te2(p2.begin()+0,p2.begin()+k);
    // for(int it:te1){
    //     cout<<it<<" ";
    // }
    // cout<<endl;
    // for(int it:te2){
    //     cout<<it<<" ";
    // }
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
    te1.insert(te1.begin(),0);
    te1.push_back(0);
    te2.insert(te2.begin(),0);
    te2.push_back(0);
    cout<<endl;
//  cout<<"Parents after mutations"<<endl;
//    for(int it:te1){
//         cout<<it<<" ";
//     }
//     cout<<endl;
//     for(int it:te2){
//         cout<<it<<" ";
//     }
    container_for_parents.push_back(te1);
    container_for_parents.push_back(te2);
    return container_for_parents;
}
void crossOverAndMutations(const vector<vector<int>>&population,vector<float>&cumalative){
     // generate a random number between 0 and 1 from float
  float random_num=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  float random_num1=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  int index_for_mutation,index_for_mutation1;
  for(int i=0;i<cumalative.size()-1;i++){
    if(cumalative[i]<=random_num && cumalative[i+1]>random_num){
            index_for_mutation=i;
    }
  }
  for(int i=0;i<cumalative.size()-1;i++){
    if(cumalative[i]<=random_num1 && cumalative[i+1]>random_num1){
            index_for_mutation1=i;
    }
  }
  vector<int> p1=population[index_for_mutation];
  vector<int>p2=population[index_for_mutation1];
//   cout<<index_for_mutation<<endl;
//   cout<<index_for_mutation1<<endl;
  float threshold_for_mutations=0.5;
  float value_for_mutation=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 if(value_for_mutation>=threshold_for_mutations){
    vector<vector<int>>tmp=doMutations(p1,p2);
      st.insert(tmp[0]);
      st.insert(tmp[1]);
      cout<<"After we have added the mutated population"<<endl;
      make_population();
  }
}

vector<float>getFitnessandNormalized(const vector<vector<int>>&dist){
     vector<int>fitnessVals;
    for(int i=0;i<population.size();i++){
        int ans=0;
        for(int j=0;j<population[0].size()-1;j++){
            int tmp=dist[population[i][j]][population[i][j+1]];
            ans+=tmp;
        }
        fitnessVals.push_back(ans);
    }
  
    vector<double>nor;
    for(int it:fitnessVals){
        nor.push_back((float)1/it);
    }
    
    for(auto it:fitnessVals){
        cout<<it<<" ";
    }
    /*
    cout<<endl;
    for(auto it:    nor){
        cout<<it<<" ";
    } */
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
  return cumalative;
}

  
int main(){
    // input will be a matrix just like TSP
    // we need to get a population 
    // fitness calculation 
    // crossover 
    // selection 
    make_population();
    vector<vector<int>> input = {
        {INT_MAX, 20, 30, 10, 11},
        {15, INT_MAX, 16, 4, 2},
        {3, 5, INT_MAX, 2, 4},
        {19, 6, 18, INT_MAX, 3},
        {16, 4, 7, 16, INT_MAX},
    };
    cout<<endl;
    vector<float>cumalative=getFitnessandNormalized(input);
    crossOverAndMutations(population,cumalative);

    
    
}
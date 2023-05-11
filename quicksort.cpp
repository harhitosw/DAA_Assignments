// doing quicksort for three times by changing the Pivot elements
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
long long cnt=0;
// when the first element is the pivot
int partition(vector<int>&v,int strt,int end){
      int pivot=v[strt];
      int i=strt;
      int j=end+1;
      do
      {
       do
       {
        i++;
        cnt+=2;
       } while (v[i]<pivot);
       do
       {
        j--;
        cnt+=2;
       } while (v[j]>pivot);
       if(i<j) {
        swap(v[i],v[j]);
        cnt+=4;
       }
       cnt+=1;
      } while(i<j);
      v[strt]=v[j];
      v[j]=pivot;
      cnt+=3;
     return j;
}
// when the last element is the pivot
int partition1(vector<int>&v, int low, int high)
{
    int pivot = v[high]; // pivot
    int i
        = (low
           - 1); // Index of smaller element and indicates
                 // the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (v[j] < pivot) {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }
    }
    swap(v[i+1], v[high]);
    return (i + 1);
}
void QuickSort(vector<int>&v,int strt,int end){
     if(strt<end){
        int p=partition(v,strt,end);
        QuickSort(v,strt,p-1);
        QuickSort(v,p+1,end);
     }
     else{
        return;
     }
}
int main(){
    //vector<int> v{10,7,114,13,12,2,1,15,0,6};
    vector<int>v{45,12,60,23,80,89,65,73,8,92};
    auto start = high_resolution_clock::now();
    QuickSort(v,0,v.size()-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
   for(auto it:v){
      cout<<it<<endl;
   }
   cout<<" The Count is "<<cnt<<endl;
 
// To get the value of duration use the count()
// member function on the duration object
cout << duration.count() << endl;
}
/*
x,y
x=x^y
y=x^y
x=x^y
*/
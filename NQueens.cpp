/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
vector<int>ans(60);
int nums=0;
bool place(int k,int j){
    for(int i=1;i<=k-1;i++){
        if(ans[i]==j or (abs(ans[i]-j)==abs(i-k)) ) return false;
        
    }
    return true;
}
void Nqueens(int k,int n){
    if(nums>=1){
        return;
    }
    for(int j=1;j<=n;j++){
        if(place(k,j)){
            ans[k]=j;
            if(k==n) {
            for(int i=1;i<=n;i++){
                cout<<ans[i]<<" ";
            }
            cout<<endl;
            nums++;
        }
        else{
            Nqueens(k+1,n);
        }
        }
    }
}
int main()
{
    
    int k=1,n=30;
    auto start = chrono::high_resolution_clock::now();
    Nqueens(k,n);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = 
      chrono::duration_cast<chrono::milliseconds>(end - start).count();
  cout<<"the Time taken is "<<time_taken<<" milli seconds"<<endl;
    return 0;
}


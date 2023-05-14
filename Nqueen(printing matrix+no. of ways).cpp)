#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;
int ctr=0;
bool place(int k, int j, int x[]){
    for(int q=1; q<=k-1; q++){
        if((j==x[q])||(abs(k-q)==abs(j-x[q]))){
            return false;
        }
    }
    return true;
}

void displaymatrix(int x[], int n){
    // cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<endl;
    // cout<<n<<endl;
    for(int i=0; i<n; i++){
        int p[n];
        for(int iii=0;iii<n;iii++){p[iii]=0;}
        p[x[i+1]-1]=1;
        for(int iii=0;iii<n;iii++){cout<<p[iii]<<" ";}
        cout<<endl;
    }    
}

void nq(int k,int n, int x[]){
    for(int j=1; j<=n; j++){
        if(place(k,j, x)){
         x[k]=j;
         if(k==n){
             for(int jj=1; jj<n+1; jj++){cout<<x[jj]<<" ";}
             ctr++;
             cout<<endl;
             displaymatrix(x,n);
             cout<<endl;
             
         }
         else{
             nq(k+1, n, x);
         }
        }
    }
}


int main()
{
    // cout<<"Hello World";
    int n;
    cin>>n;
    int ctr1[n+1];
    int tt[n+1];
    for(int ii=4; ii<=n;ii++){
       
        int x[ii+1];
        auto start = high_resolution_clock::now();
        nq(1,ii,x);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // cout << duration.count() << endl;
       
        ctr1[ii]=ctr;
        ctr=0;
        tt[ii]=duration.count();
    }
    cout<<"no. of ways"<<endl;
    for(int kk=4; kk<=n;kk++){
        cout<<ctr1[kk]<<" ";
    }
    cout<<endl;
    cout<<endl;
    cout<<"time complexity"<<endl;
    for(int kk=4; kk<=n;kk++){
        cout<<tt[kk]<<" ";
    }
    cout<<endl;
   
    return 0;
}

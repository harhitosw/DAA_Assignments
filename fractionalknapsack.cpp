#include<bits/stdc++.h>
using namespace std;
bool sortbyth(const tuple<int, int, double>& a, 
              const tuple<int, int, double>& b)
{
    return (get<2>(a) > get<2>(b));
}
vector<double>solve(vector<tuple<int,int,double>>&v,int n ,int &KPrw){
    vector<double> ans(v.size(),0.00);
    int i=0;
    while(get<1>(v[i])<=KPrw and i<=v.size()){
         ans[i]=1.000;
         KPrw=KPrw-(get<1>(v[i]));
         i++;
    }
    if(i<v.size()){
        ans[i]=(double)(KPrw)/(double)get<1>(v[i]);
    }
    return ans;
}
int main(){
    int n;
    // we use a tuple for profit weight and profit/weight ratio
    vector<tuple<int,int,double>> v;
    cout<<"Enter the size of the input"<<endl;
    cin>>n;
    int KPrw=15;
    for(int i=0;i<n;i++){
        int profit,weight;
        cout<<"Enter the profit of the input"<<endl;
        cin>>profit;
        cout<<"Enter the weight of the input"<<endl;
        cin>>weight;
        double pbyw=(double)profit/(double)weight;
        v.push_back(make_tuple(profit,weight,pbyw));
    }
    sort(v.begin(),v.end(),sortbyth);
    double maxProfit=0;
       vector<double>tmp=solve(v,n,KPrw);
      for(int i=0;i<tmp.size();i++){
        maxProfit+=(double)tmp[i]*(double)get<0>(v[i]);
      }
      cout<<setprecision(3)<<maxProfit<<endl;

    return 0;
}
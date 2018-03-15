// https://www.codechef.com/problems/ANUBGC/
// Digit DP :) thanx to problem setter :)
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#define ll long long int
using namespace std;
int digit;
vector<int> v;
ll dp[18][2][2][2];
ll solve(int pos,int tight,int found,int nzero){
if(pos == v.size())
    return (nzero&&found);
ll &res = dp[pos][tight][found][nzero];
if(res!=-1)
    return res;
res = 0;
for(int i=0;i<10;i++){
  if(i>=1)
    nzero = 1;
  if(tight||pos==0){
    if(i<v[pos]){
      res+=solve(pos+1,0,found|(i==digit && nzero),nzero);
    }
    else if(i==v[pos]){
      res+=solve(pos+1,1,found|(i==digit && nzero),nzero);
    }
  }
  else{
    res+=solve(pos+1,0,found|(i==digit && nzero),nzero);
  }
}
return res;
}
int main(){
int t;
ll n,num,den;
scanf("%d",&t);
while(t--){
    scanf("%lld",&n);
    num = 0;
    den = n*10;
    v.clear();
    while(n){
        v.push_back(n%10);
        n/=10;
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<10;i++){
        digit = i;
        memset(dp,-1,sizeof dp);
        num += solve(0,0,0,0);
    }
    ll g = __gcd(num,den);
    printf("%lld/%lld\n",num/g,den/g);
}
return 0;
}

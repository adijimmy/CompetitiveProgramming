// https://www.codechef.com/SEPT16/problems/JTREE/
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005
typedef long long int ll;
vector<int> G[MAXN];
ll dp[MAXN];
ll res[MAXN];
ll st[4*MAXN];
int n;
vector< pair<int,int> > P[MAXN];
void build(int l,int r,int idx) {
 if(l==r) {
     st[idx] = dp[l];
     return;
 }
 int mid = (l+r)>>1;
 build(l,mid,2*idx); build(mid+1,r,2*idx+1);
 st[idx] = min(st[2*idx],st[2*idx+1]);
}
void update(int l,int r,int idx,int pos,ll val) {
  if(l>pos || r<pos) return;
  if(l == r && l == pos) {
     st[idx] = val;
     return;
  }
  int mid = (l+r)>>1;
  update(l,mid,2*idx,pos,val); update(mid+1,r,2*idx+1,pos,val);
  st[idx] = min(st[2*idx],st[2*idx+1]);
}
ll query(int l,int r,int idx,int a,int b) {
  if(l>b || r<a) return 1000000000000000000LL;
  if(l>=a && r<=b) return st[idx];
  int mid = (l+r)>>1;
  return min(query(l,mid,2*idx,a,b),query(mid+1,r,2*idx+1,a,b));
}
void dfs(int u,int idx) {
  for(int i=0;i<P[u].size();i++) {
     int v = P[u][i].first;
     int w = P[u][i].second;
     int l = max(0,idx-v);
     int r = max(0,idx-1);
     res[u] = min(res[u],w+query(0,n-1,1,l,r));
  }
  update(0,n-1,1,idx,res[u]);
  for(int i=0;i<G[u].size();i++) {
     int vv = G[u][i];
     dfs(vv,idx+1);
  }
  update(0,n-1,1,idx,0);
}
int main() {
 int m,u,v,q,s,V,K,W;
 scanf("%d %d",&n,&m);
 for(int i=1;i<=n;i++) dp[i] = res[i] = 1000000000000000000LL;
 dp[0] = 0;
 res[1] = 0;
 build(0,n-1,1);
 for(int i=0;i<n-1;i++) {
     scanf("%d %d",&u,&v);
     G[v].push_back(u);
 }
 for(int i=0;i<m;i++) {
     scanf("%d %d %d",&V,&K,&W);
     P[V].push_back(make_pair(K,W));
 }
 dfs(1,0);
 scanf("%d",&q);
 while(q--) {
     scanf("%d",&s);
     printf("%lld\n",res[s]);
 }
 return 0;
}

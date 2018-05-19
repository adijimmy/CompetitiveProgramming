// https://www.codechef.com/JUNE17/problems/CLONEME/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 100005
const ll p = 1e6+3;
const ll m = 1e6+3;
const ll mod = 1e9+7;
ll pw[MAXN];
struct node {
  node *left;
  node *right;
  ll sum;
  int cnt;
};
int N,Q;
int ar[MAXN];
node *root[MAXN];
vector<pair<int,int> > vec;
int indexx[MAXN],rindexx[MAXN];
 
inline ll power(ll a,ll b) {
  ll res = 1LL;
  while(b) {
    if(b&1) res = (res*a)%mod;
    a = (a*a)%mod;
    b >>= 1;
  }
  return res;
}
 
void pre() {
  pw[0] = 0;
  for(int i=1;i<=100000;i++) {
    pw[i] = (power(i,p)*m)%mod;
  }
}
 
node * makeNode() {
  node *p = new node;
  p->left = p->right = NULL; p->sum = 0LL; p->cnt = 0;
  return p;
}
 
void build(int l,int r,node *ptr) {
    if(l > r || l == r) return;
    int mid = (l+r)>>1;
    ptr->left = makeNode(); ptr->right = makeNode();
    build(l,mid,ptr->left); build(mid+1,r,ptr->right);
}
 
void persist(node *cur,node *prev,int l,int r,int position,int val) {
    if(l > r || l > position || r < position) return;
    if(l == r && l == position) {
      cur->sum = pw[val];
      cur->cnt = 1;
      return;
    }
    int mid = (l+r)>>1;
    if(position <= mid) {
      cur->right = prev->right;
      cur->left = makeNode();
      persist(cur->left,prev->left,l,mid,position,val);
      cur->sum = cur->left->sum + cur->right->sum;
      if(cur->sum >= mod) cur->sum -= mod;
      cur->cnt = cur->left->cnt + cur->right->cnt;
    }
    else {
      cur->left = prev->left;
      cur->right = makeNode();
      persist(cur->right,prev->right,mid+1,r,position,val);
      cur->sum = cur->left->sum + cur->right->sum;
      if(cur->sum >= mod) cur->sum -= mod;
      cur->cnt = cur->left->cnt + cur->right->cnt;
    }
}
 
void process(int pos) {
     root[pos] = makeNode();
     node *cur = root[pos];
     node *prev = root[pos-1];
     persist(cur,prev,1,N,indexx[pos],ar[pos]);
}
 
ll query(node *cur,int l,int r,int a,int b) {
   if(l > r || r < a || l > b || a > b) return 0;
   if(l >= a && r <= b) return cur->sum;
   int mid = (l+r)>>1;
   ll res = query(cur->left,l,mid,a,b) + query(cur->right,mid+1,r,a,b);
   if(res >= mod) res -= mod;
   return res;
}
 
inline int getMiddle(node *p,node *q,int l,int r,int k) {
    if(l == r) return l;
    ll mid = (l+r)>>1;
    ll cnt = p->left->cnt - q->left->cnt;
    if(cnt >= k) return getMiddle(p->left,q->left,l,mid,k);
    return getMiddle(p->right,q->right,mid+1,r,k-cnt);
}
 
bool solve(int l,int r,int a,int b,int c,int d) {
    int cnt = 0;
    while(l <= r) {
        if(cnt >= 2) break;
        int mid = (l+r)>>1;
        int midA = getMiddle(root[b],root[a-1],1,N,mid);
        int midB = getMiddle(root[d],root[c-1],1,N,mid);
 
        ll totHashA = (query(root[b],1,N,1,N) - query(root[a-1],1,N,1,N) + mod)%mod;
        ll rHashA = (query(root[b],1,N,midA+1,N) - query(root[a-1],1,N,midA+1,N) + mod)%mod;
        ll lHashA = (totHashA - (pw[rindexx[midA]]+rHashA)%mod + mod)%mod;
 
        ll totHashB = (query(root[d],1,N,1,N) - query(root[c-1],1,N,1,N) + mod)%mod;
        ll rHashB = (query(root[d],1,N,midB+1,N) - query(root[c-1],1,N,midB+1,N) + mod)%mod;
        ll lHashB = (totHashB - (pw[rindexx[midB]]+rHashB)%mod + mod)%mod;
 
        if(lHashA != lHashB && rHashA != rHashB) {
          cnt += 2;
          break;
          if(rindexx[midA] != rindexx[midB]) cnt++;
        }
        else if(lHashA != lHashB && rHashA == rHashB) {
          if(rindexx[midA] != rindexx[midB]) cnt++;
          r = mid-1;
        }
        else if(lHashA == lHashB && rHashA != rHashB) {
          if(rindexx[midA] != rindexx[midB]) cnt++;
          l = mid+1;
        }
        else if(lHashA == lHashB && rHashA == rHashB) {
          if(rindexx[midA] != rindexx[midB]) cnt++;
          break;
        }
    }
    if(cnt >= 2) return false;
    return true;
}
 
int main() {
  int T,a,b,c,d;
  pre();
  scanf("%d",&T);
  while(T--) {
    scanf("%d %d",&N,&Q);
    root[0] = makeNode();
    vec.clear();
    for(int i=1;i<=N;i++) {
       scanf("%d",&ar[i]);
       vec.push_back(make_pair(ar[i],i));
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<vec.size();i++) {
        indexx[vec[i].second] = i+1;
        rindexx[i+1] = vec[i].first;
    }
    build(0,N,root[0]);
    for(int i=1;i<=N;i++) process(i);
    while(Q--) {
        scanf("%d %d %d %d",&a,&b,&c,&d);
        bool flag = solve(1,b-a+1,a,b,c,d);
        if(flag) puts("YES");
        else puts("NO");
    }
  }
  return 0;
}

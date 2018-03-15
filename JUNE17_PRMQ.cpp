// https://www.codechef.com/JUNE17/problems/PRMQ/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 100005
#define MAXP 1000005
int a[MAXN];
int cnt[MAXP];
vector<pair<int,int> > v;
struct node {
    node *left,*right;
    ll value;
};
node *root[MAXP];
node* makeNode() {
  node *p = new node;
  p->left = NULL;
  p->right = NULL;
  return p;
}
void getPrimeFactors(int n) {
  v.clear();
  if(n%2 == 0) {
    while(n%2 == 0) {
        cnt[2]++;
        n = n/2;
    }
    v.push_back(make_pair(2,cnt[2]));
  }
  for(int i=3;i<=sqrt(n);i+=2) {
     if(n%i == 0) {
        while(n%i == 0) {
            cnt[i]++;
            n = n/i;
        }
        v.push_back(make_pair(i,cnt[i]));
     }
  }
  if(n>2) {
    cnt[n]++;
    v.push_back(make_pair(n,cnt[n]));
  }
}
void build(node * ptr,int l,int r) {
   if(l > r) return;
   if(l == r) {
     ptr->value = cnt[l];
     return;
   }
   int mid = (l+r)>>1;
   ptr->left = makeNode();
   ptr->right = makeNode();
   build(ptr->left,l,mid); build(ptr->right,mid+1,r);
   ptr->value = ptr->left->value + ptr->right->value;
}
int bsearch(int l,int r,int val) {
  while(l <= r) {
    int mid = (l+r)>>1;
    if(v[mid].first <= val) l = mid+1;
    else r = mid-1;
  }
  return l-1;
}
void persist(node *cur,node *prev,int l,int r,int a,int b) {
   if(l > r || l > v[b].first || r < v[a].first || a > b) return;
   if(l == r && a == b && l == v[a].first) {
    cur->value = v[a].second;
    return;
   }
   int mid = (l+r)>>1;
   int pos = bsearch(a,b,mid);
   int lpart = pos-a+1;
   int rpart = b-a+1-lpart;
   if(lpart > 0 && rpart == 0) {
     cur->right = prev->right;
     cur->left = makeNode();
     persist(cur->left,prev->left,l,mid,a,pos);
   }
   else if(lpart == 0 && rpart > 0) {
     cur->left = prev->left;
     cur->right = makeNode();
     persist(cur->right,prev->right,mid+1,r,pos+1,b);
   }
   else {
     cur->left = makeNode();
     cur->right = makeNode();
     persist(cur->left,prev->left,l,mid,a,pos);
     persist(cur->right,prev->right,mid+1,r,pos+1,b);
   }
   cur->value = cur->left->value + cur->right->value;
}
void process(int pos) {
  int n = a[pos];
  if(pos == 0) {
    root[pos] = makeNode();
    getPrimeFactors(n);
    build(root[pos],1,1000000);
  }
  else {
     root[pos] = makeNode();
     node *cur = root[pos];
     node *prev = root[pos-1];
     getPrimeFactors(n);
     persist(cur,prev,1,1000000,0,v.size()-1);
  }
}
ll query(node *cur,int l,int r,int a,int b) {
   if(l > r || l > b || r < a) return 0;
   if(l >= a && r <= b) return cur->value;
   int mid = (l+r)>>1;
   return query(cur->left,l,mid,a,b) + query(cur->right,mid+1,r,a,b);
}
ll solve(int lastPos,int l,int r) {
   if(lastPos < 0) return 0;
   return query(root[lastPos],1,1000000,l,r);
}
int main() {
  int N,L,R,X,Y;
  scanf("%d",&N);
  for(int i=0;i<N;i++) scanf("%d",&a[i]);
  memset(cnt,0,sizeof cnt);
  for(int i=0;i<N;i++) process(i);
  int Q;
  scanf("%d",&Q);
  while(Q--) {
    scanf("%d %d %d %d",&L,&R,&X,&Y);
    L--; R--;
    ll res = solve(R,X,Y) - solve(L-1,X,Y);
    printf("%lld\n",res);
  }
}
 

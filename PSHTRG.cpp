#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 100005;
struct R {
    ll val,pos;
};
R T[4*N];
ll a[N],n;
void B(ll idx,ll l,ll r) {
   if(l == r) {
      T[idx] = {a[l],l};
      return;
   }
   ll m = (l+r)>>1;
   B(2*idx,l,m); B(2*idx+1,m+1,r);
   if(T[2*idx].val > T[2*idx+1].val) T[idx] = T[2*idx];
   else T[idx] = T[2*idx+1];
}
R Q(ll idx,ll l,ll r,ll a,ll b) {
   if(l>b || r<a) return {0,0};
   if(l>=a && r<=b) return T[idx];
   ll m = (l+r)>>1;
   R p = Q(2*idx,l,m,a,b);
   R q = Q(2*idx+1,m+1,r,a,b);
   if(p.val > q.val) return p;
   return q;
}
void D(ll idx,ll l,ll r,ll p,ll v) {
   if(l == r && l == p) {
     a[p] = v;
     T[idx] = {v,l};
     return;
   }
   if(r < p || l > p) return;
   ll m = (l+r)>>1;
   D(2*idx,l,m,p,v); D(2*idx+1,m+1,r,p,v);
   if(T[2*idx].val > T[2*idx+1].val) T[idx] = T[2*idx];
   else T[idx] = T[2*idx+1];
}
ll solve(ll l,ll r) {
    ll a = 0,b = 0,c = 0;
    vector<pair<ll,ll> > revert; // val and pos
    bool flag = false;
    while(1) {
        R p = Q(1,0,n-1,l,r);
        if(p.val == 0) break;
        revert.push_back({p.val,p.pos});
        D(1,0,n-1,p.pos,0);
        a = b;
        b = c;
        c = p.val;
        if(a!=0 && b!=0 && c!=0 && b+c>a) {
            flag = true;
            break;
        }
    }
    for(ll i=0;i<revert.size();i++) {
        D(1,0,n-1,revert[i].second,revert[i].first);
    }
    if(flag) return a+b+c;
    return 0;
}
int main() {
    //freopen("qns.txt","r",stdin);
    //freopen("ans.txt","w",stdout);
    ll q,t,L,R,idx,val;
    scanf("%lld %lld",&n,&q);
    for(ll i=0;i<n;i++) {
        scanf("%lld",&a[i]);
    }
    B(1,0,n-1);
    while(q--) {
        scanf("%lld",&t);
        if(t == 1) {
            scanf("%lld %lld",&idx,&val);
            idx--;
            D(1,0,n-1,idx,val);
        }
        else {
            scanf("%lld %lld",&L,&R);
            L--; R--;
            ll res = solve(L,R);
            printf("%lld\n",res);
        }
    }
    return 0;
}

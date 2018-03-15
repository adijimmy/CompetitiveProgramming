// https://www.codechef.com/MARCH18A/problems/XXOR/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAXN = 1e5+5;
int a[MAXN];
int T[4*MAXN][31];
void build(int l,int r,int idx) {
    if(l == r) {
        int n = a[l];
        for(int i=0;i<31;i++) {
            if(n & (1<<i)) T[idx][30-i] = 1;
            else T[idx][30-i] = 0;
        }
        return;
    }
    int m = (l+r)>>1;
    build(l,m,2*idx); build(m+1,r,2*idx+1);
    for(int i=0;i<31;i++) {
       T[idx][i] = T[2*idx][i] + T[2*idx+1][i];
    }
}
vector<int> solve(int l,int r,int idx,int a,int b) {
    if(l>=a && r<=b) {
        vector<int> v1(31);
        for(int i=0;i<31;i++) v1[i] = T[idx][i];
        return v1;
    }
    if(r<a || l>b) {
        vector<int> v2(31);
        for(int i=0;i<31;i++) v2[i] = 0;
        return v2;
    }
    int m = (l+r)>>1;
    vector<int> v1 = solve(l,m,2*idx,a,b);
    vector<int> v2 = solve(m+1,r,2*idx+1,a,b);
    vector<int> v(31);
    for(int i=0;i<31;i++) v[i] = v1[i] + v2[i];
    return v;
}
int main() {
    //freopen("qns.txt","r",stdin);
    int N,Q,L,R;
    scanf("%d %d",&N,&Q);
    for(int i=0;i<N;i++) scanf("%d",&a[i]);
    build(0,N-1,1);
    while(Q--) {
        scanf("%d %d",&L,&R);
        vector<int> v = solve(0,N-1,1,L-1,R-1);
        // logic to set bits
        int res = 0;
        int r = R-L+1;
        for(int i=30;i>=0;i--) {
            int s = v[30-i]; // set
            int ns = r-s;  // not set
            if(ns > s ) res |= (1LL<<i);
        }
        printf("%d\n",res);
    }
    return 0;
}
 

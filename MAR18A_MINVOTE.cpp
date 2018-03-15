// https://www.codechef.com/MARCH18A/problems/MINVOTE/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e5+5;
ll a[N],b[N];
ll L[N],R[N];
ll LA[N],RA[N],AL[N],AR[N];
int upperboundL(int l,int r,ll v) {
   int n = r;
   while(l < r) {
        int m = (l+r)>>1;
        if(L[m] <= v) l = m+1;
        else r = m;
   }
   if(l > n) l = n;
   return l;
}
int upperboundR(int l,int r,ll v) {
   int n = r;
   while(l < r) {
        int m = (l+r)>>1;
        if(R[m] <= v) l = m+1;
        else r = m;
   }
   if(l > n) l = n;
   return l;
}
inline void init() {
    memset(LA,-1,sizeof LA);
    memset(RA,-1,sizeof RA);
    memset(L,0,sizeof L);
    memset(R,0,sizeof R);
    memset(AL,0,sizeof AL);
    memset(AR,0,sizeof AR);
}
int main() {
    //freopen("qns.txt","r",stdin);
    //freopen("ans.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        for(int i=0;i<n;i++) b[i] = a[n-1-i];
        L[0] = a[0];
        for(int i=1;i<n;i++) L[i] = L[i-1] + a[i];
        for(int i=n-1;i>=0;i--) {
            int r = upperboundL(0,n-1,L[i]+a[i]);
            if(r > i) LA[i] = r;
        }
        R[0] = b[0];
        for(int i=1;i<n;i++) R[i] = R[i-1] + b[i];
        for(int i=n-1;i>=0;i--) {
            int r = upperboundR(0,n-1,R[i]+b[i]);
            if(r > i) RA[n-1-i] = n-1-r;
        }
        /*
        for(int i=0;i<n;i++) {
            cout << LA[i] << " ";
        }
        cout << endl << endl;
        for(int i=0;i<n;i++) {
            cout << RA[i] << " ";
        }
        cout << endl;
        */
        for(ll i=0;i<n;i++) {
            if(LA[i] != -1) {
                ll a = min(i+1,LA[i]);
                ll b = max(i+1,LA[i]);
                if(a <= b) {
                    AL[a] += 1;
                    AL[b+1] -=1;
                }
            }
            if(RA[i] != -1) {
                ll a = min(RA[i],i-1);
                ll b = max(RA[i],i-1);
                if(a <= b) {
                    AR[a] += 1;
                    AR[b+1] -= 1;
                }
            }
        }
        for(int i=1;i<=n;i++) {
            AL[i] += AL[i-1];
            AR[i] += AR[i-1];
        }
 
        /*
        for(int i=0;i<=n;i++) cout << AL[i] << " ";
        cout << endl;
 
        for(int i=0;i<=n;i++) cout << AR[i] << " ";
        cout << endl;
        */
        for(int i=0;i<n;i++) {
            printf("%lld ",AR[i]+AL[i]);
        }
        printf("\n");
    }
    return 0;
}

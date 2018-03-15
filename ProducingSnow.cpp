// http://codeforces.com/problemset/problem/948/C
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 1e5+5;
int flag[maxn];
ll t[maxn],v[maxn],melt[maxn],s[maxn];
int main() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> v[i];
    for(int i=1;i<=n;i++) {
        cin >> t[i];
        s[i] = s[i-1] + t[i];
    }
    for(int i=1;i<=n;i++) {
        int l = i-1;
        int r = n;
        while(l < r) {
            int m = (l+r+1)/2;
            ll sm = s[m]-s[i-1];
            if(sm <= v[i]) l = m;
            else r = m-1;
        }
        flag[i]++;
        flag[r+1]--;
        melt[r+1] += v[i] - (s[r]-s[i-1]);
    }
    ll sm = 0;
    for(int i=1;i<=n;i++) {
       sm += flag[i];
       melt[i] += sm*t[i];
    }
    for(int i=1;i<=n;i++) cout << melt[i] << " ";
    cout << endl;
    return 0;
}

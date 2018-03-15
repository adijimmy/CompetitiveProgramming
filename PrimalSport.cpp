// http://codeforces.com/contest/948/problem/B
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int p[1000005];
vector<int> pr;
bool isprime[1000005];
int maxp[1000005];
void pre() {
  for(int i=2;i<=1000000;i++) {
    if(p[i] == 0) {
        for(int j=i;j<=1000000;j+=i) {
          p[j] = 1;
          maxp[j] = i;
        }
        p[i] = 0;
    }
  }
  for(int i=2;i<=1000000;i++) {
    if(p[i] == 0) {
        pr.push_back(i);
        isprime[i] = true;
    }
  }
}
int main() {
    pre();
    int n;
    cin >> n;
    int l = maxp[n];
    int mini = 100000000;
    //cout << n-l+1 << endl;
    for(int i=n-l+1;i<=n;i++) {
        int x1 = i;
        if(isprime[x1]) continue;
        mini = min(mini,x1-maxp[x1]+1);
    }
    cout << mini << endl;
    return 0;
}

#include "bits/stdc++.h"
using namespace std;
int dp[27];
int main() {
 string s;
 cin >> s;
 memset(dp,0,sizeof dp);
 int N = s.length();
 for(int i=0;i<N;i++) {
    dp[s[i]-'a'] = 1;
 }
 int n;
 cin >> n;
 string p;
 for(int i=0;i<n;i++) {
    cin >> p;
    bool flag = true;
    for(int j=0;j<p.length();j++) {
        if(dp[p[j]-'a'] == 0) {
            flag = false;
            break;
        }
    }
    if(!flag) cout << "No" << endl;
    else cout << "Yes" << endl;
 }
 return 0;
}
 

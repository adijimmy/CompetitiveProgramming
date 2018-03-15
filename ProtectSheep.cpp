// http://codeforces.com/contest/948/problem/A
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
char a[505][505];
int r,c;
bool ok(int a,int b) {
  return a>=0 && a<r & b>=0 && b<c;
}
int main() {
    cin >> r >> c;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            cin >> a[i][j];
        }
    }
    bool flag = true;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(a[i][j] == '.') a[i][j] = 'D';
            if(a[i][j] == 'W') {
                if(ok(i+1,j) && a[i+1][j] == 'S') flag = false;
                if(ok(i-1,j) && a[i-1][j] == 'S') flag = false;
                if(ok(i,j-1) && a[i][j-1] == 'S') flag = false;
                if(ok(i,j+1) && a[i][j+1] == 'S') flag = false;
            }
        }
    }
    if(flag) {
            cout << "Yes" << endl;
            for(int i=0;i<r;i++) {
               for(int j=0;j<c;j++) {
                  cout << a[i][j];
               }
               cout << endl;
             }
    }
    else cout << "No" << endl;

    return 0;
}

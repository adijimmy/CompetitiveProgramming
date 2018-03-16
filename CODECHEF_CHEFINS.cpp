// https://www.codechef.com/problems/CHEFINS/
/*
  Dijkstra algorithm used to avoid dynamic programming for large data inputs
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2e5+1;
set<pair<int,int> > PQ;
int dist[maxn];
int main() {
    int N,K,Q,F;
    cin >> N >> K >> Q;
    vector<int> a(K);
    for(int i=0;i<K;i++) cin >> a[i];
    sort(a.begin(),a.end());
    for(int i=0;i<a[0];i++) dist[i] = 1e9;
    dist[0] = 0;
    PQ.insert({dist[0],0});
    while(!PQ.empty()) {
        int d = PQ.begin()->first;
        int v = PQ.begin()->second;
        PQ.erase(PQ.begin());
        for(int i=1;i<K;i++) {
            int nd = d+a[i];
            int p = (v+a[i])%a[0];
            if(nd < dist[p]) {
                dist[p] = nd;
                PQ.insert({nd,p});
            }
        }
    }
    while(Q--) {
        cin >> F;
        if(dist[F%a[0]] <= F) puts("Yes");
        else puts("No");
    }
    return 0;
}

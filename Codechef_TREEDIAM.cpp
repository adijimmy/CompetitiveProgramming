#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 100005
#define LOGN 20
const ll mod = 1e9+7;
int N;
ll W[MAXN],V[MAXN];
vector<ll> res;
int parent[MAXN],sz[MAXN];
int possibility[MAXN][2];
int dist[MAXN];
vector<pair<int,int> > edges;
int DP[MAXN][LOGN+2];
ll maxW[MAXN];
ll P = 1;
vector<int> G[MAXN];
int edge[MAXN];

ll power(ll a,ll b) {
 ll ans = 1;
 while(b) {
    if(b&1) ans = (ans*a) % mod;
    a = (a*a) % mod;
    b >>= 1;
 }
 return ans;
}

void dfs(int u,int pa) {
  dist[u] = dist[pa] + 1;
  DP[u][0] = pa;
  maxW[u] = maxW[pa] + W[u];
  for(int i=0;i<G[u].size();i++) {
    int v = G[u][i];
    if(v != pa) dfs(v,u);
  }
}

int findParent(int u) {
  if(parent[u] == u) return u;
  parent[u] = findParent(parent[u]);
  return parent[u];
}

int lca(int u,int v) {
  if(dist[u] < dist[v]) swap(u,v);
  int dif = dist[u] - dist[v];
  for(int i=0;i<LOGN;i++) {
    if(dif&(1<<i)) {
       u = DP[u][i];
    }
  }
  if(u != v) {
    for(int i=LOGN;i>=0;i--) {
        if(DP[u][i] != DP[v][i]) {
            u = DP[u][i];
            v = DP[v][i];
        }
    }
    u = DP[u][0];
  }
  return u;
}

ll calMaxDistanceFromOppositeTrees(int u,int v) {
  int ancestor = lca(u,v);
  ll res = maxW[u]+maxW[v]-maxW[ancestor]-maxW[DP[ancestor][0]];
  //cout << ancestor << " " << u << " " << v << " " << res << endl;
  return res;
}
void unionFind(int u,int v) {
  u = findParent(u);
  v = findParent(v);
  if(sz[u] < sz[v]) swap(u,v);
  parent[v] = u;
  sz[u] += sz[v];
  P = (P*power(V[u],mod-2)) % mod;
  P = (P*power(V[v],mod-2)) % mod;
  ll maxiDist = 0;
  int p1,p2;
  //  retrieving from two different trees
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
        ll d = calMaxDistanceFromOppositeTrees(possibility[u][i],possibility[v][j]);
        if(d > maxiDist) {
            maxiDist = d;
            p1 = possibility[u][i];
            p2 = possibility[v][j];
        }
    }
  }
  //  retrieving from 1st tree
  if(V[u] > maxiDist) {
     maxiDist = V[u];
     p1 = possibility[u][0];
     p2 = possibility[u][1];
  }
  //  retrieving from 2nd tree
  if(V[v] > maxiDist) {
     maxiDist = V[v];
     p1 = possibility[v][0];
     p2 = possibility[v][1];
  }
  //cout << maxiDist << " " << p1 << " " << p2 << endl;
  V[u] = maxiDist;
  possibility[u][0] = p1;
  possibility[u][1] = p2;
  P = (P*maxiDist) % mod;
}

int main() {
 int u,v;
 cin >> N;
 for(int i=1;i<=N;i++) {
    cin >> W[i];
    V[i] = W[i];
    possibility[i][0] = possibility[i][1] = i;
    P = (P*W[i]) % mod;
    parent[i] = i;
    sz[i] = 1;
 }
 for(int i=0;i<N-1;i++) {
    cin >> u >> v;
    G[u].push_back(v); G[v].push_back(u);
    edges.push_back(make_pair(u,v));
 }
 dfs(1,0);
 for(int i=0;i<LOGN;i++) {
    for(int j=1;j<=N;j++) {
        if(DP[j][i] != 0) {
            DP[j][i+1] = DP[DP[j][i]][i];
        }
    }
 }
 for(int i=0;i<N-1;i++) {
    cin >> edge[i];
    edge[i]--;
 }
 for(int i=N-2;i>=0;i--) {
    res.push_back(P);
    unionFind(edges[edge[i]].first,edges[edge[i]].second);
 }
 res.push_back(P);
 for(int i=res.size()-1;i>=0;i--) cout << res[i] << endl;
 return 0;
}

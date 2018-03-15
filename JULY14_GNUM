// https://www.codechef.com/JULY14/problems/GNUM/
// Ford Fulkerson - Maximum flow in a network
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <map>
#include <queue>
#define gc getchar
using namespace std;
int a[410],b[410];
int G[3000][3000];
int parent[260005];
int visited[260005];
vector<int> vec[260005];
vector<int> arr[260005];
map<int,int> S1,S2,mp;
int k,cnt,src,dest;
map<int,int>::iterator it;
inline int read_int(){
	char r;
	bool start=false,neg=false;
    int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}
inline int gcd(int a,int b){
return b==0?a:gcd(b,a%b);
}
inline int bfs(){
for(int i=0;i<=dest;i++)
    visited[i]=0;
parent[0] = -1;
visited[0] = 1;
queue<int> q;
q.push(src);
while(!q.empty()){
 int u = q.front();
 q.pop();
 for(int i=arr[u].size()-1;i>=0;i--){
    int v = arr[u][i];
    if(G[u][v] > 0 && visited[v] == 0){
       parent[v] = u;
       visited[v] = 1;
       q.push(v);
    }
 }
}
if(visited [dest]==0)
    return 0;
else{
   int path_flow = INT_MAX;
   for(int v=dest; v!=src;v=parent[v]){
     int u = parent[v];
     path_flow = min(path_flow,G[u][v]);
   }
   for(int v=dest;v!=src;v=parent[v]){
     int u = parent[v];
     G[u][v] -= path_flow;
     G[v][u] += path_flow;
   }
   return path_flow;
}
}
// finding all prime factors of numbersinline
 
inline vector<int> solve(int n){
vector<int> v;
for(int i=2;i*i<=n;i++){
   if(n%i == 0){
     if(mp.find(i) == mp.end()){
        mp[i] = cnt;
        cnt++;
     }
     while(n%i == 0)
        n/=i;
     v.push_back(i);
   }
}
if(n!=1){
   if(mp.find(n) == mp.end()){
      mp[n] = cnt;
      cnt++;
   }
   v.push_back(n);
}
return v;
}
int main(){
int t,n;
t = read_int();
while(t--){
n = read_int();
S1.clear();
S2.clear();
mp.clear();
cnt = 0;
k = 1;
for(int i=0;i<n;i++)
    a[i] = read_int();
for(int i=0;i<n;i++)
    b[i] = read_int();
//checking for each pair for non-coprimeness
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        //int g = calc(a[i]);
        if(a[i] > b[j]){
            int l = gcd(a[i],b[j]);
            if(l != 1){
               if(S2.find(l) == S2.end())
                    S2[l] = 0;
               S2[l]++;
            }
        }
        else if(a[i] < b[j]){
            int l = gcd(a[i],b[j]);
            if(l != 1){
               if(S1.find(l) == S1.end())
                    S1[l] = 0;
               S1[l]++;
            }
        }
    }
}
// mapping
for(it=S2.begin();it!=S2.end();it++){
  vec[k] = solve(it->first);
  k++;
}
for(it=S1.begin();it!=S1.end();it++){
  vec[k] = solve(it->first);
  k++;
}
src = 0;
dest = S1.size()+S2.size()+cnt+1;
for(int i=0;i<=dest;i++){
    arr[i].clear();
    for(int j=0;j<=dest;j++){
        G[i][j] = 0;
    }
}
int i = 1;
// constructing the graph from S1 to S2
for(it=S2.begin();it!=S2.end();it++){
    G[src][i] = it->second;
    arr[src].push_back(i);
    for(int j=vec[i].size()-1;j>=0;j--){
        k = mp[vec[i][j]]+dest-cnt;
        G[i][k] = INT_MAX;
        arr[i].push_back(k);
        arr[k].push_back(i);
    }
    i++;
}
// constructig the graph from S2 to S1 right to left
for(it=S1.begin();it!=S1.end();it++){
    G[i][dest] = it->second;
    arr[i].push_back(dest);
    for(int j=vec[i].size()-1;j>=0;j--){
        k = mp[vec[i][j]]+dest-cnt;
        G[k][i] = INT_MAX;
        arr[i].push_back(k);
        arr[k].push_back(i);
    }
    i++;
}
int max_flow = 0;
int val;
while(1){
   val = bfs();
   if(val==0)
     break;
   else
     max_flow+=val;
}
printf("%d\n",max_flow);
// test cases
}
return 0;
} 

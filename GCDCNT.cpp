#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 50001;
const int M = 100001;
bool isprime[M];
int prime[9594];
int primecnt;
struct Update {
    int index,newvalue,previous_value;
};
struct Query {
    int index,left,right,updatestillnow,g;
};
int a[N],temp[N],ans[N];
int divcnt[M];
vector<Update> update;
vector<Query> query;
int block;
vector<int> Div[M];
bool comp(const Query &f,const Query &s) {
    int lindex = f.left/block;
    int loindex = s.left/block;
    if(lindex != loindex) return lindex < loindex;
    else {
        int rindex = f.right/block;
        int roindex = s.right/block;
        if(rindex != roindex) return rindex < roindex;
        return f.updatestillnow < s.updatestillnow;
    }
}
inline void add(int n,int v) {
 
}
void pre() {
  memset(isprime,true,sizeof isprime);
  //isprime[0] = isprime[1] = false;
  for(int i=2;i<=100000;i++) {
     if(isprime[i]) {
        for(int j=i;j<=100000;j+=i) {
            isprime[j] = false;
        }
        isprime[i] = true;
     }
  }
  for(int i=2;i<=100000;i++) {
    if(isprime[i] == true) {
        prime[primecnt++] = i;
    }
  }
  for(int i=1;i<=100000;i++) {
    int sq = sqrt(i);
    for(int j=1;j<=sq;j++) {
        if(i%j == 0) {
            int p = j;
            int q = i/j;
            if(p == q) {
                Div[i].push_back(p);
            }
            else {
                Div[i].push_back(p);
                Div[i].push_back(q);
            }
        }
    }
 
  }
}
int main() {
    //freopen("qns.txt","r",stdin);
    //freopen("ans.txt","w",stdout);
    pre();
    int n,q,t,index,newvalue,L,R,G;
    scanf("%d",&n);
    block = (int)pow(n,0.73);
    for(int i=0;i<n;i++) {
        scanf("%d",&a[i]);
        temp[i] = a[i];
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++) {
        scanf("%d",&t);
        if(t == 1) {
            scanf("%d %d",&index,&newvalue);
            index--;
            update.push_back(Update{index,newvalue,temp[index]});
            temp[index] = newvalue;
        }
        else {
            scanf("%d %d %d",&L,&R,&G);
            L--; R--;
            query.push_back(Query{query.size(),L,R,update.size(),G});
        }
    }
    sort(query.begin(),query.end(),comp);
    int s = 0;
    int e = -1;
    int updateDoneTillNow = 0;
 
    int sz = query.size();
    for(int i=0;i<sz;i++) {
        Query qq = query[i];
        int left = qq.left;
        int right = qq.right;
        int qupdatestillnow = qq.updatestillnow;
        int index = qq.index;
        int g = qq.g;
 
        while(updateDoneTillNow < qupdatestillnow) {
            Update U = update[updateDoneTillNow];
            if(U.index >= s && U.index <= e) {
                for(int j=0;j<Div[a[U.index]].size();j++) {
                   divcnt[Div[a[U.index]][j]]--;
                }
            }
            a[U.index] = U.newvalue;
            if(U.index >= s && U.index <= e) {
                for(int j=0;j<Div[a[U.index]].size();j++) {
                   divcnt[Div[a[U.index]][j]]++;
                }
            }
            updateDoneTillNow++;
        }
        while(updateDoneTillNow > qupdatestillnow) {
            updateDoneTillNow--;
            Update U = update[updateDoneTillNow];
            if(U.index >= s && U.index <= e) {
                for(int j=0;j<Div[a[U.index]].size();j++) {
                   divcnt[Div[a[U.index]][j]]--;
                }
            }
            a[U.index] = U.previous_value;
            if(U.index >= s && U.index <= e) {
                for(int j=0;j<Div[a[U.index]].size();j++) {
                   divcnt[Div[a[U.index]][j]]++;
                }
            }
        }
        while(e < right) {
             e++;
             for(int j=0;j<Div[a[e]].size();j++) {
                   divcnt[Div[a[e]][j]]++;
             }
        }
        while(e > right) {
            for(int j=0;j<Div[a[e]].size();j++) {
                   divcnt[Div[a[e]][j]]--;
            }
            e--;
        }
        while(s < left) {
             for(int j=0;j<Div[a[s]].size();j++) {
                   divcnt[Div[a[s]][j]]--;
             }
             s++;
        }
        while(s > left) {
            s--;
            for(int j=0;j<Div[a[s]].size();j++) {
                   divcnt[Div[a[s]][j]]++;
            }
        }
        vector<int> x;
        for(int j=0;j<primecnt;j++) {
            int rp = prime[j];
            if(g < rp || g < 2) break;
            if(g%rp == 0) {
                x.push_back(rp);
                while(g%rp == 0) g /= rp;
            }
        }
        int cntRes = 0;
        int xsz = x.size();
        int upbnd = 1<<xsz;
        for(int j=1;j<upbnd;j++) {
            int cnt= 0;
            int prod = 1;
            for(int k=0;k<xsz;k++) {
                if(j & (1<<k)) {
                    cnt++;
                    prod *= x[k];
                }
            }
            if(cnt&1) cntRes += divcnt[prod];
            else cntRes -= divcnt[prod];
        }
        ans[index] = right-left+1-cntRes;
    }
    for(int i=0;i<sz;i++) {
        printf("%d\n",ans[i]);
    }
    return 0;
}

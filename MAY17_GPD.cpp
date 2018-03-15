// https://www.codechef.com/MAY17/problems/GPD/
#include <bits/stdc++.h>
using namespace std;
#define MAXN 300025
int N,Q,R;
int value[MAXN];
map<int,int> mp;
struct node {
    node *left,*right;
};
node *root[MAXN];
vector<int> G[MAXN];
int p = 0;
 
node* makeNode() {
  node *p = new node;
  p->left = NULL;
  p->right = NULL;
  return p;
}
 
void createTrie(int cur,int par,int val) {
  // to make the base trie node
  if(par == -1) {
    root[cur] = makeNode();
    node *headCur = root[cur];
    //cout << "Node " << cur << " value is " << val << endl;
    for(int i=31;i>=0;i--) {
        if(val & (1<<i)) {
           headCur->right = makeNode();
           headCur = headCur->right;
        }
        else {
           headCur->left = makeNode();
           headCur = headCur->left;
        }
    }
  }
  // to make the persistent trie nodes
  else {
    root[cur] = makeNode();
    node *childHead = root[cur];
    node *parHead = root[par];
    for(int i=31;i>=0;i--) {
        if(val & (1<<i)) {
           childHead->right = makeNode();
           childHead = childHead->right;
        }
        else {
           childHead->left = makeNode();
           childHead = childHead->left;
        }
    }
    node *curTail = childHead;
    childHead = root[cur];
    while(1) {
        if(childHead->left == NULL && childHead->right == NULL) break;
        if(childHead->left != NULL) {
            childHead->right = parHead->right;
            if(parHead->left == NULL) break;
            else {
               childHead = childHead->left;
               parHead = parHead->left;
            }
        }
        else if(childHead->right != NULL) {
            childHead->left = parHead->left;
            if(parHead->right == NULL) break;
            else {
                childHead = childHead->right;
                parHead = parHead->right;
            }
        }
    }
  }
}
int queryMin(node *head,int val) {
   int res = 0;
   for(int i=31;i>=0;i--) {
    if(val & (1<<i)) {
        if(head->right != NULL) head = head->right;
        else if(head->left != NULL) {
            res += (1<<i);
            head = head->left;
        }
    }
    else {
        if(head->left != NULL) head = head->left;
        else if(head->right != NULL) {
            res += (1<<i);
            head = head->right;
        }
    }
   }
   return res;
}
 
int queryMax(node *head,int val) {
   int res = 0;
   for(int i=31;i>=0;i--) {
     if(val & (1<<i)) {
        if(head->left != NULL) {
            res += (1<<i);
            head = head->left;
        }
        else if(head->right != NULL) head = head->right;
     }
     else {
        if(head->right != NULL) {
            res += (1<<i);
            head = head->right;
        }
        else if(head->left != NULL) head = head->left;
     }
   }
   return res;
}
void printHeadTress(node *head) {
   if(head == NULL) return;
   if(head->left != NULL) {
    cout << 0 << " ";
    printHeadTress(head->left);
   }
   if(head->right != NULL) {
    cout << 1 << " " ;
    printHeadTress(head->right);
   }
}
void dfs(int u,int par) {
    createTrie(u,par,value[u]);
    //cout << "For node " << u << " value is : " << value[u] << endl;
    //printHeadTress(root[u]);
    //cout << endl;
    for(int i=0;i<G[u].size();i++) {
        int v = G[u][i];
        if(v == par) continue;
        dfs(v,u);
    }
}
int main() {
 
    //freopen("qns.txt","r",stdin);
    //freopen("ans.txt","w",stdout);
 
    int u,v,t,K;
	scanf("%d %d",&N,&Q);
	scanf("%d %d",&R,&K);
 
    p = 0;
	mp[R] = p;
	value[p] = K;
	p++;
 
	for(int i=0;i<N-1;i++) {
	    scanf("%d %d %d",&u,&v,&K);
	    mp[u] = p;
	    value[p] = K;
	    G[mp[v]].push_back(p);
	    p++;
	}
	dfs(0,-1);
	/*for(int i=0;i<N;i++) {
       cout << "For node " << i << " value is : " << value[i] << endl;
       printHeadTress(root[i]);
       cout << endl;
	}*/
	int last_answer = 0;
	while(Q--) {
      scanf("%d",&t);
      t ^= last_answer;
      if(t == 0) {
        scanf("%d %d %d",&v,&u,&K);
        u ^= last_answer;
        v ^= last_answer;
        K ^= last_answer;
        mp[u] = p;
        value[p] = K;
        createTrie(p,mp[v],value[p]);
        p++;
      }
      else {
        scanf("%d %d",&v,&K);
        v ^= last_answer;
        K ^= last_answer;
        //cout << "Current Node is" << mp[v] << endl;
        int cur = mp[v];
        //printHeadTress(root[cur]);
        //cout << endl;
        int min_ans = queryMin(root[cur],K);
        int max_ans = queryMax(root[cur],K);
        last_answer = min_ans ^ max_ans;
        printf("%d %d\n",min_ans,max_ans);
      }
	}
	return 0;
}

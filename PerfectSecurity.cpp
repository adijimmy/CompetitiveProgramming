// http://codeforces.com/problemset/problem/948/D
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 3e5+5;
int a[maxn],p[maxn];
class Node{
public:
    int lCount,rCount;
    Node *lChild,*rChild;
    Node() {
        lCount = rCount = 0;
        lChild = rChild = NULL;
    }
};
void addBit(Node *root,int n){
    for(int i=29;i>=0;i--){
        int x = (n>>i) & 1;
        if(x) {
            root->rCount++;
            if(root->rChild == NULL)
                root->rChild = new Node();
            root = root->rChild;
        }
        else {
            root->lCount++;
            if(root->lChild == NULL)
                root->lChild = new Node();
            root = root->lChild;
        }
    }
}
int query(Node *root,int n){
    if(root == NULL) return 0;
    int res = 0;
    for(int i=29;i>=0;i--){
        bool ch = (n>>i) & 1;
        if(ch) {
            if(root->rChild && root->rCount > 0) {
                root->rCount--;
                res += (1<<i);
                root = root->rChild;
            }
            else if(root->lChild && root->lCount > 0) {
                root->lCount--;
                root = root->lChild;
            }
            else return res;
        }
        else {
            if(root->lChild && root->lCount > 0) {
                root->lCount--;
                root = root->lChild;
            }
            else if(root->rChild && root->rCount > 0) {
                root->rCount--;
                res += (1<<i);
                root = root->rChild;
            }
            else return res;
        }
    }
    return res;
}
int main() {
    int n;
    cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    Node *root = new Node();
    for(int i=0;i<n;i++) {
        cin >> p[i];
        addBit(root,p[i]);
    }
    for(int i=0;i<n;i++) {
        int q = query(root,a[i]);
        int res = q ^ a[i];
        cout << res << " ";
    }
    cout << endl;
    return 0;
}

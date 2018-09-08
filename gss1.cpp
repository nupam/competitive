#include <iostream>
#include <algorithm>

using namespace std;

template <class T> inline T max(const T& a,const T& b,const T& c){
    return max(max(a,b), c);
}

class node{
public:
    long long p, s, sum, b;
    node():p(0), s(0), sum(0), b(0) {}
};

long long *a;
node *tree;

void buildTree(int n, int i, int j){
    if(i==j){
        tree[n].s = tree[n].p = tree[n].sum = tree[n].b = a[i];
    }
    else{
        int mid = (i+j)/2;
        int l = n*2 + 1;
        int r = l+1;
        buildTree(l, i, mid);
        buildTree(r, mid+1, j);
        tree[n].sum = tree[l].sum + tree[r].sum;
        tree[n].b = max(tree[l].b, tree[r].b, tree[l].s + tree[r].p);
        tree[n].p = max(tree[l].p, tree[l].sum+tree[r].p);
        tree[n].s = max(tree[r].s, tree[r].sum+tree[l].s);
    }
}

node query(int n, int i, int j, int b, int e){
    if(i==b && j==e){
        return tree[n];
    }
    int mid = (i+j)/2;
    if(mid < b) return query(2*n+2, mid+1, j, b, e);
    else if(e<=mid) return query(2*n+1, i, mid, b, e);
    else{
        node l = query(2*n+1, i, mid, b, mid);
        node r = query(2*n+2, mid+1, j, mid+1, e);
        node ans;
        ans.sum = l.sum + r.sum;
        ans.b = max(l.b, r.b, l.s+r.p);
        ans.p = max(l.p, l.sum + r.p);
        ans.s = max(r.s, l.s+r.sum);
        return ans;
    }
}


int main(){
    int n; cin >> n;
    a = new long long[n];
    for(int i=0; i<n; i++) cin >> a[i];

    tree = new node[4*n + 1];
    buildTree(0,0,n-1);
    int m, u, v;
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> u >> v;
        if(u==v) cout << a[u-1] << '\n';
        else cout << query(0, 0, n-1, u-1, v-1).b << '\n';
    }
    
}
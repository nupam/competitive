#include <iostream>
#include <algorithm>
using namespace std;

template <class T> inline T max(const T& a,const T& b,const T& c){
    return max(max(a,b), c);
}


struct node{
    long long s, p, sum, b;
};

node *tree;
int *a;

node merge(node& a, node& b){
    node ans;
    ans.sum = a.sum + b.sum;
    ans.b = max(a.b, b.b, a.s+b.p);
    ans.s = max(b.s, b.sum+a.s);
    ans.p = max(a.p, a.sum+b.p);
    return ans;
}

void buildTree(int n, int i, int j){
    if(i==j){
        tree[n].s = tree[n].sum = tree[n].p = tree[n].b = a[i];
    }
    else{
        int mid = (i+j)/2;
        buildTree(2*n+1, i, mid);
        buildTree (2*n+2, mid+1, j);
        tree[n] = merge(tree[2*n+1], tree[2*n+2]);
    }
}

node query(int n, int i, int j, int b, int e){
    if(i==b && j==e) return tree[n];
    int mid = (i+j)/2;
    if(mid < b) return query(2*n+2, mid+1, j, b, e);
    else if(e<=mid) return query(2*n+1, i, mid, b, e);
    else{
        node l = query(2*n+1, i, mid, b, mid);
        node r = query(2*n+2, mid+1, j, mid+1, e);
        return merge(l,r);
    }
}

void update(int n, int i, int j, int ind, int val){
    if(i==j){
        a[i]=tree[n].s = tree[n].sum = tree[n].p = tree[n].b = val;
    }
    else{
        int mid = (i+j)/2;
        if(ind <= mid) update(2*n+1, i, mid, ind, val);
        else update(2*n+2, mid+1, j, ind, val);
        tree[n] = merge(tree[2*n+1], tree[2*n+2]);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    a = new int[n];
    for(int i=0; i<n; i++) cin >> a[i];
    tree = new node[4*n + 1];
    buildTree(0, 0, n-1);

    int m; cin >> m;
    for(int i=0; i<m; i++){
        int w, p, q; cin >> w >> p >> q;
        if(w) cout << query(0, 0, n-1, p-1, q-1).b << '\n';
        else update(0, 0, n-1, p-1, q);
    }
    delete[] a;
    delete[] tree;

}

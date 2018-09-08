#include <iostream>
using namespace std;

long long *tree, *lazy;

void update(int n, int i, int j, int b, int e, const int& val){
    if(b>j || e<i) return;
    if(b==j && e==i){
        lazy[n]+=val;
        return;
    }
    int mid = (i+j)/2;
    if(e<=mid) update(2*n+1, i, mid, b, e, val);
    else if(mid>b) update(2*n+2, mid+1, j, b, e, val);
    else{
        update(2*n+1, i, mid, b, mid);
        update(2*n+2, mid+1, j, mid+1, e);
    }
}

long long query(int n, int i, int j, int b, int e){
    //out of the range
    if(b>j || e<i) return 0;

    if(!lazy[n]){
        tree[n] += val*(j-i+1);
        lazy[2*n+1] += val;
        lazy[2*n+2] += val;
        lazy[n] = 0;
    }

    if(i<=b && j>=e) return tree[n];
    else{
        int mid = (i+j)/2;
        long long l = query(2*n+1, i, mid, b, e);
        long long r = query(2*n+1, mid+1, j, b, e);
        return l+r;
    }

}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    tree = new long long[4*n+1]();
    lazy = new long long[4*n+1]();
    int m; cim >> m;
    for(int i=0; i<m; i++){
        int t, p, q; cin >> t >> p >> q;
        if(t) cout << query(0, 0, n-1, p-1, q-1) << '\n';
        else update(0, n-1, p-1, q-1, val);
    }
    delete[] tree;
    delete[] lazy;
}
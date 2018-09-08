#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
typedef  long long ll;
class node;
node* tree;
int* a;

class node{
    int* a;
    public:
    int n;
    node(int n=0):n(n){a = new int[n];}
    node(const node& b){
        n=b.n;
        a = new int[n];
        for(int i=0; i<b.n; i++){
            a[i] = b[i];
        }
    }
    ~node(){delete[] a;}
    int& operator[](const int i){
        return a[i];
    }
    const int& operator[](const int i)const{
        return a[i];
    }
    void resize(int n){
        this->n = n;
        delete[] a;
        a = new int[n];
    }
    void operator=(const node& b){
        resize(b.n);
        for(int i=0; i<b.n; i++){
            a[i] = b[i];
        }
    }
};

node merge(const node& a, const node& b){
    int l1= a.n, l2 = b.n, l = a.n+b.n;
    node n(l);
    int i, i1, i2;
    i=i1=i2=0;
    while(i1<l1 && i2<l2){
        if(a[i1]<b[i2]){
            n[i] = a[i1];
            i1++;
        }
        else{
            n[i] = b[i2];
            i2++;
        }
        i++;
    }
    while(i1<l1) n[i++] = a[i1++];
    while(i2<l2) n[i++] = b[i2++];
    return n;
}

void buildTree(int n, int i, int j){
    if(i==j){
        tree[n].resize(1);
        tree[n][0] = a[i];
        return;
    }
    int m =  (i+j)/2;
    buildTree(2*n+1, i, m);
    buildTree(2*n+2, m+1, j);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
}

/*
node query(int n, int i, int j, int b, int e){
    if(i==b && j==e) return tree[n];
    int m = (i+j)/2;
    if(e<=m) return query(2*n+1, i, m, b, e);
    else if(m<b) return query(2*n+2, m+1, j, b, e);
    node l = query(2*n+1, i, m, b, m);
    node r = query(2*n+2, m+1, j, m+1, e);
    return merge(l, r);
}
*/

int query(int n, int i, int j, int b, int e, int k){
    if(i==b && j==e) return tree[n][k];
    int m = (i+j)/2;
    if(k<=m) return query(2*n+1, i, m, b, e, k);
    return query(2*n+2, m+1, j, m+1, e, k-m);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; scanf("%d %d", &n, &m);
    a = new int[n];
    tree = new node[4*n+1];
    for(int i=0; i<n; i++) scanf("%d", &a[i]);
    buildTree(0, 0, n-1);
    int p, q, r;
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &p, &q, &r);
        printf("%d\n",query(0, 0, n-1, p-1, q-1, r-1));
    }
    
    //delete[] a;
    //delete[] tree;
}
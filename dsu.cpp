class dsu{
    int *par, *rank, n;
public:
    dsu(int n=1024):n(n){
        par = new int[n+1];
        rank = new int[n+1]();
        for(int i=0; i<=n; i++) par[i] = i;
    }

    ~dsu(){delete[] par; delete[] rank;}

    int size(){return n;}

    int parent(const int& n){
        if(par[n]==n) return n;
        else{
            par[n] = parent(par[n]);
            return par[n];
        }
    }

    void set_union(int a, int b){
        int pa =parent(a), pb = parent(b);
        if(pa==pb) return;
        if(rank[pa] > rank[pb]){
            par[pb] = pa;
        }
        else{
            par[pa] = pb;
            if(rank[pb]==rank[pa]) rank[pb]++;
        }
        return;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

std::vector<std::vector<int> > FW(std::vector<std::vector<int> >& a){
    int n = a.size();
    std::vector<std::vector<int> > sol = a, p(n+1, std::vector<int> (n+1));
    
    for (int i = 1; i < n; ++i){
        for (int j = 1; j < n; ++j){
            if(a[i][j] == INF || !a[i][j]) p[i][j] = 0;
            else p[i][j] = i;
        }
    }

    for (int k = 1; k < n; ++k){
        for (int i = 1; i < n; ++i){
            for (int j = 1; j < n; ++j){
                if(sol[i][j] > sol[i][k] + sol[k][j]){
                    sol[i][j] = sol[i][k] + sol[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }

    return sol;

}



int main(){
    cout << "Number of Vertices:\t"; int n; cin >> n;
    cout << "Number of Edges:\t"; int m; cin >> m;

    std::vector<std::vector<int> > a(n+1, std::vector<int> (n+1, INF));
    for(int i=0; i<m; i++){
        int u, v, w; cin >> u >> v >> w;
        a[u][v] = w;
    }
    for(int i=0; i<=n; i++){
        a[i][i] = 0;
    }


    std::vector<std::vector<int> > sol = FW(a);

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            if(sol[i][j] == INF ) cout << "INF\t"; 
            else cout << sol[i][j] << '\t';
        }
        cout << '\n';
    }


    
    return 0;

}


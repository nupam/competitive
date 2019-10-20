#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int INF = 1000000000;

class point{
public:
    int f, s;
    point(int f=0, int s=0):f(f), s(s) { }
};

std::pair<std::vector<int> , std::vector<int> > BF(std::vector<std::vector<point> >& a, int s){
    int n = a.size();
    std::vector<int> d(n, INF), p(n, INF);
    d[s] = 0; p[s] = s;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0, l = a[j].size(); k<l; k++){
                int c = a[j][k].f, w = a[j][k].s;
                if(d[c] > d[j] + w){
                    d[c] = d[j] + w;
                    p[c] = j;
                }
            }
        }
    }

    for(int j=0; j<n; j++){
        for(int k=0, l = a[j].size(); k<l; k++){
            int c = a[j][k].f, w = a[j][k].s;
            if(d[c] > d[j] + w){
                d[c] = -INF;
                p[c] = -INF;
            }
        }
    }

    return make_pair(d, p);
}

void prntpth(const std::vector<int>& a, int d){
    std::vector<int> p;
    p.push_back(d);
    while(a[d]!=d){
        d = a[d];
        p.push_back(d);
    }

    for(int i=p.size()-1; i>=0; i--) cout << p[i] << "->";
}


int main(){
    cout << "Number of Vertices:\t"; int n; cin >> n;
    cout << "Number of Edges:\t"; int m; cin >> m;

    std::vector<std::vector<point> > a(n+1);
    for(int i=0; i<m; i++){
        int u, v, w; cin >> u >> v >> w;
        a[u].push_back(point(v, w));
    }

    cout << "Enter source node: "; int s; cin >> s;

    pair<std::vector<int> , std::vector<int> > ans = BF(a, s);
    std::vector<int> d = ans.first, p = ans.second;

    for(int i=0; i<=n; i++){
        if(d[i]==-INF || d[i]==INF){
            cout <<"From " << s << " to " << i << " no path is poissible\n\n";
        }
        else{
            cout << "Weight of Path from " << s << " to " << i << " is " << d[i] << '\n';
            cout << "\tPath: ";
            prntpth(p, i);
        }
    }
    return 0;

}


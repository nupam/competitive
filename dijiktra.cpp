#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <utility>

using namespace std;
const int INF = 1000000000;

typedef pair<int, int> pii;

vector<pii> dijiktra(vector<vector<pii> > a, int s){
    std::vector<pii> sol;
    std::vector<bool> f(a.size(), false);
    std::priority_queue <pii, std::vector<pii>, std::greater<pii> > q;
    for(int i=1, l=a.size(); i<l; i++) q.push(make_pair(INF, i));
    q.push(make_pair(0,s));

    while(!q.empty()){
        pii c = q.top();
        q.pop();
        int n = c.second, d = c.first;
        if(f[n]) continue;
        f[n] = true;
        sol.push_back(make_pair(n, d));
        for(int i=0, l=a[n].size(); i<l; i++){
            if(!f[a[n][i].first])
                q.push(make_pair(d+a[n][i].second, a[n][i].first));
        }
    }

    return sol;
}

int main(){
    int n, m, p, q, r; cin >> n >> m;
    std::vector<std::vector<pii> > v(n+1);
    for(int i=0; i<m; i++){
        cout << "Enter edge " << i+1 << " : ";
        cin >> p >> q >> r;
        v[p].push_back(make_pair(q, r));
    }
    int s; cin >> s;
    std::vector<pii> sol = dijiktra(v, s);
    for(int i=0, l=sol.size(); i<l; i++){
        cout <<  "To " << sol[i].first  << " is " << sol[i].second << '\n';
    }
}
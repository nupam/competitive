#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    register int i;
    int t; cin >> t;
    for(int j=0; j<t; j++){
        int n; cin >> n;
        LL *a = new LL[n], *sol = new LL[n];
        for(i=0; i<n; i++) cin >> a[i];
        sol[n-1] = a[n-1];
        if(n!=1){
            sol[n-2] = max(a[n-1], a[n-2]);
            for(i=n-3; i>=0; i--){
                sol[i] = max(a[i] + sol[i+2], sol[i+1]);
            }
        }
        cout <<"Case " << j+1 << ": "<< sol[0] << '\n';
        delete[] a; delete[] sol;
    }
}

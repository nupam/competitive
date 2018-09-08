#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

#define LL long long
#define MOD 1000000007

using namespace std;

LL _x, _y, _d;

LL power(LL x, LL n){
    LL res = 1;
    x = x%MOD;
    while(n){
        if(n&1)
            res = (res*x)%MOD;
        x = (x*x)%MOD;
        n>>=1;
    }
    return res;
}

void modInverseHelper(LL a, LL b){
    if(b==0){
        _x = 1;
        _y = 0;
        _d =a;
    }
    else{
        modInverseHelper(b, a%b);
        LL temp = _x;
        _x = _y;
        _y = temp - (a/b)*_y;
    }
}

LL modInverse(LL a){
    modInverseHelper(a, MOD);
    return (_x+MOD)%MOD;
}

LL G(LL p, LL a){   //calculates sum of gp of first term 1 and last term p^a mod MOD
    LL n = power(p, a+1);
    n = (n + MOD - 1)%MOD;
    LL d = modInverse(p-1);
    return (n*d)%MOD;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    vector<bool>isPrime(32000, true);
    for(LL i = 2; i*i<32000; i++){
        if(isPrime[i]){
            for(LL j=i*i; j<32000; j+=i)
                isPrime[j]= false;
        }
    }
    vector<LL> primes;
    primes.push_back(2);
    for(LL i=3; i<32000; i+=2){
        if(isPrime[i]) primes.push_back(i);
    }
    
    int t;
    cin >>t;
    while(t--){
        unordered_map<LL, LL> f;
        LL n;
        cin >> n;
        while(n--){
            LL a;
            cin >> a;
            LL i=0;
            while(a>1 && primes[i]*primes[i] <= a){
                while(a%primes[i]==0){
                    f[primes[i]]++; a/=primes[i];
                }
                i++;
            }
            if(a!=1)
                f[a]++;
        }
        LL ans = 1; 
        for(unordered_map<LL, LL>::iterator it = f.begin(), l = f.end(); it != l; it++){
            LL g = 0;
            //cout << "el " << c++ << " "<< it->first << " " << it->second << "\n";
            for(LL i = 0; i<= it->second; i++){
                g = (g + G(it->first, i))%MOD;
            }
            ans = (ans * g)%MOD;
        }
        cout << ans << '\n';
        
    }
       
}

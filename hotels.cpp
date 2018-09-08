#include <iostream>

int main(){
	int n, m; std::cin >> n >> m;
	
	int* a = new int[n+1];
	for(int i=1; i<=n; i++) std::cin >> a[i];
	
	long long s = 0, cs=0; int b, bb, be;
	for(int i=1; i<=n; i++){
		if(cs<=0){b=i; cs = 0;}
		cs += 1ll*a[i];
		while(cs>m){
			cs-=1ll*a[b];
			b++;
		}
		if(cs >s && cs<=m){
			s = cs;
			bb = b;
			be = i;
		}
	}
	std::cout << s << '\n';
	delete[] a;
}

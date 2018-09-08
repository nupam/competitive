#include <iostream>
#include <cstdlib>
#include <ctime>
template <class T> inline void swap(T& a, T&b){
T t = a;
a = b;
b = t;
}
int partition(int *b, int *e){
	srand(time(NULL));
	int l = (int)(e-b) - 1;
	int p = rand()%l;
	swap(b[l], b[p]);
	int pivot = b[l];
	int g = -1;
	for(int i=0; i<l; i++){
		if(b[i] < pivot && g != -1){
			swap(b[i],b[g]);
			g++;
		}
	else if(b[i]>=pivot && g == -1)
		g = i;
	}
	if(g!=-1) swap(b[g], b[l]);
	return g;
}

int kthMin(int *b, int* e, int k){
	if(b == e+1) return *e;
	int q = partition(b, e);
	if(q+1 == k) return b[q];
	if(q+1 < k) return kthMin(b+q+1, e, k-q-1);
	return kthMin(b, b+q, k);
}
int main(){
	int n,k;
	std::cout << "Number of Elements: "; std::cin >> n;
	int* a = new int[n];
	for(int i=0; i<n; i++) std::cin >> a[i];
	std::cout << "K: "; std::cin >> k;
	std:: cout << kthMin(a, a+n, n-k+1) << "\n";
	//for(int i=0; i<n; i++) std::cout << a[i] << ' ';	
}

#include <iostream>

int main(){
	struct funcs{
	private:	
		static int merge(int* a, int m, int n){
			int* b = a+m;
			n = n-m;
			int i1=0, i2=0, i=0, inv=0;
			int* arr = new int[n];
			while(i1<m && i2<n){
				if(a[i1] > b[i2]){
					inv += m-i1;
					arr[i++] = b[i2++];
				}
				else{
					arr[i++] = a[i1++];
				}
			}
			
			while(i1<m) arr[i++] = a[i1++];
			while(i2<n) arr[i++] = b[i2++];
			for(int i=0; i<m+n; i++) a[i] = arr[i];
			delete[] arr;
			return inv;
		}

	public:
		static int invc(int* a, int n){
			if(!n || n==1) return 0;

			int m = n/2, inv = 0;
			inv = invc(a, m) + invc(a+m, n-m);
			inv += merge(a, m, n);

			return inv;
		}
	};

	int n; std::cin >> n;
	int *a = new int[n];
	for(int i=0; i<n; i++) std::cin >> a[i];
	std::cout << funcs::invc(a, n) << '\n';
	//for(int i=0; i<n; i++) std::cout << a[i] << ' '; std::cout << '\n';
	return 0;

}

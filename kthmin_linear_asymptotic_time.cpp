#include <algorithm>
#include <cmath>
using namespace std;

void insertionSort(int* a, int n){
    if(n<=1 || !a) return;
    for(int i=1; i<n; i++){
        int t = a[i];
        int j = i-1;
        while(j>=0 && a[j] > t){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = t;
    }
}

int partition(int* a, int n){
    if(n==1) return 0;
    int p = a[--n];
    int b = -1;
    for(int i=0; i<n; i++){
        if(a[i] >= p);
        else swap(a[++b], a[i]);
    }
    swap(a[++b], a[n]);
    return b;
}

int findMedianOfMedians(int* a, int n){
    int* b = new int[n];
    for(int i=0; i<n; i++) b[i] = a[i];
    while(n>1){
        int g = ceil(1.0*n/5);
        bool extra =( n%5!=0);
        int* medians = new int[g];
        if(extra) g--;
        for(int i=0; i<g; i++){
            insertionSort(b+5*i, 5);
            medians[i] = b[5*i+2];
        }
        if(extra){
            int eit = n-5*g;
            insertionSort(b+5*g, eit);
            medians[g] = b[5*g + ((int)ceil(1.0*eit/2)-1)];
        }
        n = g;
        if(extra) n++;
        delete[] b;
        b = medians;
    }
    int ans = b[0];
    delete[] b;
    return ans;
}

int kthmin(int* a, int n, int k){
    if(n==1) return a[0];
    int m = findMedianOfMedians(a, n);
    int p = (int)(find(a, a+n, m)-a);
    swap(a[p], a[n-1]);
    p = partition(a, n);
    if(p+1==k) return a[p];
    else if(p>=k) return kthmin(a, p, k);
    else return kthmin(a+p+1, n-p-1, k-p-1);
}


int main() {
	int t; cin >> t;
	while(t--){
	    int n, k; cin >> n;
	    int *a = new int[n];
	    for(int i=0; i<n; i++) cin >> a[i];
	    cin >> k;
	    cout << kthmin(a, n, k) <<  '\n';
	    delete[] a;
	}
	return 0;
}

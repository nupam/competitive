#include <iostream>
#include <cmath>
template <class T> inline void swap(T& a, T&b){
T t = a;
a = b;
b = t;
}
int partition(int *b, int n, int k){
int l = n - 1, p;
for(int i=0; i<=l; i++) if(b[i]==k){p=i; break;}
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
void insertionSort(int* a, int n){
for(int i=1; i<n; i++){
int j = i-1;
while(j>=0 && a[j] > a[j+1]){
swap(a[j], a[j+1]);
j--;
}
}
}
int kthMin(int *a, int n, int k){
if(n==1) return a[0];
int* median = new int[n], l = n;
for(int i=0; i<n; i++) median[i] = a[i];
while(l>1){
int gp = ceil(1.0*l/5);int* temp = new int[gp];
int it_count = l%5==0 ? gp:gp-1;
for(int i=0; i<it_count; i++){
insertionSort(median+5*i, 5);
temp[i] = (median+5*i)[2];
}
if(l%5 !=0){
insertionSort(a+(gp-1)*5, l%5);
temp[gp-1] = (a+(gp-1)*5)[(int)ceil((l%5)/2) -1];
}
delete[] median;
median = temp;
l = gp;
}
int q = partition(a, n, median[0]);
if(q+1 == k) return a[q];
if(q+1 < k) return kthMin(a+q+1, n-q-1, k-q-1);
return kthMin(a, q, k);
}
int main(){
int n,k;
std::cout << "Number of Elements: "; std::cin >> n;
int* a = new int[n];
for(int i=0; i<n; i++){
std::cin >> a[i];
}
std::cout << "K: "; std::cin >> k;
std:: cout << kthMin(a, n, k) << "\n";
//for(int i=0; i<n; i++) std::cout << a[i] << ' ';

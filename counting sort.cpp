#include <iostream>

int* countingSort(int* a, int n, int k){
    int *b = new int[n], *c = new int[k+1]();
    for(int i=0; i<n; i++) c[a[i]]++;
    for(int i=1; i<=k; i++) c[i] += c[i-1];
    for(int i=n-1; i>=0; i--){
        b[c[a[i]]-1] = a[i];
        c[a[i]]--;
    }
    delete[] c;
    return b;
}


int main(){
    int a[7] = {5 , 9, 1, 6, 12, 65, 6};
    int* b = countingSort(a, 7, 65);
    for(int i=0; i<7; i++) std::cout << b[i] << ' ';
    std::cout << '\n';
    delete[] b;
}
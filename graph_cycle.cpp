#include <iostream>
#include <cstdio>
#include <cmath>

using std::cin;
using std::cout;

inline void swap(int&a, int&b){
    int t = a;
    a=b;
    b=t;
}

inline int min(int a, int b){
    return a>b ? b:a;
}

class s{
public:
    int w, c;
    s():w(0), c(0) { }
};

class edge{
public:
    int v1, v2, w;
    edge(int v1=0, int v2=0, int w=0): v1(v1), v2(v2), w(w) { }
};

int solution(int** in, s* a, int n,edge* l, int v1, int c1, int v2, int c2 );
inline int minDis2Nodes(int* c, int p1, int p2, int& count);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    scanf("%d", &t);

    while(t--){
        int n, q, in1, in2;
        scanf("%d %d", &n, &q);
        int**a;
        a = new int*[n];
        for(int i=0;i<n;i++){
            scanf("%d", &in1);;
            a[i] = new int[in1+1];
            a[i][0] = in1;
            scanf("%d", &in2);;
            a[i][1] = in2;
            for(int j=2;j<=in1;j++){
                scanf("%d", &in2);;
                a[i][j] = a[i][j-1] + in2;
            }
        }

        edge l[n];
        for(int i=0;i<n;i++){ scanf("%d %d %d", &l[i].v1 ,&l[i].v2 ,&l[i].w); }


        s sol[n+1];
        int p=l[n-1].v2;
        for(int i=1;i<=n;i++){
            sol[i].w = sol[i-1].w + minDis2Nodes(a[i-1], p, l[i-1].v1, sol[i].c)+ l[i-1].w;
            sol[i].c+=sol[i-1].c + 1;
            p = l[i-1].v2;
        }


        int v1, c1, v2, c2;
        while(q--){
            
            scanf("%d %d %d %d", &v1 ,&c1 ,&v2, &c2);
            cout << solution(a, sol, n, l, v1, c1, v2, c2) << "\n";
        }

        //for(int i=0;i<n;i++){
           // delete[] a[i];
        //}
        //delete[] a;
    }
    
}


int solution(int** in, s* a, int n,edge* l, int v1, int c1, int v2, int c2 ){

    if(c1>c2){
        swap(c1,c2);
        swap(v1,v2);
    }
    int w1c=0,w2c =0;
    int ans1 = minDis2Nodes(in[c1-1], v1, l[c1-1].v1, w1c);
    ans1 += a[c2-1].w - a[c1-1].w;
    ans1 += minDis2Nodes(in[c2-1], l[c2-2].v2, v2, w1c);
    w1c += a[c2-1].c - a[c1-1].c;

    int ans2 = minDis2Nodes(in[c2-1], v2, l[c2-1].v1, w2c);
    ans2 += l[c2-1].w;
    w2c++;
    ans2 += a[n].w - (a[c2].w - a[c1-1].w) + minDis2Nodes( in[c1 -1], l[(c1-1+n)%n].v2, v1, w2c);
    w2c += a[n].c - (a[c2].c - a[c1-1].c);

    return w1c>w2c ? ans2 :ans1;
}


//fix it it it it it it it
inline int minDis2Nodes(int* c, int p1, int p2, int& count){
    if(p1==p2) return 0;
    if(p1>p2) swap(p1, p2);
    int s = c[0];
    c[0] =0;
    int ans= p2-p1 < std::abs(s-p2+p1) ? c[p2-1]-c[p1-1] : c[s] - c[p2-1] + c[p1-1];
    c[0] = s;
    count+= min(p2-p1, std::abs(s-p2+p1));
    return ans;
}
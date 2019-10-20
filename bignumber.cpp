#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using std::cout;
using std::cin;

class bignumber{
    std::vector<char>n;
    void m10(){
        if(!(n.size()==1 && n[0]=='0')) n.insert(n.begin(), '0'); 
    }
public:
    bignumber(){n.push_back('0');}
    
    bignumber(long long num){
        while(num){
            n.push_back(num%10 + '0');
            num/=10;
        }
        if(!n.size()) n.push_back('0');
    }
    
    bignumber(std::string num){
        for(int i = num.size()-1; i>=0; i--)
            n.push_back(num[i]);
        while(n[n.size()-1] == '0' && n.size()>1) n.erase(n.end()-1); //remove leading zeroes
    }

    //bignumber(const char* s) { bignumber(std::string(s)); }

    bignumber(std::vector<char> _n): n(_n){
        while(n[n.size()-1] == '0' && n.size()>1) n.erase(n.end()-1); //remove leading zeroes
    }

    char& operator[](int i){
        return n[i];
    }
    
    char& operator[](int i) const{
        return n[i];
    }

    int size() const { return n.size(); }

    bignumber add(bignumber& n1);

    bignumber operator+(bignumber& n1) {
        int p = n.size() > n1.size() ? n.size() - n1.size() : n1.size() - n.size();
        for(int i=0; i<)
        return add( n1); 
    }
    bignumber operator+(long long n1) { bignumber n = n1; return add(n); }

    bignumber multiply(bignumber& n1);

    bignumber operator*(bignumber& n1) { return multiply(n1); }
    bignumber operator*(long long n1) { bignumber n = n1; return multiply(n); }

    void show(){
        for(int i = n.size()-1; i >=0; i--)
            std::cout << n[i];
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        std::string in;
        cin >> s;
        int a, b;
        char c;
        std::stringstream ss(in);
        ss >> a >> c >> b;


    }
}



bignumber bignumber::add(bignumber& n1){
    if(n.size()==1 && n[0]=='0')
        return n1;
    if(n1.size()==1 && n1[0]=='0')
        return n;
    int l1 = n.size(), l2 = n1.size();
    int l = l1>l2? l1+1:l2+1;
    std::vector<char> sum(l, '0');
    int carry = 0;
    int i = 0;

    for(; i<l1 && i<l2; i++){
        int temp = n[i] - '0' + n1[i] - '0' + carry;
        carry = temp/10;
        temp %=10;
        sum[i] = temp + '0';
    }
    for(;i<l1; i++){
        int temp = n[i] - '0' + carry;
        carry = temp/10;
        temp %=10;
        sum[i] = temp + '0';
    }
    for(;i<l2; i++){
        int temp = n1[i] + carry;
        carry = temp/10;
        temp %=10;
        sum[i] = temp + '0';
    }
    sum[i] = carry + '0';

    return bignumber(sum);
}

bignumber bignumber::multiply(bignumber& n1){
    if(n.size()==1 && n[0]=='0')
        return bignumber();
    if(n1.size()==1 && n1[0]=='0')
        return bignumber();
    bignumber p;
    for(int i= n.size()-1; i>=0; i--){
        bignumber temp;
        for(int j = 0; j< n[i]-'0'; j++)
            temp = temp + n1;
        p.m10();
        p = p + temp;
    }
    return p;
}

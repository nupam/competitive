#include <iostream>
#include <string>
#include <stack>

int isp(char c){
    if(c=='(')
        return 0;
    if(c=='^')
        return 5;
    if(c == '*' || c =='/')
        return 4;
    if(c == '+' || c =='-')
        return 2;
    if(c==')')
        return 9;
    return 8;
}


int icp(char c){
    if(c==')')
        return 0;
    if(c=='^')
        return 6;
    if(c == '*' || c =='/')
        return 3;
    if(c == '+' || c =='-')
        return 1;
    if(c=='(')
        return 9;
    return 7;
}


std::string in_to_post(std::string in){
    std::stack<char> S;
    std::string post;
    in+=')';
    S.push('(');
    char curr;
    int index = -1;


    while(++index < in.size()){
        curr= in[index];

        while(  icp(curr) < isp(S.top())  ){
            post+=S.top();
            S.pop();
        }

        if(icp(curr) == isp(S.top()))  S.pop();
        
        else S.push(curr);
    }

    return post;
}




int main(){
    std::string s;
    int t;
    std::cin >> t;
    while(t--){
        std::cin >>s;
        std::cout <<in_to_post(s) <<std::endl;
    }

}




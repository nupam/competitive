#include <iostream>
#include <string>

std::string increment(std::string n){
    
    
    int size = n.size();

    int i=size-1;
    while(i>=0){
        if(n[i] != '9'){
            n[i]++;
            return n;
        }
        else
            n[i--]='0'; 
    }

    n = '1' + n;
    return n;
}


//reverses the string
inline std::string rev(std::string s){
    int size = s.size();
    for(int i=0, l= size/2;i<l; i++){
        char temp = s[i];
        s[i] = s[size - i -1];
        s[size - i - 1] = temp;
    }

    return s;
}

//compares two strings representing number without leading zeroes
inline bool comp(std::string s1, std::string s2){
    if(s1.size()==s2.size())
        return s1 > s2;

    else if(s1.size()>s2.size())
        return true;

    return false;
}


//return solution string
std::string sol(std::string n){

    int size = n.size();
    //odd number of digits
    if(size%2){
        if(n=="9")
            return "11";
        std::string h1(n.substr(0, size/2));
        std::string h2(n.substr(size/2+1));

        if(comp(rev(h1),h2))
            return n.substr(0, size/2+1) + rev(h1);
        

        else{
            h1+=n[size/2];
            std::string rtr =  increment(h1);

            if(increment(h1).size() != h1.size())
                rtr += rev(rtr.substr(0, rtr.size()-2));
            else
                rtr += rev(rtr.substr(0, rtr.size()-1));
            return rtr;
        }
        

    }

    //even number of digits
    else{
        std::string h1(n.substr(0, size/2));
        std::string h2(n.substr(size/2));

        if(comp(rev(h1),h2))
            return h1 + rev(h1);
        

        else{
            std::string rtr =  increment(h1);

            if(increment(h1).size() != h1.size())
                rtr += rev(rtr.substr(0, rtr.size()-1));
            else
                rtr += rev(rtr);
            return rtr;

        }

    }
    
}


int main(){

    //lets have a quickie
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int t;
    std::string in;
    std::cin >> t;

    for(int i=0;i<t;i++){
        std::cin >> in;
        std::cout << sol(in) << std::endl;
    }

}
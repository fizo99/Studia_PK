#include <iostream>
bool isPalindrome(std::string s);

int main(int argc, char *argv[]){
    if(argv[1] == NULL) {
        std::cout << "no arguments";
        return 1;
    }

    std::string s(argv[1]);

    if(isPalindrome(s)) std::cout << "palindrom"; 
    else                std::cout << "nie palindrom";
    
    return 0;
}

bool isPalindrome(std::string s){
    int it = s.length()-1;
    for(int i = 0; i < s.length()/2; i++){
        if( !(s[i] == s[it]) ) {
            return false;;
        }
        it--;
    }
    return true;
}
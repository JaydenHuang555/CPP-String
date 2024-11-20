#include "iostream"
#include "String.h" 

int main(){
    jay::String *str = new jay::String();

    *str += "this is an test";
    std::cout << *str <<"\n";

    delete str;

    return 0;
}
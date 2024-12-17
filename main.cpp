#include "iostream"
#include "String.h" 

int main(){
    jay::String *str = new jay::String();

    std::cout << "enter input: ";

    std::cin >> *str;

    std::cout << *str << "\n";

    delete str;

    return 0;
}
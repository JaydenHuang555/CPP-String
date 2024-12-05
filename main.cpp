#include "iostream"
#include "String.h" 

int main(){
    jay::String *str = new jay::String();

    *str += "this is a test foo bar";
    // std::cout << str->compareTo("thioihoihoioihoihoihio") <<"\n";
    printf("%s\n", str->contains("foo bar") == 0 ? "false" : "true");

    delete str;

    return 0;
}
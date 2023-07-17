#if false
g++ -std=gnu++20 -Wall -Wextra libtest.cpp -o libtest
./libtest
rm libtest
exit
#endif
#include <iostream>
#include "DLTS/lsb.hpp"

int main(){
    std::cout << lsb(10) << std::endl;
    return 0;
}
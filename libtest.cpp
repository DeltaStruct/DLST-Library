#if false
g++ -std=gnu++20 -Wall -Wextra libtest.cpp -o libtest
echo
./libtest
rm libtest
exit
#endif
#include <iostream>
#include "DLTS/fastio.hpp"

int main(){
    char x;
    fastio >> x;
    std::cout << x << std::endl;
    fastio >> x;
    std::cout << x << std::endl;
    return 0;
}
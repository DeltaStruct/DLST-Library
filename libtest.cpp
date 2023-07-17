#if false
g++ -std=gnu++20 -Wall -Wextra libtest.cpp -o libtest
./libtest
rm libtest
exit
#endif
#include <iostream>
#include "DLTS/tarai.hpp"

int main(){
    std::cout << tarai(15, 6, 0) << std::endl;
    std::cout << tarai_fast(15, 6, 0) << std::endl;
    return 0;
}
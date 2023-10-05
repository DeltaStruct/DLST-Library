#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../DataStructures/binary_indexed_tree.hpp"

#include <iostream>

int main(){
    int n, q, l, r, t; std::cin >> n >> q;
    BinaryIndexedTree<long long> b(n);
    for (int i(0);i < n;++i) (std::cin >> t),b[i] = t;
    while(q--){
        std::cin >> t >> l >> r;
        if (t==0) b[l] += r;
        else std::cout << b.query(l, r) << std::endl;
    }
}
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../DataStructures/binary_indexed_tree.hpp"

#include <iostream>

int main(){
    int n, q, l, r, t; std::cin >> n >> q;
    BinaryIndexedTree<int> b(n);
    while(q--){
        std::cin >> t >> l >> r;
        if (t==0) b[l] = r;
        else std::cout << b.query(l, r) << std::endl;
    }
}
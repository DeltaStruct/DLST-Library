#include <vector>
#include <concepts>
#include <iostream>
#include <string>
#define private public

template<typename To, typename Tl>
concept BIT_function = std::invocable<To, bool, Tl, Tl>;
template<typename T>
struct add_BIT {
    T operator()(const bool&& t, const T& x, const T& y) noexcept {
        return (t?x+y:x-y);
    }
};
template<>
struct add_BIT<std::string> {
    std::string operator()(const bool&& t, const std::string& x, const std::string& y) noexcept {
        return (t?x+y:x.substr(y.size()));
    }
};

template<typename T, BIT_function<T> U = add_BIT<T>>
class BinaryIndexedTree {
    private:
    std::vector<T> data;
    U fn; std::size_t sz, clog;
    public:
    BinaryIndexedTree()noexcept:data(1), fn(add_BIT<T>()), sz(0), clog(0) {}
    BinaryIndexedTree(const U& f)noexcept:data(1), fn(f), sz(0), clog(0) {}
    BinaryIndexedTree(const std::size_t n)noexcept:data(n+1), fn(add_BIT<T>()), sz(n), clog(0) {}
    BinaryIndexedTree(const std::size_t n, const U f)noexcept:data(n+1), fn(f), sz(n), clog(0) {}
    void resize(const size_t& n) noexcept { data.resize(n); }
    struct element {
        private:
        std::vector<T>* d; std::size_t s, ci;
        T cache; std::size_t* cip;
        public:
        element() = delete;
        element(const element&) = default;
        element(element&&) = default;
        explicit operator T() noexcept {
            std::size_t t = s;
            if (*cip==ci) return cache;
            cache = (*d)[t],t-= ((t & -t)>>1) ;
            for (;t&1==0;t-= ((t & -t)>>1) ){
                /* 未証明 LSBを2で割ったものを引いていくと横の要素全部得られる */
                cache -= (*d)[t];
            }
            return (ci=*cip,cache);
        }
        element(std::vector<T>* p, std::size_t i, std::size_t* cii) noexcept : 
        d(p),s(i+1),ci((*cii)+1),cip(cii) { cache=(T)*this; }
        element& operator=(const T&) noexcept {
            return *this;
        }
    };
    element operator[](std::size_t s) noexcept {
        return element(&data, s, &clog);
    }
    /* デバッグ用 */
    T op(const T& x, const T& y){ return fn(true, x, y); }
    T op(const T&& x, const T&& y){ return fn(true, x, y); }
    T rop(const T& x, const T& y){ return fn(false, x, y); }
    T rop(const T&& x, const T&& y){ return fn(false, x, y); }
};
template<typename T>
using binary_indexed_tree = BinaryIndexedTree<T>;
template<typename T>
using BIT = BinaryIndexedTree<T>;

int main(){
    BinaryIndexedTree<int> b(3);
    std::cout << (int)b[0] << std::endl;
    std::cout << b.op(1, 2) << ' ' << b.rop(18, 7) << std::endl;
}
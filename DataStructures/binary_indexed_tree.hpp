#include <vector>
#include <concepts>
#include <string>

template<typename To, typename Tl>
concept BIT_function = std::invocable<To, bool, Tl, Tl>;
template<typename T>
struct add_BIT {
    T operator()(const bool&& t, T& x, T& y) noexcept {
        return (t?x+y:x-y);
    }
    T operator()(const bool&& t, T&& x, T&& y) noexcept {
        return (t?x+y:x-y);
    }
};
template<>
struct add_BIT<std::string> {
    std::string operator()(const bool&& t, std::string& x, std::string& y) noexcept {
        return (t?x+y:x.substr(y.size()));
    }
    std::string operator()(const bool&& t, std::string&& x, std::string&& y) noexcept {
        return (t?x+y:x.substr(y.size()));
    }
};

template<typename T, BIT_function<T> U = add_BIT<T>>
class BinaryIndexedTree {
    private:
    std::vector<T> data;
    U fn; std::size_t sz, clog;
    public:
    BinaryIndexedTree()noexcept:data(1), fn(U()), sz(0), clog(0) {}
    BinaryIndexedTree(const std::size_t n)noexcept:data(n+1), fn(U()), sz(n), clog(0) {}
    void resize(const size_t& n) noexcept { data.resize(n); }
    struct element {
        private:
        std::vector<T>* d; std::size_t s, ci;
        T cache, dinit; std::size_t* cip; U fn;
        public:
        element() = delete;
        element(const element&) = default;
        element(element&&) = default;
        explicit operator T() noexcept {
            if (*cip==ci) return cache;
            cache = (*d)[s];
            if (s&1) return (ci=*cip,cache);
            for (std::size_t t = s-((s & -s)>>1);(t&1)==0;t+= ((t & -t)>>1) ){
                /* 未証明 LSBを2で割ったものを足していくと横の要素全部得られる */
                cache = fn(false,cache,(*d)[t]);
            }
            return (ci=*cip,cache=fn(false,cache,(*d)[s-1]));
        }
        element(std::vector<T>* p, std::size_t i, std::size_t* cii) noexcept : 
        d(p),s(i+1),ci((*cii)+1),cip(cii), dinit(),fn(U()) { cache=(T)*this; }
        element& operator+=(T& x) noexcept {
            for (std::size_t i = s,sz = d->size();i <= sz;i+=(i & -i)) (*d)[i]=fn(true,(*d)[i],x);
            return (++(*cip),*this);
        }
        element& operator+=(T&& x) noexcept {
            for (std::size_t i = s,sz = d->size();i <= sz;i+=(i & -i)) (*d)[i]=fn(true,(*d)[i],x);
            return (++(*cip),*this);
        }
        element& operator=(T& x) noexcept { return (T)(*this),(*this)+=(fn(false,x,cache)); }
        element& operator=(T&& x) noexcept { return (T)(*this),(*this)+=(fn(false,x,cache)); }
        element& operator-=(T& x) noexcept { return (T)(*this),(*this)+=(fn(false,dinit,x)); }
        element& operator-=(T&& x) noexcept { return (T)(*this),(*this)+=(fn(false,dinit,x)); }
    };
    element operator[](std::size_t s) noexcept {
        return element(&data, s, &clog);
    }
    T query(std::size_t s) noexcept {
        T res{}; // resは0初期化されることが望ましい
        for (std::size_t i = s;i > 0;i -= (i & -i) ) res=fn(true,res,data[i]);
        return res;
    }
    T query(std::size_t s, std::size_t e) noexcept {
        return fn(false,query(e),query(s));
    }
    T kth(std::size_t k) noexcept {
        for(;k&1==0;k+=){}
    }
    /* デバッグ用 */
    T op(T& x, T& y){ return fn(true, x, y); }
    T op(T&& x, T&& y){ return fn(true, x, y); }
    T rop(T& x, T& y){ return fn(false, x, y); }
    T rop(T&& x, T&& y){ return fn(false, x, y); }
};
template<typename T>
using binary_indexed_tree = BinaryIndexedTree<T>;
template<typename T>
using BIT = BinaryIndexedTree<T>;
#include <concepts>
#include <vector>
#include <limits>
#include <algorithm>

#include <iostream>

template<typename T,typename U>
concept monotone_exec = std::invocable<T, U, U> && requires(T x){
    { x(std::declval<U>(),std::declval<U>()) } -> std::same_as<U>;
};

template<typename T>
struct mm_min_obj_t { T operator()(T x, T y) const noexcept { return x; } } ;
mm_min_obj_t<int> mm_min_obj;

template<typename T, monotone_exec<T> U>
class MonotoneMinima {
    private:
    T _m, _n,_maxi;
    U _f;
    void monotone_back(T m, T n, std::vector<T>& v, T x, T y) noexcept {
        if (x+2>=m){
            for (T i = y; i < n;++i) v[x] = std::min(v[x],_f(x,i));
            if (x+2==m) monotone_back(m,n,v,x+1,y);
            return;
        }
        T s = (m-x)/2+x, u = -1, tmp;
        for (T i = y; i < n;++i){
            tmp = _f(s,i);
            if (tmp<v[s]) v[s] = tmp,u = i;
        }
        monotone_back(s,u+1,v,x,y);
        monotone_back(m,n,v,s+1,u);
    }
    public:
    MonotoneMinima(T m, T n, U f = U()): _m(m),_n(n),_f(f) { _maxi = std::numeric_limits<T>::max(); }
    void operator()(std::vector<T>& v) noexcept {
        if (v.size()!=_m) v.assign(_m,_maxi);
        monotone_back(_m,_n,v,0,0);
    }
};
template<typename T, monotone_exec<T> U>
using monotone_minima = MonotoneMinima<T,U>;
template<typename T, monotone_exec<T> U>
using Monotone_Minima = MonotoneMinima<T,U>;

std::vector<long long> A;
long long f(int m, int n) noexcept {
  return A[n]+(long long)(n-m)*(long long)(n-m);
}

int main(){
    // verify: https://atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
    long long n; std::cin >> n;
    A.assign(n,0);
    std::vector<long long> dp(n,std::numeric_limits<long long>::max()); for (long long& a:A) std::cin >> a;
    MonotoneMinima<long long, decltype(f)*> mm(n,n,&f);
    mm(dp);
    for (auto a:dp) std::cout << a << std::endl;;
}
#if __INCLUDE_LEVEL__

int main(){
    return 0;
}

#else // __INCLUDE_LEVEL__が0の場合
/* Library Zone */
#include <bits/stdc++.h>
using namespace std;
using i8 = std::int_fast8_t; using i16 = std::int_fast16_t; using i32 = std::int_fast32_t;
using i64 = std::int_fast64_t; using u8 = std::uint_fast8_t; using u16 = std::uint_fast16_t;
using u32 = std::uint_fast32_t; using u64 = std::uint_fast64_t; using str = std::string;
using f32 = float; using f64 = double; using f80 = long double; using f128 = __float128;
using vi = std::vector<int>; using vvi = std::vector<vi>; using vvvi = std::vector<vvi>;

class infinity {
    public:
    template<typename T>
    constexpr operator T() noexcept { return std::numeric_limits<T>::max(); }
	constexpr auto operator-() noexcept ;
} inf;
class neg_infinity {
    public:
    template<typename T>
    constexpr operator T() noexcept { return std::numeric_limits<T>::lowest(); }
	constexpr auto operator-() noexcept ;
} ninf;
constexpr auto infinity::operator-() noexcept { return ninf; }
constexpr auto neg_infinity::operator-() noexcept { return inf; }

#include __FILE__ // 自分自身をincludeしmain関数とかを定義
#endif

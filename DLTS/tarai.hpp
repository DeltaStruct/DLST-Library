/*
Copyright (c) 2023 DeltaStruct
Released under the MIT license
https://github.com/DeltaStruct/DLTS-Library/blob/main/LICENSE
*/

// tarai.hpp
// たらい回し関数(竹内関数)とかマッカーシ版とかO(1)で高速に計算するやつとか
// 言語のベンチマークテストとかで使われるやつなのでとくに置いておく理由はない

template<typename T>
concept can_tarai = requires(T a) { a - a; a <= a; };
template<typename T>
concept can_tarai_fast = requires(T a) { a > a; a <= a; };
template<can_tarai T>
T tarai(T x, T y, T z) noexcept {
    if (x <= y) return y;
    return tarai(tarai(x-1, y, z), tarai(y-1, z, x), tarai(z-1, x, y));
}
template<can_tarai T>
T tak(T x, T y, T z) noexcept {
    if (x <= y) return z;
    return tak(tak(x-1, y, z), tak(y-1, z, x), tak(z-1, x, y));
}
template<can_tarai_fast T>
T tarai_fast(T x, T y, T z) noexcept {
    if (x <= y) return y;
    if (x > y && y <= z) return z;
    return x;
}
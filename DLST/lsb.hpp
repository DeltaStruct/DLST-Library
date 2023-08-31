/*
Copyright (c) 2023 DeltaStruct
Released under the MIT license
https://github.com/DeltaStruct/DLTS-Library/blob/main/LICENSE
*/

// LSB(Least Significant Bit)を求める

template<typename T>
concept can_lsb = requires(T x) { (x & (-x)); };

template<can_lsb T>
constexpr T lsb(T x) noexcept {
    return x & (-x);
}
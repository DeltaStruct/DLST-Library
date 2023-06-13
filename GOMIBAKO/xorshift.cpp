// GOMIBAKO
// Copyright (c) 2023 DeltaStruct
// Released under the MIT license
// https://github.com/DeltaStruct/DLTS-Library/blob/main/LICENSE
// 廃棄理由:テスト用(同じ値のときに正しく動作しない ゴミ箱テスト用なので条件分岐入れない)

template<typename T>
void xorswap(T& x, T& y) noexcept { x^=y,y^=x,x^=y; }

template<typename T>
void xorswap(T* x, T* y) noexcept { *x^=*y,*y^=*x,*x^=*y; }

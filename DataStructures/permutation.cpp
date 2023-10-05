#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>

template<typename T>
class permutation{
  std::vector<T> _v;
  public:
  permutation(permutation& p) noexcept = default;
  permutation(permutation&& p) noexcept = default;
  permutation(std::vector<T> v) noexcept : _v(std::move(v)) {}
  permutation(std::vector<T>& v) noexcept : _v(v) {}
  permutation(std::vector<T>&& v) noexcept : _v(v) {}
  permutation(const std::vector<T>& v) noexcept : _v(v) {}
  permutation(std::size_t sz) noexcept : _v(sz) { std::iota(_v.begin(), _v.end(), 1); }
  T& operator[](std::size_t ind) noexcept { return _v[ind]; }
  T& at(std::size_t ind) noexcept { return _v.at(ind); }
  std::size_t size() noexcept { return _v.size(); }
  decltype(_v.begin()) begin() noexcept { return _v.begin(); }
  decltype(_v.end()) end() noexcept { return _v.end(); }
  decltype(_v.rbegin()) rbegin() noexcept { return _v.rbegin(); }
  decltype(_v.rend()) rend() noexcept { return _v.rend(); }
  bool next() noexcept { return std::next_permutation(_v.begin(), _v.end()); }
  bool prev() noexcept { return std::prev_permutation(_v.begin(), _v.end()); }
  void resize(std::size_t sz) noexcept { return _v.resize(sz); }
  void build(std::vector<T> v) noexcept { _v = std::move(v); }
  void build(std::vector<T>& v) noexcept { _v = v; }
  void build(std::vector<T>&& v) noexcept { _v = v; }
  void build(std::size_t sz) noexcept { _v.resize(sz),std::iota(_v.begin(), _v.end(), 1); }
};
template<typename T>
std::istream& operator>>(std::istream& is, permutation<T>& p) noexcept {
    for (T& a:p) is >> a;
    return is;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, permutation<T>& p) noexcept {
    for (T a:p) os << a << ' ';
    return os;
}

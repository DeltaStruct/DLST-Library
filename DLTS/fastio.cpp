#include <cstdio>
#include <concepts>
#include <string>

class fastio_t {
    private:
    static char buf[1024*1024];
    constexpr std::size_t sz = 1024*1024;
    std::ssize_t now_write;
    public:
    fastio_t() noexcept {
        std::ssize_t ret = read(0, buf, sz);
        assert(ret > -1);
    }
    template<std::integral T>
    fastio& operator>>(fastio& f, T x) noexcept {
        return f;
    }
    template<>
    fastio& operator>><char>(fastio& f, char x) noexcept {
        return f;
    }
} fastio ;
// Depracted?(スペルこれであってたっけ)

#include <cstdio>
#include <unistd.h>
#include <cassert>
#include <concepts>
#include <string>

class fastio_t {
    private:
    char buf[1024*1024];
    static constexpr std::size_t sz = 1024*1024;
    ssize_t now_buf, now_read;
    public:
    fastio_t() noexcept : now_buf(0), now_read(0) {
        now_buf = read(0, buf, sz);
        assert(now_buf > -1);
    }
    void new_read() noexcept {
        now_buf = read(0, buf, sz);
        assert(now_buf > -1);
    }
    template<std::integral T>
    fastio_t& operator>>(T x) noexcept {
        return *this;
    }
    fastio_t& operator>>(char& x) noexcept {
        int c = (now_read>=now_buf?((now_read=now_buf),EOF):buf[now_read]);
        while(std::isspace(c)||now_read==now_buf){
            ++now_read;
            if (now_read==now_buf) now_buf = read(0, buf, sz),assert(now_buf > -1);
            c = (now_read>=now_buf?((--now_read),' '):buf[now_read]);
        }
        x = buf[now_read++];
        return *this;
    }
} fastio ;
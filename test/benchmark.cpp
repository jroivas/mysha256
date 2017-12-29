#include <iostream>
#include <array>
#include <chrono>
#include <functional>
#include "hash.hh"

class Benchmark
{
public:
    Benchmark() {
        start();
    }
    double execute(std::function<void()> f, uint32_t cnt = 1000) {
        start();
        while (cnt > 0) {
            f();
            --cnt;
        }
        return stop();
    }
    std::string run(std::function<void()> f, uint32_t cnt = 1000, uint32_t multiply = 1) {
        double r = execute(f, cnt);
        return std::to_string(r) + " total, " + std::to_string(cnt * multiply / r) + " rounds per second";
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    double stop() const {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
        return duration.count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

void test1() {
    sha::Hash hash;
    hash.calculate("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
}

void test2() {
    sha::Hash hash("37e4e3c02a59b5f82b095a3c75acf04a0bad972ef5488999a71e99df56c28772");
}

void checkDigest(const std::array<uint32_t, 8> &a, const std::array<uint32_t, 8> &b)
{
    for (size_t i = 0; i < 8; ++i) {
        if (a[i] != b[i]) throw std::string("Digest does not match: ") + std::to_string(a[i]) + " != " + std::to_string(b[i]) + " at " + std::to_string(i);
    }
}

void test3() {
    std::array<uint32_t, 8> result = {
        0xcd4e763f,
        0x4b146a41,
        0x3df15c48,
        0xb450371d,
        0x35eb3b36,
        0x32d0b2b7,
        0x135cc324,
        0xc02e55d3
    };
    sha::Hash hash("37e4e3c02a59b5f82b095a3c75acf04a0bad972ef5488999a71e99df56c28772");
    for (size_t i = 0; i < 100; ++i) {
        hash.calculate("37e4e3c02a59b5f82b095a3c75acf04a0bad972ef5488999a71e99df56c28772");
        checkDigest(hash.rawDigest(), result);
    }
}

void test4() {
    sha::Hash hash;
    hash.calculate("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
}

int main(int argc, char **argv)
{
    Benchmark bm;
    uint32_t base = 1000;
    std::cout << bm.run(test1, 100 * base) << "\n";
    std::cout << bm.run(test2, 1000 * base) << "\n";
    std::cout << bm.run(test3, 10 * base, 100) << "\n";
    std::cout << bm.run(test4, 30 * base) << "\n";
    return 0;
}

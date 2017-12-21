#pragma once

#include <iostream>
#include <sstream>
#include <string>

static long __success = 0;
static long __suite_success = 0;

#define TEST_MAIN(X) \
int main(int argc, char**argv) {\
    (void)argc; (void)argv;\
    try {\
        X;\
    }\
    catch (std::string e) {\
        std::cout << "-- FAIL: " << e << "\n";\
        return 1;\
    }\
    std::cout << "++ " << __success << " tests PASSED\n"; \
    return 0;\
}
#define TEST_SUITE(X, Y) \
    std::cout << "== SUITE: " << #X << "\n";\
    __suite_success = __success;\
    {\
        Y;\
    }\
    std::cout << "== " << (__success - __suite_success) << " tests PASSED in suite: " << #X << "\n";
#define TEST_CASE(X, Y) {\
    std::cout << "   TEST " << #X << "\n"; \
    Y;\
}
#define TEST_ASSERT_TRUE(X) do { if ((X)) { __success++; } else { std::stringstream s; s << #X; throw s.str(); } } while (0);
#define TEST_ASSERT_FALSE(X) TEST_ASSERT_TRUE(!X)
#define TEST_ASSERT_EQUALS(X, Y) do { if ((X == Y)) { __success++; } else { std::stringstream s; s << #X << " != " << #Y << ", got " << std::hex << X << std::dec; throw s.str(); } } while (0);
#define TEST_ASSERT_EQUALS_ARRAY_INDEX(X, Y, IDX, SIZE) do { \
    for (size_t i = 0; i < SIZE; ++i) {\
        if (X[IDX + i] != Y[i]) {\
            std::stringstream s; s << "Array does not match at index " << i << " " << std::hex << X[IDX + i] << " != " << Y[i] << std::dec;\
            throw s.str();\
        }\
    }\
     __success++;} while (0);
#define TEST_ASSERT_EQUALS_ARRAY(X, Y, SIZE) TEST_ASSERT_EQUALS_ARRAY_INDEX(X, Y, 0, SIZE)

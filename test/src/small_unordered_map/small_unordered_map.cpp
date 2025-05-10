#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/small_unordered_map.hpp"

#include "check.hpp"
#include "count_kv.hpp"
#include "istream_view.hpp"
#include "nth.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"

#include <sstream>
#include <vector>

#ifdef _MSC_VER // Visual C++
#pragma warning(disable : 4127) // conditional expression is constant
#endif

void test_small_unordered_map_N0_M0_A1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 0
    #undef   TPARAM_M
    #define  TPARAM_M 0
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N0_M0_A2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 0
    #undef   TPARAM_M
    #define  TPARAM_M 0
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N0_M0_A3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 0
    #undef   TPARAM_M
    #define  TPARAM_M 0
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N0_M0_A4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 0
    #undef   TPARAM_M
    #define  TPARAM_M 0
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N0_M0_A5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 0
    #undef   TPARAM_M
    #define  TPARAM_M 0
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N32_M32_A1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 32
    #undef   TPARAM_M
    #define  TPARAM_M 32
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N32_M32_A2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 32
    #undef   TPARAM_M
    #define  TPARAM_M 32
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N32_M32_A3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 32
    #undef   TPARAM_M
    #define  TPARAM_M 32
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N32_M32_A4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 32
    #undef   TPARAM_M
    #define  TPARAM_M 32
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "small_unordered_map.inc"
}

void test_small_unordered_map_N32_M32_A5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 32
    #undef   TPARAM_M
    #define  TPARAM_M 32
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "small_unordered_map.inc"
}

int main()
{
    test_small_unordered_map_N0_M0_A1();
    test_small_unordered_map_N0_M0_A2();
    test_small_unordered_map_N0_M0_A3();
    test_small_unordered_map_N0_M0_A4();
    test_small_unordered_map_N0_M0_A5();

    test_small_unordered_map_N32_M32_A1();
    test_small_unordered_map_N32_M32_A2();
    test_small_unordered_map_N32_M32_A3();
    test_small_unordered_map_N32_M32_A4();
    test_small_unordered_map_N32_M32_A5();
}

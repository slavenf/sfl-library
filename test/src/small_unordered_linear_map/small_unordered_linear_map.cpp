#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/small_unordered_linear_map.hpp"

#include "check.hpp"
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

void test_small_unordered_linear_map_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "small_unordered_linear_map.inc"
}

void test_small_unordered_linear_map_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "small_unordered_linear_map.inc"
}

void test_small_unordered_linear_map_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "small_unordered_linear_map.inc"
}

void test_small_unordered_linear_map_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "small_unordered_linear_map.inc"
}

void test_small_unordered_linear_map_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "small_unordered_linear_map.inc"
}

int main()
{
    test_small_unordered_linear_map_1();
    test_small_unordered_linear_map_2();
    test_small_unordered_linear_map_3();
    test_small_unordered_linear_map_4();
    test_small_unordered_linear_map_5();
}

#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/flat_multimap.hpp"

#include "check.hpp"
#include "contains.hpp"
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

#include <algorithm>
#include <random>
#include <sstream>
#include <vector>

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_flat_multimap_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "flat_multimap.inc"
}

void test_flat_multimap_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "flat_multimap.inc"
}

void test_flat_multimap_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "flat_multimap.inc"
}

void test_flat_multimap_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "flat_multimap.inc"
}

void test_flat_multimap_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "flat_multimap.inc"
}

int main()
{
    test_flat_multimap_1();
    test_flat_multimap_2();
    test_flat_multimap_3();
    test_flat_multimap_4();
    test_flat_multimap_5();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#undef  TPARAM_ALLOCATOR
#define TPARAM_ALLOCATOR std::allocator

#define TEST_CPP20_CONSTEXPR

#include "flat_multimap.inc"

#endif // SFL_CPP_VERSION >= SFL_CPP_20

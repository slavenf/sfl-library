#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/small_unordered_flat_multiset.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "nth.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xint_xint.hpp"
#include "xobj.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"

#include <sstream>
#include <vector>

void test_small_unordered_flat_multiset_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "small_unordered_flat_multiset.inc"
}

void test_small_unordered_flat_multiset_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "small_unordered_flat_multiset.inc"
}

void test_small_unordered_flat_multiset_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "small_unordered_flat_multiset.inc"
}

void test_small_unordered_flat_multiset_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "small_unordered_flat_multiset.inc"
}

void test_small_unordered_flat_multiset_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "small_unordered_flat_multiset.inc"
}

int main()
{
    test_small_unordered_flat_multiset_1();
    test_small_unordered_flat_multiset_2();
    test_small_unordered_flat_multiset_3();
    test_small_unordered_flat_multiset_4();
    test_small_unordered_flat_multiset_5();
}

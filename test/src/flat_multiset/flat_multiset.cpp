#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/flat_multiset.hpp"

#include "check.hpp"
#include "contains.hpp"
#include "count.hpp"
#include "count_kv.hpp"
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

#include <algorithm>
#include <random>
#include <sstream>
#include <vector>

void test_flat_multiset_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "flat_multiset.inc"
}

void test_flat_multiset_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "flat_multiset.inc"
}

void test_flat_multiset_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "flat_multiset.inc"
}

void test_flat_multiset_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "flat_multiset.inc"
}

void test_flat_multiset_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "flat_multiset.inc"
}

int main()
{
    test_flat_multiset_1();
    test_flat_multiset_2();
    test_flat_multiset_3();
    test_flat_multiset_4();
    test_flat_multiset_5();
}

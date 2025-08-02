#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_ASSOCIATIVE_VECTOR
#include "sfl/detail/associative_vector.hpp"

#include "sfl/detail/functional.hpp"
#include "sfl/vector.hpp"

#include "check.hpp"
#include "contains.hpp"
#include "count.hpp"
#include "count_kv.hpp"
#include "nth.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"
#include "partially_propagable_alloc.hpp"

#include <algorithm>
#include <random>
#include <vector>

template <>
void test_associative_vector<1>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "associative_vector.inc"
}

template <>
void test_associative_vector<2>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "associative_vector.inc"
}

template <>
void test_associative_vector<3>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "associative_vector.inc"
}

template <>
void test_associative_vector<4>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "associative_vector.inc"
}

template <>
void test_associative_vector<5>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "associative_vector.inc"
}

template <>
void test_associative_vector<6>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::partially_propagable_alloc
    #include "associative_vector.inc"
}

int main()
{
    test_associative_vector<1>();
    test_associative_vector<2>();
    test_associative_vector<3>();
    test_associative_vector<4>();
    test_associative_vector<5>();
    test_associative_vector<6>();
}

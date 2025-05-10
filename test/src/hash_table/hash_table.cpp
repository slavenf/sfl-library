#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_HASH_TABLE
#include "sfl/detail/hash_table.hpp"

#include "sfl/detail/functional.hpp"

#include "check.hpp"
#include "hash.hpp"
#include "nth.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"
#include "partially_propagable_alloc.hpp"

#include <numeric> // accumulate
#include <random>
#include <vector>

template <>
void test_hash_table<1>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "hash_table.inc"
}

template <>
void test_hash_table<2>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "hash_table.inc"
}

template <>
void test_hash_table<3>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "hash_table.inc"
}

template <>
void test_hash_table<4>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "hash_table.inc"
}

template <>
void test_hash_table<5>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "hash_table.inc"
}

template <>
void test_hash_table<6>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::partially_propagable_alloc
    #include "hash_table.inc"
}

int main()
{
    for (std::size_t i = 0; i < sfl::dtl::hash_table_prime_list<>::size; ++i)
    {
        sfl::dtl::is_prime(sfl::dtl::hash_table_prime_list<>::list[i]);
    }

    test_hash_table<1>();
    test_hash_table<2>();
    test_hash_table<3>();
    test_hash_table<4>();
    test_hash_table<5>();
    test_hash_table<6>();
}

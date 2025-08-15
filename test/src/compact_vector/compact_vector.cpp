#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/compact_vector.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"

#include <sstream>
#include <vector>

void test_compact_vector_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "compact_vector.inc"
}

void test_compact_vector_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "compact_vector.inc"
}

void test_compact_vector_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "compact_vector.inc"
}

void test_compact_vector_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "compact_vector.inc"
}

void test_compact_vector_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "compact_vector.inc"
}

int main()
{
    test_compact_vector_1();
    test_compact_vector_2();
    test_compact_vector_3();
    test_compact_vector_4();
    test_compact_vector_5();
}

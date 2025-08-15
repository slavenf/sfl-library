#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_DEVECTOR
#include "sfl/devector.hpp"

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

template <>
void test_devector<1>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "devector.inc"
}

template <>
void test_devector<2>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "devector.inc"
}

template <>
void test_devector<3>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "devector.inc"
}

template <>
void test_devector<4>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "devector.inc"
}

template <>
void test_devector<5>()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "devector.inc"
}

int main()
{
    test_devector<1>();
    test_devector<2>();
    test_devector<3>();
    test_devector<4>();
    test_devector<5>();
}

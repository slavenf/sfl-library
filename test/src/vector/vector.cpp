#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/vector.hpp"

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

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_vector_1()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "vector.inc"
}

void test_vector_2()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "vector.inc"
}

void test_vector_3()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "vector.inc"
}

void test_vector_4()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "vector.inc"
}

void test_vector_5()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "vector.inc"
}

int main()
{
    test_vector_1();
    test_vector_2();
    test_vector_3();
    test_vector_4();
    test_vector_5();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#undef  TPARAM_ALLOCATOR
#define TPARAM_ALLOCATOR std::allocator

#define TEST_CPP20_CONSTEXPR

#include "vector.inc"

#endif // SFL_CPP_VERSION >= SFL_CPP_20

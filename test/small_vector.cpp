//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include small_vector.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/small_vector.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"

#include <sstream>
#include <vector>

#if 0 // TODO: Review this
static_assert
(
    sizeof(sfl::small_vector<double, 0>) ==
        3 * sizeof(sfl::small_vector<double, 0>::pointer),
    "Invalid size"
);

static_assert
(
    sizeof(sfl::small_vector<double, 5>) ==
        3 * sizeof(sfl::small_vector<double, 5>::pointer) +
        5 * sizeof(sfl::small_vector<double, 5>::value_type),
    "Invalid size"
);
#endif

void test_small_vector()
{
    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "small_vector.inc"

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "small_vector.inc"

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "small_vector.inc"

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "small_vector.inc"

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "small_vector.inc"
}

int main()
{
    test_small_vector();
}

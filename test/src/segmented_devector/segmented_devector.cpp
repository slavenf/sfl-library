#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/segmented_devector.hpp"

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

void test_segmented_devector_N_1_A_1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 1

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_1_A_2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 1

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_1_A_3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 1

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_1_A_4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 1

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_1_A_5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 1

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_2_A_1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 2

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_2_A_2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 2

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_2_A_3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 2

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_2_A_4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 2

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_2_A_5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 2

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_3_A_1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 3

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_3_A_2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 3

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_3_A_3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 3

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_3_A_4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 3

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_3_A_5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 3

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_4_A_1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 4

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_4_A_2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 4

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_4_A_3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 4

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_4_A_4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 4

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_4_A_5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 4

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_100_A_1()
{
    #undef   TPARAM_N
    #define  TPARAM_N 100

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR std::allocator
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_100_A_2()
{
    #undef   TPARAM_N
    #define  TPARAM_N 100

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::statefull_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_100_A_3()
{
    #undef   TPARAM_N
    #define  TPARAM_N 100

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_100_A_4()
{
    #undef   TPARAM_N
    #define  TPARAM_N 100

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
    #include "segmented_devector.inc"
}

void test_segmented_devector_N_100_A_5()
{
    #undef   TPARAM_N
    #define  TPARAM_N 100

    #undef   TPARAM_ALLOCATOR
    #define  TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
    #include "segmented_devector.inc"
}

int main()
{
    test_segmented_devector_N_1_A_1();
    test_segmented_devector_N_1_A_2();
    test_segmented_devector_N_1_A_3();
    test_segmented_devector_N_1_A_4();
    test_segmented_devector_N_1_A_5();

    test_segmented_devector_N_2_A_1();
    test_segmented_devector_N_2_A_2();
    test_segmented_devector_N_2_A_3();
    test_segmented_devector_N_2_A_4();
    test_segmented_devector_N_2_A_5();

    test_segmented_devector_N_3_A_1();
    test_segmented_devector_N_3_A_2();
    test_segmented_devector_N_3_A_3();
    test_segmented_devector_N_3_A_4();
    test_segmented_devector_N_3_A_5();

    test_segmented_devector_N_4_A_1();
    test_segmented_devector_N_4_A_2();
    test_segmented_devector_N_4_A_3();
    test_segmented_devector_N_4_A_4();
    test_segmented_devector_N_4_A_5();

    test_segmented_devector_N_100_A_1();
    test_segmented_devector_N_100_A_2();
    test_segmented_devector_N_100_A_3();
    test_segmented_devector_N_100_A_4();
    test_segmented_devector_N_100_A_5();
}

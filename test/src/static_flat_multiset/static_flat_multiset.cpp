#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_flat_multiset.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "nth.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xint_xint.hpp"
#include "xobj.hpp"

#include <sstream>
#include <vector>

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_static_flat_multiset()
{
    #include "static_flat_multiset.inc"
}

int main()
{
    test_static_flat_multiset();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#define TEST_CPP20_CONSTEXPR

#include "static_flat_multiset.inc"

///////////////////////////////////////////////////////////////////////////////

namespace constexpr_test
{

using set_type = sfl::static_flat_multiset<int, 8>;

constexpr set_type create_set()
{
    set_type set;
    set.emplace(10);
    set.emplace(20);
    set.emplace(30);
    return set;
}

constexpr bool test()
{
    set_type set1 = create_set();

    set_type set2;

    int sum_before = 0;

    for (const auto& elem : set2)
    {
        sum_before += elem;
    }

    set2 = set1;

    int sum_after = 0;

    for (const auto& elem : set2)
    {
        sum_after += elem;
    }

    return sum_before == 0 && sum_after == 60;
}

static_assert(test());

#if !(defined(__GNUC__) && !defined(__clang__))

constexpr set_type g_set = create_set();

static_assert(g_set.size() == 3);

#endif

} // namespace constexpr_test

#endif // SFL_CPP_VERSION >= SFL_CPP_20

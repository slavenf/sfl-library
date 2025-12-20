#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_vector.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"

#include <sstream>
#include <vector>

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_static_vector()
{
    #include "static_vector.inc"
}

int main()
{
    test_static_vector();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#define TEST_CPP20_CONSTEXPR

#include "static_vector.inc"

///////////////////////////////////////////////////////////////////////////////

namespace constexpr_test
{

using vector_type = sfl::static_vector<int, 8>;

constexpr vector_type create_vector()
{
    vector_type vec;
    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);
    return vec;
}

constexpr bool test()
{
    vector_type vec1 = create_vector();

    vector_type vec2;

    int sum_before = 0;

    for (const auto& elem : vec2)
    {
        sum_before += elem;
    }

    vec2 = vec1;

    int sum_after = 0;

    for (const auto& elem : vec2)
    {
        sum_after += elem;
    }

    return sum_before == 0 && sum_after == 60;
}

static_assert(test());

#if !(defined(__GNUC__) && !defined(__clang__))

constexpr vector_type g_vec = create_vector();

static_assert(g_vec.size() == 3);

#endif

} // namespace constexpr_test

#endif // SFL_CPP_VERSION >= SFL_CPP_20

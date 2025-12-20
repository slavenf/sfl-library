#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_unordered_map.hpp"

#include "check.hpp"
#include "count_kv.hpp"
#include "istream_view.hpp"
#include "nth.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include <sstream>
#include <vector>

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_static_unordered_map()
{
    #include "static_unordered_map.inc"
}

int main()
{
    test_static_unordered_map();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#define TEST_CPP20_CONSTEXPR

#include "static_unordered_map.inc"

///////////////////////////////////////////////////////////////////////////////

namespace constexpr_test
{

struct hash_int
{
    constexpr std::size_t operator()(int x) const noexcept
    {
        return static_cast<std::size_t>(x);
    }
};

using map_type = sfl::static_unordered_map<int, int, 8, 8, hash_int>;

constexpr map_type create_map()
{
    map_type map;
    map.emplace(10, 10);
    map.emplace(20, 20);
    map.emplace(30, 30);
    return map;
}

constexpr bool test()
{
    map_type map1 = create_map();

    map_type map2;

    int sum_before = 0;

    for (const auto& elem : map2)
    {
        sum_before += elem.first;
    }

    map2 = map1;

    int sum_after = 0;

    for (const auto& elem : map2)
    {
        sum_after += elem.first;
    }

    return sum_before == 0 && sum_after == 60;
}

static_assert(test());

#if !(defined(__GNUC__) && !defined(__clang__))

constexpr map_type g_map = create_map();

static_assert(g_map.size() == 3);

#endif

} // namespace constexpr_test

#endif // SFL_CPP_VERSION >= SFL_CPP_20

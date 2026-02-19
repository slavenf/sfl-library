using sfl::test::xint;
using sfl::test::xobj;

BEGIN_TEST("Test static_capacity and static_bucket_count")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    CHECK((map_type::static_capacity == 32));
}
END_TEST()

BEGIN_TEST("Test container()")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.empty() == true);
    CHECK(map.full() == false);
    CHECK(map.size() == 0);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 32);
}
END_TEST()

BEGIN_TEST("Test container(const KeyEqual&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    typename map_type::key_equal equal;

    map_type map(equal);

    CHECK(map.empty() == true);
    CHECK(map.full() == false);
    CHECK(map.size() == 0);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 32);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map_type map(data.begin(), data.end());

    CHECK(map.empty() == false);
    CHECK(map.full() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 27);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const KeyEqual&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    typename map_type::key_equal equal;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map_type map(data.begin(), data.end(), equal);

    CHECK(map.empty() == false);
    CHECK(map.full() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 27);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    map_type map(ilist);

    CHECK(map.empty() == false);
    CHECK(map.full() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 27);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const KeyEqual&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    typename map_type::key_equal equal;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    map_type map(ilist, equal);

    CHECK(map.empty() == false);
    CHECK(map.full() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() == 32);
    CHECK(map.capacity() == 32);
    CHECK(map.available() == 27);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 1);
    CHECK(COUNT_KV(map1, 20, 3) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(map1);

    CHECK(map2.size() == 5);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 1);
    CHECK(COUNT_KV(map2, 20, 3) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 1);
    CHECK(COUNT_KV(map1, 20, 3) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(std::move(map1));

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, -10, -1) == 1);
    CHECK(COUNT_KV(map1, -20, -1) == 1);
    CHECK(COUNT_KV(map1, -20, -2) == 1);
    CHECK(COUNT_KV(map1, -20, -3) == 1);
    CHECK(COUNT_KV(map1, -30, -1) == 1);

    CHECK(map2.size() == 5);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 1);
    CHECK(COUNT_KV(map2, 20, 3) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map_type map((sfl::from_range_t()), (std::views::istream<std::pair<xint, xint>>(iss)));
        #else
        map_type map((sfl::from_range_t()), (sfl::test::istream_view<std::pair<xint, xint>>(iss)));
        #endif

        CHECK(map.empty() == false);
        CHECK(map.size() == 5);
        CHECK(map.max_size() > 0);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename map_type::value_type> data
        (
            {
                {10, 1},
                {20, 1},
                {30, 1},
                {20, 2},
                {20, 3}
            }
        );

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map_type map(sfl::from_range_t(), std::views::all(data));
        #else
        map_type map(sfl::from_range_t(), data);
        #endif

        CHECK(map.empty() == false);
        CHECK(map.size() == 5);
        CHECK(map.max_size() > 0);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const KeyEqual&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        typename map_type::key_equal equal;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map_type map((sfl::from_range_t()), (std::views::istream<std::pair<xint, xint>>(iss)), equal);
        #else
        map_type map((sfl::from_range_t()), (sfl::test::istream_view<std::pair<xint, xint>>(iss)), equal);
        #endif

        CHECK(map.empty() == false);
        CHECK(map.size() == 5);
        CHECK(map.max_size() > 0);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename map_type::value_type> data
        (
            {
                {10, 1},
                {20, 1},
                {30, 1},
                {20, 2},
                {20, 3}
            }
        );

        typename map_type::key_equal equal;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map_type map(sfl::from_range_t(), std::views::all(data), equal);
        #else
        map_type map(sfl::from_range_t(), data, equal);
        #endif

        CHECK(map.empty() == false);
        CHECK(map.size() == 5);
        CHECK(map.max_size() > 0);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 1);
    CHECK(COUNT_KV(map1, 20, 3) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    map2 = map1;

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 1);
    CHECK(COUNT_KV(map1, 20, 3) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 5);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 1);
    CHECK(COUNT_KV(map2, 20, 3) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 1);
    CHECK(COUNT_KV(map1, 20, 3) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    map2 = std::move(map1);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, -10, -1) == 1);
    CHECK(COUNT_KV(map1, -20, -1) == 1);
    CHECK(COUNT_KV(map1, -20, -2) == 1);
    CHECK(COUNT_KV(map1, -20, -3) == 1);
    CHECK(COUNT_KV(map1, -30, -1) == 1);

    CHECK(map2.size() == 5);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 1);
    CHECK(COUNT_KV(map2, 20, 3) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(std::initializer_list)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);

    CHECK(map.size() == 5);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    std::initializer_list<typename map_type::value_type> ilist
    {
        {40, 2},
        {50, 2},
        {60, 2},
        {50, 3},
        {50, 4}
    };

    map = ilist;

    CHECK(map.size() == 5);
    CHECK(COUNT_KV(map, 40, 2) == 1);
    CHECK(COUNT_KV(map, 50, 2) == 1);
    CHECK(COUNT_KV(map, 50, 3) == 1);
    CHECK(COUNT_KV(map, 50, 4) == 1);
    CHECK(COUNT_KV(map, 60, 2) == 1);
}
END_TEST()

BEGIN_TEST("Test key_eq()")
{
    {
        using key_type = xint;
        using mapped_type = xint;
        constexpr std::size_t N = 32;
        using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

        map_type map;

        auto key_eq = map.key_eq();

        CHECK(key_eq(10, 10) == true);
        CHECK(key_eq(10, 20) == false);
        CHECK(key_eq(20, 10) == false);
        CHECK(key_eq(20, 20) == true);
    }

    #if !(defined(_MSC_VER) && defined(TEST_CPP20_CONSTEXPR)) // There is some weird bug in Visual C++ compiler
    {
        using key_type = xobj;
        using mapped_type = xint;
        constexpr std::size_t N = 32;
        using key_equal = xobj::equal;
        using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N, key_equal>;

        map_type map;

        auto key_eq = map.key_eq();

        CHECK(key_eq(xobj(10), 10) == true);
        CHECK(key_eq(xobj(10), 20) == false);
        CHECK(key_eq(xobj(20), 10) == false);
        CHECK(key_eq(xobj(20), 20) == true);
    }
    #endif
}
END_TEST()

BEGIN_TEST("Test begin, end, cbegin, cend")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);
    map.emplace(30, 1);

    // iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (it->first == 10 && it->second == 1)
            {
                ++count_10_1;
            }
            else if (it->first == 20 && it->second == 1)
            {
                ++count_20_1;
            }
            else if (it->first == 20 && it->second == 2)
            {
                ++count_20_2;
            }
            else if (it->first == 20 && it->second == 3)
            {
                ++count_20_3;
            }
            else if (it->first == 30 && it->second == 1)
            {
                ++count_30_1;
            }
            else
            {
                CHECK(false);
            }
        }

        CHECK(count_10_1 == 1);
        CHECK(count_20_1 == 1);
        CHECK(count_20_2 == 1);
        CHECK(count_20_3 == 1);
        CHECK(count_30_1 == 1);
    }

    // const_iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = map.cbegin(); it != map.cend(); ++it)
        {
            if (it->first == 10 && it->second == 1)
            {
                ++count_10_1;
            }
            else if (it->first == 20 && it->second == 1)
            {
                ++count_20_1;
            }
            else if (it->first == 20 && it->second == 2)
            {
                ++count_20_2;
            }
            else if (it->first == 20 && it->second == 3)
            {
                ++count_20_3;
            }
            else if (it->first == 30 && it->second == 1)
            {
                ++count_30_1;
            }
            else
            {
                CHECK(false);
            }
        }

        CHECK(count_10_1 == 1);
        CHECK(count_20_1 == 1);
        CHECK(count_20_2 == 1);
        CHECK(count_20_3 == 1);
        CHECK(count_30_1 == 1);
    }

    // iterator + const_iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = map.begin(); it != map.cend(); ++it)
        {
            if (it->first == 10 && it->second == 1)
            {
                ++count_10_1;
            }
            else if (it->first == 20 && it->second == 1)
            {
                ++count_20_1;
            }
            else if (it->first == 20 && it->second == 2)
            {
                ++count_20_2;
            }
            else if (it->first == 20 && it->second == 3)
            {
                ++count_20_3;
            }
            else if (it->first == 30 && it->second == 1)
            {
                ++count_30_1;
            }
            else
            {
                CHECK(false);
            }
        }

        CHECK(count_10_1 == 1);
        CHECK(count_20_1 == 1);
        CHECK(count_20_2 == 1);
        CHECK(count_20_3 == 1);
        CHECK(count_30_1 == 1);
    }
}
END_TEST()

BEGIN_TEST("Test find, count, contains")
{
    // xint, xint
    {
        using key_type = xint;
        using mapped_type = xint;
        constexpr std::size_t N = 32;
        using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

        map_type map;

        map.emplace(20, 1);
        map.emplace(40, 1);
        map.emplace(40, 2);
        map.emplace(60, 1);
        map.emplace(60, 2);
        map.emplace(60, 3);

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.find(10) == map.end());
        CHECK(map.find(20) != map.end());
        CHECK(map.find(30) == map.end());
        CHECK(map.find(40) != map.end());
        CHECK(map.find(50) == map.end());
        CHECK(map.find(60) != map.end());
        CHECK(map.find(70) == map.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.count(10) == 0);
        CHECK(map.count(20) == 1);
        CHECK(map.count(30) == 0);
        CHECK(map.count(40) == 2);
        CHECK(map.count(50) == 0);
        CHECK(map.count(60) == 3);
        CHECK(map.count(70) == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.contains(10) == false);
        CHECK(map.contains(20) == true);
        CHECK(map.contains(30) == false);
        CHECK(map.contains(40) == true);
        CHECK(map.contains(50) == false);
        CHECK(map.contains(60) == true);
        CHECK(map.contains(70) == false);
    }

    // xobj, xint
    {
        using key_type = xobj;
        using mapped_type = xint;
        constexpr std::size_t N = 32;
        using key_equal = xobj::equal;
        using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N, key_equal>;

        map_type map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.find(10) == map.end());
        CHECK(map.find(20) != map.end());
        CHECK(map.find(30) == map.end());
        CHECK(map.find(40) != map.end());
        CHECK(map.find(50) == map.end());
        CHECK(map.find(60) != map.end());
        CHECK(map.find(70) == map.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.count(10) == 0);
        CHECK(map.count(20) == 1);
        CHECK(map.count(30) == 0);
        CHECK(map.count(40) == 2);
        CHECK(map.count(50) == 0);
        CHECK(map.count(60) == 3);
        CHECK(map.count(70) == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.contains(10) == false);
        CHECK(map.contains(20) == true);
        CHECK(map.contains(30) == false);
        CHECK(map.contains(40) == true);
        CHECK(map.contains(50) == false);
        CHECK(map.contains(60) == true);
        CHECK(map.contains(70) == false);
    }
}
END_TEST()

BEGIN_TEST("Test emplace(Args&&...)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.emplace(10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.emplace(10, 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test emplace_hint(const_iterator, Args&&...)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.emplace_hint(map.begin(), 10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.emplace_hint(map.begin(), 10, 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const value_type&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = map.insert(value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = map.insert(value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(value_type&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(std::move(value_10_1));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_1.first  == -10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(std::move(value_10_2));

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);

        CHECK(value_10_2.first  == -10);
        CHECK(value_10_2.second == -2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(P&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<long, long>;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const value_type&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = map.insert(map.begin(), value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = map.insert(map.begin(), value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, value_type&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(map.begin(), std::move(value_10_1));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_1.first  == -10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(map.begin(), std::move(value_10_2));

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);

        CHECK(value_10_2.first  == -10);
        CHECK(value_10_2.second == -2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, P&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<long, long>;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(map.begin(), value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(map.begin(), value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(InputIt, InputIt")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map.insert(data.begin(), data.end());

    CHECK(map.size() == 5);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test insert(std::initializer_list")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    CHECK(map.size() == 0);

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    map.insert(ilist);

    CHECK(map.size() == 5);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test insert_range(Range&&")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        map_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::istream<std::pair<xint, xint>>(iss));
        #else
        map.insert_range(sfl::test::istream_view<std::pair<xint, xint>>(iss));
        #endif

        CHECK(map.size() == 5);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename map_type::value_type> data
        (
            {
                {10, 1},
                {20, 1},
                {30, 1},
                {20, 2},
                {20, 3}
            }
        );

        map_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::all(data));
        #else
        map.insert_range(data);
        #endif

        CHECK(map.size() == 5);
        CHECK(COUNT_KV(map, 10, 1) == 1);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 20, 2) == 1);
        CHECK(COUNT_KV(map, 20, 3) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    {
        auto it = map.begin();
        while (it != map.end())
        {
            if (it->first == 10)
            {
                break;
            }
            ++it;
        }

        const auto res = map.erase(it);

        if (res != map.end())
        {
            CHECK(res->first == 20 || res->first == 30);
        }

        CHECK(map.size() == 2);
        CHECK(COUNT_KV(map, 20, 1) == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }

    {
        auto it = map.begin();
        while (it != map.end())
        {
            if (it->first == 20)
            {
                break;
            }
            ++it;
        }

        const auto res = map.erase(it);

        if (res != map.end())
        {
            CHECK(res->first == 30);
        }

        CHECK(map.size() == 1);
        CHECK(COUNT_KV(map, 30, 1) == 1);
    }

    {
        auto it = map.begin();
        while (it != map.end())
        {
            if (it->first == 30)
            {
                break;
            }
            ++it;
        }

        const auto res = map.erase(it);

        CHECK(res == map.end());
        CHECK(map.size() == 0);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    auto it = map.begin();
    while (it != map.end())
    {
        if (it->first == 20)
        {
            break;
        }
        ++it;
    }

    const auto res = map.erase(it, std::next(it));

    if (res != map.end())
    {
        CHECK(res->first == 10 || res->first == 30);
    }

    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test erase(const Key&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);
    map.emplace(30, 1);

    CHECK(map.size() == 5);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 3);
    CHECK(map.count(30) == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 4);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 3);

    CHECK(map.erase(20) == 3);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(map.count(10) == 1);

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);
    CHECK(map.size() == 0);
}
END_TEST()

BEGIN_TEST("Test erase(K&&)")
{
    using key_type = xobj;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using key_equal = xobj::equal;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N, key_equal>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(2));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(3));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.size() == 5);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 3);
    CHECK(map.count(30) == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 4);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 3);

    CHECK(map.erase(20) == 3);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(map.count(10) == 1);

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);
    CHECK(map.size() == 0);
}
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);
    map2.emplace(70, 2);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 4);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);
    CHECK(COUNT_KV(map2, 70, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    map1.swap(map2);

    CHECK(map1.size() == 4);
    CHECK(COUNT_KV(map1, 40, 2) == 1);
    CHECK(COUNT_KV(map1, 50, 2) == 1);
    CHECK(COUNT_KV(map1, 60, 2) == 1);
    CHECK(COUNT_KV(map1, 70, 2) == 1);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    map1.swap(map2);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 4);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);
    CHECK(COUNT_KV(map2, 70, 2) == 1);
}
END_TEST()

#ifndef TEST_CPP20_CONSTEXPR
BEGIN_TEST("Test data()")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
    CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
    CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    auto data = map.data();
    CHECK(data->first == 10); CHECK(data->second == 1); ++data;
    CHECK(data->first == 20); CHECK(data->second == 1); ++data;
    CHECK(data->first == 30); CHECK(data->second == 1); ++data;
}
END_TEST()
#endif // TEST_CPP20_CONSTEXPR

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    map2.emplace(10, 1);
    map2.emplace(20, 1);
    map2.emplace(30, 1);
    map2.emplace(40, 1);
    map2.emplace(50, 1);

    CHECK((map1 == map1) == true);
    CHECK((map1 == map2) == false);
    CHECK((map2 == map1) == false);
    CHECK((map2 == map2) == true);

    CHECK((map1 != map1) == false);
    CHECK((map1 != map2) == true);
    CHECK((map2 != map1) == true);
    CHECK((map2 != map2) == false);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER swap(container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);
    map2.emplace(70, 2);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 4);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);
    CHECK(COUNT_KV(map2, 70, 2) == 1);

    ///////////////////////////////////////////////////////////////////////////

    swap(map1, map2);

    CHECK(map1.size() == 4);
    CHECK(COUNT_KV(map1, 40, 2) == 1);
    CHECK(COUNT_KV(map1, 50, 2) == 1);
    CHECK(COUNT_KV(map1, 60, 2) == 1);
    CHECK(COUNT_KV(map1, 70, 2) == 1);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase_if(container&, Predicate)")
{
    using key_type = xint;
    using mapped_type = xint;
    constexpr std::size_t N = 32;
    using map_type = sfl::static_unordered_linear_multimap<key_type, mapped_type, N>;

    using const_reference = typename map_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);

    CHECK(map.size() == 5);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 3);
    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

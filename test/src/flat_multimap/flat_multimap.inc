#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xobj;

BEGIN_TEST("Test container()")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}
END_TEST()

BEGIN_TEST("Test container(const Compare&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::key_compare comp;

    map_type map(comp);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}
END_TEST()

BEGIN_TEST("Test container(const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::allocator_type alloc;

    map_type map(alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}
END_TEST()

BEGIN_TEST("Test container(const Compare&, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(comp, alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map(data.begin(), data.end());

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    typename map_type::key_compare comp;

    map_type map(data.begin(), data.end(), comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1010},
        {20, 1020},
        {30, 1030},
        {40, 1040},
        {50, 1050},
        {10, 2010},
        {20, 2020},
        {30, 2030},
        {40, 2040},
        {50, 2050},
        {10, 3010},
        {20, 3020},
        {30, 3030},
        {40, 3040},
        {50, 3050}
    };

    map_type map(ilist);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1010},
        {20, 1020},
        {30, 1030},
        {40, 1040},
        {50, 1050},
        {10, 2010},
        {20, 2020},
        {30, 2030},
        {40, 2040},
        {50, 2050},
        {10, 3010},
        {20, 3020},
        {30, 3030},
        {40, 3040},
        {50, 3050}
    };

    typename map_type::key_compare comp;

    map_type map(ilist, comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1010},
        {20, 1020},
        {30, 1030},
        {40, 1040},
        {50, 1050},
        {10, 2010},
        {20, 2020},
        {30, 2030},
        {40, 2040},
        {50, 2050},
        {10, 3010},
        {20, 3020},
        {30, 3030},
        {40, 3040},
        {50, 3050}
    };

    typename map_type::allocator_type alloc;

    map_type map(ilist, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1010},
        {20, 1020},
        {30, 1030},
        {40, 1040},
        {50, 1050},
        {10, 2010},
        {20, 2020},
        {30, 2030},
        {40, 2040},
        {50, 2050},
        {10, 3010},
        {20, 3020},
        {30, 3030},
        {40, 3040},
        {50, 3050}
    };

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(ilist, comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 15);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 15);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);
    CHECK(COUNT_KV(map1, 40, 2040) == 1);
    CHECK(COUNT_KV(map1, 50, 2050) == 1);
    CHECK(COUNT_KV(map1, 10, 3010) == 1);
    CHECK(COUNT_KV(map1, 20, 3020) == 1);
    CHECK(COUNT_KV(map1, 30, 3030) == 1);
    CHECK(COUNT_KV(map1, 40, 3040) == 1);
    CHECK(COUNT_KV(map1, 50, 3050) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map_type map2(map1);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 15);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 10, 3010) == 1);
    CHECK(COUNT_KV(map2, 20, 3020) == 1);
    CHECK(COUNT_KV(map2, 30, 3030) == 1);
    CHECK(COUNT_KV(map2, 40, 3040) == 1);
    CHECK(COUNT_KV(map2, 50, 3050) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(const container&, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 15);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);
    CHECK(COUNT_KV(map1, 40, 2040) == 1);
    CHECK(COUNT_KV(map1, 50, 2050) == 1);
    CHECK(COUNT_KV(map1, 10, 3010) == 1);
    CHECK(COUNT_KV(map1, 20, 3020) == 1);
    CHECK(COUNT_KV(map1, 30, 3030) == 1);
    CHECK(COUNT_KV(map1, 40, 3040) == 1);
    CHECK(COUNT_KV(map1, 50, 3050) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(map1, alloc);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 15);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 10, 3010) == 1);
    CHECK(COUNT_KV(map2, 20, 3020) == 1);
    CHECK(COUNT_KV(map2, 30, 3030) == 1);
    CHECK(COUNT_KV(map2, 40, 3040) == 1);
    CHECK(COUNT_KV(map2, 50, 3050) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 15);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);
    CHECK(COUNT_KV(map1, 40, 2040) == 1);
    CHECK(COUNT_KV(map1, 50, 2050) == 1);
    CHECK(COUNT_KV(map1, 10, 3010) == 1);
    CHECK(COUNT_KV(map1, 20, 3020) == 1);
    CHECK(COUNT_KV(map1, 30, 3030) == 1);
    CHECK(COUNT_KV(map1, 40, 3040) == 1);
    CHECK(COUNT_KV(map1, 50, 3050) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map_type map2(std::move(map1));

    CHECK(map1.empty() == true);
    CHECK(map1.size() == 0);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 15);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 10, 3010) == 1);
    CHECK(COUNT_KV(map2, 20, 3020) == 1);
    CHECK(COUNT_KV(map2, 30, 3030) == 1);
    CHECK(COUNT_KV(map2, 40, 3040) == 1);
    CHECK(COUNT_KV(map2, 50, 3050) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(container&&, const Allocator&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 15);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);
    CHECK(COUNT_KV(map1, 40, 2040) == 1);
    CHECK(COUNT_KV(map1, 50, 2050) == 1);
    CHECK(COUNT_KV(map1, 10, 3010) == 1);
    CHECK(COUNT_KV(map1, 20, 3020) == 1);
    CHECK(COUNT_KV(map1, 30, 3030) == 1);
    CHECK(COUNT_KV(map1, 40, 3040) == 1);
    CHECK(COUNT_KV(map1, 50, 3050) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(std::move(map1), alloc);

    if (map1.size() == 15)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(map1, -10, -1010) == 1);
        CHECK(COUNT_KV(map1, -20, -1020) == 1);
        CHECK(COUNT_KV(map1, -30, -1030) == 1);
        CHECK(COUNT_KV(map1, -40, -1040) == 1);
        CHECK(COUNT_KV(map1, -50, -1050) == 1);
        CHECK(COUNT_KV(map1, -10, -2010) == 1);
        CHECK(COUNT_KV(map1, -20, -2020) == 1);
        CHECK(COUNT_KV(map1, -30, -2030) == 1);
        CHECK(COUNT_KV(map1, -40, -2040) == 1);
        CHECK(COUNT_KV(map1, -50, -2050) == 1);
        CHECK(COUNT_KV(map1, -10, -3010) == 1);
        CHECK(COUNT_KV(map1, -20, -3020) == 1);
        CHECK(COUNT_KV(map1, -30, -3030) == 1);
        CHECK(COUNT_KV(map1, -40, -3040) == 1);
        CHECK(COUNT_KV(map1, -50, -3050) == 1);
    }
    else
    {
        CHECK(map1.empty() == true);
        CHECK(map1.size() == 0);
    }

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 15);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 10, 3010) == 1);
    CHECK(COUNT_KV(map2, 20, 3020) == 1);
    CHECK(COUNT_KV(map2, 30, 3030) == 1);
    CHECK(COUNT_KV(map2, 40, 3040) == 1);
    CHECK(COUNT_KV(map2, 50, 3050) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data1
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {10, 2010},
            {20, 2020},
            {30, 2030}
        }
    );

    std::vector<typename map_type::value_type> data2
    (
        {
            {40, 1040},
            {50, 1050},
            {60, 1060},
            {40, 2040},
            {50, 2050},
            {60, 2060}
        }
    );

    map_type map1(data1.begin(), data1.end());
    map_type map2(data2.begin(), data2.end());

    CHECK(map1.size() == 6);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 6);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 60, 1060) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 60, 2060) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map2 = map1;

    CHECK(map1.size() == 6);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 6);
    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data1
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {10, 2010},
            {20, 2020},
            {30, 2030}
        }
    );

    std::vector<typename map_type::value_type> data2
    (
        {
            {40, 1040},
            {50, 1050},
            {60, 1060},
            {40, 2040},
            {50, 2050},
            {60, 2060}
        }
    );

    map_type map1(data1.begin(), data1.end());
    map_type map2(data2.begin(), data2.end());

    CHECK(map1.size() == 6);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 1);
    CHECK(COUNT_KV(map1, 20, 2020) == 1);
    CHECK(COUNT_KV(map1, 30, 2030) == 1);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 6);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 60, 1060) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 1);
    CHECK(COUNT_KV(map2, 50, 2050) == 1);
    CHECK(COUNT_KV(map2, 60, 2060) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map2 = std::move(map1);

    if (map1.size() == 6)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(map1, -10, -1010) == 1);
        CHECK(COUNT_KV(map1, -20, -1020) == 1);
        CHECK(COUNT_KV(map1, -30, -1030) == 1);
        CHECK(COUNT_KV(map1, -10, -2010) == 1);
        CHECK(COUNT_KV(map1, -20, -2020) == 1);
        CHECK(COUNT_KV(map1, -30, -2030) == 1);
    }
    else
    {
        CHECK(map1.size() == 0);
    }

    CHECK(map2.size() == 6);
    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 1);
    CHECK(COUNT_KV(map2, 20, 2020) == 1);
    CHECK(COUNT_KV(map2, 30, 2030) == 1);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {10, 2010},
            {20, 2020},
            {30, 2030}
        }
    );

    map_type map(data.begin(), data.end());

    CHECK(map.size() == 6);
    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    std::initializer_list<typename map_type::value_type> ilist
    {
        {40, 1040},
        {50, 1050},
        {60, 1060},
        {40, 2040},
        {50, 2050},
        {60, 2060}
    };

    map = ilist;

    CHECK(map.size() == 6);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 60, 1060) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 60, 2060) == 1);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test get_allocator()")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    auto alloc = map.get_allocator();

    (void)alloc;
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test key_comp()")
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto key_comp = map.key_comp();

        CHECK(key_comp(10, 10) == false);
        CHECK(key_comp(10, 20) == true);
        CHECK(key_comp(20, 10) == false);
        CHECK(key_comp(20, 20) == false);
    }

    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto key_comp = map.key_comp();

        CHECK(key_comp(xobj(10), 10) == false);
        CHECK(key_comp(xobj(10), 20) == true);
        CHECK(key_comp(xobj(20), 10) == false);
        CHECK(key_comp(xobj(20), 20) == false);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test value_comp()")
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto value_comp = map.value_comp();

        CHECK(value_comp({10, 1}, {10, 2}) == false);
        CHECK(value_comp({10, 1}, {20, 2}) == true);
        CHECK(value_comp({20, 1}, {10, 2}) == false);
        CHECK(value_comp({20, 1}, {20, 2}) == false);
    }

    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto value_comp = map.value_comp();

        CHECK(value_comp({xobj(10), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(10), 1}, {xobj(20), 2}) == true);
        CHECK(value_comp({xobj(20), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(20), 1}, {xobj(20), 2}) == false);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    ///////////////////////////////////////////////////////////////////////////

    auto it = map.begin();
    CHECK(it->first == 10); CHECK(it->second == 1); ++it;
    CHECK(it->first == 20); CHECK(it->second == 1); ++it;
    CHECK(it->first == 30); CHECK(it->second == 1); ++it;
    CHECK(it == map.end());

    ///////////////////////////////////////////////////////////////////////////

    auto cit = map.cbegin();
    CHECK(cit->first == 10); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 30); CHECK(cit->second == 1); ++cit;
    CHECK(cit == map.cend());

    ///////////////////////////////////////////////////////////////////////////

    auto rit = map.rbegin();
    CHECK(rit->first == 30); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 10); CHECK(rit->second == 1); ++rit;
    CHECK(rit == map.rend());

    ///////////////////////////////////////////////////////////////////////////

    auto crit = map.crbegin();
    CHECK(crit->first == 30); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 10); CHECK(crit->second == 1); ++crit;
    CHECK(crit == map.crend());

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
    CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
    CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.index_of(map.nth(0)) == 0);
    CHECK(map.index_of(map.nth(1)) == 1);
    CHECK(map.index_of(map.nth(2)) == 2);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test clear()")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1010);
    map.emplace(20, 1020);
    map.emplace(30, 1030);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);

    map.clear();

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
}
END_TEST()

BEGIN_TEST("Test emplace(Args&&...)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    map_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            const int key = elem;
            const int value = key + 1000 * (iter + 1);

            const auto res = map.emplace(key, value);

            ++size;

            // Check result
            CHECK(res != map.end());
            CHECK(res->first == key);
            CHECK(res->second == value);

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check ordering
            for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(map, key, key + 1000) == 1);
        CHECK(COUNT_KV(map, key, key + 2000) == 1);
        CHECK(COUNT_KV(map, key, key + 3000) == 1);
    }

    #else // C++20 constexpr

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(20, 2);
    map.emplace(30, 1);
    map.emplace(30, 2);
    map.emplace(30, 3);

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test emplace_hint(const_iterator, Args&&...)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initial elements
    std::vector<int> data1({10, 20, 30, 40});

    // Additional elements
    std::vector<int> data2({5, 10, 15, 20, 25, 30, 35, 40, 45});

    // Repeat test several times, but shuffle elements after each iteration
    for (int iter = 0; iter < 3; ++iter)
    {
        for (int insert_pos = 0; insert_pos <= int(data1.size()); ++insert_pos)
        {
            for (const auto& elem2 : data2)
            {
                map_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = map.end();

                    const auto res = map.emplace_hint(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.emplace_hint(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size() + 1));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
                else
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    map_type map;

    map.emplace_hint(map.end(), 10, 1);
    map.emplace_hint(map.end(), 20, 1);
    map.emplace_hint(map.end(), 20, 2);
    map.emplace_hint(map.end(), 30, 1);
    map.emplace_hint(map.end(), 30, 2);
    map.emplace_hint(map.end(), 30, 3);

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const value_type&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    map_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            const int key = elem;
            const int value = key + 1000 * (iter + 1);

            typename map_type::value_type key_value(key, value);

            const auto res = map.insert(key_value);

            ++size;

            // Check result
            CHECK(res != map.end());
            CHECK(res->first == key);
            CHECK(res->second == value);

            // Check original key-value
            CHECK(key_value.first == key);
            CHECK(key_value.second == value);

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check ordering
            for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(map, key, key + 1000) == 1);
        CHECK(COUNT_KV(map, key, key + 2000) == 1);
        CHECK(COUNT_KV(map, key, key + 3000) == 1);
    }

    #else // C++20 constexpr

    map_type map;

    using value_type = typename map_type::value_type;

    { const value_type value_10_1(10, 1); map.insert(value_10_1); }
    { const value_type value_20_1(20, 1); map.insert(value_20_1); }
    { const value_type value_20_2(20, 2); map.insert(value_20_2); }
    { const value_type value_30_1(30, 1); map.insert(value_30_1); }
    { const value_type value_30_2(30, 2); map.insert(value_30_2); }
    { const value_type value_30_3(30, 3); map.insert(value_30_3); }

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(value_type&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    map_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            const int key = elem;
            const int value = key + 1000 * (iter + 1);

            typename map_type::value_type key_value(key, value);

            const auto res = map.insert(std::move(key_value));

            ++size;

            // Check result
            CHECK(res != map.end());
            CHECK(res->first == key);
            CHECK(res->second == value);

            // Check original key-value
            CHECK(key_value.first == -key);
            CHECK(key_value.second == -value);

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check ordering
            for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(map, key, key + 1000) == 1);
        CHECK(COUNT_KV(map, key, key + 2000) == 1);
        CHECK(COUNT_KV(map, key, key + 3000) == 1);
    }

    #else // C++20 constexpr

    map_type map;

    using value_type = typename map_type::value_type;

    { value_type value_10_1(10, 1); map.insert(std::move(value_10_1)); }
    { value_type value_20_1(20, 1); map.insert(std::move(value_20_1)); }
    { value_type value_20_2(20, 2); map.insert(std::move(value_20_2)); }
    { value_type value_30_1(30, 1); map.insert(std::move(value_30_1)); }
    { value_type value_30_2(30, 2); map.insert(std::move(value_30_2)); }
    { value_type value_30_3(30, 3); map.insert(std::move(value_30_3)); }

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const value_type&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initial elements
    std::vector<int> data1({10, 20, 30, 40});

    // Additional elements
    std::vector<int> data2({5, 10, 15, 20, 25, 30, 35, 40, 45});

    // Repeat test several times, but shuffle elements after each iteration
    for (int iter = 0; iter < 3; ++iter)
    {
        for (int insert_pos = 0; insert_pos <= int(data1.size()); ++insert_pos)
        {
            for (const auto& elem2 : data2)
            {
                map_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename map_type::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = map.end();

                    const auto res = map.insert(hint, key_value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == elem1);
                    CHECK(key_value.second == elem1 + 1000);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename map_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert(hint, key_value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key-value
                    CHECK(key_value.first == elem2);
                    CHECK(key_value.second == elem2 + 2000);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size() + 1));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
                else
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    map_type map;

    using value_type = typename map_type::value_type;

    { const value_type value_10_1(10, 1); map.insert(map.end(), value_10_1); }
    { const value_type value_20_1(20, 1); map.insert(map.end(), value_20_1); }
    { const value_type value_20_2(20, 2); map.insert(map.end(), value_20_2); }
    { const value_type value_30_1(30, 1); map.insert(map.end(), value_30_1); }
    { const value_type value_30_2(30, 2); map.insert(map.end(), value_30_2); }
    { const value_type value_30_3(30, 3); map.insert(map.end(), value_30_3); }

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, value_type&&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initial elements
    std::vector<int> data1({10, 20, 30, 40});

    // Additional elements
    std::vector<int> data2({5, 10, 15, 20, 25, 30, 35, 40, 45});

    // Repeat test several times, but shuffle elements after each iteration
    for (int iter = 0; iter < 3; ++iter)
    {
        for (int insert_pos = 0; insert_pos <= int(data1.size()); ++insert_pos)
        {
            for (const auto& elem2 : data2)
            {
                map_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename map_type::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = map.end();

                    const auto res = map.insert(hint, std::move(key_value));

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == -elem1);
                    CHECK(key_value.second == -(elem1 + 1000));
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename map_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert(hint, std::move(key_value));

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key-value
                    CHECK(key_value.first == -elem2);
                    CHECK(key_value.second == -(elem2 + 2000));
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size() + 1));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
                else
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    map_type map;

    using value_type = typename map_type::value_type;

    { value_type value_10_1(10, 1); map.insert(map.end(), std::move(value_10_1)); }
    { value_type value_20_1(20, 1); map.insert(map.end(), std::move(value_20_1)); }
    { value_type value_20_2(20, 2); map.insert(map.end(), std::move(value_20_2)); }
    { value_type value_30_1(30, 1); map.insert(map.end(), std::move(value_30_1)); }
    { value_type value_30_2(30, 2); map.insert(map.end(), std::move(value_30_2)); }
    { value_type value_30_3(30, 3); map.insert(map.end(), std::move(value_30_3)); }

    CHECK(map.size() == 6);

    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 30, 3) == 1);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(InputIt, InputIt")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<typename map_type::value_type> data
    (
        {
            {10, 1010},
            {20, 1020},
            {30, 1030},
            {40, 1040},
            {50, 1050},
            {10, 2010},
            {20, 2020},
            {30, 2030},
            {40, 2040},
            {50, 2050},
            {10, 3010},
            {20, 3020},
            {30, 3030},
            {40, 3040},
            {50, 3050}
        }
    );

    map_type map;

    map.insert(data.begin(), data.end());

    CHECK(map.size() == 15);

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);
}
END_TEST()

BEGIN_TEST("Test insert(std::initializer_list")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1010},
        {20, 1020},
        {30, 1030},
        {40, 1040},
        {50, 1050},
        {10, 2010},
        {20, 2020},
        {30, 2030},
        {40, 2040},
        {50, 2050},
        {10, 3010},
        {20, 3020},
        {30, 3030},
        {40, 3040},
        {50, 3050}
    };

    map_type map;

    map.insert(ilist);

    CHECK(map.size() == 15);

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 1);
    CHECK(COUNT_KV(map, 20, 2020) == 1);
    CHECK(COUNT_KV(map, 30, 2030) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 1);
    CHECK(COUNT_KV(map, 50, 2050) == 1);
    CHECK(COUNT_KV(map, 10, 3010) == 1);
    CHECK(COUNT_KV(map, 20, 3020) == 1);
    CHECK(COUNT_KV(map, 30, 3030) == 1);
    CHECK(COUNT_KV(map, 40, 3040) == 1);
    CHECK(COUNT_KV(map, 50, 3050) == 1);
}
END_TEST()

BEGIN_TEST("Test insert_range(Range&&")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss
        (
            "10 1010 "
            "20 1020 "
            "30 1030 "
            "40 1040 "
            "50 1050 "
            "10 2010 "
            "20 2020 "
            "30 2030 "
            "40 2040 "
            "50 2050 "
            "10 3010 "
            "20 3020 "
            "30 3030 "
            "40 3040 "
            "50 3050 "
        );

        map_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::istream<typename map_type::value_type>(iss));
        #else
        map.insert_range(sfl::test::istream_view<typename map_type::value_type>(iss));
        #endif

        CHECK(map.size() == 15);

        CHECK(COUNT_KV(map, 10, 1010) == 1);
        CHECK(COUNT_KV(map, 20, 1020) == 1);
        CHECK(COUNT_KV(map, 30, 1030) == 1);
        CHECK(COUNT_KV(map, 40, 1040) == 1);
        CHECK(COUNT_KV(map, 50, 1050) == 1);
        CHECK(COUNT_KV(map, 10, 2010) == 1);
        CHECK(COUNT_KV(map, 20, 2020) == 1);
        CHECK(COUNT_KV(map, 30, 2030) == 1);
        CHECK(COUNT_KV(map, 40, 2040) == 1);
        CHECK(COUNT_KV(map, 50, 2050) == 1);
        CHECK(COUNT_KV(map, 10, 3010) == 1);
        CHECK(COUNT_KV(map, 20, 3020) == 1);
        CHECK(COUNT_KV(map, 30, 3030) == 1);
        CHECK(COUNT_KV(map, 40, 3040) == 1);
        CHECK(COUNT_KV(map, 50, 3050) == 1);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename map_type::value_type> data
        (
            {
                {10, 1010},
                {20, 1020},
                {30, 1030},
                {40, 1040},
                {50, 1050},
                {10, 2010},
                {20, 2020},
                {30, 2030},
                {40, 2040},
                {50, 2050},
                {10, 3010},
                {20, 3020},
                {30, 3030},
                {40, 3040},
                {50, 3050}
            }
        );

        map_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::all(data));
        #else
        map.insert_range(data);
        #endif

        CHECK(map.size() == 15);

        CHECK(COUNT_KV(map, 10, 1010) == 1);
        CHECK(COUNT_KV(map, 20, 1020) == 1);
        CHECK(COUNT_KV(map, 30, 1030) == 1);
        CHECK(COUNT_KV(map, 40, 1040) == 1);
        CHECK(COUNT_KV(map, 50, 1050) == 1);
        CHECK(COUNT_KV(map, 10, 2010) == 1);
        CHECK(COUNT_KV(map, 20, 2020) == 1);
        CHECK(COUNT_KV(map, 30, 2030) == 1);
        CHECK(COUNT_KV(map, 40, 2040) == 1);
        CHECK(COUNT_KV(map, 50, 2050) == 1);
        CHECK(COUNT_KV(map, 10, 3010) == 1);
        CHECK(COUNT_KV(map, 20, 3020) == 1);
        CHECK(COUNT_KV(map, 30, 3030) == 1);
        CHECK(COUNT_KV(map, 40, 3040) == 1);
        CHECK(COUNT_KV(map, 50, 3050) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos = 0; erase_pos < size; ++erase_pos)
        {
            map_type map;

            // Insert elements
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                map.emplace(elem, elem + 1000);
            }

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                CHECK(COUNT_KV(map, elem, elem + 1000) == 1);
            }

            ///////////////////////////////////////////////////////////////////

            // Erase
            const auto it = NTH(map, erase_pos);
            map.erase(it);

            // Check size
            CHECK(int(map.size()) == int(size - 1));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                if (i == erase_pos)
                {
                    continue;
                }
                const auto& elem = data[i];
                CHECK(COUNT_KV(map, elem, elem + 1000) == 1);
            }
        }
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos1 = 0; erase_pos1 < size; ++erase_pos1)
        {
            for (int erase_pos2 = erase_pos1; erase_pos2 < size; ++erase_pos2)
            {
                map_type map;

                // Insert elements
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    map.emplace(elem, elem + 1000);
                }

                // Check size
                CHECK(int(map.size()) == int(size));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(map, elem, elem + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////////

                // Range to erase
                const auto it1 = NTH(map, erase_pos1);
                const auto it2 = NTH(map, erase_pos2);

                // Number of erased elements
                const int size_delta = int(std::distance(it1, it2));

                // Erase
                map.erase(it1, it2);

                // Check size
                CHECK(int(map.size()) == int(size - size_delta));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    if (i >= erase_pos1 && i < erase_pos2)
                    {
                        continue;
                    }
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(map, elem, elem + 1000) == 1);
                }
            }
        }
    }
}
END_TEST()

BEGIN_TEST("Test erase(const Key&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);
    map.emplace(30, 4);
    map.emplace(30, 5);
    map.emplace(30, 6);

    CHECK(map.size() == 6);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 4) == 1);
    CHECK(COUNT_KV(map, 30, 5) == 1);
    CHECK(COUNT_KV(map, 30, 6) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(30) == 3);
    CHECK(map.erase(30) == 0);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 1);
    CHECK(COUNT_KV(map, 30, 4) == 0);
    CHECK(COUNT_KV(map, 30, 5) == 0);
    CHECK(COUNT_KV(map, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(20) == 2);
    CHECK(map.erase(20) == 0);

    CHECK(map.size() == 1);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 4) == 0);
    CHECK(COUNT_KV(map, 30, 5) == 0);
    CHECK(COUNT_KV(map, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);

    CHECK(map.size() == 0);
    CHECK(COUNT_KV(map, 10, 1) == 0);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 4) == 0);
    CHECK(COUNT_KV(map, 30, 5) == 0);
    CHECK(COUNT_KV(map, 30, 6) == 0);
}
END_TEST()

BEGIN_TEST("Test erase(K&&)")
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_compare = xobj::less;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(2));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(3));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(4));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(5));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(6));

    CHECK(map.size() == 6);
    for (const auto& p : map)
    {
        CHECK(p.first.value() == 10 || p.first.value() == 20 || p.first.value() == 30);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(30) == 3);
    CHECK(map.erase(30) == 0);

    CHECK(map.size() == 3);
    for (const auto& p : map)
    {
        CHECK(p.first.value() == 10 || p.first.value() == 20);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(20) == 2);
    CHECK(map.erase(20) == 0);

    CHECK(map.size() == 1);
    for (const auto& p : map)
    {
        CHECK(p.first.value() == 10);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);

    CHECK(map.size() == 0);
}
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

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

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test lower_bound, upper_bound, equal_range, find, count, contains")
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(20, 2);
        map.emplace(30, 1);
        map.emplace(30, 2);
        map.emplace(30, 3);

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = map.lower_bound(x);
                auto it2 = map.upper_bound(x);

                CHECK(std::distance(it1, it2) == (x == 10 ? 1 : x == 20 ? 2 : 3));

                auto er = map.equal_range(x);

                CHECK(er.first == it1);
                CHECK(er.second == it2);

                while (it1 != it2)
                {
                    CHECK(it1->first == x);
                    ++it1;
                }
            }

            // Check find
            {
                auto it = map.find(x);
                CHECK(it != map.end());
                CHECK(it->first == x);
            }

            // Check count
            CHECK(map.count(x) == (x == 10 ? 1 : x == 20 ? 2 : 3));

            // Check contains
            CHECK(map.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = map.lower_bound(x);
                auto it2 = map.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = map.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = map.find(x);
                CHECK(it == map.end());
            }

            // Check count
            CHECK(map.count(x) == 0);

            // Check contains
            CHECK(map.contains(x) == false);
        }
    }

    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
        using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(3));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(4));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(5));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(6));

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = map.lower_bound(x);
                auto it2 = map.upper_bound(x);

                CHECK(std::distance(it1, it2) == (x == 10 ? 1 : x == 20 ? 2 : 3));

                auto er = map.equal_range(x);

                CHECK(er.first == it1);
                CHECK(er.second == it2);

                while (it1 != it2)
                {
                    CHECK(it1->first.value() == x);
                    ++it1;
                }
            }

            // Check find
            {
                auto it = map.find(x);
                CHECK(it != map.end());
                CHECK(it->first.value() == x);
            }

            // Check count
            CHECK(map.count(x) == (x == 10 ? 1 : x == 20 ? 2 : 3));

            // Check contains
            CHECK(map.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = map.lower_bound(x);
                auto it2 = map.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = map.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = map.find(x);
                CHECK(it == map.end());
            }

            // Check count
            CHECK(map.count(x) == 0);

            // Check contains
            CHECK(map.contains(x) == false);
        }
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test data()")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(std::next(map.data(), 0)->first == 10); CHECK(std::next(map.data(), 0)->second == 1);
    CHECK(std::next(map.data(), 1)->first == 20); CHECK(std::next(map.data(), 1)->second == 1);
    CHECK(std::next(map.data(), 2)->first == 30); CHECK(std::next(map.data(), 2)->second == 1);

    const auto& cref = map;

    CHECK(cref.size() == 3);
    CHECK(std::next(cref.data(), 0)->first == 10); CHECK(std::next(cref.data(), 0)->second == 1);
    CHECK(std::next(cref.data(), 1)->first == 20); CHECK(std::next(cref.data(), 1)->second == 1);
    CHECK(std::next(cref.data(), 2)->first == 30); CHECK(std::next(cref.data(), 2)->second == 1);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

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

    CHECK((map1 < map1) == false);
    CHECK((map1 < map2) == true);
    CHECK((map2 < map1) == false);
    CHECK((map2 < map2) == false);

    CHECK((map1 > map1) == false);
    CHECK((map1 > map2) == false);
    CHECK((map2 > map1) == true);
    CHECK((map2 > map2) == false);

    CHECK((map1 <= map1) == true);
    CHECK((map1 <= map2) == true);
    CHECK((map2 <= map1) == false);
    CHECK((map2 <= map2) == true);

    CHECK((map1 >= map1) == true);
    CHECK((map1 >= map2) == false);
    CHECK((map2 >= map1) == true);
    CHECK((map2 >= map2) == true);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER swap(container&)")
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);
    map2.emplace(70, 2);
    map2.emplace(80, 2);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 5);
    CHECK(COUNT_KV(map2, 40, 2) == 1);
    CHECK(COUNT_KV(map2, 50, 2) == 1);
    CHECK(COUNT_KV(map2, 60, 2) == 1);
    CHECK(COUNT_KV(map2, 70, 2) == 1);
    CHECK(COUNT_KV(map2, 80, 2) == 1);

    ///////////////////////////////////////////////////////////////////////////

    swap(map1, map2);

    CHECK(map1.size() == 5);
    CHECK(COUNT_KV(map1, 40, 2) == 1);
    CHECK(COUNT_KV(map1, 50, 2) == 1);
    CHECK(COUNT_KV(map1, 60, 2) == 1);
    CHECK(COUNT_KV(map1, 70, 2) == 1);
    CHECK(COUNT_KV(map1, 80, 2) == 1);

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
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<std::pair<key_type, mapped_type>>;
    using map_type = sfl::flat_multimap<key_type, mapped_type, key_compare, allocator_type>;

    using const_reference = typename map_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 1);
    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_TEST()

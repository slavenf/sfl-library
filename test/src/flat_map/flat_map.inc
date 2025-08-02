#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xobj;

PRINT("Test container()");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}

PRINT("Test container(const Compare&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    typename container_type::key_compare comp;

    container_type map(comp);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}

PRINT("Test container(const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    typename container_type::allocator_type alloc;

    container_type map(alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}

PRINT("Test container(const Compare&, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    typename container_type::key_compare comp;

    typename container_type::allocator_type alloc;

    container_type map(comp, alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());
}

PRINT("Test container(InputIt, InputIt)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map(data.begin(), data.end());

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(InputIt, InputIt, const Compare&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    typename container_type::key_compare comp;

    container_type map(data.begin(), data.end(), comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(InputIt, InputIt, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    typename container_type::allocator_type alloc;

    container_type map(data.begin(), data.end(), alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(InputIt, InputIt, const Compare&, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    typename container_type::key_compare comp;

    typename container_type::allocator_type alloc;

    container_type map(data.begin(), data.end(), comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(std::initializer_list)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::initializer_list<typename container_type::value_type> ilist
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

    container_type map(ilist);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(std::initializer_list, const Compare&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::initializer_list<typename container_type::value_type> ilist
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

    typename container_type::key_compare comp;

    container_type map(ilist, comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(std::initializer_list, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::initializer_list<typename container_type::value_type> ilist
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

    typename container_type::allocator_type alloc;

    container_type map(ilist, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(std::initializer_list, const Compare&, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::initializer_list<typename container_type::value_type> ilist
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

    typename container_type::key_compare comp;

    typename container_type::allocator_type alloc;

    container_type map(ilist, comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 5);
    CHECK(map.max_size() > 0);
    CHECK(map.available() == map.capacity() - map.size());

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(const container&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 5);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);
    CHECK(COUNT_KV(map1, 40, 2040) == 0);
    CHECK(COUNT_KV(map1, 50, 2050) == 0);
    CHECK(COUNT_KV(map1, 10, 3010) == 0);
    CHECK(COUNT_KV(map1, 20, 3020) == 0);
    CHECK(COUNT_KV(map1, 30, 3030) == 0);
    CHECK(COUNT_KV(map1, 40, 3040) == 0);
    CHECK(COUNT_KV(map1, 50, 3050) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    container_type map2(map1);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 5);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 10, 3010) == 0);
    CHECK(COUNT_KV(map2, 20, 3020) == 0);
    CHECK(COUNT_KV(map2, 30, 3030) == 0);
    CHECK(COUNT_KV(map2, 40, 3040) == 0);
    CHECK(COUNT_KV(map2, 50, 3050) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(const container&, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 5);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);
    CHECK(COUNT_KV(map1, 40, 2040) == 0);
    CHECK(COUNT_KV(map1, 50, 2050) == 0);
    CHECK(COUNT_KV(map1, 10, 3010) == 0);
    CHECK(COUNT_KV(map1, 20, 3020) == 0);
    CHECK(COUNT_KV(map1, 30, 3030) == 0);
    CHECK(COUNT_KV(map1, 40, 3040) == 0);
    CHECK(COUNT_KV(map1, 50, 3050) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename container_type::allocator_type alloc;

    container_type map2(map1, alloc);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 5);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 10, 3010) == 0);
    CHECK(COUNT_KV(map2, 20, 3020) == 0);
    CHECK(COUNT_KV(map2, 30, 3030) == 0);
    CHECK(COUNT_KV(map2, 40, 3040) == 0);
    CHECK(COUNT_KV(map2, 50, 3050) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(container&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 5);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);
    CHECK(COUNT_KV(map1, 40, 2040) == 0);
    CHECK(COUNT_KV(map1, 50, 2050) == 0);
    CHECK(COUNT_KV(map1, 10, 3010) == 0);
    CHECK(COUNT_KV(map1, 20, 3020) == 0);
    CHECK(COUNT_KV(map1, 30, 3030) == 0);
    CHECK(COUNT_KV(map1, 40, 3040) == 0);
    CHECK(COUNT_KV(map1, 50, 3050) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    container_type map2(std::move(map1));

    CHECK(map1.empty() == true);
    CHECK(map1.size() == 0);

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 5);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 10, 3010) == 0);
    CHECK(COUNT_KV(map2, 20, 3020) == 0);
    CHECK(COUNT_KV(map2, 30, 3030) == 0);
    CHECK(COUNT_KV(map2, 40, 3040) == 0);
    CHECK(COUNT_KV(map2, 50, 3050) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test container(container&&, const Allocator&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map1(data.begin(), data.end());

    CHECK(map1.empty() == false);
    CHECK(map1.size() == 5);
    CHECK(map1.max_size() > 0);
    CHECK(map1.available() == map1.capacity() - map1.size());

    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 40, 1040) == 1);
    CHECK(COUNT_KV(map1, 50, 1050) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);
    CHECK(COUNT_KV(map1, 40, 2040) == 0);
    CHECK(COUNT_KV(map1, 50, 2050) == 0);
    CHECK(COUNT_KV(map1, 10, 3010) == 0);
    CHECK(COUNT_KV(map1, 20, 3020) == 0);
    CHECK(COUNT_KV(map1, 30, 3030) == 0);
    CHECK(COUNT_KV(map1, 40, 3040) == 0);
    CHECK(COUNT_KV(map1, 50, 3050) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename container_type::allocator_type alloc;

    container_type map2(std::move(map1), alloc);

    if (map1.size() == 5)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(map1, -10, -1010) == 1);
        CHECK(COUNT_KV(map1, -20, -1020) == 1);
        CHECK(COUNT_KV(map1, -30, -1030) == 1);
        CHECK(COUNT_KV(map1, -40, -1040) == 1);
        CHECK(COUNT_KV(map1, -50, -1050) == 1);
        CHECK(COUNT_KV(map1, -10, -2010) == 0);
        CHECK(COUNT_KV(map1, -20, -2020) == 0);
        CHECK(COUNT_KV(map1, -30, -2030) == 0);
        CHECK(COUNT_KV(map1, -40, -2040) == 0);
        CHECK(COUNT_KV(map1, -50, -2050) == 0);
        CHECK(COUNT_KV(map1, -10, -3010) == 0);
        CHECK(COUNT_KV(map1, -20, -3020) == 0);
        CHECK(COUNT_KV(map1, -30, -3030) == 0);
        CHECK(COUNT_KV(map1, -40, -3040) == 0);
        CHECK(COUNT_KV(map1, -50, -3050) == 0);
    }
    else
    {
        CHECK(map1.empty() == true);
        CHECK(map1.size() == 0);
    }

    CHECK(map2.empty() == false);
    CHECK(map2.size() == 5);
    CHECK(map2.max_size() > 0);
    CHECK(map2.available() == map2.capacity() - map2.size());

    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 10, 3010) == 0);
    CHECK(COUNT_KV(map2, 20, 3020) == 0);
    CHECK(COUNT_KV(map2, 30, 3030) == 0);
    CHECK(COUNT_KV(map2, 40, 3040) == 0);
    CHECK(COUNT_KV(map2, 50, 3050) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test operator=(const container&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data1
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

    std::vector<typename container_type::value_type> data2
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

    container_type map1(data1.begin(), data1.end());
    container_type map2(data2.begin(), data2.end());

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 60, 1060) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 60, 2060) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map2 = map1;

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test operator=(container&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data1
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

    std::vector<typename container_type::value_type> data2
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

    container_type map1(data1.begin(), data1.end());
    container_type map2(data2.begin(), data2.end());

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1010) == 1);
    CHECK(COUNT_KV(map1, 20, 1020) == 1);
    CHECK(COUNT_KV(map1, 30, 1030) == 1);
    CHECK(COUNT_KV(map1, 10, 2010) == 0);
    CHECK(COUNT_KV(map1, 20, 2020) == 0);
    CHECK(COUNT_KV(map1, 30, 2030) == 0);

    for (auto it1 = map1.begin(), it2 = std::next(it1); it2 != map1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 40, 1040) == 1);
    CHECK(COUNT_KV(map2, 50, 1050) == 1);
    CHECK(COUNT_KV(map2, 60, 1060) == 1);
    CHECK(COUNT_KV(map2, 40, 2040) == 0);
    CHECK(COUNT_KV(map2, 50, 2050) == 0);
    CHECK(COUNT_KV(map2, 60, 2060) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    map2 = std::move(map1);

    if (map1.size() == 3)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(map1, -10, -1010) == 1);
        CHECK(COUNT_KV(map1, -20, -1020) == 1);
        CHECK(COUNT_KV(map1, -30, -1030) == 1);
        CHECK(COUNT_KV(map1, -10, -2010) == 0);
        CHECK(COUNT_KV(map1, -20, -2020) == 0);
        CHECK(COUNT_KV(map1, -30, -2030) == 0);
    }
    else
    {
        CHECK(map1.size() == 0);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1010) == 1);
    CHECK(COUNT_KV(map2, 20, 1020) == 1);
    CHECK(COUNT_KV(map2, 30, 1030) == 1);
    CHECK(COUNT_KV(map2, 10, 2010) == 0);
    CHECK(COUNT_KV(map2, 20, 2020) == 0);
    CHECK(COUNT_KV(map2, 30, 2030) == 0);

    for (auto it1 = map2.begin(), it2 = std::next(it1); it2 != map2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

PRINT("Test operator=(const container&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map(data.begin(), data.end());

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    std::initializer_list<typename container_type::value_type> ilist
    {
        {40, 1040},
        {50, 1050},
        {60, 1060},
        {40, 2040},
        {50, 2050},
        {60, 2060}
    };

    map = ilist;

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 60, 1060) == 1);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 60, 2060) == 0);

    for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test get_allocator()");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    auto alloc = map.get_allocator();

    (void)alloc;
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test key_comp()");
{
    {
        using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

        container_type map;

        auto key_comp = map.key_comp();

        CHECK(key_comp(10, 10) == false);
        CHECK(key_comp(10, 20) == true);
        CHECK(key_comp(20, 10) == false);
        CHECK(key_comp(20, 20) == false);
    }

    {
        using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

        container_type map;

        auto key_comp = map.key_comp();

        CHECK(key_comp(xobj(10), 10) == false);
        CHECK(key_comp(xobj(10), 20) == true);
        CHECK(key_comp(xobj(20), 10) == false);
        CHECK(key_comp(xobj(20), 20) == false);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test value_comp()");
{
    {
        using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

        container_type map;

        auto value_comp = map.value_comp();

        CHECK(value_comp({10, 1}, {10, 2}) == false);
        CHECK(value_comp({10, 1}, {20, 2}) == true);
        CHECK(value_comp({20, 1}, {10, 2}) == false);
        CHECK(value_comp({20, 1}, {20, 2}) == false);
    }

    {
        using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

        container_type map;

        auto value_comp = map.value_comp();

        CHECK(value_comp({xobj(10), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(10), 1}, {xobj(20), 2}) == true);
        CHECK(value_comp({xobj(20), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(20), 1}, {xobj(20), 2}) == false);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test clear()");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    map.emplace(10, 1010);
    map.emplace(20, 1020);
    map.emplace(30, 1030);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);

    map.clear();

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
}

PRINT("Test emplace(Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test emplace_hint(const_iterator, Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

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
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test insert(const value_type&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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

            typename container_type::value_type key_value(key, value);

            const auto res = map.insert(key_value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test insert(value_type&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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

            typename container_type::value_type key_value(key, value);

            const auto res = map.insert(std::move(key_value));

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key-value
            CHECK(key_value.first == (iter == 0 ? -key : +key));
            CHECK(key_value.second == (iter == 0 ? -value : +value));

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test insert(P&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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

            std::pair<int, int> key_value(key, value);

            const auto res = map.insert(key_value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test insert(const_iterator, const value_type&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename container_type::value_type key_value(elem1, elem1 + 1000);

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
                    typename container_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert(hint, key_value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key-value
                    CHECK(key_value.first == elem2);
                    CHECK(key_value.second == elem2 + 2000);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test insert(const_iterator, value_type&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename container_type::value_type key_value(elem1, elem1 + 1000);

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
                    typename container_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert(hint, std::move(key_value));

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key-value
                    CHECK(key_value.first == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2));
                    CHECK(key_value.second == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2 + 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test insert(const_iterator, P&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    std::pair<int, int> key_value(elem1, elem1 + 1000);

                    const auto hint = map.end();

                    const auto res = map.insert(hint, key_value);

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
                    std::pair<int, int> key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert(hint, key_value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test insert(InputIt, InputIt");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::vector<typename container_type::value_type> data
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

    container_type map;

    map.insert(data.begin(), data.end());

    CHECK(map.size() == 5);

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);
}

PRINT("Test insert(std::initializer_list");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    std::initializer_list<typename container_type::value_type> ilist
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

    container_type map;

    map.insert(ilist);

    CHECK(map.size() == 5);

    CHECK(COUNT_KV(map, 10, 1010) == 1);
    CHECK(COUNT_KV(map, 20, 1020) == 1);
    CHECK(COUNT_KV(map, 30, 1030) == 1);
    CHECK(COUNT_KV(map, 40, 1040) == 1);
    CHECK(COUNT_KV(map, 50, 1050) == 1);
    CHECK(COUNT_KV(map, 10, 2010) == 0);
    CHECK(COUNT_KV(map, 20, 2020) == 0);
    CHECK(COUNT_KV(map, 30, 2030) == 0);
    CHECK(COUNT_KV(map, 40, 2040) == 0);
    CHECK(COUNT_KV(map, 50, 2050) == 0);
    CHECK(COUNT_KV(map, 10, 3010) == 0);
    CHECK(COUNT_KV(map, 20, 3020) == 0);
    CHECK(COUNT_KV(map, 30, 3030) == 0);
    CHECK(COUNT_KV(map, 40, 3040) == 0);
    CHECK(COUNT_KV(map, 50, 3050) == 0);
}

PRINT("Test insert_range(Range&&");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // Input iterator (exactly)
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

        container_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::istream<typename container_type::value_type>(iss));
        #else
        map.insert_range(sfl::test::istream_view<typename container_type::value_type>(iss));
        #endif

        CHECK(map.size() == 5);

        CHECK(COUNT_KV(map, 10, 1010) == 1);
        CHECK(COUNT_KV(map, 20, 1020) == 1);
        CHECK(COUNT_KV(map, 30, 1030) == 1);
        CHECK(COUNT_KV(map, 40, 1040) == 1);
        CHECK(COUNT_KV(map, 50, 1050) == 1);
        CHECK(COUNT_KV(map, 10, 2010) == 0);
        CHECK(COUNT_KV(map, 20, 2020) == 0);
        CHECK(COUNT_KV(map, 30, 2030) == 0);
        CHECK(COUNT_KV(map, 40, 2040) == 0);
        CHECK(COUNT_KV(map, 50, 2050) == 0);
        CHECK(COUNT_KV(map, 10, 3010) == 0);
        CHECK(COUNT_KV(map, 20, 3020) == 0);
        CHECK(COUNT_KV(map, 30, 3030) == 0);
        CHECK(COUNT_KV(map, 40, 3040) == 0);
        CHECK(COUNT_KV(map, 50, 3050) == 0);
    }

    // Forward iterator
    {
        std::vector<typename container_type::value_type> data
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

        container_type map;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        map.insert_range(std::views::all(data));
        #else
        map.insert_range(data);
        #endif

        CHECK(map.size() == 5);

        CHECK(COUNT_KV(map, 10, 1010) == 1);
        CHECK(COUNT_KV(map, 20, 1020) == 1);
        CHECK(COUNT_KV(map, 30, 1030) == 1);
        CHECK(COUNT_KV(map, 40, 1040) == 1);
        CHECK(COUNT_KV(map, 50, 1050) == 1);
        CHECK(COUNT_KV(map, 10, 2010) == 0);
        CHECK(COUNT_KV(map, 20, 2020) == 0);
        CHECK(COUNT_KV(map, 30, 2030) == 0);
        CHECK(COUNT_KV(map, 40, 2040) == 0);
        CHECK(COUNT_KV(map, 50, 2050) == 0);
        CHECK(COUNT_KV(map, 10, 3010) == 0);
        CHECK(COUNT_KV(map, 20, 3020) == 0);
        CHECK(COUNT_KV(map, 30, 3030) == 0);
        CHECK(COUNT_KV(map, 40, 3040) == 0);
        CHECK(COUNT_KV(map, 50, 3050) == 0);
    }
}

PRINT("Test insert_or_assign(const Key&, M&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            xint key = elem;
            const int value = elem + 1000 * (iter + 1);

            const auto res = map.insert_or_assign(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == value);

            // Check original key
            CHECK(key == elem);

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
        CHECK(COUNT_KV(map, key, key + 1000) == 0);
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 1);
    }
}

PRINT("Test insert_or_assign(Key&&, M&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            xint key = elem;
            const int value = elem + 1000 * (iter + 1);

            const auto res = map.insert_or_assign(std::move(key), value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == value);

            // Check original key
            CHECK(key == (iter == 0 ? -elem : +elem));

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
        CHECK(COUNT_KV(map, key, key + 1000) == 0);
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 1);
    }
}

PRINT("Test insert_or_assign(K&&, M&&)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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

            const auto res = map.insert_or_assign(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first.value() == key);
            CHECK(res.first->second == value);

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check ordering
            for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
            {
                CHECK(it1->first.value() <= it2->first.value());
            }
        }
    }
}

PRINT("Test insert_or_assign(const_iterator, const Key&, M&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    xint key = elem1;
                    const int value = elem1 + 1000;

                    const auto hint = map.end();

                    const auto res = map.insert_or_assign(hint, key, value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == elem1);
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
                    xint key = elem2;
                    const int value = elem2 + 2000;

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert_or_assign(hint, key, value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key
                    CHECK(key == elem2);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    if (elem1 == elem2 && CONTAINS(data2, elem1))
                    {
                        CHECK(COUNT_KV(map, elem1, elem1 + 2000) == 1);
                    }
                    else
                    {
                        CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                    }
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test insert_or_assign(const_iterator, Key&&, M&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    xint key = elem1;
                    const int value = elem1 + 1000;

                    const auto hint = map.end();

                    const auto res = map.insert_or_assign(hint, std::move(key), value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == -elem1);
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
                    xint key = elem2;
                    const int value = elem2 + 2000;

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert_or_assign(hint, std::move(key), value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key
                    CHECK(key == (CONTAINS(data1, elem2) ? +elem2 : -elem2));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    if (elem1 == elem2 && CONTAINS(data2, elem1))
                    {
                        CHECK(COUNT_KV(map, elem1, elem1 + 2000) == 1);
                    }
                    else
                    {
                        CHECK(COUNT_KV(map, elem1, elem1 + 1000) == 1);
                    }
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(map, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test insert_or_assign(const_iterator, K&&, M&&)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const int key = elem1;
                    const int value = elem1 + 1000;

                    const auto hint = map.end();

                    const auto res = map.insert_or_assign(hint, key, value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first.value() == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == elem1);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const int key = elem2;
                    const int value = elem2 + 2000;

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.insert_or_assign(hint, key, value);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first.value() == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key
                    CHECK(key == elem2);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test try_emplace(const Key&, Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            xint key = elem;
            const int value = elem + 1000 * (iter + 1);

            const auto res = map.try_emplace(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key
            CHECK(key == elem);

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test try_emplace(Key&&, Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

    int size = 0;

    // Insert same elements several times
    for (int iter = 0; iter < 3; ++iter)
    {
        // Shuffle elements before insert
        std::shuffle(data.begin(), data.end(), gen);

        // Insert elements into container
        for (const auto& elem : data)
        {
            xint key = elem;
            const int value = elem + 1000 * (iter + 1);

            const auto res = map.try_emplace(std::move(key), value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key
            CHECK(key == (iter == 0 ? -elem : +elem));

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
        CHECK(COUNT_KV(map, key, key + 2000) == 0);
        CHECK(COUNT_KV(map, key, key + 3000) == 0);
    }
}

PRINT("Test try_emplace(K&&, Args&&...)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    container_type map;

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
            const int value = elem + 1000 * (iter + 1);

            const auto res = map.try_emplace(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != map.end());
            CHECK(res.first->first.value() == elem);
            CHECK(res.first->second == elem + 1000);

            // Check size
            CHECK(int(map.size()) == int(size));

            // Check ordering
            for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
            {
                CHECK(it1->first.value() <= it2->first.value());
            }
        }
    }
}

PRINT("Test try_emplace(const_iterator, const Key&, Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    xint key = elem1;

                    const auto hint = map.end();

                    const auto res = map.try_emplace(hint, key, elem1 + 1000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == elem1);
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
                    xint key = elem2;

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.try_emplace(hint, key, elem2 + 2000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key
                    CHECK(key == elem2);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test try_emplace(const_iterator, Key&&, Args&&...)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    xint key = elem1;

                    const auto hint = map.end();

                    const auto res = map.try_emplace(hint, std::move(key), elem1 + 1000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == -elem1);
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
                    xint key = elem2;

                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.try_emplace(hint, std::move(key), elem2 + 2000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key
                    CHECK(key == (CONTAINS(data1, elem2) ? +elem2 : -elem2));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

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
                    CHECK(COUNT_KV(map, elem2, elem2 + 2000) == 0);
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
}

PRINT("Test try_emplace(const_iterator, K&&, Args&&...)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

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
                container_type map;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = map.end();

                    const auto res = map.try_emplace(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first.value() == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(map.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(map, insert_pos);

                    const auto res = map.try_emplace(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != map.end());
                    CHECK(res->first.value() == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(map.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(map.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = map.begin(), it2 = std::next(it1); it2 != map.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test erase(const_iterator)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos = 0; erase_pos < size; ++erase_pos)
        {
            container_type map;

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

PRINT("Test erase(const_iterator, const_iterator)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos1 = 0; erase_pos1 < size; ++erase_pos1)
        {
            for (int erase_pos2 = erase_pos1; erase_pos2 < size; ++erase_pos2)
            {
                container_type map;

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

PRINT("Test erase(const Key&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    map.emplace(10, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);
    map.emplace(30, 4);
    map.emplace(30, 5);
    map.emplace(30, 6);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 4) == 1);
    CHECK(COUNT_KV(map, 30, 5) == 0);
    CHECK(COUNT_KV(map, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);

    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 4) == 0);
    CHECK(COUNT_KV(map, 30, 5) == 0);
    CHECK(COUNT_KV(map, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(20) == 1);
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

PRINT("Test erase(K&&)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

    container_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(2));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(3));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(4));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(5));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(6));

    CHECK(map.size() == 3);
    for (const auto& p : map)
    {
        CHECK(p.first.value() == 10 || p.first.value() == 20 || p.first.value() == 30);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);

    CHECK(map.size() == 2);
    for (const auto& p : map)
    {
        CHECK(p.first.value() == 10 || p.first.value() == 20);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.erase(20) == 1);
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

PRINT("Test swap(container&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map1, map2;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test lower_bound, upper_bound, equal_range, find, count, contains");
{
    {
        using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

        container_type map;

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

                CHECK(std::distance(it1, it2) == 1);

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
            CHECK(map.count(x) == 1);

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
        using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

        container_type map;

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

                CHECK(std::distance(it1, it2) == 1);

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
            CHECK(map.count(x) == 1);

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test at(const Key&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.at(10) == 1);
    CHECK(map.at(20) == 1);
    CHECK(map.at(30) == 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    map.at(10) = 2;
    map.at(20) = 2;
    map.at(30) = 2;

    CHECK(map.at(10) == 2);
    CHECK(map.at(20) == 2);
    CHECK(map.at(30) == 2);

    #if !defined(SFL_NO_EXCEPTIONS)
    bool caught_exception = false;

    try
    {
        map.at(40) = 1;
    }
    catch (...)
    {
        caught_exception = true;
    }

    CHECK(caught_exception == true);
    #endif

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 2) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
}

PRINT("Test at(const K&)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

    container_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.at(10) == 1);
    CHECK(map.at(20) == 1);
    CHECK(map.at(30) == 1);

    auto count_kv = [](const container_type& map, const int k, const int v)
    {
        int n = 0;
        for (auto& kv : map)
        {
            if (kv.first.value() == k && kv.second == v)
            {
                ++n;
            }
        }
        return n;
    };

    CHECK(map.size() == 3);
    CHECK(count_kv(map, 10, 1) == 1);
    CHECK(count_kv(map, 20, 1) == 1);
    CHECK(count_kv(map, 30, 1) == 1);

    map.at(10) = 2;
    map.at(20) = 2;
    map.at(30) = 2;

    CHECK(map.at(10) == 2);
    CHECK(map.at(20) == 2);
    CHECK(map.at(30) == 2);

    #if !defined(SFL_NO_EXCEPTIONS)
    bool caught_exception = false;

    try
    {
        map.at(40) = 1;
    }
    catch (...)
    {
        caught_exception = true;
    }

    CHECK(caught_exception == true);
    #endif

    CHECK(map.size() == 3);
    CHECK(count_kv(map, 10, 2) == 1);
    CHECK(count_kv(map, 20, 2) == 1);
    CHECK(count_kv(map, 30, 2) == 1);
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test operator[](const Key&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    xint key_10 = 10;
    xint key_20 = 20;
    xint key_30 = 30;
    xint key_40 = 40;
    xint key_50 = 50;
    xint key_60 = 60;

    map[key_10] = 2;
    map[key_20] = 2;
    map[key_30] = 2;
    map[key_40] = 2;
    map[key_50] = 2;
    map[key_60] = 2;

    CHECK(map.size() == 6);
    CHECK(COUNT_KV(map, 10, 2) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 40, 2) == 1);
    CHECK(COUNT_KV(map, 50, 2) == 1);
    CHECK(COUNT_KV(map, 60, 2) == 1);

    CHECK(key_10 == 10);
    CHECK(key_20 == 20);
    CHECK(key_30 == 30);
    CHECK(key_40 == 40);
    CHECK(key_50 == 50);
    CHECK(key_60 == 60);
}

PRINT("Test operator[](Key&&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    xint key_10 = 10;
    xint key_20 = 20;
    xint key_30 = 30;
    xint key_40 = 40;
    xint key_50 = 50;
    xint key_60 = 60;

    map[std::move(key_10)] = 2;
    map[std::move(key_20)] = 2;
    map[std::move(key_30)] = 2;
    map[std::move(key_40)] = 2;
    map[std::move(key_50)] = 2;
    map[std::move(key_60)] = 2;

    CHECK(map.size() == 6);
    CHECK(COUNT_KV(map, 10, 2) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 1);
    CHECK(COUNT_KV(map, 30, 2) == 1);
    CHECK(COUNT_KV(map, 40, 2) == 1);
    CHECK(COUNT_KV(map, 50, 2) == 1);
    CHECK(COUNT_KV(map, 60, 2) == 1);

    CHECK(key_10 == +10);
    CHECK(key_20 == +20);
    CHECK(key_30 == +30);
    CHECK(key_40 == -40);
    CHECK(key_50 == -50);
    CHECK(key_60 == -60);
}

PRINT("Test operator[](K&&)");
{
    using container_type = sfl::flat_map<xobj, xint, xobj::less, TPARAM_ALLOCATOR<std::pair<xobj, xint>>>;

    container_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    auto count_kv = [](const container_type& map, const int k, const int v)
    {
        int n = 0;
        for (auto& kv : map)
        {
            if (kv.first.value() == k && kv.second == v)
            {
                ++n;
            }
        }
        return n;
    };

    CHECK(map.size() == 3);
    CHECK(count_kv(map, 10, 1) == 1);
    CHECK(count_kv(map, 20, 1) == 1);
    CHECK(count_kv(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    map[10] = 2;
    map[20] = 2;
    map[30] = 2;
    map[40] = 2;
    map[50] = 2;
    map[60] = 2;

    CHECK(map.size() == 6);
    CHECK(count_kv(map, 10, 2) == 1);
    CHECK(count_kv(map, 20, 2) == 1);
    CHECK(count_kv(map, 30, 2) == 1);
    CHECK(count_kv(map, 40, 2) == 1);
    CHECK(count_kv(map, 50, 2) == 1);
    CHECK(count_kv(map, 60, 2) == 1);
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test data()");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test NON-MEMBER comparison operators");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map1, map2;

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

PRINT("Test NON-MEMBER swap(container&)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    container_type map1, map2;

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

PRINT("Test NON-MEMBER erase_if(container&, Predicate)");
{
    using container_type = sfl::flat_map<xint, xint, std::less<xint>, TPARAM_ALLOCATOR<std::pair<xint, xint>>>;

    using const_reference = typename container_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    container_type map;

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

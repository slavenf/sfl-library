#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xint_xint;
using sfl::test::xobj;

BEGIN_TEST("Test container()")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());
}
END_TEST()

BEGIN_TEST("Test container(const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    typename set_type::key_compare comp;

    set_type set(comp);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());
}
END_TEST()

BEGIN_TEST("Test container(const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    typename set_type::allocator_type alloc;

    set_type set(alloc);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());
}
END_TEST()

BEGIN_TEST("Test container(const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(comp, alloc);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set(data.begin(), data.end());

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    typename set_type::key_compare comp;

    set_type set(data.begin(), data.end(), comp);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    typename set_type::allocator_type alloc;

    set_type set(data.begin(), data.end(), alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(data.begin(), data.end(), comp, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
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

    set_type set(ilist);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
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

    typename set_type::key_compare comp;

    set_type set(ilist, comp);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
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

    typename set_type::allocator_type alloc;

    set_type set(ilist, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
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

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(ilist, comp, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(set.available() == set.capacity() - set.size());

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set1(data.begin(), data.end());

    CHECK(set1.empty() == false);
    CHECK(set1.size() == 5);
    CHECK(set1.max_size() > 0);
    CHECK(set1.available() == set1.capacity() - set1.size());

    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 40, 1040) == 1);
    CHECK(COUNT_KV(set1, 50, 1050) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);
    CHECK(COUNT_KV(set1, 40, 2040) == 0);
    CHECK(COUNT_KV(set1, 50, 2050) == 0);
    CHECK(COUNT_KV(set1, 10, 3010) == 0);
    CHECK(COUNT_KV(set1, 20, 3020) == 0);
    CHECK(COUNT_KV(set1, 30, 3030) == 0);
    CHECK(COUNT_KV(set1, 40, 3040) == 0);
    CHECK(COUNT_KV(set1, 50, 3050) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    set_type set2(set1);

    CHECK(set2.empty() == false);
    CHECK(set2.size() == 5);
    CHECK(set2.max_size() > 0);
    CHECK(set2.available() == set2.capacity() - set2.size());

    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 10, 3010) == 0);
    CHECK(COUNT_KV(set2, 20, 3020) == 0);
    CHECK(COUNT_KV(set2, 30, 3030) == 0);
    CHECK(COUNT_KV(set2, 40, 3040) == 0);
    CHECK(COUNT_KV(set2, 50, 3050) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(const container&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set1(data.begin(), data.end());

    CHECK(set1.empty() == false);
    CHECK(set1.size() == 5);
    CHECK(set1.max_size() > 0);
    CHECK(set1.available() == set1.capacity() - set1.size());

    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 40, 1040) == 1);
    CHECK(COUNT_KV(set1, 50, 1050) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);
    CHECK(COUNT_KV(set1, 40, 2040) == 0);
    CHECK(COUNT_KV(set1, 50, 2050) == 0);
    CHECK(COUNT_KV(set1, 10, 3010) == 0);
    CHECK(COUNT_KV(set1, 20, 3020) == 0);
    CHECK(COUNT_KV(set1, 30, 3030) == 0);
    CHECK(COUNT_KV(set1, 40, 3040) == 0);
    CHECK(COUNT_KV(set1, 50, 3050) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename set_type::allocator_type alloc;

    set_type set2(set1, alloc);

    CHECK(set2.empty() == false);
    CHECK(set2.size() == 5);
    CHECK(set2.max_size() > 0);
    CHECK(set2.available() == set2.capacity() - set2.size());

    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 10, 3010) == 0);
    CHECK(COUNT_KV(set2, 20, 3020) == 0);
    CHECK(COUNT_KV(set2, 30, 3030) == 0);
    CHECK(COUNT_KV(set2, 40, 3040) == 0);
    CHECK(COUNT_KV(set2, 50, 3050) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set1(data.begin(), data.end());

    CHECK(set1.empty() == false);
    CHECK(set1.size() == 5);
    CHECK(set1.max_size() > 0);
    CHECK(set1.available() == set1.capacity() - set1.size());

    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 40, 1040) == 1);
    CHECK(COUNT_KV(set1, 50, 1050) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);
    CHECK(COUNT_KV(set1, 40, 2040) == 0);
    CHECK(COUNT_KV(set1, 50, 2050) == 0);
    CHECK(COUNT_KV(set1, 10, 3010) == 0);
    CHECK(COUNT_KV(set1, 20, 3020) == 0);
    CHECK(COUNT_KV(set1, 30, 3030) == 0);
    CHECK(COUNT_KV(set1, 40, 3040) == 0);
    CHECK(COUNT_KV(set1, 50, 3050) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    set_type set2(std::move(set1));

    CHECK(set1.empty() == true);
    CHECK(set1.size() == 0);

    CHECK(set2.empty() == false);
    CHECK(set2.size() == 5);
    CHECK(set2.max_size() > 0);
    CHECK(set2.available() == set2.capacity() - set2.size());

    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 10, 3010) == 0);
    CHECK(COUNT_KV(set2, 20, 3020) == 0);
    CHECK(COUNT_KV(set2, 30, 3030) == 0);
    CHECK(COUNT_KV(set2, 40, 3040) == 0);
    CHECK(COUNT_KV(set2, 50, 3050) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test container(container&&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set1(data.begin(), data.end());

    CHECK(set1.empty() == false);
    CHECK(set1.size() == 5);
    CHECK(set1.max_size() > 0);
    CHECK(set1.available() == set1.capacity() - set1.size());

    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 40, 1040) == 1);
    CHECK(COUNT_KV(set1, 50, 1050) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);
    CHECK(COUNT_KV(set1, 40, 2040) == 0);
    CHECK(COUNT_KV(set1, 50, 2050) == 0);
    CHECK(COUNT_KV(set1, 10, 3010) == 0);
    CHECK(COUNT_KV(set1, 20, 3020) == 0);
    CHECK(COUNT_KV(set1, 30, 3030) == 0);
    CHECK(COUNT_KV(set1, 40, 3040) == 0);
    CHECK(COUNT_KV(set1, 50, 3050) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    typename set_type::allocator_type alloc;

    set_type set2(std::move(set1), alloc);

    if (set1.size() == 5)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(set1, -10, -1010) == 1);
        CHECK(COUNT_KV(set1, -20, -1020) == 1);
        CHECK(COUNT_KV(set1, -30, -1030) == 1);
        CHECK(COUNT_KV(set1, -40, -1040) == 1);
        CHECK(COUNT_KV(set1, -50, -1050) == 1);
        CHECK(COUNT_KV(set1, -10, -2010) == 0);
        CHECK(COUNT_KV(set1, -20, -2020) == 0);
        CHECK(COUNT_KV(set1, -30, -2030) == 0);
        CHECK(COUNT_KV(set1, -40, -2040) == 0);
        CHECK(COUNT_KV(set1, -50, -2050) == 0);
        CHECK(COUNT_KV(set1, -10, -3010) == 0);
        CHECK(COUNT_KV(set1, -20, -3020) == 0);
        CHECK(COUNT_KV(set1, -30, -3030) == 0);
        CHECK(COUNT_KV(set1, -40, -3040) == 0);
        CHECK(COUNT_KV(set1, -50, -3050) == 0);
    }
    else
    {
        CHECK(set1.empty() == true);
        CHECK(set1.size() == 0);
    }

    CHECK(set2.empty() == false);
    CHECK(set2.size() == 5);
    CHECK(set2.max_size() > 0);
    CHECK(set2.available() == set2.capacity() - set2.size());

    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 10, 3010) == 0);
    CHECK(COUNT_KV(set2, 20, 3020) == 0);
    CHECK(COUNT_KV(set2, 30, 3030) == 0);
    CHECK(COUNT_KV(set2, 40, 3040) == 0);
    CHECK(COUNT_KV(set2, 50, 3050) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data1
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

    std::vector<typename set_type::value_type> data2
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

    set_type set1(data1.begin(), data1.end());
    set_type set2(data2.begin(), data2.end());

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 60, 1060) == 1);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 60, 2060) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    set2 = set1;

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data1
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

    std::vector<typename set_type::value_type> data2
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

    set_type set1(data1.begin(), data1.end());
    set_type set2(data2.begin(), data2.end());

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1010) == 1);
    CHECK(COUNT_KV(set1, 20, 1020) == 1);
    CHECK(COUNT_KV(set1, 30, 1030) == 1);
    CHECK(COUNT_KV(set1, 10, 2010) == 0);
    CHECK(COUNT_KV(set1, 20, 2020) == 0);
    CHECK(COUNT_KV(set1, 30, 2030) == 0);

    for (auto it1 = set1.begin(), it2 = std::next(it1); it2 != set1.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 40, 1040) == 1);
    CHECK(COUNT_KV(set2, 50, 1050) == 1);
    CHECK(COUNT_KV(set2, 60, 1060) == 1);
    CHECK(COUNT_KV(set2, 40, 2040) == 0);
    CHECK(COUNT_KV(set2, 50, 2050) == 0);
    CHECK(COUNT_KV(set2, 60, 2060) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    set2 = std::move(set1);

    if (set1.size() == 3)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(set1, -10, -1010) == 1);
        CHECK(COUNT_KV(set1, -20, -1020) == 1);
        CHECK(COUNT_KV(set1, -30, -1030) == 1);
        CHECK(COUNT_KV(set1, -10, -2010) == 0);
        CHECK(COUNT_KV(set1, -20, -2020) == 0);
        CHECK(COUNT_KV(set1, -30, -2030) == 0);
    }
    else
    {
        CHECK(set1.size() == 0);
    }

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1010) == 1);
    CHECK(COUNT_KV(set2, 20, 1020) == 1);
    CHECK(COUNT_KV(set2, 30, 1030) == 1);
    CHECK(COUNT_KV(set2, 10, 2010) == 0);
    CHECK(COUNT_KV(set2, 20, 2020) == 0);
    CHECK(COUNT_KV(set2, 30, 2030) == 0);

    for (auto it1 = set2.begin(), it2 = std::next(it1); it2 != set2.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set(data.begin(), data.end());

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }

    ///////////////////////////////////////////////////////////////////////////

    std::initializer_list<typename set_type::value_type> ilist
    {
        {40, 1040},
        {50, 1050},
        {60, 1060},
        {40, 2040},
        {50, 2050},
        {60, 2060}
    };

    set = ilist;

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 60, 1060) == 1);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 60, 2060) == 0);

    for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
    {
        CHECK(it1->first <= it2->first);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test get_allocator()")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    auto alloc = set.get_allocator();

    (void)alloc;
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test key_comp()")
{
    {
        using key_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        auto key_comp = set.key_comp();

        CHECK(key_comp(10, 10) == false);
        CHECK(key_comp(10, 20) == true);
        CHECK(key_comp(20, 10) == false);
        CHECK(key_comp(20, 20) == false);
    }

    {
        using key_type = xobj;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        auto key_comp = set.key_comp();

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
        using key_compare = std::less<key_type>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        auto value_comp = set.value_comp();

        CHECK(value_comp(10, 10) == false);
        CHECK(value_comp(10, 20) == true);
        CHECK(value_comp(20, 10) == false);
        CHECK(value_comp(20, 20) == false);
    }

    {
        using key_type = xobj;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        auto value_comp = set.value_comp();

        CHECK(value_comp(xobj(10), xobj(10)) == false);
        CHECK(value_comp(xobj(10), xobj(20)) == true);
        CHECK(value_comp(xobj(20), xobj(10)) == false);
        CHECK(value_comp(xobj(20), xobj(20)) == false);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    ///////////////////////////////////////////////////////////////////////////

    auto it = set.begin();
    CHECK(it->first == 10); CHECK(it->second == 1); ++it;
    CHECK(it->first == 20); CHECK(it->second == 1); ++it;
    CHECK(it->first == 30); CHECK(it->second == 1); ++it;
    CHECK(it == set.end());

    ///////////////////////////////////////////////////////////////////////////

    auto cit = set.cbegin();
    CHECK(cit->first == 10); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 30); CHECK(cit->second == 1); ++cit;
    CHECK(cit == set.cend());

    ///////////////////////////////////////////////////////////////////////////

    auto rit = set.rbegin();
    CHECK(rit->first == 30); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 10); CHECK(rit->second == 1); ++rit;
    CHECK(rit == set.rend());

    ///////////////////////////////////////////////////////////////////////////

    auto crit = set.crbegin();
    CHECK(crit->first == 30); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 10); CHECK(crit->second == 1); ++crit;
    CHECK(crit == set.crend());

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
    CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
    CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.index_of(set.nth(0)) == 0);
    CHECK(set.index_of(set.nth(1)) == 1);
    CHECK(set.index_of(set.nth(2)) == 2);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test clear()")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1010);
    set.emplace(20, 1020);
    set.emplace(30, 1030);

    CHECK(set.empty() == false);
    CHECK(set.size() == 3);

    set.clear();

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test emplace(Args&&...)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    set_type set;

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

            const auto res = set.emplace(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != set.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check size
            CHECK(int(set.size()) == int(size));

            // Check ordering
            for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(set, key, key + 1000) == 1);
        CHECK(COUNT_KV(set, key, key + 2000) == 0);
        CHECK(COUNT_KV(set, key, key + 3000) == 0);
    }

    #else // C++20 constexpr

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(20, 2);
    set.emplace(30, 1);
    set.emplace(30, 2);
    set.emplace(30, 3);

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test emplace_hint(const_iterator, Args&&...)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

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
                set_type set;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = set.end();

                    const auto res = set.emplace_hint(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(set.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(set, insert_pos);

                    const auto res = set.emplace_hint(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(set.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(set.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 0);
                }
                else
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    set_type set;

    set.emplace_hint(set.end(), 10, 1);
    set.emplace_hint(set.end(), 20, 1);
    set.emplace_hint(set.end(), 20, 2);
    set.emplace_hint(set.end(), 30, 1);
    set.emplace_hint(set.end(), 30, 2);
    set.emplace_hint(set.end(), 30, 3);

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const value_type&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    set_type set;

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

            typename set_type::value_type key_value(key, value);

            const auto res = set.insert(key_value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != set.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key-value
            CHECK(key_value.first == key);
            CHECK(key_value.second == value);

            // Check size
            CHECK(int(set.size()) == int(size));

            // Check ordering
            for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(set, key, key + 1000) == 1);
        CHECK(COUNT_KV(set, key, key + 2000) == 0);
        CHECK(COUNT_KV(set, key, key + 3000) == 0);
    }

    #else // C++20 constexpr

    set_type set;

    using value_type = typename set_type::value_type;

    { const value_type value_10_1(10, 1); set.insert(value_10_1); }
    { const value_type value_20_1(20, 1); set.insert(value_20_1); }
    { const value_type value_20_2(20, 2); set.insert(value_20_2); }
    { const value_type value_30_1(30, 1); set.insert(value_30_1); }
    { const value_type value_30_2(30, 2); set.insert(value_30_2); }
    { const value_type value_30_3(30, 3); set.insert(value_30_3); }

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(value_type&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    set_type set;

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

            typename set_type::value_type key_value(key, value);

            const auto res = set.insert(std::move(key_value));

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != set.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key-value
            CHECK(key_value.first == (iter == 0 ? -key : +key));
            CHECK(key_value.second == (iter == 0 ? -value : +value));

            // Check size
            CHECK(int(set.size()) == int(size));

            // Check ordering
            for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(set, key, key + 1000) == 1);
        CHECK(COUNT_KV(set, key, key + 2000) == 0);
        CHECK(COUNT_KV(set, key, key + 3000) == 0);
    }

    #else // C++20 constexpr

    set_type set;

    using value_type = typename set_type::value_type;

    { value_type value_10_1(10, 1); set.insert(std::move(value_10_1)); }
    { value_type value_20_1(20, 1); set.insert(std::move(value_20_1)); }
    { value_type value_20_2(20, 2); set.insert(std::move(value_20_2)); }
    { value_type value_30_1(30, 1); set.insert(std::move(value_30_1)); }
    { value_type value_30_2(30, 2); set.insert(std::move(value_30_2)); }
    { value_type value_30_3(30, 3); set.insert(std::move(value_30_3)); }

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const K&)")
{
    using key_type = xobj;
    using key_compare = xobj::less;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    #ifndef TEST_CPP20_CONSTEXPR

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    set_type set;

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

            const auto res = set.insert(key);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != set.end());
            CHECK(res.first->value() == elem);

            // Check size
            CHECK(int(set.size()) == int(size));

            // Check ordering
            for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
            {
                CHECK(it1->value() <= it2->value());
            }
        }
    }

    #else // C++20 constexpr

    set_type set;

    { const int value_10(10); set.insert(value_10); }
    { const int value_20(20); set.insert(value_20); }
    { const int value_20(20); set.insert(value_20); }
    { const int value_30(30); set.insert(value_30); }
    { const int value_30(30); set.insert(value_30); }
    { const int value_30(30); set.insert(value_30); }

    CHECK(set.size() == 3);

    auto it = set.begin();
    CHECK(it->value() == 10); ++it;
    CHECK(it->value() == 20); ++it;
    CHECK(it->value() == 30); ++it;
    CHECK(it == set.end());

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const value_type&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

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
                set_type set;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename set_type::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = set.end();

                    const auto res = set.insert(hint, key_value);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == elem1);
                    CHECK(key_value.second == elem1 + 1000);
                }

                // Check size
                CHECK(int(set.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename set_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(set, insert_pos);

                    const auto res = set.insert(hint, key_value);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key-value
                    CHECK(key_value.first == elem2);
                    CHECK(key_value.second == elem2 + 2000);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(set.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(set.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 0);
                }
                else
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    set_type set;

    using value_type = typename set_type::value_type;

    { const value_type value_10_1(10, 1); set.insert(set.end(), value_10_1); }
    { const value_type value_20_1(20, 1); set.insert(set.end(), value_20_1); }
    { const value_type value_20_2(20, 2); set.insert(set.end(), value_20_2); }
    { const value_type value_30_1(30, 1); set.insert(set.end(), value_30_1); }
    { const value_type value_30_2(30, 2); set.insert(set.end(), value_30_2); }
    { const value_type value_30_3(30, 3); set.insert(set.end(), value_30_3); }

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, value_type&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

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
                set_type set;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename set_type::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = set.end();

                    const auto res = set.insert(hint, std::move(key_value));

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == -elem1);
                    CHECK(key_value.second == -(elem1 + 1000));
                }

                // Check size
                CHECK(int(set.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename set_type::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(set, insert_pos);

                    const auto res = set.insert(hint, std::move(key_value));

                    // Check result
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key-value
                    CHECK(key_value.first == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2));
                    CHECK(key_value.second == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2 + 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(set.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(set.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(set, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 0);
                }
                else
                {
                    CHECK(COUNT_KV(set, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(set, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    set_type set;

    using value_type = typename set_type::value_type;

    { value_type value_10_1(10, 1); set.insert(set.end(), std::move(value_10_1)); }
    { value_type value_20_1(20, 1); set.insert(set.end(), std::move(value_20_1)); }
    { value_type value_20_2(20, 2); set.insert(set.end(), std::move(value_20_2)); }
    { value_type value_30_1(30, 1); set.insert(set.end(), std::move(value_30_1)); }
    { value_type value_30_2(30, 2); set.insert(set.end(), std::move(value_30_2)); }
    { value_type value_30_3(30, 3); set.insert(set.end(), std::move(value_30_3)); }

    CHECK(set.size() == 3);

    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
    CHECK(COUNT_KV(set, 30, 2) == 0);
    CHECK(COUNT_KV(set, 30, 3) == 0);

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const K&)")
{
    using key_type = xobj;
    using key_compare = xobj::less;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

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
                set_type set;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = set.end();

                    const auto res = set.insert(hint, elem1);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->value() == elem1);
                }

                // Check size
                CHECK(int(set.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->value() <= it2->value());
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(set, insert_pos);

                    const auto res = set.insert(hint, elem2);

                    // Check result
                    CHECK(res != set.end());
                    CHECK(res->value() == elem2);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(set.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(set.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = set.begin(), it2 = std::next(it1); it2 != set.end(); ++it1, ++it2)
                {
                    CHECK(it1->value() <= it2->value());
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }

    #else // C++20 constexpr

    set_type set;

    { const int value_10(10); set.insert(set.end(), value_10); }
    { const int value_20(20); set.insert(set.end(), value_20); }
    { const int value_20(20); set.insert(set.end(), value_20); }
    { const int value_30(30); set.insert(set.end(), value_30); }
    { const int value_30(30); set.insert(set.end(), value_30); }
    { const int value_30(30); set.insert(set.end(), value_30); }

    CHECK(set.size() == 3);

    auto it = set.begin();
    CHECK(it->value() == 10); ++it;
    CHECK(it->value() == 20); ++it;
    CHECK(it->value() == 30); ++it;
    CHECK(it == set.end());

    #endif // C++20 constexpr
}
END_TEST()

BEGIN_TEST("Test insert(InputIt, InputIt")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
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

    set_type set;

    set.insert(data.begin(), data.end());

    CHECK(set.size() == 5);

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);
}
END_TEST()

BEGIN_TEST("Test insert(std::initializer_list")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
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

    set_type set;

    set.insert(ilist);

    CHECK(set.size() == 5);

    CHECK(COUNT_KV(set, 10, 1010) == 1);
    CHECK(COUNT_KV(set, 20, 1020) == 1);
    CHECK(COUNT_KV(set, 30, 1030) == 1);
    CHECK(COUNT_KV(set, 40, 1040) == 1);
    CHECK(COUNT_KV(set, 50, 1050) == 1);
    CHECK(COUNT_KV(set, 10, 2010) == 0);
    CHECK(COUNT_KV(set, 20, 2020) == 0);
    CHECK(COUNT_KV(set, 30, 2030) == 0);
    CHECK(COUNT_KV(set, 40, 2040) == 0);
    CHECK(COUNT_KV(set, 50, 2050) == 0);
    CHECK(COUNT_KV(set, 10, 3010) == 0);
    CHECK(COUNT_KV(set, 20, 3020) == 0);
    CHECK(COUNT_KV(set, 30, 3030) == 0);
    CHECK(COUNT_KV(set, 40, 3040) == 0);
    CHECK(COUNT_KV(set, 50, 3050) == 0);
}
END_TEST()

BEGIN_TEST("Test insert_range(Range&&")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

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

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::istream<typename set_type::value_type>(iss));
        #else
        set.insert_range(sfl::test::istream_view<typename set_type::value_type>(iss));
        #endif

        CHECK(set.size() == 5);

        CHECK(COUNT_KV(set, 10, 1010) == 1);
        CHECK(COUNT_KV(set, 20, 1020) == 1);
        CHECK(COUNT_KV(set, 30, 1030) == 1);
        CHECK(COUNT_KV(set, 40, 1040) == 1);
        CHECK(COUNT_KV(set, 50, 1050) == 1);
        CHECK(COUNT_KV(set, 10, 2010) == 0);
        CHECK(COUNT_KV(set, 20, 2020) == 0);
        CHECK(COUNT_KV(set, 30, 2030) == 0);
        CHECK(COUNT_KV(set, 40, 2040) == 0);
        CHECK(COUNT_KV(set, 50, 2050) == 0);
        CHECK(COUNT_KV(set, 10, 3010) == 0);
        CHECK(COUNT_KV(set, 20, 3020) == 0);
        CHECK(COUNT_KV(set, 30, 3030) == 0);
        CHECK(COUNT_KV(set, 40, 3040) == 0);
        CHECK(COUNT_KV(set, 50, 3050) == 0);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data
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

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::all(data));
        #else
        set.insert_range(data);
        #endif

        CHECK(set.size() == 5);

        CHECK(COUNT_KV(set, 10, 1010) == 1);
        CHECK(COUNT_KV(set, 20, 1020) == 1);
        CHECK(COUNT_KV(set, 30, 1030) == 1);
        CHECK(COUNT_KV(set, 40, 1040) == 1);
        CHECK(COUNT_KV(set, 50, 1050) == 1);
        CHECK(COUNT_KV(set, 10, 2010) == 0);
        CHECK(COUNT_KV(set, 20, 2020) == 0);
        CHECK(COUNT_KV(set, 30, 2030) == 0);
        CHECK(COUNT_KV(set, 40, 2040) == 0);
        CHECK(COUNT_KV(set, 50, 2050) == 0);
        CHECK(COUNT_KV(set, 10, 3010) == 0);
        CHECK(COUNT_KV(set, 20, 3020) == 0);
        CHECK(COUNT_KV(set, 30, 3030) == 0);
        CHECK(COUNT_KV(set, 40, 3040) == 0);
        CHECK(COUNT_KV(set, 50, 3050) == 0);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos = 0; erase_pos < size; ++erase_pos)
        {
            set_type set;

            // Insert elements
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                set.emplace(elem, elem + 1000);
            }

            // Check size
            CHECK(int(set.size()) == int(size));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                CHECK(COUNT_KV(set, elem, elem + 1000) == 1);
            }

            ///////////////////////////////////////////////////////////////////

            // Erase
            const auto it = NTH(set, erase_pos);
            set.erase(it);

            // Check size
            CHECK(int(set.size()) == int(size - 1));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                if (i == erase_pos)
                {
                    continue;
                }
                const auto& elem = data[i];
                CHECK(COUNT_KV(set, elem, elem + 1000) == 1);
            }
        }
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos1 = 0; erase_pos1 < size; ++erase_pos1)
        {
            for (int erase_pos2 = erase_pos1; erase_pos2 < size; ++erase_pos2)
            {
                set_type set;

                // Insert elements
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    set.emplace(elem, elem + 1000);
                }

                // Check size
                CHECK(int(set.size()) == int(size));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(set, elem, elem + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////////

                // Range to erase
                const auto it1 = NTH(set, erase_pos1);
                const auto it2 = NTH(set, erase_pos2);

                // Number of erased elements
                const int size_delta = int(std::distance(it1, it2));

                // Erase
                set.erase(it1, it2);

                // Check size
                CHECK(int(set.size()) == int(size - size_delta));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    if (i >= erase_pos1 && i < erase_pos2)
                    {
                        continue;
                    }
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(set, elem, elem + 1000) == 1);
                }
            }
        }
    }
}
END_TEST()

BEGIN_TEST("Test erase(const Key&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(20);
    set.emplace(30);
    set.emplace(30);
    set.emplace(30);

    CHECK(set.size() == 3);
    CHECK(COUNT(set, 10) == 1);
    CHECK(COUNT(set, 20) == 1);
    CHECK(COUNT(set, 30) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);

    CHECK(set.size() == 2);
    CHECK(COUNT(set, 10) == 1);
    CHECK(COUNT(set, 20) == 1);
    CHECK(COUNT(set, 30) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(20) == 1);
    CHECK(set.erase(20) == 0);

    CHECK(set.size() == 1);
    CHECK(COUNT(set, 10) == 1);
    CHECK(COUNT(set, 20) == 0);
    CHECK(COUNT(set, 30) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);

    CHECK(set.size() == 0);
    CHECK(COUNT(set, 10) == 0);
    CHECK(COUNT(set, 20) == 0);
    CHECK(COUNT(set, 30) == 0);
}
END_TEST()

BEGIN_TEST("Test erase(K&&)")
{
    using key_type = xobj;
    using key_compare = xobj::less;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(20);
    set.emplace(30);
    set.emplace(30);
    set.emplace(30);

    CHECK(set.size() == 3);
    for (const auto& k : set)
    {
        CHECK(k.value() == 10 || k.value() == 20 || k.value() == 30);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);

    CHECK(set.size() == 2);
    for (const auto& k : set)
    {
        CHECK(k.value() == 10 || k.value() == 20);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(20) == 1);
    CHECK(set.erase(20) == 0);

    CHECK(set.size() == 1);
    for (const auto& k : set)
    {
        CHECK(k.value() == 10);
    }

    ///////////////////////////////////////////////////////////////////////////

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);

    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);
    set2.emplace(70, 2);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    CHECK(set2.size() == 4);
    CHECK(COUNT_KV(set2, 40, 2) == 1);
    CHECK(COUNT_KV(set2, 50, 2) == 1);
    CHECK(COUNT_KV(set2, 60, 2) == 1);
    CHECK(COUNT_KV(set2, 70, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    set1.swap(set2);

    CHECK(set1.size() == 4);
    CHECK(COUNT_KV(set1, 40, 2) == 1);
    CHECK(COUNT_KV(set1, 50, 2) == 1);
    CHECK(COUNT_KV(set1, 60, 2) == 1);
    CHECK(COUNT_KV(set1, 70, 2) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    set1.swap(set2);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    CHECK(set2.size() == 4);
    CHECK(COUNT_KV(set2, 40, 2) == 1);
    CHECK(COUNT_KV(set2, 50, 2) == 1);
    CHECK(COUNT_KV(set2, 60, 2) == 1);
    CHECK(COUNT_KV(set2, 70, 2) == 1);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test lower_bound, upper_bound, equal_range, find, count, contains")
{
    {
        using key_type = xint;
        using key_compare = std::less<xint>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        set.emplace(10);
        set.emplace(20);
        set.emplace(20);
        set.emplace(30);
        set.emplace(30);
        set.emplace(30);

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = set.lower_bound(x);
                auto it2 = set.upper_bound(x);

                CHECK(std::distance(it1, it2) == 1);

                auto er = set.equal_range(x);

                CHECK(er.first == it1);
                CHECK(er.second == it2);

                while (it1 != it2)
                {
                    CHECK(*it1 == x);
                    ++it1;
                }
            }

            // Check find
            {
                auto it = set.find(x);
                CHECK(it != set.end());
                CHECK(*it == x);
            }

            // Check count
            CHECK(set.count(x) == 1);

            // Check contains
            CHECK(set.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = set.lower_bound(x);
                auto it2 = set.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = set.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = set.find(x);
                CHECK(it == set.end());
            }

            // Check count
            CHECK(set.count(x) == 0);

            // Check contains
            CHECK(set.contains(x) == false);
        }
    }

    {
        using key_type = xobj;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

        set_type set;

        set.emplace(10);
        set.emplace(20);
        set.emplace(20);
        set.emplace(30);
        set.emplace(30);
        set.emplace(30);

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = set.lower_bound(x);
                auto it2 = set.upper_bound(x);

                CHECK(std::distance(it1, it2) == 1);

                auto er = set.equal_range(x);

                CHECK(er.first == it1);
                CHECK(er.second == it2);

                while (it1 != it2)
                {
                    CHECK(it1->value() == x);
                    ++it1;
                }
            }

            // Check find
            {
                auto it = set.find(x);
                CHECK(it != set.end());
                CHECK(it->value() == x);
            }

            // Check count
            CHECK(set.count(x) == 1);

            // Check contains
            CHECK(set.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = set.lower_bound(x);
                auto it2 = set.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = set.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = set.find(x);
                CHECK(it == set.end());
            }

            // Check count
            CHECK(set.count(x) == 0);

            // Check contains
            CHECK(set.contains(x) == false);
        }
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test data()")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(std::next(set.data(), 0)->first == 10); CHECK(std::next(set.data(), 0)->second == 1);
    CHECK(std::next(set.data(), 1)->first == 20); CHECK(std::next(set.data(), 1)->second == 1);
    CHECK(std::next(set.data(), 2)->first == 30); CHECK(std::next(set.data(), 2)->second == 1);

    const auto& cref = set;

    CHECK(cref.size() == 3);
    CHECK(std::next(cref.data(), 0)->first == 10); CHECK(std::next(cref.data(), 0)->second == 1);
    CHECK(std::next(cref.data(), 1)->first == 20); CHECK(std::next(cref.data(), 1)->second == 1);
    CHECK(std::next(cref.data(), 2)->first == 30); CHECK(std::next(cref.data(), 2)->second == 1);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    set2.emplace(10, 1);
    set2.emplace(20, 1);
    set2.emplace(30, 1);
    set2.emplace(40, 1);
    set2.emplace(50, 1);

    CHECK((set1 == set1) == true);
    CHECK((set1 == set2) == false);
    CHECK((set2 == set1) == false);
    CHECK((set2 == set2) == true);

    CHECK((set1 != set1) == false);
    CHECK((set1 != set2) == true);
    CHECK((set2 != set1) == true);
    CHECK((set2 != set2) == false);

    CHECK((set1 < set1) == false);
    CHECK((set1 < set2) == true);
    CHECK((set2 < set1) == false);
    CHECK((set2 < set2) == false);

    CHECK((set1 > set1) == false);
    CHECK((set1 > set2) == false);
    CHECK((set2 > set1) == true);
    CHECK((set2 > set2) == false);

    CHECK((set1 <= set1) == true);
    CHECK((set1 <= set2) == true);
    CHECK((set2 <= set1) == false);
    CHECK((set2 <= set2) == true);

    CHECK((set1 >= set1) == true);
    CHECK((set1 >= set2) == false);
    CHECK((set2 >= set1) == true);
    CHECK((set2 >= set2) == true);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER swap(container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);
    set2.emplace(70, 2);
    set2.emplace(80, 2);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    CHECK(set2.size() == 5);
    CHECK(COUNT_KV(set2, 40, 2) == 1);
    CHECK(COUNT_KV(set2, 50, 2) == 1);
    CHECK(COUNT_KV(set2, 60, 2) == 1);
    CHECK(COUNT_KV(set2, 70, 2) == 1);
    CHECK(COUNT_KV(set2, 80, 2) == 1);

    ///////////////////////////////////////////////////////////////////////////

    swap(set1, set2);

    CHECK(set1.size() == 5);
    CHECK(COUNT_KV(set1, 40, 2) == 1);
    CHECK(COUNT_KV(set1, 50, 2) == 1);
    CHECK(COUNT_KV(set1, 60, 2) == 1);
    CHECK(COUNT_KV(set1, 70, 2) == 1);
    CHECK(COUNT_KV(set1, 80, 2) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase_if(container&, Predicate)")
{
    using key_type = xint_xint;
    using key_compare = std::less<key_type>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::flat_set<key_type, key_compare, allocator_type>;

    using const_reference = typename set_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 1);
    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(set.size() == 2);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

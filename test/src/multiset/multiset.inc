#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xint_xint;
using sfl::test::xobj;

BEGIN_TEST("Test container()")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
}
END_TEST()

BEGIN_TEST("Test container(const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    typename set_type::key_compare comp;

    set_type set(comp);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
}
END_TEST()

BEGIN_TEST("Test container(const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    typename set_type::allocator_type alloc;

    set_type set(alloc);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
}
END_TEST()

BEGIN_TEST("Test container(const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(comp, alloc);

    CHECK(set.empty() == true);
    CHECK(set.size() == 0);
    CHECK(set.max_size() > 0);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    set_type set(data.begin(), data.end());

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename set_type::key_compare comp;

    set_type set(data.begin(), data.end(), comp);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename set_type::allocator_type alloc;

    set_type set(data.begin(), data.end(), alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::vector<typename set_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(data.begin(), data.end(), comp, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    set_type set(ilist);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename set_type::key_compare comp;

    set_type set(ilist, comp);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename set_type::allocator_type alloc;

    set_type set(ilist, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Compare&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename set_type::key_compare comp;

    typename set_type::allocator_type alloc;

    set_type set(ilist, comp, alloc);

    CHECK(set.empty() == false);
    CHECK(set.size() == 5);
    CHECK(set.max_size() > 0);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    set_type set2(set1);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(const container&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    typename set_type::allocator_type alloc;

    set_type set2(set1, alloc);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    set_type set2(std::move(set1));

    CHECK(set1.size() == 0);
    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(container&&, const Allocator&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    typename set_type::allocator_type alloc;

    set_type set2(std::move(set1), alloc);

    if (set1.size() == 3)
    {
        // Elements are moved one-by-one
        CHECK(NTH(set1, 0)->first == -10); CHECK(NTH(set1, 0)->second == -1);
        CHECK(NTH(set1, 1)->first == -20); CHECK(NTH(set1, 1)->second == -1);
        CHECK(NTH(set1, 2)->first == -30); CHECK(NTH(set1, 2)->second == -1);
    }
    else
    {
        CHECK(set1.size() == 0);
    }

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 20 20");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<int>(iss)));
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<int>(iss)));
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data({10, 20, 30, 20, 20});

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data));
        #else
        set_type set(sfl::from_range_t(), data);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const Compare&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 20 20");

        typename set_type::key_compare comp;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<int>(iss)), comp);
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<int>(iss)), comp);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data({10, 20, 30, 20, 20});

        typename set_type::key_compare comp;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data), comp);
        #else
        set_type set(sfl::from_range_t(), data, comp);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const Allocator&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 20 20");

        typename set_type::allocator_type alloc;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<int>(iss)), alloc);
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<int>(iss)), alloc);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data({10, 20, 30, 20, 20});

        typename set_type::allocator_type alloc;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data), alloc);
        #else
        set_type set(sfl::from_range_t(), data, alloc);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const Compare&, const Allocator&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 20 20");

        typename set_type::key_compare comp;

        typename set_type::allocator_type alloc;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<int>(iss)), comp, alloc);
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<int>(iss)), comp, alloc);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data({10, 20, 30, 20, 20});

        typename set_type::key_compare comp;

        typename set_type::allocator_type alloc;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data), comp, alloc);
        #else
        set_type set(sfl::from_range_t(), data, comp, alloc);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 40); CHECK(NTH(set2, 0)->second == 2);
    CHECK(NTH(set2, 1)->first == 50); CHECK(NTH(set2, 1)->second == 2);
    CHECK(NTH(set2, 2)->first == 60); CHECK(NTH(set2, 2)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    set2 = set1;

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 40); CHECK(NTH(set2, 0)->second == 2);
    CHECK(NTH(set2, 1)->first == 50); CHECK(NTH(set2, 1)->second == 2);
    CHECK(NTH(set2, 2)->first == 60); CHECK(NTH(set2, 2)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    set2 = std::move(set1);

    if (set1.size() == 3)
    {
        // Elements are move one-by-one
        CHECK(NTH(set1, 0)->first == -10); CHECK(NTH(set1, 0)->second == -1);
        CHECK(NTH(set1, 1)->first == -20); CHECK(NTH(set1, 1)->second == -1);
        CHECK(NTH(set1, 2)->first == -30); CHECK(NTH(set1, 2)->second == -1);
    }
    else
    {
        CHECK(set1.size() == 0);
    }

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(std::initializer_list)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 30); CHECK(NTH(set, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    std::initializer_list<typename set_type::value_type> ilist
    {
        {40, 2},
        {50, 2},
        {60, 2},
        {50, 3},
        {50, 4}
    };

    set = ilist;

    CHECK(set.size() == 5);
    CHECK(NTH(set, 0)->first == 40); CHECK(NTH(set, 0)->second == 2);
    CHECK(NTH(set, 1)->first == 50); CHECK(NTH(set, 1)->second == 2);
    CHECK(NTH(set, 2)->first == 50); CHECK(NTH(set, 2)->second == 3);
    CHECK(NTH(set, 3)->first == 50); CHECK(NTH(set, 3)->second == 4);
    CHECK(NTH(set, 4)->first == 60); CHECK(NTH(set, 4)->second == 2);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test get_allocator()")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
        using key_compare = std::less<xint>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
        using key_compare = std::less<xint>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

        set_type set;

        auto value_comp = set.value_comp();

        CHECK(value_comp(xobj(10), 10) == false);
        CHECK(value_comp(xobj(10), 20) == true);
        CHECK(value_comp(xobj(20), 10) == false);
        CHECK(value_comp(xobj(20), 20) == false);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(20, 1);
    set.emplace(40, 1);
    set.emplace(60, 1);

    ///////////////////////////////////////////////////////////////////////

    auto it = set.begin();
    CHECK(it->first == 20); CHECK(it->second == 1); ++it;
    CHECK(it->first == 40); CHECK(it->second == 1); ++it;
    CHECK(it->first == 60); CHECK(it->second == 1); ++it;
    CHECK(it == set.end());

    ///////////////////////////////////////////////////////////////////////

    auto cit = set.cbegin();
    CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 40); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 60); CHECK(cit->second == 1); ++cit;
    CHECK(cit == set.cend());

    ///////////////////////////////////////////////////////////////////////

    auto rit = set.rbegin();
    CHECK(rit->first == 60); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 40); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
    CHECK(rit == set.rend());

    ///////////////////////////////////////////////////////////////////////

    auto crit = set.crbegin();
    CHECK(crit->first == 60); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 40); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
    CHECK(crit == set.crend());
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test lower_bound, upper_bound, equal_range, find, count, contains")
{
    // xint
    {
        using key_type = xint;
        using key_compare = std::less<xint>;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.lower_bound(10) == NTH(set, 0));
        CHECK(set.lower_bound(20) == NTH(set, 0));
        CHECK(set.lower_bound(30) == NTH(set, 1));
        CHECK(set.lower_bound(40) == NTH(set, 1));
        CHECK(set.lower_bound(50) == NTH(set, 2));
        CHECK(set.lower_bound(60) == NTH(set, 2));
        CHECK(set.lower_bound(70) == NTH(set, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.upper_bound(10) == NTH(set, 0));
        CHECK(set.upper_bound(20) == NTH(set, 1));
        CHECK(set.upper_bound(30) == NTH(set, 1));
        CHECK(set.upper_bound(40) == NTH(set, 2));
        CHECK(set.upper_bound(50) == NTH(set, 2));
        CHECK(set.upper_bound(60) == NTH(set, 3));
        CHECK(set.upper_bound(70) == NTH(set, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.equal_range(10) == std::make_pair(NTH(set, 0), NTH(set, 0)));
        CHECK(set.equal_range(20) == std::make_pair(NTH(set, 0), NTH(set, 1)));
        CHECK(set.equal_range(30) == std::make_pair(NTH(set, 1), NTH(set, 1)));
        CHECK(set.equal_range(40) == std::make_pair(NTH(set, 1), NTH(set, 2)));
        CHECK(set.equal_range(50) == std::make_pair(NTH(set, 2), NTH(set, 2)));
        CHECK(set.equal_range(60) == std::make_pair(NTH(set, 2), NTH(set, 3)));
        CHECK(set.equal_range(70) == std::make_pair(NTH(set, 3), NTH(set, 3)));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.find(10) == set.end());
        CHECK(set.find(20) == NTH(set, 0));
        CHECK(set.find(30) == set.end());
        CHECK(set.find(40) == NTH(set, 1));
        CHECK(set.find(50) == set.end());
        CHECK(set.find(60) == NTH(set, 2));
        CHECK(set.find(70) == set.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.count(10) == 0);
        CHECK(set.count(20) == 1);
        CHECK(set.count(30) == 0);
        CHECK(set.count(40) == 1);
        CHECK(set.count(50) == 0);
        CHECK(set.count(60) == 1);
        CHECK(set.count(70) == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.contains(10) == false);
        CHECK(set.contains(20) == true);
        CHECK(set.contains(30) == false);
        CHECK(set.contains(40) == true);
        CHECK(set.contains(50) == false);
        CHECK(set.contains(60) == true);
        CHECK(set.contains(70) == false);
    }

    // xobj
    {
        using key_type = xobj;
        using key_compare = xobj::less;
        using allocator_type = TPARAM_ALLOCATOR<key_type>;
        using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.lower_bound(10) == NTH(set, 0));
        CHECK(set.lower_bound(20) == NTH(set, 0));
        CHECK(set.lower_bound(30) == NTH(set, 1));
        CHECK(set.lower_bound(40) == NTH(set, 1));
        CHECK(set.lower_bound(50) == NTH(set, 2));
        CHECK(set.lower_bound(60) == NTH(set, 2));
        CHECK(set.lower_bound(70) == NTH(set, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.upper_bound(10) == NTH(set, 0));
        CHECK(set.upper_bound(20) == NTH(set, 1));
        CHECK(set.upper_bound(30) == NTH(set, 1));
        CHECK(set.upper_bound(40) == NTH(set, 2));
        CHECK(set.upper_bound(50) == NTH(set, 2));
        CHECK(set.upper_bound(60) == NTH(set, 3));
        CHECK(set.upper_bound(70) == NTH(set, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.equal_range(10) == std::make_pair(NTH(set, 0), NTH(set, 0)));
        CHECK(set.equal_range(20) == std::make_pair(NTH(set, 0), NTH(set, 1)));
        CHECK(set.equal_range(30) == std::make_pair(NTH(set, 1), NTH(set, 1)));
        CHECK(set.equal_range(40) == std::make_pair(NTH(set, 1), NTH(set, 2)));
        CHECK(set.equal_range(50) == std::make_pair(NTH(set, 2), NTH(set, 2)));
        CHECK(set.equal_range(60) == std::make_pair(NTH(set, 2), NTH(set, 3)));
        CHECK(set.equal_range(70) == std::make_pair(NTH(set, 3), NTH(set, 3)));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.find(10) == set.end());
        CHECK(set.find(20) == NTH(set, 0));
        CHECK(set.find(30) == set.end());
        CHECK(set.find(40) == NTH(set, 1));
        CHECK(set.find(50) == set.end());
        CHECK(set.find(60) == NTH(set, 2));
        CHECK(set.find(70) == set.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.count(10) == 0);
        CHECK(set.count(20) == 1);
        CHECK(set.count(30) == 0);
        CHECK(set.count(40) == 1);
        CHECK(set.count(50) == 0);
        CHECK(set.count(60) == 1);
        CHECK(set.count(70) == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.contains(10) == false);
        CHECK(set.contains(20) == true);
        CHECK(set.contains(30) == false);
        CHECK(set.contains(40) == true);
        CHECK(set.contains(50) == false);
        CHECK(set.contains(60) == true);
        CHECK(set.contains(70) == false);
    }
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test emplace(Args&&...)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.emplace(10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.emplace(10, 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test emplace_hint(const_iterator, Args&&...)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.emplace_hint(set.begin(), 10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.emplace_hint(set.begin(), 10, 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const value_type&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = set.insert(value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = set.insert(value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(value_type&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = set.insert(std::move(value_10_1));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);

        CHECK(value_10_1.first  == -10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = set.insert(std::move(value_10_2));

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);

        CHECK(value_10_2.first  == -10);
        CHECK(value_10_2.second == -2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const value_type&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = set.insert(set.begin(), value_10_1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = set.insert(set.begin(), value_10_2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, value_type&&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = set.insert(set.begin(), std::move(value_10_1));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);

        CHECK(value_10_1.first  == -10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = set.insert(set.begin(), std::move(value_10_2));

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(set.size() == 2);

        CHECK(value_10_2.first  == -10);
        CHECK(value_10_2.second == -2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(InputIt, InputIt")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    std::vector<typename set_type::value_type> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    set.insert(data.begin(), data.end());

    CHECK(set.size() == 5);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test insert(std::initializer_list")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    CHECK(set.size() == 0);

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    set.insert(ilist);

    CHECK(set.size() == 5);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);
}
END_TEST()

BEGIN_TEST("Test insert_range(Range&&")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 20 20");

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::istream<int>(iss));
        #else
        set.insert_range(sfl::test::istream_view<int>(iss));
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
    #endif

    // Forward iterator
    {
        std::vector<typename set_type::value_type> data({10, 20, 30, 20, 20});

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::all(data));
        #else
        set.insert_range(data);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 5);
        CHECK(set.max_size() > 0);
        CHECK(*NTH(set, 0) == 10);
        CHECK(*NTH(set, 1) == 20);
        CHECK(*NTH(set, 2) == 20);
        CHECK(*NTH(set, 3) == 20);
        CHECK(*NTH(set, 4) == 30);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 30); CHECK(NTH(set, 2)->second == 1);

    {
        const auto res = set.erase(set.begin());

        CHECK(res == set.begin());
        CHECK(set.size() == 2);
        CHECK(NTH(set, 0)->first == 20); CHECK(NTH(set, 0)->second == 1);
        CHECK(NTH(set, 1)->first == 30); CHECK(NTH(set, 1)->second == 1);
    }

    {
        const auto res = set.erase(set.begin());

        CHECK(res == set.begin());
        CHECK(set.size() == 1);
        CHECK(NTH(set, 0)->first == 30); CHECK(NTH(set, 0)->second == 1);
    }

    {
        const auto res = set.erase(set.begin());

        CHECK(res == set.end());
        CHECK(set.size() == 0);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 30); CHECK(NTH(set, 2)->second == 1);

    const auto res = set.erase(NTH(set, 1), NTH(set, 2));

    CHECK(res == NTH(set, 1));
    CHECK(set.size() == 2);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 30); CHECK(NTH(set, 0)->second == 1);
}
END_TEST()

BEGIN_TEST("Test erase(const Key&)")
{
    using key_type = xint;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(30);
    set.emplace(20);
    set.emplace(20);

    CHECK(set.size() == 5);
    CHECK(*NTH(set, 0) == 10);
    CHECK(*NTH(set, 1) == 20);
    CHECK(*NTH(set, 2) == 20);
    CHECK(*NTH(set, 3) == 20);
    CHECK(*NTH(set, 4) == 30);

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);
    CHECK(set.size() == 4);
    CHECK(*NTH(set, 0) == 10);
    CHECK(*NTH(set, 1) == 20);
    CHECK(*NTH(set, 2) == 20);
    CHECK(*NTH(set, 3) == 20);

    CHECK(set.erase(20) == 3);
    CHECK(set.erase(20) == 0);
    CHECK(set.size() == 1);
    CHECK(*NTH(set, 0) == 10);

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);
    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test erase(K&&)")
{
    using key_type = xobj;
    using key_compare = xobj::less;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(30);
    set.emplace(20);
    set.emplace(20);

    CHECK(set.size() == 5);
    CHECK(NTH(set, 0)->value() == 10);
    CHECK(NTH(set, 1)->value() == 20);
    CHECK(NTH(set, 2)->value() == 20);
    CHECK(NTH(set, 3)->value() == 20);
    CHECK(NTH(set, 4)->value() == 30);

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);
    CHECK(set.size() == 4);
    CHECK(NTH(set, 0)->value() == 10);
    CHECK(NTH(set, 1)->value() == 20);
    CHECK(NTH(set, 2)->value() == 20);
    CHECK(NTH(set, 3)->value() == 20);

    CHECK(set.erase(20) == 3);
    CHECK(set.erase(20) == 0);
    CHECK(set.size() == 1);
    CHECK(NTH(set, 0)->value() == 10);

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);
    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);
    set2.emplace(70, 2);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    CHECK(set2.size() == 4);
    CHECK(NTH(set2, 0)->first == 40); CHECK(NTH(set2, 0)->second == 2);
    CHECK(NTH(set2, 1)->first == 50); CHECK(NTH(set2, 1)->second == 2);
    CHECK(NTH(set2, 2)->first == 60); CHECK(NTH(set2, 2)->second == 2);
    CHECK(NTH(set2, 3)->first == 70); CHECK(NTH(set2, 3)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    set1.swap(set2);

    CHECK(set1.size() == 4);
    CHECK(NTH(set1, 0)->first == 40); CHECK(NTH(set1, 0)->second == 2);
    CHECK(NTH(set1, 1)->first == 50); CHECK(NTH(set1, 1)->second == 2);
    CHECK(NTH(set1, 2)->first == 60); CHECK(NTH(set1, 2)->second == 2);
    CHECK(NTH(set1, 3)->first == 70); CHECK(NTH(set1, 3)->second == 2);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    set1.swap(set2);

    CHECK(set1.size() == 3);
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    CHECK(set2.size() == 4);
    CHECK(NTH(set2, 0)->first == 40); CHECK(NTH(set2, 0)->second == 2);
    CHECK(NTH(set2, 1)->first == 50); CHECK(NTH(set2, 1)->second == 2);
    CHECK(NTH(set2, 2)->first == 60); CHECK(NTH(set2, 2)->second == 2);
    CHECK(NTH(set2, 3)->first == 70); CHECK(NTH(set2, 3)->second == 2);
}
END_TEST()

///////////////////////////////////////////////////////////////////////////////

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

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
    CHECK(NTH(set1, 0)->first == 10); CHECK(NTH(set1, 0)->second == 1);
    CHECK(NTH(set1, 1)->first == 20); CHECK(NTH(set1, 1)->second == 1);
    CHECK(NTH(set1, 2)->first == 30); CHECK(NTH(set1, 2)->second == 1);

    CHECK(set2.size() == 5);
    CHECK(NTH(set2, 0)->first == 40); CHECK(NTH(set2, 0)->second == 2);
    CHECK(NTH(set2, 1)->first == 50); CHECK(NTH(set2, 1)->second == 2);
    CHECK(NTH(set2, 2)->first == 60); CHECK(NTH(set2, 2)->second == 2);
    CHECK(NTH(set2, 3)->first == 70); CHECK(NTH(set2, 3)->second == 2);
    CHECK(NTH(set2, 4)->first == 80); CHECK(NTH(set2, 4)->second == 2);

    ///////////////////////////////////////////////////////////////////////////

    swap(set1, set2);

    CHECK(set1.size() == 5);
    CHECK(NTH(set1, 0)->first == 40); CHECK(NTH(set1, 0)->second == 2);
    CHECK(NTH(set1, 1)->first == 50); CHECK(NTH(set1, 1)->second == 2);
    CHECK(NTH(set1, 2)->first == 60); CHECK(NTH(set1, 2)->second == 2);
    CHECK(NTH(set1, 3)->first == 70); CHECK(NTH(set1, 3)->second == 2);
    CHECK(NTH(set1, 4)->first == 80); CHECK(NTH(set1, 4)->second == 2);

    CHECK(set2.size() == 3);
    CHECK(NTH(set2, 0)->first == 10); CHECK(NTH(set2, 0)->second == 1);
    CHECK(NTH(set2, 1)->first == 20); CHECK(NTH(set2, 1)->second == 1);
    CHECK(NTH(set2, 2)->first == 30); CHECK(NTH(set2, 2)->second == 1);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase_if(container&, Predicate)")
{
    using key_type = xint_xint;
    using key_compare = std::less<xint_xint>;
    using allocator_type = TPARAM_ALLOCATOR<key_type>;
    using set_type = sfl::multiset<key_type, key_compare, allocator_type>;

    using const_reference = typename set_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(20, 2);
    set.emplace(20, 3);
    set.emplace(30, 1);

    CHECK(set.size() == 5);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 20); CHECK(NTH(set, 1)->second == 1);
    CHECK(NTH(set, 2)->first == 20); CHECK(NTH(set, 2)->second == 2);
    CHECK(NTH(set, 3)->first == 20); CHECK(NTH(set, 3)->second == 3);
    CHECK(NTH(set, 4)->first == 30); CHECK(NTH(set, 4)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 3);
    CHECK(set.size() == 2);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 30); CHECK(NTH(set, 1)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(set.size() == 2);
    CHECK(NTH(set, 0)->first == 10); CHECK(NTH(set, 0)->second == 1);
    CHECK(NTH(set, 1)->first == 30); CHECK(NTH(set, 1)->second == 1);
}
END_TEST()

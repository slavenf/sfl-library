using sfl::test::xint;
using sfl::test::xint_xint;
using sfl::test::xobj;

BEGIN_TEST("Test static_capacity and static_bucket_count")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    CHECK((set_type::static_capacity == 32));
    CHECK((set_type::static_bucket_count == 32));
}
END_TEST()

BEGIN_TEST("Test container()")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    CHECK(set.empty() == true);
    CHECK(set.full() == false);
    CHECK(set.size() == 0);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 32);
}
END_TEST()

BEGIN_TEST("Test container(const Hash&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

    set_type set(hash);

    CHECK(set.empty() == true);
    CHECK(set.full() == false);
    CHECK(set.size() == 0);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 32);
}
END_TEST()

BEGIN_TEST("Test container(const Hash&, const KeyEqual&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

    typename set_type::key_equal equal;

    set_type set(hash, equal);

    CHECK(set.empty() == true);
    CHECK(set.full() == false);
    CHECK(set.size() == 0);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 32);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Hash&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

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

    set_type set(data.begin(), data.end(), hash);

    CHECK(set.empty() == false);
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt, const Hash&, const KeyEqual&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

    typename set_type::key_equal equal;

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

    set_type set(data.begin(), data.end(), hash, equal);

    CHECK(set.empty() == false);
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Hash&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    set_type set(ilist, hash);

    CHECK(set.empty() == false);
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list, const Hash&, const KeyEqual&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    typename set_type::hasher hash;

    typename set_type::key_equal equal;

    std::initializer_list<typename set_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    set_type set(ilist, hash, equal);

    CHECK(set.empty() == false);
    CHECK(set.full() == false);
    CHECK(set.size() == 3);
    CHECK(set.max_size() == 32);
    CHECK(set.capacity() == 32);
    CHECK(set.available() == 29);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);
    set1.emplace(20, 2);
    set1.emplace(20, 3);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 2) == 0);
    CHECK(COUNT_KV(set1, 20, 3) == 0);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    set_type set2(set1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 2) == 0);
    CHECK(COUNT_KV(set2, 20, 3) == 0);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set1;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);
    set1.emplace(20, 2);
    set1.emplace(20, 3);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 2) == 0);
    CHECK(COUNT_KV(set1, 20, 3) == 0);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    set_type set2(std::move(set1));

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, -10, -1) == 1);
    CHECK(COUNT_KV(set1, -20, -1) == 1);
    CHECK(COUNT_KV(set1, -20, -2) == 0);
    CHECK(COUNT_KV(set1, -20, -3) == 0);
    CHECK(COUNT_KV(set1, -30, -1) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 2) == 0);
    CHECK(COUNT_KV(set2, 20, 3) == 0);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<xint_xint>(iss)));
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<xint_xint>(iss)));
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
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

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data));
        #else
        set_type set(sfl::from_range_t(), data);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const Hash&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        typename set_type::hasher hash;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<xint_xint>(iss)), hash);
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<xint_xint>(iss)), hash);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
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

        typename set_type::hasher hash;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data), hash);
        #else
        set_type set(sfl::from_range_t(), data, hash);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&, const Hash&, const KeyEqual&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        typename set_type::hasher hash;

        typename set_type::key_equal equal;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set((sfl::from_range_t()), (std::views::istream<xint_xint>(iss)), hash, equal);
        #else
        set_type set((sfl::from_range_t()), (sfl::test::istream_view<xint_xint>(iss)), hash, equal);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
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

        typename set_type::hasher hash;

        typename set_type::key_equal equal;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set_type set(sfl::from_range_t(), std::views::all(data), hash, equal);
        #else
        set_type set(sfl::from_range_t(), data, hash, equal);
        #endif

        CHECK(set.empty() == false);
        CHECK(set.size() == 3);
        CHECK(set.max_size() > 0);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(const container&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);
    set1.emplace(20, 2);
    set1.emplace(20, 3);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 2) == 0);
    CHECK(COUNT_KV(set1, 20, 3) == 0);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 40, 2) == 1);
    CHECK(COUNT_KV(set2, 50, 2) == 1);
    CHECK(COUNT_KV(set2, 60, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    set2 = set1;

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 2) == 0);
    CHECK(COUNT_KV(set1, 20, 3) == 0);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 2) == 0);
    CHECK(COUNT_KV(set2, 20, 3) == 0);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set1, set2;

    set1.emplace(10, 1);
    set1.emplace(20, 1);
    set1.emplace(30, 1);
    set1.emplace(20, 2);
    set1.emplace(20, 3);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, 10, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 1) == 1);
    CHECK(COUNT_KV(set1, 20, 2) == 0);
    CHECK(COUNT_KV(set1, 20, 3) == 0);
    CHECK(COUNT_KV(set1, 30, 1) == 1);

    set2.emplace(40, 2);
    set2.emplace(50, 2);
    set2.emplace(60, 2);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 40, 2) == 1);
    CHECK(COUNT_KV(set2, 50, 2) == 1);
    CHECK(COUNT_KV(set2, 60, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    set2 = std::move(set1);

    CHECK(set1.size() == 3);
    CHECK(COUNT_KV(set1, -10, -1) == 1);
    CHECK(COUNT_KV(set1, -20, -1) == 1);
    CHECK(COUNT_KV(set1, -20, -2) == 0);
    CHECK(COUNT_KV(set1, -20, -3) == 0);
    CHECK(COUNT_KV(set1, -30, -1) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 2) == 0);
    CHECK(COUNT_KV(set2, 20, 3) == 0);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test operator=(std::initializer_list)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);
    set.emplace(20, 2);
    set.emplace(20, 3);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);

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

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 40, 2) == 1);
    CHECK(COUNT_KV(set, 50, 2) == 1);
    CHECK(COUNT_KV(set, 50, 3) == 0);
    CHECK(COUNT_KV(set, 50, 4) == 0);
    CHECK(COUNT_KV(set, 60, 2) == 1);
}
END_TEST()

BEGIN_TEST("Test hash_function()")
{
    {
        using key_type = xint;
        constexpr std::size_t N = 32;
        using set_type = sfl::static_unordered_set<key_type, N>;

        set_type set;

        auto hash_function = set.hash_function();

        (void)hash_function(10);
        (void)hash_function(10);
        (void)hash_function(20);
        (void)hash_function(20);
    }

    {
        using key_type = xobj;
        constexpr std::size_t N = 32;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

        set_type set;

        auto hash_function = set.hash_function();

        (void)hash_function(xobj(10));
        (void)hash_function(xobj(10));
        (void)hash_function(xobj(20));
        (void)hash_function(xobj(20));
    }
}
END_TEST()

BEGIN_TEST("Test key_eq()")
{
    {
        using key_type = xint;
        constexpr std::size_t N = 32;
        using set_type = sfl::static_unordered_set<key_type, N>;

        set_type set;

        auto key_eq = set.key_eq();

        CHECK(key_eq(10, 10) == true);
        CHECK(key_eq(10, 20) == false);
        CHECK(key_eq(20, 10) == false);
        CHECK(key_eq(20, 20) == true);
    }

    {
        using key_type = xobj;
        constexpr std::size_t N = 32;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

        set_type set;

        auto key_eq = set.key_eq();

        CHECK(key_eq(xobj(10), 10) == true);
        CHECK(key_eq(xobj(10), 20) == false);
        CHECK(key_eq(xobj(20), 10) == false);
        CHECK(key_eq(xobj(20), 20) == true);
    }
}
END_TEST()

BEGIN_TEST("Test begin, end, cbegin, cend")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(20, 2);
    set.emplace(20, 3);
    set.emplace(30, 1);

    // iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = set.begin(); it != set.end(); ++it)
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
        CHECK(count_20_2 == 0);
        CHECK(count_20_3 == 0);
        CHECK(count_30_1 == 1);
    }

    // const_iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = set.cbegin(); it != set.cend(); ++it)
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
        CHECK(count_20_2 == 0);
        CHECK(count_20_3 == 0);
        CHECK(count_30_1 == 1);
    }

    // iterator + const_iterator
    {
        int count_10_1 = 0;
        int count_20_1 = 0;
        int count_20_2 = 0;
        int count_20_3 = 0;
        int count_30_1 = 0;

        for (auto it = set.begin(); it != set.cend(); ++it)
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
        CHECK(count_20_2 == 0);
        CHECK(count_20_3 == 0);
        CHECK(count_30_1 == 1);
    }
}
END_TEST()

BEGIN_TEST("Test equal_range, find, count, contains")
{
    // xint
    {
        using key_type = xint;
        constexpr std::size_t N = 32;
        using set_type = sfl::static_unordered_set<key_type, N>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(40);
        set.emplace(60);
        set.emplace(60);
        set.emplace(60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.equal_range(10) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(20) == std::make_pair(set.find(20), std::next(set.find(20))));
        CHECK(set.equal_range(30) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(40) == std::make_pair(set.find(40), std::next(set.find(40))));
        CHECK(set.equal_range(50) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(60) == std::make_pair(set.find(60), std::next(set.find(60))));
        CHECK(set.equal_range(70) == std::make_pair(set.end(), set.end()));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.find(10) == set.end());
        CHECK(set.find(20) != set.end());
        CHECK(set.find(30) == set.end());
        CHECK(set.find(40) != set.end());
        CHECK(set.find(50) == set.end());
        CHECK(set.find(60) != set.end());
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
        constexpr std::size_t N = 32;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(40);
        set.emplace(60);
        set.emplace(60);
        set.emplace(60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.equal_range(10) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(20) == std::make_pair(set.find(20), std::next(set.find(20))));
        CHECK(set.equal_range(30) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(40) == std::make_pair(set.find(40), std::next(set.find(40))));
        CHECK(set.equal_range(50) == std::make_pair(set.end(), set.end()));
        CHECK(set.equal_range(60) == std::make_pair(set.find(60), std::next(set.find(60))));
        CHECK(set.equal_range(70) == std::make_pair(set.end(), set.end()));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.find(10) == set.end());
        CHECK(set.find(20) != set.end());
        CHECK(set.find(30) == set.end());
        CHECK(set.find(40) != set.end());
        CHECK(set.find(50) == set.end());
        CHECK(set.find(60) != set.end());
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

BEGIN_TEST("Test emplace(Args&&...)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.emplace(10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.emplace(10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test emplace_hint(const_iterator, Args&&...)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.emplace_hint(set.begin(), 10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.emplace_hint(set.begin(), 10, 2);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const value_type&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = set.insert(value_10_1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = set.insert(value_10_2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test insert(value_type&&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    CHECK(set.size() == 0);

    using value_type = typename set_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = set.insert(std::move(value_10_1));

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);

        CHECK(value_10_1.first  == -10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = set.insert(std::move(value_10_2));

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(set.size() == 1);

        CHECK(value_10_2.first  == +10);
        CHECK(value_10_2.second == +2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(K&&)")
{
    using key_type = xobj;
    constexpr std::size_t N = 32;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.insert(10);

        CHECK(res.second == true);
        CHECK(res.first->value() == 10);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.insert(10);

        CHECK(res.second == false);
        CHECK(res.first->value() == 10);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const value_type&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, value_type&&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(set.size() == 1);

        CHECK(value_10_2.first  == +10);
        CHECK(value_10_2.second == +2);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, K&&)")
{
    using key_type = xobj;
    constexpr std::size_t N = 32;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

    set_type set;

    CHECK(set.size() == 0);

    {
        const auto res = set.insert(set.begin(), 10);

        CHECK(res->value() == 10);

        CHECK(set.size() == 1);
    }

    {
        const auto res = set.insert(set.begin(), 10);

        CHECK(res->value() == 10);

        CHECK(set.size() == 1);
    }
}
END_TEST()

BEGIN_TEST("Test insert(InputIt, InputIt")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test insert(std::initializer_list")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test insert_range(Range&&")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::istream<xint_xint>(iss));
        #else
        set.insert_range(sfl::test::istream_view<xint_xint>(iss));
        #endif

        CHECK(set.size() == 3);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
    #endif

    // Forward iterator
    {
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

        set_type set;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        set.insert_range(std::views::all(data));
        #else
        set.insert_range(data);
        #endif

        CHECK(set.size() == 3);
        CHECK(COUNT_KV(set, 10, 1) == 1);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 20, 2) == 0);
        CHECK(COUNT_KV(set, 20, 3) == 0);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);

    {
        auto it = set.begin();
        while (it != set.end())
        {
            if (it->first == 10)
            {
                break;
            }
            ++it;
        }

        const auto res = set.erase(it);

        if (res != set.end())
        {
            CHECK(res->first == 20 || res->first == 30);
        }

        CHECK(set.size() == 2);
        CHECK(COUNT_KV(set, 20, 1) == 1);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }

    {
        auto it = set.begin();
        while (it != set.end())
        {
            if (it->first == 20)
            {
                break;
            }
            ++it;
        }

        const auto res = set.erase(it);

        if (res != set.end())
        {
            CHECK(res->first == 30);
        }

        CHECK(set.size() == 1);
        CHECK(COUNT_KV(set, 30, 1) == 1);
    }

    {
        auto it = set.begin();
        while (it != set.end())
        {
            if (it->first == 30)
            {
                break;
            }
            ++it;
        }

        const auto res = set.erase(it);

        CHECK(res == set.end());
        CHECK(set.size() == 0);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);

    auto it = set.begin();
    while (it != set.end())
    {
        if (it->first == 20)
        {
            break;
        }
        ++it;
    }

    const auto res = set.erase(it, std::next(it));

    if (res != set.end())
    {
        CHECK(res->first == 10 || res->first == 30);
    }

    CHECK(set.size() == 2);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test erase(const Key&)")
{
    using key_type = xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(20);
    set.emplace(20);
    set.emplace(30);

    CHECK(set.size() == 3);
    CHECK(set.count(10) == 1);
    CHECK(set.count(20) == 1);
    CHECK(set.count(30) == 1);

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);
    CHECK(set.size() == 2);
    CHECK(set.count(10) == 1);
    CHECK(set.count(20) == 1);

    CHECK(set.erase(20) == 1);
    CHECK(set.erase(20) == 0);
    CHECK(set.size() == 1);
    CHECK(set.count(10) == 1);

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);
    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test erase(K&&)")
{
    using key_type = xobj;
    constexpr std::size_t N = 32;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

    set_type set;

    set.emplace(10);
    set.emplace(20);
    set.emplace(20);
    set.emplace(20);
    set.emplace(30);

    CHECK(set.size() == 3);
    CHECK(set.count(10) == 1);
    CHECK(set.count(20) == 1);
    CHECK(set.count(30) == 1);

    CHECK(set.erase(30) == 1);
    CHECK(set.erase(30) == 0);
    CHECK(set.size() == 2);
    CHECK(set.count(10) == 1);
    CHECK(set.count(20) == 1);

    CHECK(set.erase(20) == 1);
    CHECK(set.erase(20) == 0);
    CHECK(set.size() == 1);
    CHECK(set.count(10) == 1);

    CHECK(set.erase(10) == 1);
    CHECK(set.erase(10) == 0);
    CHECK(set.size() == 0);
}
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

BEGIN_TEST("Test bucket interface functions")
{
    // xint
    {
        using key_type = xint;
        constexpr std::size_t N = 32;
        using set_type = sfl::static_unordered_set<key_type, N>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(60);
        set.emplace(60);
        set.emplace(60);

        CHECK(set.size() == 3);
        CHECK(set.count(20) == 1);
        CHECK(set.count(40) == 1);
        CHECK(set.count(60) == 1);

        CHECK(set.bucket_count() == 32);
        CHECK(set.max_bucket_count() == 32);

        for (int elem : {10, 30, 50, 70})
        {
            bool found = false;
            auto bucket = set.bucket(elem);
            auto it1 = set.begin(bucket);
            auto it2 = set.end(bucket);
            while (it1 != it2)
            {
                if (it1->value() == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == false);
        }

        for (int elem : {20, 40, 60})
        {
            bool found = false;
            auto bucket = set.bucket(elem);
            CHECK(set.bucket_size(bucket) > 0);
            auto it1 = set.begin(bucket);
            auto it2 = set.end(bucket);
            while (it1 != it2)
            {
                if (it1->value() == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == true);
        }

        int sum = 0;
        for (int i = 0; i < int(set.bucket_count()); ++i)
        {
            for (auto it1 = set.begin(i), it2 = set.end(i); it1 != it2; ++it1)
            {
                sum += it1->value();
            }
        }
        CHECK(sum == 120);
    }

    // xobj
    {
        using key_type = xobj;
        constexpr std::size_t N = 32;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using set_type = sfl::static_unordered_set<key_type, N, N, key_hash, key_equal>;

        set_type set;

        set.emplace(20);
        set.emplace(40);
        set.emplace(60);
        set.emplace(60);
        set.emplace(60);

        CHECK(set.size() == 3);
        CHECK(set.count(20) == 1);
        CHECK(set.count(40) == 1);
        CHECK(set.count(60) == 1);

        CHECK(set.bucket_count() == 32);
        CHECK(set.max_bucket_count() == 32);

        for (int elem : {10, 30, 50, 70})
        {
            bool found = false;
            auto bucket = set.bucket(elem);
            auto it1 = set.begin(bucket);
            auto it2 = set.end(bucket);
            while (it1 != it2)
            {
                if (it1->value() == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == false);
        }

        for (int elem : {20, 40, 60})
        {
            bool found = false;
            auto bucket = set.bucket(elem);
            CHECK(set.bucket_size(bucket) > 0);
            auto it1 = set.begin(bucket);
            auto it2 = set.end(bucket);
            while (it1 != it2)
            {
                if (it1->value() == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == true);
        }

        int sum = 0;
        for (int i = 0; i < int(set.bucket_count()); ++i)
        {
            for (auto it1 = set.begin(i), it2 = set.end(i); it1 != it2; ++it1)
            {
                sum += it1->value();
            }
        }
        CHECK(sum == 120);
    }
}
END_TEST()

BEGIN_TEST("Test hash policy functions")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    set_type set;

    set.emplace(20, 1);
    set.emplace(40, 1);
    set.emplace(60, 1);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 40, 1) == 1);
    CHECK(COUNT_KV(set, 60, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    CHECK(set.load_factor() > 0.0f);

    CHECK(set.max_load_factor() == 1.0f);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER swap(container&)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

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

    ///////////////////////////////////////////////////////////////////////////

    swap(set1, set2);

    CHECK(set1.size() == 4);
    CHECK(COUNT_KV(set1, 40, 2) == 1);
    CHECK(COUNT_KV(set1, 50, 2) == 1);
    CHECK(COUNT_KV(set1, 60, 2) == 1);
    CHECK(COUNT_KV(set1, 70, 2) == 1);

    CHECK(set2.size() == 3);
    CHECK(COUNT_KV(set2, 10, 1) == 1);
    CHECK(COUNT_KV(set2, 20, 1) == 1);
    CHECK(COUNT_KV(set2, 30, 1) == 1);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase_if(container&, Predicate)")
{
    using key_type = xint_xint;
    constexpr std::size_t N = 32;
    using set_type = sfl::static_unordered_set<key_type, N>;

    using const_reference = typename set_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    set_type set;

    set.emplace(10, 1);
    set.emplace(20, 1);
    set.emplace(30, 1);
    set.emplace(20, 2);
    set.emplace(20, 3);

    CHECK(set.size() == 3);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 20, 1) == 1);
    CHECK(COUNT_KV(set, 20, 2) == 0);
    CHECK(COUNT_KV(set, 20, 3) == 0);
    CHECK(COUNT_KV(set, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 1);
    CHECK(set.size() == 2);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(set, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(set.size() == 2);
    CHECK(COUNT_KV(set, 10, 1) == 1);
    CHECK(COUNT_KV(set, 30, 1) == 1);
}
END_TEST()

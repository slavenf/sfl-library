#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

using sfl::test::xint;
using sfl::test::xobj;

// Test container()
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const Compare&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::key_compare comp;

    map_type map(comp);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::allocator_type alloc;

    map_type map(alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const Compare&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(comp, alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
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
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, const Compare&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::key_compare comp;

    map_type map(data.begin(), data.end(), comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, const Compare&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, const Compare&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::key_compare comp;

    map_type map(ilist, comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::allocator_type alloc;

    map_type map(ilist, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, const Compare&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::initializer_list<typename map_type::value_type> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(ilist, comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(map1);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(const container&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(map1, alloc);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(std::move(map1));

    CHECK(map1.size() == 0);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(container&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(std::move(map1), alloc);

    CHECK(map1.size() == 0);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map_type map(sfl::from_range_t(), std::views::all(data));

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, const Compare&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::key_compare comp;

    map_type map(sfl::from_range_t(), std::views::all(data), comp);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::allocator_type alloc;

    map_type map(sfl::from_range_t(), std::views::all(data), alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, const Compare&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::key_compare comp;

    typename map_type::allocator_type alloc;

    map_type map(sfl::from_range_t(), std::views::all(data), comp, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test operator=(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 40); CHECK(NTH(map2, 0)->second == 2);
    CHECK(NTH(map2, 1)->first == 50); CHECK(NTH(map2, 1)->second == 2);
    CHECK(NTH(map2, 2)->first == 60); CHECK(NTH(map2, 2)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    map2 = map1;

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test operator=(container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 40); CHECK(NTH(map2, 0)->second == 2);
    CHECK(NTH(map2, 1)->first == 50); CHECK(NTH(map2, 1)->second == 2);
    CHECK(NTH(map2, 2)->first == 60); CHECK(NTH(map2, 2)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    map2 = std::move(map1);

    CHECK(map1.size() == 0);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test operator=(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

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

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 40); CHECK(NTH(map, 0)->second == 2);
    CHECK(NTH(map, 1)->first == 50); CHECK(NTH(map, 1)->second == 2);
    CHECK(NTH(map, 2)->first == 60); CHECK(NTH(map, 2)->second == 2);
}
END_STATIC_ASSERT

// Test get_allocator()
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    auto alloc = map.get_allocator();

    (void)alloc;
}
END_STATIC_ASSERT

// Test key_comp()
BEGIN_STATIC_ASSERT
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto key_comp = map.key_comp();

        CHECK(key_comp(xobj(10), 10) == false);
        CHECK(key_comp(xobj(10), 20) == true);
        CHECK(key_comp(xobj(20), 10) == false);
        CHECK(key_comp(xobj(20), 20) == false);
    }
}
END_STATIC_ASSERT

// Test value_comp()
BEGIN_STATIC_ASSERT
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        auto value_comp = map.value_comp();

        CHECK(value_comp({xobj(10), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(10), 1}, {xobj(20), 2}) == true);
        CHECK(value_comp({xobj(20), 1}, {xobj(10), 2}) == false);
        CHECK(value_comp({xobj(20), 1}, {xobj(20), 2}) == false);
    }
}
END_STATIC_ASSERT

// Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(20, 1);
    map.emplace(40, 1);
    map.emplace(60, 1);

    ///////////////////////////////////////////////////////////////////////

    auto it = map.begin();
    CHECK(it->first == 20); CHECK(it->second == 1); ++it;
    CHECK(it->first == 40); CHECK(it->second == 1); ++it;
    CHECK(it->first == 60); CHECK(it->second == 1); ++it;
    CHECK(it == map.end());

    ///////////////////////////////////////////////////////////////////////

    auto cit = map.cbegin();
    CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 40); CHECK(cit->second == 1); ++cit;
    CHECK(cit->first == 60); CHECK(cit->second == 1); ++cit;
    CHECK(cit == map.cend());

    ///////////////////////////////////////////////////////////////////////

    auto rit = map.rbegin();
    CHECK(rit->first == 60); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 40); CHECK(rit->second == 1); ++rit;
    CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
    CHECK(rit == map.rend());

    ///////////////////////////////////////////////////////////////////////

    auto crit = map.crbegin();
    CHECK(crit->first == 60); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 40); CHECK(crit->second == 1); ++crit;
    CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
    CHECK(crit == map.crend());
}
END_STATIC_ASSERT

// Test lower_bound, upper_bound, equal_range, find, count, contains
BEGIN_STATIC_ASSERT
{
    // xint, xint
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_compare = std::less<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        map.emplace(20, 1);
        map.emplace(40, 1);
        map.emplace(60, 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.lower_bound(10) == NTH(map, 0));
        CHECK(map.lower_bound(20) == NTH(map, 0));
        CHECK(map.lower_bound(30) == NTH(map, 1));
        CHECK(map.lower_bound(40) == NTH(map, 1));
        CHECK(map.lower_bound(50) == NTH(map, 2));
        CHECK(map.lower_bound(60) == NTH(map, 2));
        CHECK(map.lower_bound(70) == NTH(map, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.upper_bound(10) == NTH(map, 0));
        CHECK(map.upper_bound(20) == NTH(map, 1));
        CHECK(map.upper_bound(30) == NTH(map, 1));
        CHECK(map.upper_bound(40) == NTH(map, 2));
        CHECK(map.upper_bound(50) == NTH(map, 2));
        CHECK(map.upper_bound(60) == NTH(map, 3));
        CHECK(map.upper_bound(70) == NTH(map, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.equal_range(10) == std::make_pair(NTH(map, 0), NTH(map, 0)));
        CHECK(map.equal_range(20) == std::make_pair(NTH(map, 0), NTH(map, 1)));
        CHECK(map.equal_range(30) == std::make_pair(NTH(map, 1), NTH(map, 1)));
        CHECK(map.equal_range(40) == std::make_pair(NTH(map, 1), NTH(map, 2)));
        CHECK(map.equal_range(50) == std::make_pair(NTH(map, 2), NTH(map, 2)));
        CHECK(map.equal_range(60) == std::make_pair(NTH(map, 2), NTH(map, 3)));
        CHECK(map.equal_range(70) == std::make_pair(NTH(map, 3), NTH(map, 3)));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.find(10) == map.end());
        CHECK(map.find(20) == NTH(map, 0));
        CHECK(map.find(30) == map.end());
        CHECK(map.find(40) == NTH(map, 1));
        CHECK(map.find(50) == map.end());
        CHECK(map.find(60) == NTH(map, 2));
        CHECK(map.find(70) == map.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.count(10) == 0);
        CHECK(map.count(20) == 1);
        CHECK(map.count(30) == 0);
        CHECK(map.count(40) == 1);
        CHECK(map.count(50) == 0);
        CHECK(map.count(60) == 1);
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
        using key_compare = xobj::less;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

        map_type map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.lower_bound(10) == NTH(map, 0));
        CHECK(map.lower_bound(20) == NTH(map, 0));
        CHECK(map.lower_bound(30) == NTH(map, 1));
        CHECK(map.lower_bound(40) == NTH(map, 1));
        CHECK(map.lower_bound(50) == NTH(map, 2));
        CHECK(map.lower_bound(60) == NTH(map, 2));
        CHECK(map.lower_bound(70) == NTH(map, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.upper_bound(10) == NTH(map, 0));
        CHECK(map.upper_bound(20) == NTH(map, 1));
        CHECK(map.upper_bound(30) == NTH(map, 1));
        CHECK(map.upper_bound(40) == NTH(map, 2));
        CHECK(map.upper_bound(50) == NTH(map, 2));
        CHECK(map.upper_bound(60) == NTH(map, 3));
        CHECK(map.upper_bound(70) == NTH(map, 3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.equal_range(10) == std::make_pair(NTH(map, 0), NTH(map, 0)));
        CHECK(map.equal_range(20) == std::make_pair(NTH(map, 0), NTH(map, 1)));
        CHECK(map.equal_range(30) == std::make_pair(NTH(map, 1), NTH(map, 1)));
        CHECK(map.equal_range(40) == std::make_pair(NTH(map, 1), NTH(map, 2)));
        CHECK(map.equal_range(50) == std::make_pair(NTH(map, 2), NTH(map, 2)));
        CHECK(map.equal_range(60) == std::make_pair(NTH(map, 2), NTH(map, 3)));
        CHECK(map.equal_range(70) == std::make_pair(NTH(map, 3), NTH(map, 3)));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.find(10) == map.end());
        CHECK(map.find(20) == NTH(map, 0));
        CHECK(map.find(30) == map.end());
        CHECK(map.find(40) == NTH(map, 1));
        CHECK(map.find(50) == map.end());
        CHECK(map.find(60) == NTH(map, 2));
        CHECK(map.find(70) == map.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.count(10) == 0);
        CHECK(map.count(20) == 1);
        CHECK(map.count(30) == 0);
        CHECK(map.count(40) == 1);
        CHECK(map.count(50) == 0);
        CHECK(map.count(60) == 1);
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
END_STATIC_ASSERT

// Test emplace(Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.emplace(10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.emplace(10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test emplace_hint(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.emplace_hint(map.begin(), 10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.emplace_hint(map.begin(), 10, 2);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert(const value_type&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        const value_type value_10_1(10, 1);

        const auto res = map.insert(value_10_1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const value_type value_10_2(10, 2);

        const auto res = map.insert(value_10_2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert(value_type&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(std::move(value_10_1));

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_1.first  == +10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(std::move(value_10_2));

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_2.first  == +10);
        CHECK(value_10_2.second == +2);
    }
}
END_STATIC_ASSERT

// Test insert(P&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<long, long>;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(value_10_1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(value_10_2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, const value_type&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, value_type&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = typename map_type::value_type;

    {
        value_type value_10_1(10, 1);

        const auto res = map.insert(map.begin(), std::move(value_10_1));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_1.first  == +10);
        CHECK(value_10_1.second == -1);
    }

    {
        value_type value_10_2(10, 2);

        const auto res = map.insert(map.begin(), std::move(value_10_2));

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(value_10_2.first  == +10);
        CHECK(value_10_2.second == +2);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, P&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test insert(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test insert_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    std::vector<std::pair<int, int>> data
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

    map.insert_range(std::views::all(data));

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
}
END_STATIC_ASSERT

// Test insert_or_assign(const Key&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const key_type key_10(10);

        const auto res = map.insert_or_assign(key_10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const key_type key_10(10);

        const auto res = map.insert_or_assign(key_10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 2);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(Key&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        key_type key_10(10);

        const auto res = map.insert_or_assign(std::move(key_10), 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        key_type key_10(10);

        const auto res = map.insert_or_assign(std::move(key_10), 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 2);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(const_iterator, const Key&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const key_type key_10(10);

        const auto res = map.insert_or_assign(map.begin(), key_10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const key_type key_10(10);

        const auto res = map.insert_or_assign(map.begin(), key_10, 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(const_iterator, Key&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        key_type key_10(10);

        const auto res = map.insert_or_assign(map.begin(), std::move(key_10), 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        key_type key_10(10);

        const auto res = map.insert_or_assign(map.begin(), std::move(key_10), 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test try_emplace(const Key&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const key_type key_10(10);

        const auto res = map.try_emplace(key_10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const key_type key_10(10);

        const auto res = map.try_emplace(key_10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace(Key&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        key_type key_10(10);

        const auto res = map.try_emplace(std::move(key_10), 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        key_type key_10(10);

        const auto res = map.try_emplace(std::move(key_10), 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test try_emplace(K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_compare = xobj::less;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.try_emplace(10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first.value() == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.try_emplace(10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first.value() == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace(const_iterator, const Key&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const key_type key_10(10);

        const auto res = map.try_emplace(map.begin(), key_10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const key_type key_10(10);

        const auto res = map.try_emplace(map.begin(), key_10, 2);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace(const_iterator, Key&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        key_type key_10(10);

        const auto res = map.try_emplace(map.begin(), std::move(key_10), 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        key_type key_10(10);

        const auto res = map.try_emplace(map.begin(), std::move(key_10), 2);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test try_emplace(const_iterator, K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_compare = xobj::less;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.try_emplace(map.begin(), 10, 1);

        CHECK(res->first.value() == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.try_emplace(map.begin(), 10, 2);

        CHECK(res->first.value() == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test erase(const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    {
        const auto res = map.erase(map.begin());

        CHECK(res == map.begin());
        CHECK(map.size() == 2);
        CHECK(NTH(map, 0)->first == 20); CHECK(NTH(map, 0)->second == 1);
        CHECK(NTH(map, 1)->first == 30); CHECK(NTH(map, 1)->second == 1);
    }

    {
        const auto res = map.erase(map.begin());

        CHECK(res == map.begin());
        CHECK(map.size() == 1);
        CHECK(NTH(map, 0)->first == 30); CHECK(NTH(map, 0)->second == 1);
    }

    {
        const auto res = map.erase(map.begin());

        CHECK(res == map.end());
        CHECK(map.size() == 0);
    }
}
END_STATIC_ASSERT

// Test erase(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    const auto res = map.erase(NTH(map, 1), NTH(map, 2));

    CHECK(res == NTH(map, 1));
    CHECK(map.size() == 2);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 30); CHECK(NTH(map, 0)->second == 1);
}
END_STATIC_ASSERT

// Test erase(const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 2);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);

    CHECK(map.erase(20) == 1);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);
    CHECK(map.size() == 0);
}
END_STATIC_ASSERT

// Test erase(K&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_compare = xobj::less;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first.value() == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first.value() == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first.value() == 30); CHECK(NTH(map, 2)->second == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 2);
    CHECK(NTH(map, 0)->first.value() == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first.value() == 20); CHECK(NTH(map, 1)->second == 1);

    CHECK(map.erase(20) == 1);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(NTH(map, 0)->first.value() == 10); CHECK(NTH(map, 0)->second == 1);

    CHECK(map.erase(10) == 1);
    CHECK(map.erase(10) == 0);
    CHECK(map.size() == 0);
}
END_STATIC_ASSERT

// Test swap(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);

    map2.emplace(40, 2);
    map2.emplace(50, 2);
    map2.emplace(60, 2);
    map2.emplace(70, 2);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    CHECK(map2.size() == 4);
    CHECK(NTH(map2, 0)->first == 40); CHECK(NTH(map2, 0)->second == 2);
    CHECK(NTH(map2, 1)->first == 50); CHECK(NTH(map2, 1)->second == 2);
    CHECK(NTH(map2, 2)->first == 60); CHECK(NTH(map2, 2)->second == 2);
    CHECK(NTH(map2, 3)->first == 70); CHECK(NTH(map2, 3)->second == 2);

    ///////////////////////////////////////////////////////////////////////

    map1.swap(map2);

    CHECK(map1.size() == 4);
    CHECK(NTH(map1, 0)->first == 40); CHECK(NTH(map1, 0)->second == 2);
    CHECK(NTH(map1, 1)->first == 50); CHECK(NTH(map1, 1)->second == 2);
    CHECK(NTH(map1, 2)->first == 60); CHECK(NTH(map1, 2)->second == 2);
    CHECK(NTH(map1, 3)->first == 70); CHECK(NTH(map1, 3)->second == 2);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////

    map1.swap(map2);

    CHECK(map1.size() == 3);
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    CHECK(map2.size() == 4);
    CHECK(NTH(map2, 0)->first == 40); CHECK(NTH(map2, 0)->second == 2);
    CHECK(NTH(map2, 1)->first == 50); CHECK(NTH(map2, 1)->second == 2);
    CHECK(NTH(map2, 2)->first == 60); CHECK(NTH(map2, 2)->second == 2);
    CHECK(NTH(map2, 3)->first == 70); CHECK(NTH(map2, 3)->second == 2);
}
END_STATIC_ASSERT

// Test at(const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.at(10) == 1);
    CHECK(map.at(20) == 1);
    CHECK(map.at(30) == 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    map.at(10) = 2;
    map.at(20) = 2;
    map.at(30) = 2;

    CHECK(map.at(10) == 2);
    CHECK(map.at(20) == 2);
    CHECK(map.at(30) == 2);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 2);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 2);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 2);
}
END_STATIC_ASSERT

// Test operator[](const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    key_type key_10 = 10;
    key_type key_20 = 20;
    key_type key_30 = 30;
    key_type key_40 = 40;
    key_type key_50 = 50;
    key_type key_60 = 60;

    map[key_10] = 2;
    map[key_20] = 2;
    map[key_30] = 2;
    map[key_40] = 2;
    map[key_50] = 2;
    map[key_60] = 2;

    CHECK(map.size() == 6);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 2);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 2);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 2);
    CHECK(NTH(map, 3)->first == 40); CHECK(NTH(map, 3)->second == 2);
    CHECK(NTH(map, 4)->first == 50); CHECK(NTH(map, 4)->second == 2);
    CHECK(NTH(map, 5)->first == 60); CHECK(NTH(map, 5)->second == 2);

    CHECK(key_10 == 10);
    CHECK(key_20 == 20);
    CHECK(key_30 == 30);
    CHECK(key_40 == 40);
    CHECK(key_50 == 50);
    CHECK(key_60 == 60);
}
END_STATIC_ASSERT

// Test operator[](Key&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    key_type key_10 = 10;
    key_type key_20 = 20;
    key_type key_30 = 30;
    key_type key_40 = 40;
    key_type key_50 = 50;
    key_type key_60 = 60;

    map[std::move(key_10)] = 2;
    map[std::move(key_20)] = 2;
    map[std::move(key_30)] = 2;
    map[std::move(key_40)] = 2;
    map[std::move(key_50)] = 2;
    map[std::move(key_60)] = 2;

    CHECK(map.size() == 6);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 2);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 2);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 2);
    CHECK(NTH(map, 3)->first == 40); CHECK(NTH(map, 3)->second == 2);
    CHECK(NTH(map, 4)->first == 50); CHECK(NTH(map, 4)->second == 2);
    CHECK(NTH(map, 5)->first == 60); CHECK(NTH(map, 5)->second == 2);
}
END_STATIC_ASSERT

// Test operator[](K&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_compare = xobj::less;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first.value() == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first.value() == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first.value() == 30); CHECK(NTH(map, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    map[10] = 2;
    map[20] = 2;
    map[30] = 2;
    map[40] = 2;
    map[50] = 2;
    map[60] = 2;

    CHECK(map.size() == 6);
    CHECK(NTH(map, 0)->first.value() == 10); CHECK(NTH(map, 0)->second == 2);
    CHECK(NTH(map, 1)->first.value() == 20); CHECK(NTH(map, 1)->second == 2);
    CHECK(NTH(map, 2)->first.value() == 30); CHECK(NTH(map, 2)->second == 2);
    CHECK(NTH(map, 3)->first.value() == 40); CHECK(NTH(map, 3)->second == 2);
    CHECK(NTH(map, 4)->first.value() == 50); CHECK(NTH(map, 4)->second == 2);
    CHECK(NTH(map, 5)->first.value() == 60); CHECK(NTH(map, 5)->second == 2);
}
END_STATIC_ASSERT

// Test NON-MEMBER comparison operators
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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
END_STATIC_ASSERT

// Test NON-MEMBER swap(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

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
    CHECK(NTH(map1, 0)->first == 10); CHECK(NTH(map1, 0)->second == 1);
    CHECK(NTH(map1, 1)->first == 20); CHECK(NTH(map1, 1)->second == 1);
    CHECK(NTH(map1, 2)->first == 30); CHECK(NTH(map1, 2)->second == 1);

    CHECK(map2.size() == 5);
    CHECK(NTH(map2, 0)->first == 40); CHECK(NTH(map2, 0)->second == 2);
    CHECK(NTH(map2, 1)->first == 50); CHECK(NTH(map2, 1)->second == 2);
    CHECK(NTH(map2, 2)->first == 60); CHECK(NTH(map2, 2)->second == 2);
    CHECK(NTH(map2, 3)->first == 70); CHECK(NTH(map2, 3)->second == 2);
    CHECK(NTH(map2, 4)->first == 80); CHECK(NTH(map2, 4)->second == 2);

    ///////////////////////////////////////////////////////////////////////////

    swap(map1, map2);

    CHECK(map1.size() == 5);
    CHECK(NTH(map1, 0)->first == 40); CHECK(NTH(map1, 0)->second == 2);
    CHECK(NTH(map1, 1)->first == 50); CHECK(NTH(map1, 1)->second == 2);
    CHECK(NTH(map1, 2)->first == 60); CHECK(NTH(map1, 2)->second == 2);
    CHECK(NTH(map1, 3)->first == 70); CHECK(NTH(map1, 3)->second == 2);
    CHECK(NTH(map1, 4)->first == 80); CHECK(NTH(map1, 4)->second == 2);

    CHECK(map2.size() == 3);
    CHECK(NTH(map2, 0)->first == 10); CHECK(NTH(map2, 0)->second == 1);
    CHECK(NTH(map2, 1)->first == 20); CHECK(NTH(map2, 1)->second == 1);
    CHECK(NTH(map2, 2)->first == 30); CHECK(NTH(map2, 2)->second == 1);
}
END_STATIC_ASSERT

// Test NON-MEMBER erase_if(container&, Predicate)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_compare = std::less<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::map<key_type, mapped_type, key_compare, allocator_type>;

    using const_reference = typename map_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
    CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 1);
    CHECK(map.size() == 2);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 30); CHECK(NTH(map, 1)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(map.size() == 2);
    CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
    CHECK(NTH(map, 1)->first == 30); CHECK(NTH(map, 1)->second == 1);
}
END_STATIC_ASSERT

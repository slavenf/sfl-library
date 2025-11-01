#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

using sfl::test::xint;
using sfl::test::xobj;

// Test container()
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::allocator_type alloc;

    map_type map;

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map(11);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::allocator_type alloc;

    map_type map(11, alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Hash&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::hasher hash;

    map_type map(11, hash);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Hash&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::hasher hash;

    typename map_type::allocator_type alloc;

    map_type map(11, hash, alloc);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Hash&, const KeyEqual&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    map_type map(11, hash, equal);

    CHECK(map.empty() == true);
    CHECK(map.size() == 0);
    CHECK(map.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Hash&, const KeyEqual&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    typename map_type::allocator_type alloc;

    map_type map(11, hash, equal, alloc);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
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
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map_type map(data.begin(), data.end(), 11);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
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

    map_type map(data.begin(), data.end(), 11, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type, const Hash&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    map_type map(data.begin(), data.end(), 11, hash);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type, const Hash&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), 11, hash, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type, const Hash&, const KeyEqual&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    map_type map(data.begin(), data.end(), 11, hash, equal);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, size_type, const Hash&, const KeyEqual&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    typename map_type::allocator_type alloc;

    map_type map(data.begin(), data.end(), 11, hash, equal, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
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
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    map_type map(ilist, 11);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::allocator_type alloc;

    map_type map(ilist, 11, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type, const Hash&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::hasher hash;

    map_type map(ilist, 11, hash);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type, const Hash&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::hasher hash;

    typename map_type::allocator_type alloc;

    map_type map(ilist, 11, hash, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type, const Hash&, const KeyEqual&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    map_type map(ilist, 11, hash, equal);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, size_type, const Hash&, const KeyEqual&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    typename map_type::allocator_type alloc;

    map_type map(ilist, 11, hash, equal, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(map1);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(const container&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(map1, alloc);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    map_type map2(std::move(map1));

    CHECK(map1.size() == 0);
    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(container&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    typename map_type::allocator_type alloc;

    map_type map2(std::move(map1), alloc);

    if (map1.size() == 3)
    {
        // Elements are moved one-by-one
        CHECK(COUNT_KV(map1, +10, -1) == 1);
        CHECK(COUNT_KV(map1, +20, -1) == 1);
        CHECK(COUNT_KV(map1, +20, -2) == 0);
        CHECK(COUNT_KV(map1, +20, -3) == 0);
        CHECK(COUNT_KV(map1, +30, -1) == 1);
    }
    else
    {
        CHECK(map1.size() == 0);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
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
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    map_type map(sfl::from_range_t(), std::views::all(data), 11);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
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

    map_type map(sfl::from_range_t(), std::views::all(data), 11, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type, const Hash&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    map_type map(sfl::from_range_t(), std::views::all(data), 11, hash);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type, const Hash&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::allocator_type alloc;

    map_type map(sfl::from_range_t(), std::views::all(data), 11, hash, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type, const Hash&, const KeyEqual&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    map_type map(sfl::from_range_t(), std::views::all(data), 11, hash, equal);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, size_type, const Hash&, const KeyEqual&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
    (
        {
            {10, 1},
            {20, 1},
            {30, 1},
            {20, 2},
            {20, 3}
        }
    );

    typename map_type::hasher hash;

    typename map_type::key_equal equal;

    typename map_type::allocator_type alloc;

    map_type map(sfl::from_range_t(), std::views::all(data), 11, hash, equal, alloc);

    CHECK(map.empty() == false);
    CHECK(map.size() == 3);
    CHECK(map.max_size() > 0);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test operator=(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
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

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
    CHECK(COUNT_KV(map1, 30, 1) == 1);

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test operator=(container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map1, map2;

    map1.emplace(10, 1);
    map1.emplace(20, 1);
    map1.emplace(30, 1);
    map1.emplace(20, 2);
    map1.emplace(20, 3);

    CHECK(map1.size() == 3);
    CHECK(COUNT_KV(map1, 10, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 1) == 1);
    CHECK(COUNT_KV(map1, 20, 2) == 0);
    CHECK(COUNT_KV(map1, 20, 3) == 0);
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

    if (map1.size() == 3)
    {
        // Elements are move one-by-one
        CHECK(COUNT_KV(map1, +10, -1) == 1);
        CHECK(COUNT_KV(map1, +20, -1) == 1);
        CHECK(COUNT_KV(map1, +20, -2) == 0);
        CHECK(COUNT_KV(map1, +20, -3) == 0);
        CHECK(COUNT_KV(map1, +30, -1) == 1);
    }
    else
    {
        CHECK(map1.size() == 0);
    }

    CHECK(map2.size() == 3);
    CHECK(COUNT_KV(map2, 10, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 1) == 1);
    CHECK(COUNT_KV(map2, 20, 2) == 0);
    CHECK(COUNT_KV(map2, 20, 3) == 0);
    CHECK(COUNT_KV(map2, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test operator=(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {40, 2},
        {50, 2},
        {60, 2},
        {50, 3},
        {50, 4}
    };

    map = ilist;

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 40, 2) == 1);
    CHECK(COUNT_KV(map, 50, 2) == 1);
    CHECK(COUNT_KV(map, 50, 3) == 0);
    CHECK(COUNT_KV(map, 50, 4) == 0);
    CHECK(COUNT_KV(map, 60, 2) == 1);
}
END_STATIC_ASSERT

// Test get_allocator()
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    auto alloc = map.get_allocator();

    (void)alloc;
}
END_STATIC_ASSERT

// Test hash_function()
BEGIN_STATIC_ASSERT
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_hash = std::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        auto hash_function = map.hash_function();

        (void)hash_function(10);
        (void)hash_function(10);
        (void)hash_function(20);
        (void)hash_function(20);
    }

    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        auto hash_function = map.hash_function();

        (void)hash_function(xobj(10));
        (void)hash_function(xobj(10));
        (void)hash_function(xobj(20));
        (void)hash_function(xobj(20));
    }
}
END_STATIC_ASSERT

// Test key_eq()
BEGIN_STATIC_ASSERT
{
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_hash = std::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        auto key_eq = map.key_eq();

        CHECK(key_eq(10, 10) == true);
        CHECK(key_eq(10, 20) == false);
        CHECK(key_eq(20, 10) == false);
        CHECK(key_eq(20, 20) == true);
    }

    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        auto key_eq = map.key_eq();

        CHECK(key_eq(xobj(10), 10) == true);
        CHECK(key_eq(xobj(10), 20) == false);
        CHECK(key_eq(xobj(20), 10) == false);
        CHECK(key_eq(xobj(20), 20) == true);
    }
}
END_STATIC_ASSERT

// Test begin, end, cbegin, cend
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
        CHECK(count_20_2 == 0);
        CHECK(count_20_3 == 0);
        CHECK(count_30_1 == 1);
    }
}
END_STATIC_ASSERT

// Test equal_range, find, count, contains
BEGIN_STATIC_ASSERT
{
    // xint, xint
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_hash = std::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        map.emplace(20, 1);
        map.emplace(40, 1);
        map.emplace(40, 2);
        map.emplace(60, 1);
        map.emplace(60, 2);
        map.emplace(60, 3);

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.equal_range(10) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(20) == std::make_pair(map.find(20), std::next(map.find(20))));
        CHECK(map.equal_range(30) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(40) == std::make_pair(map.find(40), std::next(map.find(40))));
        CHECK(map.equal_range(50) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(60) == std::make_pair(map.find(60), std::next(map.find(60))));
        CHECK(map.equal_range(70) == std::make_pair(map.end(), map.end()));

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
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.equal_range(10) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(20) == std::make_pair(map.find(20), std::next(map.find(20))));
        CHECK(map.equal_range(30) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(40) == std::make_pair(map.find(40), std::next(map.find(40))));
        CHECK(map.equal_range(50) == std::make_pair(map.end(), map.end()));
        CHECK(map.equal_range(60) == std::make_pair(map.find(60), std::next(map.find(60))));
        CHECK(map.equal_range(70) == std::make_pair(map.end(), map.end()));

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<const xint, xint>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<const xint, xint>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<const xint, xint>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    using value_type = std::pair<const xint, xint>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    std::vector<std::pair<const xint, xint>> data
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
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test insert(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    std::initializer_list<std::pair<const xint, xint>> ilist
    {
        {10, 1},
        {20, 1},
        {30, 1},
        {20, 2},
        {20, 3}
    };

    map.insert(ilist);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test insert_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    std::vector<std::pair<xint, xint>> data
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
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

// Test insert_or_assign(const Key&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const xint key_10(10);

        const auto res = map.insert_or_assign(key_10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const xint key_10(10);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        xint key_10(10);

        const auto res = map.insert_or_assign(std::move(key_10), 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        xint key_10(10);

        const auto res = map.insert_or_assign(std::move(key_10), 2);

        CHECK(res.second == false);
        CHECK(res.first->first == 10); CHECK(res.first->second == 2);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.insert_or_assign(10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first.value() == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.insert_or_assign(10, 2);

        CHECK(res.second == false);
        CHECK(res.first->first.value() == 10); CHECK(res.first->second == 2);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(const_iterator, const Key&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const xint key_10(10);

        const auto res = map.insert_or_assign(map.begin(), key_10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const xint key_10(10);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        xint key_10(10);

        const auto res = map.insert_or_assign(map.begin(), std::move(key_10), 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        xint key_10(10);

        const auto res = map.insert_or_assign(map.begin(), std::move(key_10), 2);

        CHECK(res->first == 10); CHECK(res->second == 2);

        CHECK(map.size() == 1);

        CHECK(key_10 == +10);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(const_iterator, K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const auto res = map.insert_or_assign(map.begin(), 10, 1);

        CHECK(res->first.value() == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const auto res = map.insert_or_assign(map.begin(), 10, 2);

        CHECK(res->first.value() == 10); CHECK(res->second == 2);

        CHECK(map.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace(const Key&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const xint key_10(10);

        const auto res = map.try_emplace(key_10, 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const xint key_10(10);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        xint key_10(10);

        const auto res = map.try_emplace(std::move(key_10), 1);

        CHECK(res.second == true);
        CHECK(res.first->first == 10); CHECK(res.first->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        xint key_10(10);

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
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        const xint key_10(10);

        const auto res = map.try_emplace(map.begin(), key_10, 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);
    }

    {
        const xint key_10(10);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    CHECK(map.size() == 0);

    {
        xint key_10(10);

        const auto res = map.try_emplace(map.begin(), std::move(key_10), 1);

        CHECK(res->first == 10); CHECK(res->second == 1);

        CHECK(map.size() == 1);

        CHECK(key_10 == -10);
    }

    {
        xint key_10(10);

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
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
END_STATIC_ASSERT

// Test erase(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
END_STATIC_ASSERT

// Test erase(const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 1);
    CHECK(map.count(30) == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 2);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 1);

    CHECK(map.erase(20) == 1);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(map.count(10) == 1);

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
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(2));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(3));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 1);
    CHECK(map.count(30) == 1);

    CHECK(map.erase(30) == 1);
    CHECK(map.erase(30) == 0);
    CHECK(map.size() == 2);
    CHECK(map.count(10) == 1);
    CHECK(map.count(20) == 1);

    CHECK(map.erase(20) == 1);
    CHECK(map.erase(20) == 0);
    CHECK(map.size() == 1);
    CHECK(map.count(10) == 1);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
END_STATIC_ASSERT

// Test at(const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.at(10) == 1);
    CHECK(map.at(20) == 1);
    CHECK(map.at(30) == 1);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 1);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 1);

    map.at(10) = 2;
    map.at(20) = 2;
    map.at(30) = 2;

    CHECK(map.at(10) == 2);
    CHECK(map.at(20) == 2);
    CHECK(map.at(30) == 2);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 2);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 2);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 2);
}
END_STATIC_ASSERT

// Test at(const K&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.at(10) == 1);
    CHECK(map.at(20) == 1);
    CHECK(map.at(30) == 1);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 1);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 1);

    map.at(10) = 2;
    map.at(20) = 2;
    map.at(30) = 2;

    CHECK(map.at(10) == 2);
    CHECK(map.at(20) == 2);
    CHECK(map.at(30) == 2);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 2);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 2);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 2);
}
END_STATIC_ASSERT

// Test operator[](const Key&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 1);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 1);

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
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 2);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 2);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 2);
    CHECK(map.count(40) == 1); CHECK(map.find(40)->second == 2);
    CHECK(map.count(50) == 1); CHECK(map.find(50)->second == 2);
    CHECK(map.count(60) == 1); CHECK(map.find(60)->second == 2);

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
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 1);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 1);

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
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 2);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 2);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 2);
    CHECK(map.count(40) == 1); CHECK(map.find(40)->second == 2);
    CHECK(map.count(50) == 1); CHECK(map.find(50)->second == 2);
    CHECK(map.count(60) == 1); CHECK(map.find(60)->second == 2);

    CHECK(key_10 == +10);
    CHECK(key_20 == +20);
    CHECK(key_30 == +30);
    CHECK(key_40 == -40);
    CHECK(key_50 == -50);
    CHECK(key_60 == -60);
}
END_STATIC_ASSERT

// Test operator[](K&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xobj;
    using mapped_type = xint;
    using key_hash = xobj::hash;
    using key_equal = xobj::equal;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map;

    map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
    map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

    CHECK(map.size() == 3);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 1);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    map[10] = 2;
    map[20] = 2;
    map[30] = 2;
    map[40] = 2;
    map[50] = 2;
    map[60] = 2;

    CHECK(map.size() == 6);
    CHECK(map.count(10) == 1); CHECK(map.find(10)->second == 2);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 2);
    CHECK(map.count(30) == 1); CHECK(map.find(30)->second == 2);
    CHECK(map.count(40) == 1); CHECK(map.find(40)->second == 2);
    CHECK(map.count(50) == 1); CHECK(map.find(50)->second == 2);
    CHECK(map.count(60) == 1); CHECK(map.find(60)->second == 2);
}
END_STATIC_ASSERT

// Test bucket interface functions
BEGIN_STATIC_ASSERT
{
    // xint, xint
    {
        using key_type = xint;
        using mapped_type = xint;
        using key_hash = std::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        map.emplace(20, 1);
        map.emplace(40, 1);
        map.emplace(60, 1);
        map.emplace(60, 2);
        map.emplace(60, 3);

        CHECK(map.size() == 3);
        CHECK(map.count(20) == 1);
        CHECK(map.count(40) == 1);
        CHECK(map.count(60) == 1);

        CHECK(map.bucket_count() > 0);
        CHECK(map.max_bucket_count() > 0);

        for (int elem : {10, 30, 50, 70})
        {
            bool found = false;
            auto bucket = map.bucket(elem);
            auto it1 = map.begin(bucket);
            auto it2 = map.end(bucket);
            while (it1 != it2)
            {
                if (it1->first == elem)
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
            auto bucket = map.bucket(elem);
            CHECK(map.bucket_size(bucket) > 0);
            auto it1 = map.begin(bucket);
            auto it2 = map.end(bucket);
            while (it1 != it2)
            {
                if (it1->first == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == true);
        }

        int sum = 0;
        for (int i = 0; i < int(map.bucket_count()); ++i)
        {
            for (auto it1 = map.begin(i), it2 = map.end(i); it1 != it2; ++it1)
            {
                sum += it1->first.value();
            }
        }
        CHECK(sum == 120);
    }

    // xobj, xint
    {
        using key_type = xobj;
        using mapped_type = xint;
        using key_hash = xobj::hash;
        using key_equal = xobj::equal;
        using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
        using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

        map_type map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(2));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(3));

        CHECK(map.size() == 3);
        CHECK(map.count(20) == 1);
        CHECK(map.count(40) == 1);
        CHECK(map.count(60) == 1);

        CHECK(map.bucket_count() > 0);
        CHECK(map.max_bucket_count() > 0);

        for (int elem : {10, 30, 50, 70})
        {
            bool found = false;
            auto bucket = map.bucket(elem);
            auto it1 = map.begin(bucket);
            auto it2 = map.end(bucket);
            while (it1 != it2)
            {
                if (it1->first.value() == elem)
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
            auto bucket = map.bucket(elem);
            CHECK(map.bucket_size(bucket) > 0);
            auto it1 = map.begin(bucket);
            auto it2 = map.end(bucket);
            while (it1 != it2)
            {
                if (it1->first.value() == elem)
                {
                    found = true;
                    break;
                }
                ++it1;
            }
            CHECK(found == true);
        }

        int sum = 0;
        for (int i = 0; i < int(map.bucket_count()); ++i)
        {
            for (auto it1 = map.begin(i), it2 = map.end(i); it1 != it2; ++it1)
            {
                sum += it1->first.value();
            }
        }
        CHECK(sum == 120);
    }
}
END_STATIC_ASSERT

// Test hash policy functions
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    map_type map(11);

    map.emplace(20, 1);
    map.emplace(40, 1);
    map.emplace(60, 1);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 40, 1) == 1);
    CHECK(COUNT_KV(map, 60, 1) == 1);

    CHECK(map.bucket_count() >= 11 && map.bucket_count() < 111);

    ///////////////////////////////////////////////////////////////////////////

    map.rehash(111);

    CHECK(map.bucket_count() >= 111 && map.bucket_count() < 1111);

    CHECK(map.size() == 3);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(40) == 1); CHECK(map.find(40)->second == 1);
    CHECK(map.count(60) == 1); CHECK(map.find(60)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    map.reserve(1111);

    CHECK(map.bucket_count() >= 1111 && map.bucket_count() < 11111);

    CHECK(map.size() == 3);
    CHECK(map.count(20) == 1); CHECK(map.find(20)->second == 1);
    CHECK(map.count(40) == 1); CHECK(map.find(40)->second == 1);
    CHECK(map.count(60) == 1); CHECK(map.find(60)->second == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(map.load_factor() > 0.0f);

    CHECK(map.max_load_factor() == 1.0f);

    map.max_load_factor(0.5f);

    CHECK(map.max_load_factor() == 0.5f);
}
END_STATIC_ASSERT

// Test NON-MEMBER comparison operators
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
END_STATIC_ASSERT

// Test NON-MEMBER swap(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

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
END_STATIC_ASSERT

// Test NON-MEMBER erase_if(container&, Predicate)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using mapped_type = xint;
    using key_hash = std::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using allocator_type = std::allocator<std::pair<const key_type, mapped_type>>;
    using map_type = sfl::unordered_map<key_type, mapped_type, key_hash, key_equal, allocator_type>;

    using const_reference = typename map_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    map_type map;

    map.emplace(10, 1);
    map.emplace(20, 1);
    map.emplace(30, 1);
    map.emplace(20, 2);
    map.emplace(20, 3);

    CHECK(map.size() == 3);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 20, 1) == 1);
    CHECK(COUNT_KV(map, 20, 2) == 0);
    CHECK(COUNT_KV(map, 20, 3) == 0);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 1);
    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 0);
    CHECK(map.size() == 2);
    CHECK(COUNT_KV(map, 10, 1) == 1);
    CHECK(COUNT_KV(map, 30, 1) == 1);
}
END_STATIC_ASSERT

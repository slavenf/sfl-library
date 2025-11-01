#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

using sfl::test::xint;

BEGIN_STATIC_ASSERT
{
    sfl::dtl::hash_table_functions<std::hash<xint>, std::equal_to<xint>> f1, f2;

    f1.assign_copy(f2);
    f1.assign_move(f2);
    f1.swap(f2);
}
END_STATIC_ASSERT

// Test container(size_type)
BEGIN_STATIC_ASSERT
{
    {
        using key_type = xint;
        using value_type = xint;
        using key_of_value = sfl::dtl::identity;
        using key_hash = sfl::test::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using node_allocator = std::allocator<key_type>;
        using bucket_allocator = std::allocator<key_type>;
        using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
        using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
        using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

        hash_table_type hash_table(4);

        CHECK(hash_table.empty() == true);
        CHECK(hash_table.size() == 0);
        CHECK(hash_table.max_size() > 0);
    }

    {
        using key_type = xint;
        using value_type = xint;
        using key_of_value = sfl::dtl::identity;
        using key_hash = sfl::test::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using node_allocator = std::allocator<key_type>;
        using bucket_allocator = std::allocator<key_type>;
        using bucket_count_policy = sfl::dtl::hash_table_dynamic_prime_bucket_count_policy;
        using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
        using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

        hash_table_type hash_table(7);

        CHECK(hash_table.empty() == true);
        CHECK(hash_table.size() == 0);
        CHECK(hash_table.max_size() > 0);
    }

    {
        using key_type = xint;
        using value_type = xint;
        using key_of_value = sfl::dtl::identity;
        using key_hash = sfl::test::hash<key_type>;
        using key_equal = std::equal_to<key_type>;
        using node_allocator = std::allocator<key_type>;
        using bucket_allocator = std::allocator<key_type>;
        using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
        using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
        using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

        hash_table_type hash_table(9);

        CHECK(hash_table.empty() == true);
        CHECK(hash_table.size() == 0);
        CHECK(hash_table.max_size() > 0);
    }
}
END_STATIC_ASSERT

// Test container(size_type, const Alloc&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    node_allocator alloc;

    hash_table_type hash_table(4, alloc);

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const key_hash&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    key_hash hash;

    hash_table_type hash_table(4, hash);

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const key_hash&, const Alloc&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    key_hash hash;

    node_allocator alloc;

    hash_table_type hash_table(4, hash, alloc);

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const key_hash&, const key_equal&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    key_hash hash;

    key_equal equal;

    hash_table_type hash_table(4, hash, equal);

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(size_type, const key_hash&, const key_equal&, const Alloc&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    key_hash hash;

    key_equal equal;

    node_allocator alloc;

    hash_table_type hash_table(4, hash, equal, alloc);

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const container&, EqualOrUniqueTag)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_equal_t());

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_unique_t());

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_equal(1);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(3);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(5);

        hash_table1.emplace_equal(101);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(103);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(105);

        hash_table1.emplace_equal(201);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(203);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(205);

        CHECK(hash_table1.size() == 33);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 4);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 4);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 4);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 4);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 4);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 4);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_equal_t());

        CHECK(hash_table2.size() == 33);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 4);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 4);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 4);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 4);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 4);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 4);
        CHECK(hash_table2.count_equal(205) == 1);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_unique(1);
        hash_table1.emplace_unique(2);
        hash_table1.emplace_unique(3);
        hash_table1.emplace_unique(4);
        hash_table1.emplace_unique(5);

        hash_table1.emplace_unique(101);
        hash_table1.emplace_unique(102);
        hash_table1.emplace_unique(103);
        hash_table1.emplace_unique(104);
        hash_table1.emplace_unique(105);

        hash_table1.emplace_unique(201);
        hash_table1.emplace_unique(202);
        hash_table1.emplace_unique(203);
        hash_table1.emplace_unique(204);
        hash_table1.emplace_unique(205);

        CHECK(hash_table1.size() == 15);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 1);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 1);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 1);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 1);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 1);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 1);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_unique_t());

        CHECK(hash_table2.size() == 15);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 1);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 1);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 1);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 1);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 1);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 1);
        CHECK(hash_table2.count_equal(205) == 1);
    }
}
END_STATIC_ASSERT

// Test container(const container&, EqualOrUniqueTag, const Alloc&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_equal_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_unique_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_equal(1);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(3);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(5);

        hash_table1.emplace_equal(101);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(103);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(105);

        hash_table1.emplace_equal(201);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(203);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(205);

        CHECK(hash_table1.size() == 33);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 4);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 4);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 4);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 4);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 4);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 4);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_equal_t(), alloc);

        CHECK(hash_table2.size() == 33);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 4);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 4);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 4);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 4);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 4);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 4);
        CHECK(hash_table2.count_equal(205) == 1);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_unique(1);
        hash_table1.emplace_unique(2);
        hash_table1.emplace_unique(3);
        hash_table1.emplace_unique(4);
        hash_table1.emplace_unique(5);

        hash_table1.emplace_unique(101);
        hash_table1.emplace_unique(102);
        hash_table1.emplace_unique(103);
        hash_table1.emplace_unique(104);
        hash_table1.emplace_unique(105);

        hash_table1.emplace_unique(201);
        hash_table1.emplace_unique(202);
        hash_table1.emplace_unique(203);
        hash_table1.emplace_unique(204);
        hash_table1.emplace_unique(205);

        CHECK(hash_table1.size() == 15);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 1);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 1);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 1);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 1);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 1);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 1);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_unique_t(), alloc);

        CHECK(hash_table2.size() == 15);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 1);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 1);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 1);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 1);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 1);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 1);
        CHECK(hash_table2.count_equal(205) == 1);
    }
}
END_STATIC_ASSERT

// Test container(container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_equal_t());

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_unique_t());

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_equal(1);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(3);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(5);

        hash_table1.emplace_equal(101);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(103);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(105);

        hash_table1.emplace_equal(201);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(203);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(205);

        CHECK(hash_table1.size() == 33);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 4);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 4);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 4);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 4);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 4);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 4);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_equal_t());

        if (hash_table1.size() == 33)
        {
            // Elements are moved one-by-one

            CHECK(hash_table1.count_equal(1) == 0);
            CHECK(hash_table1.count_equal(2) == 0);
            CHECK(hash_table1.count_equal(3) == 0);
            CHECK(hash_table1.count_equal(4) == 0);
            CHECK(hash_table1.count_equal(5) == 0);

            CHECK(hash_table1.count_equal(101) == 0);
            CHECK(hash_table1.count_equal(102) == 0);
            CHECK(hash_table1.count_equal(103) == 0);
            CHECK(hash_table1.count_equal(104) == 0);
            CHECK(hash_table1.count_equal(105) == 0);

            CHECK(hash_table1.count_equal(201) == 0);
            CHECK(hash_table1.count_equal(202) == 0);
            CHECK(hash_table1.count_equal(203) == 0);
            CHECK(hash_table1.count_equal(204) == 0);
            CHECK(hash_table1.count_equal(205) == 0);
        }
        else
        {
            CHECK(hash_table1.size() == 0);
        }

        CHECK(hash_table2.size() == 33);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 4);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 4);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 4);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 4);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 4);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 4);
        CHECK(hash_table2.count_equal(205) == 1);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_unique(1);
        hash_table1.emplace_unique(2);
        hash_table1.emplace_unique(3);
        hash_table1.emplace_unique(4);
        hash_table1.emplace_unique(5);

        hash_table1.emplace_unique(101);
        hash_table1.emplace_unique(102);
        hash_table1.emplace_unique(103);
        hash_table1.emplace_unique(104);
        hash_table1.emplace_unique(105);

        hash_table1.emplace_unique(201);
        hash_table1.emplace_unique(202);
        hash_table1.emplace_unique(203);
        hash_table1.emplace_unique(204);
        hash_table1.emplace_unique(205);

        CHECK(hash_table1.size() == 15);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 1);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 1);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 1);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 1);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 1);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 1);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_unique_t());

        if (hash_table1.size() == 15)
        {
            // Elements are moved one-by-one

            CHECK(hash_table1.count_equal(1) == 0);
            CHECK(hash_table1.count_equal(2) == 0);
            CHECK(hash_table1.count_equal(3) == 0);
            CHECK(hash_table1.count_equal(4) == 0);
            CHECK(hash_table1.count_equal(5) == 0);

            CHECK(hash_table1.count_equal(101) == 0);
            CHECK(hash_table1.count_equal(102) == 0);
            CHECK(hash_table1.count_equal(103) == 0);
            CHECK(hash_table1.count_equal(104) == 0);
            CHECK(hash_table1.count_equal(105) == 0);

            CHECK(hash_table1.count_equal(201) == 0);
            CHECK(hash_table1.count_equal(202) == 0);
            CHECK(hash_table1.count_equal(203) == 0);
            CHECK(hash_table1.count_equal(204) == 0);
            CHECK(hash_table1.count_equal(205) == 0);
        }
        else
        {
            CHECK(hash_table1.size() == 0);
        }

        CHECK(hash_table2.size() == 15);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 1);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 1);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 1);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 1);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 1);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 1);
        CHECK(hash_table2.count_equal(205) == 1);
    }
}
END_STATIC_ASSERT

// Test container(container&&, const Alloc&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_equal_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_unique_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_equal(1);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(2);
        hash_table1.emplace_equal(3);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(4);
        hash_table1.emplace_equal(5);

        hash_table1.emplace_equal(101);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(102);
        hash_table1.emplace_equal(103);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(104);
        hash_table1.emplace_equal(105);

        hash_table1.emplace_equal(201);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(202);
        hash_table1.emplace_equal(203);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(204);
        hash_table1.emplace_equal(205);

        CHECK(hash_table1.size() == 33);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 4);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 4);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 4);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 4);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 4);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 4);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_equal_t(), alloc);

        if (hash_table1.size() == 33)
        {
            // Elements are moved one-by-one

            CHECK(hash_table1.count_equal(1) == 0);
            CHECK(hash_table1.count_equal(2) == 0);
            CHECK(hash_table1.count_equal(3) == 0);
            CHECK(hash_table1.count_equal(4) == 0);
            CHECK(hash_table1.count_equal(5) == 0);

            CHECK(hash_table1.count_equal(101) == 0);
            CHECK(hash_table1.count_equal(102) == 0);
            CHECK(hash_table1.count_equal(103) == 0);
            CHECK(hash_table1.count_equal(104) == 0);
            CHECK(hash_table1.count_equal(105) == 0);

            CHECK(hash_table1.count_equal(201) == 0);
            CHECK(hash_table1.count_equal(202) == 0);
            CHECK(hash_table1.count_equal(203) == 0);
            CHECK(hash_table1.count_equal(204) == 0);
            CHECK(hash_table1.count_equal(205) == 0);
        }
        else
        {
            CHECK(hash_table1.size() == 0);
        }

        CHECK(hash_table2.size() == 33);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 4);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 4);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 4);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 4);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 4);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 4);
        CHECK(hash_table2.count_equal(205) == 1);
    }

    {
        hash_table_type hash_table1(100);

        hash_table1.emplace_unique(1);
        hash_table1.emplace_unique(2);
        hash_table1.emplace_unique(3);
        hash_table1.emplace_unique(4);
        hash_table1.emplace_unique(5);

        hash_table1.emplace_unique(101);
        hash_table1.emplace_unique(102);
        hash_table1.emplace_unique(103);
        hash_table1.emplace_unique(104);
        hash_table1.emplace_unique(105);

        hash_table1.emplace_unique(201);
        hash_table1.emplace_unique(202);
        hash_table1.emplace_unique(203);
        hash_table1.emplace_unique(204);
        hash_table1.emplace_unique(205);

        CHECK(hash_table1.size() == 15);

        CHECK(hash_table1.count_equal(1) == 1);
        CHECK(hash_table1.count_equal(2) == 1);
        CHECK(hash_table1.count_equal(3) == 1);
        CHECK(hash_table1.count_equal(4) == 1);
        CHECK(hash_table1.count_equal(5) == 1);

        CHECK(hash_table1.count_equal(101) == 1);
        CHECK(hash_table1.count_equal(102) == 1);
        CHECK(hash_table1.count_equal(103) == 1);
        CHECK(hash_table1.count_equal(104) == 1);
        CHECK(hash_table1.count_equal(105) == 1);

        CHECK(hash_table1.count_equal(201) == 1);
        CHECK(hash_table1.count_equal(202) == 1);
        CHECK(hash_table1.count_equal(203) == 1);
        CHECK(hash_table1.count_equal(204) == 1);
        CHECK(hash_table1.count_equal(205) == 1);

        ///////////////////////////////////////////////////////////////////////

        node_allocator alloc;

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_unique_t(), alloc);

        if (hash_table1.size() == 15)
        {
            // Elements are moved one-by-one

            CHECK(hash_table1.count_equal(1) == 0);
            CHECK(hash_table1.count_equal(2) == 0);
            CHECK(hash_table1.count_equal(3) == 0);
            CHECK(hash_table1.count_equal(4) == 0);
            CHECK(hash_table1.count_equal(5) == 0);

            CHECK(hash_table1.count_equal(101) == 0);
            CHECK(hash_table1.count_equal(102) == 0);
            CHECK(hash_table1.count_equal(103) == 0);
            CHECK(hash_table1.count_equal(104) == 0);
            CHECK(hash_table1.count_equal(105) == 0);

            CHECK(hash_table1.count_equal(201) == 0);
            CHECK(hash_table1.count_equal(202) == 0);
            CHECK(hash_table1.count_equal(203) == 0);
            CHECK(hash_table1.count_equal(204) == 0);
            CHECK(hash_table1.count_equal(205) == 0);
        }
        else
        {
            CHECK(hash_table1.size() == 0);
        }

        CHECK(hash_table2.size() == 15);

        CHECK(hash_table2.count_equal(1) == 1);
        CHECK(hash_table2.count_equal(2) == 1);
        CHECK(hash_table2.count_equal(3) == 1);
        CHECK(hash_table2.count_equal(4) == 1);
        CHECK(hash_table2.count_equal(5) == 1);

        CHECK(hash_table2.count_equal(101) == 1);
        CHECK(hash_table2.count_equal(102) == 1);
        CHECK(hash_table2.count_equal(103) == 1);
        CHECK(hash_table2.count_equal(104) == 1);
        CHECK(hash_table2.count_equal(105) == 1);

        CHECK(hash_table2.count_equal(201) == 1);
        CHECK(hash_table2.count_equal(202) == 1);
        CHECK(hash_table2.count_equal(203) == 1);
        CHECK(hash_table2.count_equal(204) == 1);
        CHECK(hash_table2.count_equal(205) == 1);
    }
}
END_STATIC_ASSERT

// Test assign_copy(const container&, EqualOrUniqueTag)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    #define CONDITION hash_table1.size() == 0 && hash_table2.size() == 0
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_equal_t());

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_unique_t());

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() == hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);

            hash_table2.emplace_equal(4);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 2);
            CHECK(hash_table2.count_equal(6) == 3);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_equal_t());

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);

            hash_table2.emplace_unique(4);
            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_unique_t());

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() < hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);

            hash_table2.emplace_equal(4);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(8);
            hash_table2.emplace_equal(9);

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 9);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 2);
            CHECK(hash_table2.count_equal(6) == 3);
            CHECK(hash_table2.count_equal(7) == 1);
            CHECK(hash_table2.count_equal(8) == 1);
            CHECK(hash_table2.count_equal(9) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_equal_t());

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
            CHECK(hash_table2.count_equal(8) == 0);
            CHECK(hash_table2.count_equal(9) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);

            hash_table2.emplace_unique(4);
            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);
            hash_table2.emplace_unique(7);
            hash_table2.emplace_unique(8);
            hash_table2.emplace_unique(9);

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);
            CHECK(hash_table2.count_equal(7) == 1);
            CHECK(hash_table2.count_equal(8) == 1);
            CHECK(hash_table2.count_equal(9) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_unique_t());

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
            CHECK(hash_table2.count_equal(8) == 0);
            CHECK(hash_table2.count_equal(9) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() > hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);

            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(7);

            CHECK(hash_table1.size() == 10);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);
            CHECK(hash_table1.count_equal(4) == 4);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 2);
            CHECK(hash_table2.count_equal(7) == 3);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_equal_t());

            CHECK(hash_table1.size() == 10);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);
            CHECK(hash_table1.count_equal(4) == 4);

            CHECK(hash_table2.size() == 10);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 4);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);
            hash_table1.emplace_unique(4);

            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);
            hash_table2.emplace_unique(7);

            CHECK(hash_table1.size() == 4);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);
            CHECK(hash_table1.count_equal(4) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);
            CHECK(hash_table2.count_equal(7) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_copy(hash_table1, sfl::dtl::hash_table_unique_t());

            CHECK(hash_table1.size() == 4);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);
            CHECK(hash_table1.count_equal(4) == 1);

            CHECK(hash_table2.size() == 4);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test assign_move(const container&, EqualOrUniqueTag)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    #define CONDITION hash_table1.size() == 0 && hash_table2.size() == 0
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_equal_t());

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_unique_t());

            CHECK(hash_table1.size() == 0);
            CHECK(hash_table2.size() == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() == hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);

            hash_table2.emplace_equal(4);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 2);
            CHECK(hash_table2.count_equal(6) == 3);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_equal_t());

            if (hash_table1.size() == 6)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);

            hash_table2.emplace_unique(4);
            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_unique_t());

            if (hash_table1.size() == 3)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() < hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);

            hash_table2.emplace_equal(4);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(8);
            hash_table2.emplace_equal(9);

            CHECK(hash_table1.size() == 6);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);

            CHECK(hash_table2.size() == 9);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 2);
            CHECK(hash_table2.count_equal(6) == 3);
            CHECK(hash_table2.count_equal(7) == 1);
            CHECK(hash_table2.count_equal(8) == 1);
            CHECK(hash_table2.count_equal(9) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_equal_t());

            if (hash_table1.size() == 6)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
            CHECK(hash_table2.count_equal(8) == 0);
            CHECK(hash_table2.count_equal(9) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);

            hash_table2.emplace_unique(4);
            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);
            hash_table2.emplace_unique(7);
            hash_table2.emplace_unique(8);
            hash_table2.emplace_unique(9);

            CHECK(hash_table1.size() == 3);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);
            CHECK(hash_table2.count_equal(7) == 1);
            CHECK(hash_table2.count_equal(8) == 1);
            CHECK(hash_table2.count_equal(9) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_unique_t());

            if (hash_table1.size() == 3)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 0);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
            CHECK(hash_table2.count_equal(8) == 0);
            CHECK(hash_table2.count_equal(9) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() > hash_table2.size()
    {
        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_equal(1);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(2);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(3);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);
            hash_table1.emplace_equal(4);

            hash_table2.emplace_equal(5);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(6);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(7);
            hash_table2.emplace_equal(7);

            CHECK(hash_table1.size() == 10);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 2);
            CHECK(hash_table1.count_equal(3) == 3);
            CHECK(hash_table1.count_equal(4) == 4);

            CHECK(hash_table2.size() == 6);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 2);
            CHECK(hash_table2.count_equal(7) == 3);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_equal_t());

            if (hash_table1.size() == 10)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
                CHECK(hash_table1.count_equal(4) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 10);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 2);
            CHECK(hash_table2.count_equal(3) == 3);
            CHECK(hash_table2.count_equal(4) == 4);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
        }

        {
            hash_table_type hash_table1(100), hash_table2(3);

            hash_table1.emplace_unique(1);
            hash_table1.emplace_unique(2);
            hash_table1.emplace_unique(3);
            hash_table1.emplace_unique(4);

            hash_table2.emplace_unique(5);
            hash_table2.emplace_unique(6);
            hash_table2.emplace_unique(7);

            CHECK(hash_table1.size() == 4);
            CHECK(hash_table1.count_equal(1) == 1);
            CHECK(hash_table1.count_equal(2) == 1);
            CHECK(hash_table1.count_equal(3) == 1);
            CHECK(hash_table1.count_equal(4) == 1);

            CHECK(hash_table2.size() == 3);
            CHECK(hash_table2.count_equal(5) == 1);
            CHECK(hash_table2.count_equal(6) == 1);
            CHECK(hash_table2.count_equal(7) == 1);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            hash_table2.assign_move(hash_table1, sfl::dtl::hash_table_unique_t());

            if (hash_table1.size() == 4)
            {
                // Elements are moved one-by-one
                CHECK(hash_table1.count_equal(1) == 0);
                CHECK(hash_table1.count_equal(2) == 0);
                CHECK(hash_table1.count_equal(3) == 0);
                CHECK(hash_table1.count_equal(4) == 0);
            }
            else
            {
                CHECK(hash_table1.size() == 0);
            }

            CHECK(hash_table2.size() == 4);
            CHECK(hash_table2.count_equal(1) == 1);
            CHECK(hash_table2.count_equal(2) == 1);
            CHECK(hash_table2.count_equal(3) == 1);
            CHECK(hash_table2.count_equal(4) == 1);
            CHECK(hash_table2.count_equal(5) == 0);
            CHECK(hash_table2.count_equal(6) == 0);
            CHECK(hash_table2.count_equal(7) == 0);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test assign_range_equal(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    #define CONDITION n == hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_equal(data.begin(), data.end());

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);
    }
    #undef CONDITION

    #define CONDITION n < hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);
        hash_table.emplace_unique(40);
        hash_table.emplace_unique(50);
        hash_table.emplace_unique(60);

        CHECK(hash_table.size() == 6);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);

        std::vector<int> data({70, 80, 90});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_equal(data.begin(), data.end());

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 0);
        CHECK(hash_table.count_equal(50) == 0);
        CHECK(hash_table.count_equal(60) == 0);
        CHECK(hash_table.count_equal(70) == 1);
        CHECK(hash_table.count_equal(80) == 1);
        CHECK(hash_table.count_equal(90) == 1);
    }
    #undef CONDITION

    #define CONDITION n > hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60, 70, 80, 90});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_equal(data.begin(), data.end());

        CHECK(hash_table.size() == 6);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);
        CHECK(hash_table.count_equal(70) == 1);
        CHECK(hash_table.count_equal(80) == 1);
        CHECK(hash_table.count_equal(90) == 1);
    }
    #undef CONDITION

    // Input iterator range with duplicates
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        hash_table.assign_range_equal(data.begin(), data.end());

        CHECK(hash_table.size() == 5);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 3);
        CHECK(hash_table.count_equal(60) == 1);
    }

    // Move iterator range with duplicates
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<xint> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        hash_table.assign_range_equal(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));

        CHECK(hash_table.size() == 5);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 3);
        CHECK(hash_table.count_equal(60) == 1);

        CHECK(data.size() == 5);
        CHECK(data[0] == -40);
        CHECK(data[1] == -50);
        CHECK(data[2] == -60);
        CHECK(data[3] == -50);
        CHECK(data[4] == -50);
    }
}
END_STATIC_ASSERT

// Test assign_range_unique(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    #define CONDITION n == hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_unique(data.begin(), data.end());

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);
    }
    #undef CONDITION

    #define CONDITION n < hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);
        hash_table.emplace_unique(40);
        hash_table.emplace_unique(50);
        hash_table.emplace_unique(60);

        CHECK(hash_table.size() == 6);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);

        std::vector<int> data({70, 80, 90});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_unique(data.begin(), data.end());

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 0);
        CHECK(hash_table.count_equal(50) == 0);
        CHECK(hash_table.count_equal(60) == 0);
        CHECK(hash_table.count_equal(70) == 1);
        CHECK(hash_table.count_equal(80) == 1);
        CHECK(hash_table.count_equal(90) == 1);
    }
    #undef CONDITION

    #define CONDITION n > hash_table.size()
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60, 70, 80, 90});

        const hash_table_type::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table.assign_range_unique(data.begin(), data.end());

        CHECK(hash_table.size() == 6);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);
        CHECK(hash_table.count_equal(70) == 1);
        CHECK(hash_table.count_equal(80) == 1);
        CHECK(hash_table.count_equal(90) == 1);
    }
    #undef CONDITION

    // Input iterator range with duplicates
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<int> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        hash_table.assign_range_unique(data.begin(), data.end());

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);
    }

    // Move iterator range with duplicates
    {
        hash_table_type hash_table(100);

        hash_table.emplace_unique(10);
        hash_table.emplace_unique(20);
        hash_table.emplace_unique(30);

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 1);
        CHECK(hash_table.count_equal(20) == 1);
        CHECK(hash_table.count_equal(30) == 1);

        std::vector<xint> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        hash_table.assign_range_unique(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));

        CHECK(hash_table.size() == 3);
        CHECK(hash_table.count_equal(10) == 0);
        CHECK(hash_table.count_equal(20) == 0);
        CHECK(hash_table.count_equal(30) == 0);
        CHECK(hash_table.count_equal(40) == 1);
        CHECK(hash_table.count_equal(50) == 1);
        CHECK(hash_table.count_equal(60) == 1);

        CHECK(data.size() == 5);
        CHECK(data[0] == -40);
        CHECK(data[1] == -50);
        CHECK(data[2] == -60);
        CHECK(data[3] == +50);
        CHECK(data[4] == +50);
    }
}
END_STATIC_ASSERT

// Test clear()
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_equal(1);
    hash_table.emplace_equal(2);
    hash_table.emplace_equal(3);

    CHECK(hash_table.empty() == false);
    CHECK(hash_table.size() == 3);
    CHECK(hash_table.begin() != hash_table.end());
    for (int i = 0; i < int(hash_table.bucket_count()); ++i)
    {
        if (i == 1 || i == 2 || i == 3)
        {
            CHECK(hash_table.bucket_size(i) == 1);
            CHECK(hash_table.begin(i) != hash_table.end(i));
        }
        else
        {
            CHECK(hash_table.bucket_size(i) == 0);
            CHECK(hash_table.begin(i) == hash_table.end(i));
        }
    }

    hash_table.clear();

    CHECK(hash_table.empty() == true);
    CHECK(hash_table.size() == 0);
    CHECK(hash_table.begin() == hash_table.end());
    for (int i = 0; i < int(hash_table.bucket_count()); ++i)
    {
        CHECK(hash_table.bucket_size(i) == 0);
        CHECK(hash_table.begin(i) == hash_table.end(i));
    }
}
END_STATIC_ASSERT

// Test emplace_equal(Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_equal(10);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);
}
END_STATIC_ASSERT

// Test emplace_unique(Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_unique(10);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);
}
END_STATIC_ASSERT

// Test emplace_hint_equal(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_hint_equal(hash_table.end(), 10);
    hash_table.emplace_hint_equal(hash_table.end(), 20);
    hash_table.emplace_hint_equal(hash_table.end(), 20);
    hash_table.emplace_hint_equal(hash_table.end(), 30);
    hash_table.emplace_hint_equal(hash_table.end(), 30);
    hash_table.emplace_hint_equal(hash_table.end(), 30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);
}
END_STATIC_ASSERT

// Test emplace_hint_unique(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_hint_unique(hash_table.end(), 10);
    hash_table.emplace_hint_unique(hash_table.end(), 20);
    hash_table.emplace_hint_unique(hash_table.end(), 20);
    hash_table.emplace_hint_unique(hash_table.end(), 30);
    hash_table.emplace_hint_unique(hash_table.end(), 30);
    hash_table.emplace_hint_unique(hash_table.end(), 30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);
}
END_STATIC_ASSERT

// Test insert_equal(V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.insert_equal(10);
    hash_table.insert_equal(20);
    hash_table.insert_equal(20);
    hash_table.insert_equal(30);
    hash_table.insert_equal(30);
    hash_table.insert_equal(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);
}
END_STATIC_ASSERT

// Test insert_unique(V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.insert_unique(10);
    hash_table.insert_unique(20);
    hash_table.insert_unique(20);
    hash_table.insert_unique(30);
    hash_table.insert_unique(30);
    hash_table.insert_unique(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);
}
END_STATIC_ASSERT

// Test insert_hint_equal(const_iterator, V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.insert_hint_equal(hash_table.end(), 10);
    hash_table.insert_hint_equal(hash_table.end(), 20);
    hash_table.insert_hint_equal(hash_table.end(), 20);
    hash_table.insert_hint_equal(hash_table.end(), 30);
    hash_table.insert_hint_equal(hash_table.end(), 30);
    hash_table.insert_hint_equal(hash_table.end(), 30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);
}
END_STATIC_ASSERT

// Test insert_hint_unique(const_iterator, V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.insert_hint_unique(hash_table.end(), 10);
    hash_table.insert_hint_unique(hash_table.end(), 20);
    hash_table.insert_hint_unique(hash_table.end(), 20);
    hash_table.insert_hint_unique(hash_table.end(), 30);
    hash_table.insert_hint_unique(hash_table.end(), 30);
    hash_table.insert_hint_unique(hash_table.end(), 30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);
}
END_STATIC_ASSERT

// Test insert_or_assign(K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = std::pair<const xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table(100);

        {
            const auto res = hash_table.insert_or_assign(1, 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);
        }

        {
            const auto res = hash_table.insert_or_assign(1, 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 200);

            CHECK(hash_table.size() == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign(key, 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign(key, 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 200);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign(std::move(key), 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == -1);
        }

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign(std::move(key), 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 200);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }
}
END_STATIC_ASSERT

// Test insert_or_assign_hint(const_iterator, K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = std::pair<const xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table(100);

        {
            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), 1, 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);
        }

        {
            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), 1, 200);

            CHECK(res->first == 1); CHECK(res->second == 200);

            CHECK(hash_table.size() == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), key, 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), key, 200);

            CHECK(res->first == 1); CHECK(res->second == 200);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), std::move(key), 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == -1);
        }

        {
            xint key(1);

            const auto res = hash_table.insert_or_assign_hint(hash_table.begin(), std::move(key), 200);

            CHECK(res->first == 1); CHECK(res->second == 200);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }
}
END_STATIC_ASSERT

// Test try_emplace(K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = std::pair<const xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table(100);

        {
            const auto res = hash_table.try_emplace(1, 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);
        }

        {
            const auto res = hash_table.try_emplace(1, 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.try_emplace(key, 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }

        {
            xint key(1);

            const auto res = hash_table.try_emplace(key, 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.try_emplace(std::move(key), 100);

            CHECK(res.second == true);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == -1);
        }

        {
            xint key(1);

            const auto res = hash_table.try_emplace(std::move(key), 200);

            CHECK(res.second == false);
            CHECK(res.first->first == 1); CHECK(res.first->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }
}
END_STATIC_ASSERT

// Test try_emplace_hint(const_iterator, K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = std::pair<const xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    {
        hash_table_type hash_table(100);

        {
            const auto res = hash_table.try_emplace_hint(hash_table.begin(), 1, 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);
        }

        {
            const auto res = hash_table.try_emplace_hint(hash_table.begin(), 1, 200);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.try_emplace_hint(hash_table.begin(), key, 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }

        {
            xint key(1);

            const auto res = hash_table.try_emplace_hint(hash_table.begin(), key, 200);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }

    {
        hash_table_type hash_table(100);

        {
            xint key(1);

            const auto res = hash_table.try_emplace_hint(hash_table.begin(), std::move(key), 100);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == -1);
        }

        {
            xint key(1);

            const auto res = hash_table.try_emplace_hint(hash_table.begin(), std::move(key), 200);

            CHECK(res->first == 1); CHECK(res->second == 100);

            CHECK(hash_table.size() == 1);

            CHECK(key == 1);
        }
    }
}
END_STATIC_ASSERT

// Test erase_equal(const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_equal(10);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);

    {
        auto it = hash_table.find(10);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 2);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        auto it = hash_table.find(20);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        auto it = hash_table.find(30);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 2);
    }
}
END_STATIC_ASSERT

// Test erase_unique(const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_unique(10);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);

    {
        auto it = hash_table.find(10);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        auto it = hash_table.find(20);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        auto it = hash_table.find(30);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 0);
    }
}
END_STATIC_ASSERT

// Test erase_equal(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_equal(10);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);

    {
        auto it = hash_table.find(10);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 2);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        auto it = hash_table.find(20);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        auto it = hash_table.find(30);

        CHECK(it != hash_table.end());

        hash_table.erase_equal(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 2);
    }
}
END_STATIC_ASSERT

// Test erase_unique(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_unique(10);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);

    {
        auto it = hash_table.find(10);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        auto it = hash_table.find(20);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        auto it = hash_table.find(30);

        CHECK(it != hash_table.end());

        hash_table.erase_unique(it, std::next(it));

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 0);
    }
}
END_STATIC_ASSERT

// Test erase_key_equal(const K&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_equal(10);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(20);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);
    hash_table.emplace_equal(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 2);
    CHECK(COUNT(hash_table, 30) == 3);

    {
        hash_table.erase_key_equal(10);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 2);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        hash_table.erase_key_equal(20);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 3);
    }

    {
        hash_table.erase_key_equal(30);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 0);
    }
}
END_STATIC_ASSERT

// Test erase_key_unique(const K&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table(100);

    hash_table.emplace_unique(10);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(20);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);
    hash_table.emplace_unique(30);

    CHECK(COUNT(hash_table, 10) == 1);
    CHECK(COUNT(hash_table, 20) == 1);
    CHECK(COUNT(hash_table, 30) == 1);

    {
        hash_table.erase_key_unique(10);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 1);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        hash_table.erase_key_unique(20);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 1);
    }

    {
        hash_table.erase_key_unique(30);

        CHECK(COUNT(hash_table, 10) == 0);
        CHECK(COUNT(hash_table, 20) == 0);
        CHECK(COUNT(hash_table, 30) == 0);
    }
}
END_STATIC_ASSERT

// Test swap(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    #define CONDITION hash_table1.size() == 0 && hash_table2.size() == 0
    {
        hash_table_type hash_table1(100), hash_table2(100);

        CHECK(hash_table1.size() == 0);
        CHECK(hash_table2.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 0);
        CHECK(hash_table2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() == 0 && hash_table2.size() != 0
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table2.emplace_unique(10);
        hash_table2.emplace_unique(20);
        hash_table2.emplace_unique(30);

        CHECK(hash_table1.size() == 0);

        CHECK(hash_table2.size() == 3);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 3);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);

        CHECK(hash_table2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() != 0 && hash_table2.size() == 0
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table1.emplace_unique(10);
        hash_table1.emplace_unique(20);
        hash_table1.emplace_unique(30);

        CHECK(hash_table1.size() == 3);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);

        CHECK(hash_table2.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 0);

        CHECK(hash_table2.size() == 3);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() != 0 && hash_table2.size() != 0 && hash_table1.size() < hash_table2.size()
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table1.emplace_unique(10);
        hash_table1.emplace_unique(20);
        hash_table1.emplace_unique(30);

        hash_table2.emplace_unique(40);
        hash_table2.emplace_unique(50);
        hash_table2.emplace_unique(60);
        hash_table2.emplace_unique(70);
        hash_table2.emplace_unique(80);
        hash_table2.emplace_unique(90);

        CHECK(hash_table1.size() == 3);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);

        CHECK(hash_table2.size() == 6);
        CHECK(hash_table2.count_equal(40) == 1);
        CHECK(hash_table2.count_equal(50) == 1);
        CHECK(hash_table2.count_equal(60) == 1);
        CHECK(hash_table2.count_equal(70) == 1);
        CHECK(hash_table2.count_equal(80) == 1);
        CHECK(hash_table2.count_equal(90) == 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 6);
        CHECK(hash_table1.count_equal(40) == 1);
        CHECK(hash_table1.count_equal(50) == 1);
        CHECK(hash_table1.count_equal(60) == 1);
        CHECK(hash_table1.count_equal(70) == 1);
        CHECK(hash_table1.count_equal(80) == 1);
        CHECK(hash_table1.count_equal(90) == 1);

        CHECK(hash_table2.size() == 3);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() != 0 && hash_table2.size() != 0 && hash_table1.size() == hash_table2.size()
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table1.emplace_unique(10);
        hash_table1.emplace_unique(20);
        hash_table1.emplace_unique(30);
        hash_table1.emplace_unique(40);

        hash_table2.emplace_unique(50);
        hash_table2.emplace_unique(60);
        hash_table2.emplace_unique(70);
        hash_table2.emplace_unique(80);

        CHECK(hash_table1.size() == 4);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);
        CHECK(hash_table1.count_equal(40) == 1);

        CHECK(hash_table2.size() == 4);
        CHECK(hash_table2.count_equal(50) == 1);
        CHECK(hash_table2.count_equal(60) == 1);
        CHECK(hash_table2.count_equal(70) == 1);
        CHECK(hash_table2.count_equal(80) == 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 4);
        CHECK(hash_table1.count_equal(50) == 1);
        CHECK(hash_table1.count_equal(60) == 1);
        CHECK(hash_table1.count_equal(70) == 1);
        CHECK(hash_table1.count_equal(80) == 1);

        CHECK(hash_table2.size() == 4);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
        CHECK(hash_table2.count_equal(40) == 1);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() != 0 && hash_table2.size() != 0 && hash_table1.size() > hash_table2.size()
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table1.emplace_unique(10);
        hash_table1.emplace_unique(20);
        hash_table1.emplace_unique(30);
        hash_table1.emplace_unique(40);
        hash_table1.emplace_unique(50);
        hash_table1.emplace_unique(60);

        hash_table2.emplace_unique(70);
        hash_table2.emplace_unique(80);
        hash_table2.emplace_unique(90);

        CHECK(hash_table1.size() == 6);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);
        CHECK(hash_table1.count_equal(40) == 1);
        CHECK(hash_table1.count_equal(50) == 1);
        CHECK(hash_table1.count_equal(60) == 1);

        CHECK(hash_table2.size() == 3);
        CHECK(hash_table2.count_equal(70) == 1);
        CHECK(hash_table2.count_equal(80) == 1);
        CHECK(hash_table2.count_equal(90) == 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 3);
        CHECK(hash_table1.count_equal(70) == 1);
        CHECK(hash_table1.count_equal(80) == 1);
        CHECK(hash_table1.count_equal(90) == 1);

        CHECK(hash_table2.size() == 6);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
        CHECK(hash_table2.count_equal(40) == 1);
        CHECK(hash_table2.count_equal(50) == 1);
        CHECK(hash_table2.count_equal(60) == 1);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test NON-MEMBER comparison operators
BEGIN_STATIC_ASSERT
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_hash = sfl::test::hash<key_type>;
    using key_equal = std::equal_to<key_type>;
    using node_allocator = std::allocator<key_type>;
    using bucket_allocator = std::allocator<key_type>;
    using bucket_count_policy = sfl::dtl::hash_table_dynamic_basic_bucket_count_policy;
    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;
    using hash_table_type = sfl::dtl::hash_table<key_type, value_type, key_of_value, key_hash, key_equal, node_allocator, bucket_allocator, bucket_count_policy, max_load_policy>;

    hash_table_type hash_table1(100), hash_table2(100);

    hash_table1.emplace_unique(10);
    hash_table1.emplace_unique(20);
    hash_table1.emplace_unique(30);

    hash_table2.emplace_unique(10);
    hash_table2.emplace_unique(20);
    hash_table2.emplace_unique(30);
    hash_table2.emplace_unique(40);
    hash_table2.emplace_unique(50);

    CHECK((hash_table1 == hash_table1) == true);
    CHECK((hash_table1 == hash_table2) == false);
    CHECK((hash_table2 == hash_table1) == false);
    CHECK((hash_table2 == hash_table2) == true);

    CHECK((hash_table1 != hash_table1) == false);
    CHECK((hash_table1 != hash_table2) == true);
    CHECK((hash_table2 != hash_table1) == true);
    CHECK((hash_table2 != hash_table2) == false);
}
END_STATIC_ASSERT

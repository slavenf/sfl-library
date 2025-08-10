#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xobj;

PRINT("Test PRIVATE make_node and drop_node");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    using node_pointer = typename hash_table_type::node_pointer;

    hash_table_type hash_table(100);

    hash_table_type::make_node_functor make_node(hash_table);

    node_pointer p1 = make_node(1);
    node_pointer p2 = make_node(2);
    node_pointer p3 = make_node(3);

    CHECK(p1->value_.ref() == 1);
    CHECK(p2->value_.ref() == 2);
    CHECK(p3->value_.ref() == 3);

    hash_table.drop_node(p3);
    hash_table.drop_node(p2);
    hash_table.drop_node(p1);
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test emplace_equal(Args&&...)");
{
    static const std::vector<std::vector<int>> insert_patterns
    {
        {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 },
        {  1,  2,  3,  4,  5,  6,  7,  8, 16, 15, 14, 13, 12, 11, 10,  9 },
        {  8,  7,  6,  5,  4,  3,  2,  1,  9, 10, 11, 12, 13, 14, 15, 16 },
        {  8,  7,  6,  5,  4,  3,  2,  1, 16, 15, 14, 13, 12, 11, 10,  9 },

        {  9, 10, 11, 12, 13, 14, 15, 16,  1,  2,  3,  4,  5,  6,  7,  8 },
        {  9, 10, 11, 12, 13, 14, 15, 16,  8,  7,  6,  5,  4,  3,  2,  1 },
        { 16, 15, 14, 13, 12, 11, 10,  9,  1,  2,  3,  4,  5,  6,  7,  8 },
        { 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1 },

        {  1,  3,  5,  7,  9, 11, 13, 15,  2,  4,  6,  8, 10, 12, 14, 16 },
        {  1,  3,  5,  7,  9, 11, 13, 15, 16, 14, 12, 10,  8,  6,  4,  2 },
        { 15, 13, 11,  9,  7,  5,  3,  1,  2,  4,  6,  8, 10, 12, 14, 16 },
        { 15, 13, 11,  9,  7,  5,  3,  1, 16, 14, 12, 10,  8,  6,  4,  2 },

        {  2,  4,  6,  8, 10, 12, 14, 16,  1,  3,  5,  7,  9, 11, 13, 15 },
        {  2,  4,  6,  8, 10, 12, 14, 16, 15, 13, 11,  9,  7,  5,  3,  1 },
        { 16, 14, 12, 10,  8,  6,  4,  2,  1,  3,  5,  7,  9, 11, 13, 15 },
        { 16, 14, 12, 10,  8,  6,  4,  2, 15, 13, 11,  9,  7,  5,  3,  1 },
    };

    for (auto& row : insert_patterns)
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

        hash_table_type hash_table(100);

        ///////////////////////////////////////////////////////////////////////
        // Insert 1st set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(elem);
            CHECK(*res == elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 1);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem);
        }

        CHECK(hash_table.size() == row.size());

        ///////////////////////////////////////////////////////////////////////
        // Insert 1st set again

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(elem);
            CHECK(*res == elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 2);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 2);
            CHECK(std::accumulate(er1.first, er1.second, 0) == 2 * elem);

            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 2);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == 2 * elem);
        }

        CHECK(hash_table.size() == row.size() * 2);

        ///////////////////////////////////////////////////////////////////////
        // Insert 2nd set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(100 + elem);
            CHECK(*res == 100 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 2);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 2);
            CHECK(std::accumulate(er1.first, er1.second, 0) == 2 * elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 1);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 1);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 100 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 3);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == 2 * elem + (100 + elem));
        }

        CHECK(hash_table.size() == row.size() * 3);

        ///////////////////////////////////////////////////////////////////////
        // Insert 2nd set again

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(100 + elem);
            CHECK(*res == 100 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 2);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 2);
            CHECK(std::accumulate(er1.first, er1.second, 0) == 2 * elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 2);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 2);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 2 * (100 + elem));

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 4);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == 2 * elem + 2 * (100 + elem));
        }

        CHECK(hash_table.size() == row.size() * 4);

        ///////////////////////////////////////////////////////////////////////
        // Insert 3rd set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(200 + elem);
            CHECK(*res == 200 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 2);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 2);
            CHECK(std::accumulate(er1.first, er1.second, 0) == 2 * elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 2);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 2);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 2 * (100 + elem));

            CHECK(hash_table.contains(200 + elem));
            CHECK(hash_table.count_equal(200 + elem) == 1);
            auto it3 = hash_table.find(200 + elem);
            CHECK(it3 != hash_table.end());
            CHECK(*it3 == 200 + elem);
            auto er3 = hash_table.equal_range(200 + elem);
            CHECK(std::distance(er3.first, er3.second) == 1);
            CHECK(std::accumulate(er3.first, er3.second, 0) == 200 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket(elem) == hash_table.bucket(200 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 5);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == 2 * elem + 2 * (100 + elem) + (200 + elem));
        }

        CHECK(hash_table.size() == row.size() * 5);

        ///////////////////////////////////////////////////////////////////////
        // Insert 3rd set again

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_equal(200 + elem);
            CHECK(*res == 200 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 2);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 2);
            CHECK(std::accumulate(er1.first, er1.second, 0) == 2 * elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 2);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 2);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 2 * (100 + elem));

            CHECK(hash_table.contains(200 + elem));
            CHECK(hash_table.count_equal(200 + elem) == 2);
            auto it3 = hash_table.find(200 + elem);
            CHECK(it3 != hash_table.end());
            CHECK(*it3 == 200 + elem);
            auto er3 = hash_table.equal_range(200 + elem);
            CHECK(std::distance(er3.first, er3.second) == 2);
            CHECK(std::accumulate(er3.first, er3.second, 0) == 2 * (200 + elem));

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket(elem) == hash_table.bucket(200 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 6);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == 2 * elem + 2 * (100 + elem) + 2 * (200 + elem));
        }

        CHECK(hash_table.size() == row.size() * 6);

        ///////////////////////////////////////////////////////////////////////

        {
            const auto bbeg = hash_table.begin(row[0]);
            const auto bend = hash_table.end(row[0]);
            const auto cbbeg = hash_table.cbegin(row[0]);
            const auto cbend = hash_table.cend(row[0]);

            CHECK(bbeg == cbbeg);
            CHECK(cbbeg == bbeg);
            CHECK(bbeg != bend);
            CHECK(bbeg != cbend);
            CHECK(cbbeg != bend);
            CHECK(cbbeg != cbend);
        }

        {
            const int len = int(row.size());
            const int sum = std::accumulate(row.begin(), row.end(), 0);
            const int tot = 6 * sum + 2 * 100 * len + 2 * 200 * len;

            const auto beg = hash_table.begin();
            const auto end = hash_table.end();
            const auto cbeg = hash_table.cbegin();
            const auto cend = hash_table.cend();

            CHECK(int(std::accumulate(beg, end, 0)) == tot);
            CHECK(int(std::accumulate(cbeg, cend, 0)) == tot);

            CHECK(beg == cbeg);
            CHECK(cbeg == beg);
            CHECK(beg != end);
            CHECK(beg != cend);
            CHECK(cbeg != end);
            CHECK(cbeg != cend);
        }
    }
}

PRINT("Test emplace_unique(Args&&...)");
{
    static const std::vector<std::vector<int>> insert_patterns
    {
        {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 },
        {  1,  2,  3,  4,  5,  6,  7,  8, 16, 15, 14, 13, 12, 11, 10,  9 },
        {  8,  7,  6,  5,  4,  3,  2,  1,  9, 10, 11, 12, 13, 14, 15, 16 },
        {  8,  7,  6,  5,  4,  3,  2,  1, 16, 15, 14, 13, 12, 11, 10,  9 },

        {  9, 10, 11, 12, 13, 14, 15, 16,  1,  2,  3,  4,  5,  6,  7,  8 },
        {  9, 10, 11, 12, 13, 14, 15, 16,  8,  7,  6,  5,  4,  3,  2,  1 },
        { 16, 15, 14, 13, 12, 11, 10,  9,  1,  2,  3,  4,  5,  6,  7,  8 },
        { 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1 },

        {  1,  3,  5,  7,  9, 11, 13, 15,  2,  4,  6,  8, 10, 12, 14, 16 },
        {  1,  3,  5,  7,  9, 11, 13, 15, 16, 14, 12, 10,  8,  6,  4,  2 },
        { 15, 13, 11,  9,  7,  5,  3,  1,  2,  4,  6,  8, 10, 12, 14, 16 },
        { 15, 13, 11,  9,  7,  5,  3,  1, 16, 14, 12, 10,  8,  6,  4,  2 },

        {  2,  4,  6,  8, 10, 12, 14, 16,  1,  3,  5,  7,  9, 11, 13, 15 },
        {  2,  4,  6,  8, 10, 12, 14, 16, 15, 13, 11,  9,  7,  5,  3,  1 },
        { 16, 14, 12, 10,  8,  6,  4,  2,  1,  3,  5,  7,  9, 11, 13, 15 },
        { 16, 14, 12, 10,  8,  6,  4,  2, 15, 13, 11,  9,  7,  5,  3,  1 },
    };

    for (auto& row : insert_patterns)
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

        hash_table_type hash_table(100);

        ///////////////////////////////////////////////////////////////////////
        // Insert 1st set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(elem);
            CHECK(res.second == true);
            CHECK(*res.first == elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 1);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem);
        }

        CHECK(hash_table.size() == row.size());

        ///////////////////////////////////////////////////////////////////////
        // Insert 1st set again --> no changes

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(elem);
            CHECK(res.second == false);
            CHECK(*res.first == elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 1);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem);
        }

        CHECK(hash_table.size() == row.size());

        ///////////////////////////////////////////////////////////////////////
        // Insert 2nd set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(100 + elem);
            CHECK(res.second == true);
            CHECK(*res.first == 100 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 1);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 1);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 100 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 2);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem + (100 + elem));
        }

        CHECK(hash_table.size() == row.size() * 2);

        ///////////////////////////////////////////////////////////////////////
        // Insert 2nd set again --> no changes

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(100 + elem);
            CHECK(res.second == false);
            CHECK(*res.first == 100 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 1);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 1);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 100 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 2);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem + (100 + elem));
        }

        CHECK(hash_table.size() == row.size() * 2);

        ///////////////////////////////////////////////////////////////////////
        // Insert 3rd set

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(200 + elem);
            CHECK(res.second == true);
            CHECK(*res.first == 200 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 1);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 1);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 100 + elem);

            CHECK(hash_table.contains(200 + elem));
            CHECK(hash_table.count_equal(200 + elem) == 1);
            auto it3 = hash_table.find(200 + elem);
            CHECK(it3 != hash_table.end());
            CHECK(*it3 == 200 + elem);
            auto er3 = hash_table.equal_range(200 + elem);
            CHECK(std::distance(er3.first, er3.second) == 1);
            CHECK(std::accumulate(er3.first, er3.second, 0) == 200 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket(elem) == hash_table.bucket(200 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 3);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem + (100 + elem) + (200 + elem));
        }

        CHECK(hash_table.size() == row.size() * 3);

        ///////////////////////////////////////////////////////////////////////
        // Insert 3rd set again --> no changes

        for (auto& elem : row)
        {
            const auto res = hash_table.emplace_unique(200 + elem);
            CHECK(res.second == false);
            CHECK(*res.first == 200 + elem);
        }

        for (auto& elem : row)
        {
            CHECK(hash_table.contains(elem));
            CHECK(hash_table.count_equal(elem) == 1);
            auto it1 = hash_table.find(elem);
            CHECK(it1 != hash_table.end());
            CHECK(*it1 == elem);
            auto er1 = hash_table.equal_range(elem);
            CHECK(std::distance(er1.first, er1.second) == 1);
            CHECK(std::accumulate(er1.first, er1.second, 0) == elem);

            CHECK(hash_table.contains(100 + elem));
            CHECK(hash_table.count_equal(100 + elem) == 1);
            auto it2 = hash_table.find(100 + elem);
            CHECK(it2 != hash_table.end());
            CHECK(*it2 == 100 + elem);
            auto er2 = hash_table.equal_range(100 + elem);
            CHECK(std::distance(er2.first, er2.second) == 1);
            CHECK(std::accumulate(er2.first, er2.second, 0) == 100 + elem);

            CHECK(hash_table.contains(200 + elem));
            CHECK(hash_table.count_equal(200 + elem) == 1);
            auto it3 = hash_table.find(200 + elem);
            CHECK(it3 != hash_table.end());
            CHECK(*it3 == 200 + elem);
            auto er3 = hash_table.equal_range(200 + elem);
            CHECK(std::distance(er3.first, er3.second) == 1);
            CHECK(std::accumulate(er3.first, er3.second, 0) == 200 + elem);

            CHECK(hash_table.bucket(elem) == hash_table.bucket(100 + elem));
            CHECK(hash_table.bucket(elem) == hash_table.bucket(200 + elem));
            CHECK(hash_table.bucket_size(hash_table.bucket(elem)) == 3);
            auto bbeg = hash_table.begin(hash_table.bucket(elem));
            auto bend = hash_table.end(hash_table.bucket(elem));
            CHECK(std::accumulate(bbeg, bend, 0) == elem + (100 + elem) + (200 + elem));
        }

        CHECK(hash_table.size() == row.size() * 3);

        ///////////////////////////////////////////////////////////////////////

        {
            const auto bbeg = hash_table.begin(row[0]);
            const auto bend = hash_table.end(row[0]);
            const auto cbbeg = hash_table.cbegin(row[0]);
            const auto cbend = hash_table.cend(row[0]);

            CHECK(bbeg == cbbeg);
            CHECK(cbbeg == bbeg);
            CHECK(bbeg != bend);
            CHECK(bbeg != cbend);
            CHECK(cbbeg != bend);
            CHECK(cbbeg != cbend);
        }

        {
            const int len = int(row.size());
            const int sum = std::accumulate(row.begin(), row.end(), 0);
            const int tot = 3 * sum + 100 * len + 200 * len;

            const auto beg = hash_table.begin();
            const auto end = hash_table.end();
            const auto cbeg = hash_table.cbegin();
            const auto cend = hash_table.cend();

            CHECK(int(std::accumulate(beg, end, 0)) == tot);
            CHECK(int(std::accumulate(cbeg, cend, 0)) == tot);

            CHECK(beg == cbeg);
            CHECK(cbeg == beg);
            CHECK(beg != end);
            CHECK(beg != cend);
            CHECK(cbeg != end);
            CHECK(cbeg != cend);
        }
    }
}

PRINT("Test emplace_hint_equal(const_iterator, Args&&...)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            for (int insert_pos = 0; insert_pos <= int(initial_size); ++insert_pos)
            {
                hash_table_type hash_table(100);

                ///////////////////////////////////////////////////////////////

                // Insert additional elements
                for (auto& x : initial_elems)
                {
                    hash_table.emplace_equal(x);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = std::next(hash_table.begin(), insert_pos);
                    const auto res = hash_table.emplace_hint_equal(hint, additional_elem);
                    CHECK(*res == additional_elem);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    if (x != additional_elem)
                    {
                        CHECK(hash_table.count_equal(x) == 1);
                    }
                    else
                    {
                        CHECK(hash_table.count_equal(x) == 2);
                    }
                }

                // Make sure hash table contains additional element
                {
                    const auto b = initial_elems.begin();
                    const auto e = initial_elems.end();

                    // If additional elements is not in initial elements
                    if (std::find(b, e, additional_elem) == e)
                    {
                        CHECK(hash_table.count_equal(additional_elem) == 1);
                    }
                    else
                    {
                        CHECK(hash_table.count_equal(additional_elem) == 2);
                    }
                }
            }
        }
    }
}

PRINT("Test emplace_hint_unique(const_iterator, Args&&...)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            for (int insert_pos = 0; insert_pos <= int(initial_size); ++insert_pos)
            {
                hash_table_type hash_table(100);

                ///////////////////////////////////////////////////////////////

                // Insert additional elements
                for (auto& x : initial_elems)
                {
                    hash_table.emplace_equal(x);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = std::next(hash_table.begin(), insert_pos);
                    const auto res = hash_table.emplace_hint_unique(hint, additional_elem);
                    CHECK(*res == additional_elem);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                // Make sure hash table contains additional element
                {
                    CHECK(hash_table.count_equal(additional_elem) == 1);
                }
            }
        }
    }
}

PRINT("Test insert_equal(V&&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            hash_table_type hash_table(100);

            ///////////////////////////////////////////////////////////////////

            // Insert additional elements
            for (auto& x : initial_elems)
            {
                hash_table.emplace_equal(x);
            }

            // Make sure hash table contains all initial elements
            for (auto& x : initial_elems)
            {
                CHECK(hash_table.count_equal(x) == 1);
            }

            ///////////////////////////////////////////////////////////////////

            // Insert additional element
            {
                const auto res = hash_table.insert_equal(additional_elem);
                CHECK(*res == additional_elem);
            }

            // Make sure hash table contains all initial elements
            for (auto& x : initial_elems)
            {
                if (x != additional_elem)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }
                else
                {
                    CHECK(hash_table.count_equal(x) == 2);
                }
            }

            // Make sure hash table contains additional element
            {
                const auto b = initial_elems.begin();
                const auto e = initial_elems.end();

                // If additional elements is not in initial elements
                if (std::find(b, e, additional_elem) == e)
                {
                    CHECK(hash_table.count_equal(additional_elem) == 1);
                }
                else
                {
                    CHECK(hash_table.count_equal(additional_elem) == 2);
                }
            }
        }
    }
}

PRINT("Test insert_unique(V&&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            hash_table_type hash_table(100);

            ///////////////////////////////////////////////////////////////////

            // Insert additional elements
            for (auto& x : initial_elems)
            {
                hash_table.emplace_equal(x);
            }

            // Make sure hash table contains all initial elements
            for (auto& x : initial_elems)
            {
                CHECK(hash_table.count_equal(x) == 1);
            }

            ///////////////////////////////////////////////////////////////////

            // Insert additional element
            {
                const auto res = hash_table.insert_unique(additional_elem);
                CHECK(*res.first == additional_elem);
                const auto b = initial_elems.begin();
                const auto e = initial_elems.end();
                CHECK(res.second == (std::find(b, e, additional_elem) == e));
            }

            // Make sure hash table contains all initial elements
            for (auto& x : initial_elems)
            {
                CHECK(hash_table.count_equal(x) == 1);
            }

            // Make sure hash table contains additional element
            {
                CHECK(hash_table.count_equal(additional_elem) == 1);
            }
        }
    }
}

PRINT("Test insert_hint_equal(const_iterator, Args&&...)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            for (int insert_pos = 0; insert_pos <= int(initial_size); ++insert_pos)
            {
                hash_table_type hash_table(100);

                ///////////////////////////////////////////////////////////////

                // Insert additional elements
                for (auto& x : initial_elems)
                {
                    hash_table.emplace_equal(x);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = std::next(hash_table.begin(), insert_pos);
                    const auto res = hash_table.insert_hint_equal(hint, additional_elem);
                    CHECK(*res == additional_elem);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    if (x != additional_elem)
                    {
                        CHECK(hash_table.count_equal(x) == 1);
                    }
                    else
                    {
                        CHECK(hash_table.count_equal(x) == 2);
                    }
                }

                // Make sure hash table contains additional element
                {
                    const auto b = initial_elems.begin();
                    const auto e = initial_elems.end();

                    // If additional elements is not in initial elements
                    if (std::find(b, e, additional_elem) == e)
                    {
                        CHECK(hash_table.count_equal(additional_elem) == 1);
                    }
                    else
                    {
                        CHECK(hash_table.count_equal(additional_elem) == 2);
                    }
                }
            }
        }
    }
}

PRINT("Test insert_hint_unique(const_iterator, Args&&...)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    for (int initial_size = 0; initial_size <= 5; ++initial_size)
    {
        std::vector<int> initial_elems;
        for (int i = 0; i < initial_size; ++i)
        {
            initial_elems.push_back(i);
        }

        std::vector<int> additional_elems;
        for (int i = 0; i < initial_size + 3; ++i)
        {
            additional_elems.push_back(i);
        }

        for (const auto& additional_elem : additional_elems)
        {
            for (int insert_pos = 0; insert_pos <= int(initial_size); ++insert_pos)
            {
                hash_table_type hash_table(100);

                ///////////////////////////////////////////////////////////////

                // Insert additional elements
                for (auto& x : initial_elems)
                {
                    hash_table.emplace_equal(x);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = std::next(hash_table.begin(), insert_pos);
                    const auto res = hash_table.insert_hint_unique(hint, additional_elem);
                    CHECK(*res == additional_elem);
                }

                // Make sure hash table contains all initial elements
                for (auto& x : initial_elems)
                {
                    CHECK(hash_table.count_equal(x) == 1);
                }

                // Make sure hash table contains additional element
                {
                    CHECK(hash_table.count_equal(additional_elem) == 1);
                }
            }
        }
    }
}

PRINT("Test clear()");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test insert_or_assign(K&&, M&&)");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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

PRINT("Test insert_or_assign_hint(const_iterator, K&&, M&&)");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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

PRINT("Test try_emplace(K&&, Args&&...)");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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

PRINT("Test try_emplace_hint(const_iterator, K&&, Args&&...)");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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
        using hash_table_type = sfl::dtl::hash_table
        <
            xint,
            std::pair<const xint, xint>,
            sfl::dtl::first,
            sfl::test::hash<xint>,
            std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>,
            TPARAM_ALLOCATOR<xint>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_no_max_load_policy,
            void
        >;

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

PRINT("Test erase_equal(const_iterator)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < 200; ++i)
    {
        hash_table_type hash_table(100);

        for (const auto& elem : elements)
        {
            hash_table.emplace_equal(elem);
        }

        SFL_ASSERT(int(hash_table.size()) == int(elements.size()));

        while (!hash_table.empty())
        {
            std::uniform_int_distribution<> dist(0, int(hash_table.size()) - 1);

            auto it = std::next(hash_table.begin(), dist(gen));

            hash_table.erase_equal(it);

            CHECK(hash_table.verify());
        }
    }
}

PRINT("Test erase_unique(const_iterator)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < 200; ++i)
    {
        hash_table_type hash_table(100);

        for (const auto& elem : elements)
        {
            hash_table.emplace_unique(elem);
        }

        SFL_ASSERT(int(hash_table.size()) == int(elements.size()));

        while (!hash_table.empty())
        {
            std::uniform_int_distribution<> dist(0, int(hash_table.size()) - 1);

            auto it = std::next(hash_table.begin(), dist(gen));

            hash_table.erase_unique(it);

            CHECK(hash_table.verify());
        }
    }
}

PRINT("Test erase_equal(const_iterator, const_iterator)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    for (int size = 0; size < int(elements.size()); ++size)
    {
        for (int i = 0; i <= size; ++i)
        {
            for (int j = i; j <= size; ++j)
            {
                hash_table_type hash_table(100);

                for (int k = 0; k < size; ++k)
                {
                    hash_table.emplace_equal(elements[k]);
                }

                SFL_ASSERT(int(hash_table.size()) == size);

                const auto it1 = std::next(hash_table.begin(), i);
                const auto it2 = std::next(hash_table.begin(), j);

                hash_table.erase_equal(it1, it2);

                CHECK(hash_table.verify());
            }
        }
    }
}

PRINT("Test erase_unique(const_iterator, const_iterator)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    for (int size = 0; size < int(elements.size()); ++size)
    {
        for (int i = 0; i <= size; ++i)
        {
            for (int j = i; j <= size; ++j)
            {
                hash_table_type hash_table(100);

                for (int k = 0; k < size; ++k)
                {
                    hash_table.emplace_unique(elements[k]);
                }

                SFL_ASSERT(int(hash_table.size()) == size);

                const auto it1 = std::next(hash_table.begin(), i);
                const auto it2 = std::next(hash_table.begin(), j);

                hash_table.erase_unique(it1, it2);

                CHECK(hash_table.verify());
            }
        }
    }
}

PRINT("Test erase_key_unique(const K&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    hash_table_type hash_table(100);

    for (const auto& elem : elements)
    {
        hash_table.emplace_unique(elem);
    }

    SFL_ASSERT(int(hash_table.size()) == int(elements.size()));

    for (const auto& elem : elements)
    {
        CHECK(hash_table.erase_key_unique(elem) == 1);
        CHECK(hash_table.erase_key_unique(elem) == 0);
        CHECK(hash_table.verify());
    }
}

PRINT("Test erase_key_equal(const K&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    static const std::vector<int> elements
    {
          1,   2,   3,   4,   5,
        101, 102, 103, 104, 105,
        201, 202, 203, 204, 205,
    };

    hash_table_type hash_table(100);

    for (int i = 0; i < 3; i++)
    {
        for (const auto& elem : elements)
        {
            hash_table.emplace_equal(elem);
        }
    }

    SFL_ASSERT(int(hash_table.size()) == 3 * int(elements.size()));

    for (const auto& elem : elements)
    {
        CHECK(hash_table.erase_key_equal(elem) == 3);
        CHECK(hash_table.erase_key_equal(elem) == 0);
        CHECK(hash_table.verify());
    }
}

PRINT("Test swap(container&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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
        hash_table2.emplace_unique(40);
        hash_table2.emplace_unique(50);
        hash_table2.emplace_unique(60);
        hash_table2.emplace_unique(70);
        hash_table2.emplace_unique(80);
        hash_table2.emplace_unique(90);

        CHECK(hash_table1.size() == 0);

        CHECK(hash_table2.size() == 9);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
        CHECK(hash_table2.count_equal(40) == 1);
        CHECK(hash_table2.count_equal(50) == 1);
        CHECK(hash_table2.count_equal(60) == 1);
        CHECK(hash_table2.count_equal(70) == 1);
        CHECK(hash_table2.count_equal(80) == 1);
        CHECK(hash_table2.count_equal(90) == 1);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 9);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);
        CHECK(hash_table1.count_equal(40) == 1);
        CHECK(hash_table1.count_equal(50) == 1);
        CHECK(hash_table1.count_equal(60) == 1);
        CHECK(hash_table1.count_equal(70) == 1);
        CHECK(hash_table1.count_equal(80) == 1);
        CHECK(hash_table1.count_equal(90) == 1);
        CHECK(hash_table2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION hash_table1.size() != 0 && hash_table2.size() == 0
    {
        hash_table_type hash_table1(100), hash_table2(100);

        hash_table1.emplace_unique(10);
        hash_table1.emplace_unique(20);
        hash_table1.emplace_unique(30);
        hash_table1.emplace_unique(40);
        hash_table1.emplace_unique(50);
        hash_table1.emplace_unique(60);
        hash_table1.emplace_unique(70);
        hash_table1.emplace_unique(80);
        hash_table1.emplace_unique(90);

        CHECK(hash_table1.size() == 9);
        CHECK(hash_table1.count_equal(10) == 1);
        CHECK(hash_table1.count_equal(20) == 1);
        CHECK(hash_table1.count_equal(30) == 1);
        CHECK(hash_table1.count_equal(40) == 1);
        CHECK(hash_table1.count_equal(50) == 1);
        CHECK(hash_table1.count_equal(60) == 1);
        CHECK(hash_table1.count_equal(70) == 1);
        CHECK(hash_table1.count_equal(80) == 1);
        CHECK(hash_table1.count_equal(90) == 1);

        CHECK(hash_table2.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        hash_table1.swap(hash_table2);

        CHECK(hash_table1.size() == 0);
        CHECK(hash_table2.size() == 9);
        CHECK(hash_table2.count_equal(10) == 1);
        CHECK(hash_table2.count_equal(20) == 1);
        CHECK(hash_table2.count_equal(30) == 1);
        CHECK(hash_table2.count_equal(40) == 1);
        CHECK(hash_table2.count_equal(50) == 1);
        CHECK(hash_table2.count_equal(60) == 1);
        CHECK(hash_table2.count_equal(70) == 1);
        CHECK(hash_table2.count_equal(80) == 1);
        CHECK(hash_table2.count_equal(90) == 1);
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

///////////////////////////////////////////////////////////////////////////////

PRINT("Stress test insert with rehashing");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(2);

        for (int i = 0; i < 100; ++i)
        {
            hash_table.emplace_unique(i);

            for (int j = 0; j < i; ++j)
            {
                CHECK(hash_table.count_equal(j) == 1);
            }
        }
    }

    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_prime_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(11);

        for (int i = 0; i < 100; ++i)
        {
            hash_table.emplace_unique(i);

            for (int j = 0; j < i; ++j)
            {
                CHECK(hash_table.count_equal(j) == 1);
            }
        }
    }

    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(1);

        for (int i = 0; i < 100; ++i)
        {
            hash_table.emplace_unique(i);

            for (int j = 0; j < i; ++j)
            {
                CHECK(hash_table.count_equal(j) == 1);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test container(size_type)");
{
    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(4);

        (void)hash_table;

        for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
        {
            CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
        }
    }

    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_prime_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(7);

        (void)hash_table;

        for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
        {
            CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
        }
    }

    {
        using hash_table_type = sfl::dtl::hash_table
        <
            int,
            int,
            sfl::dtl::identity,
            sfl::test::hash<int>,
            std::equal_to<int>,
            TPARAM_ALLOCATOR<int>,
            TPARAM_ALLOCATOR<int>,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
            sfl::dtl::hash_table_standard_max_load_policy,
            void
        >;

        hash_table_type hash_table(9);

        (void)hash_table;

        for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
        {
            CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
        }
    }
}

PRINT("Test container(size_type, const Alloc&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        sfl::dtl::hash_table_standard_max_load_policy,
        void
    >;

    TPARAM_ALLOCATOR<int> alloc;

    hash_table_type hash_table(4, alloc);

    (void)hash_table;

    for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
    {
        CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
    }
}

PRINT("Test container(size_type, const key_hash&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        sfl::dtl::hash_table_standard_max_load_policy,
        void
    >;

    sfl::test::hash<int> hash;

    hash_table_type hash_table(4, hash);

    (void)hash_table;

    for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
    {
        CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
    }
}

PRINT("Test container(size_type, const key_hash&, const Alloc&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        sfl::dtl::hash_table_standard_max_load_policy,
        void
    >;

    sfl::test::hash<int> hash;

    TPARAM_ALLOCATOR<int> alloc;

    hash_table_type hash_table(4, hash, alloc);

    (void)hash_table;

    for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
    {
        CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
    }
}

PRINT("Test container(size_type, const key_hash&, const key_equal&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        sfl::dtl::hash_table_standard_max_load_policy,
        void
    >;

    sfl::test::hash<int> hash;

    std::equal_to<int> equal;

    hash_table_type hash_table(4, hash, equal);

    (void)hash_table;

    for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
    {
        CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
    }
}

PRINT("Test container(size_type, const key_hash&, const key_equal&, const Alloc&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        int,
        int,
        sfl::dtl::identity,
        sfl::test::hash<int>,
        std::equal_to<int>,
        TPARAM_ALLOCATOR<int>,
        TPARAM_ALLOCATOR<int>,
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        sfl::dtl::hash_table_standard_max_load_policy,
        void
    >;

    sfl::test::hash<int> hash;

    std::equal_to<int> equal;

    TPARAM_ALLOCATOR<int> alloc;

    hash_table_type hash_table(4, hash, equal, alloc);

    (void)hash_table;

    for (int i = 0; i < int(hash_table.data_.get_bucket_count()); ++i)
    {
        CHECK(hash_table.data_.buckets_[i].next_ == nullptr);
    }
}

PRINT("Test container(const container&, EqualOrUniqueTag)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test container(const container&, EqualOrUniqueTag, const Alloc&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        hash_table_type hash_table2(hash_table1, sfl::dtl::hash_table_equal_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

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

        TPARAM_ALLOCATOR<xint> alloc;

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

        TPARAM_ALLOCATOR<xint> alloc;

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

PRINT("Test container(container&&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test container(container&&, const Alloc&)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        hash_table_type hash_table2(std::move(hash_table1), sfl::dtl::hash_table_equal_t(), alloc);

        CHECK(hash_table2.size() == 0);
    }

    {
        hash_table_type hash_table1(100);

        CHECK(hash_table1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

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

        TPARAM_ALLOCATOR<xint> alloc;

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

        TPARAM_ALLOCATOR<xint> alloc;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test assign_copy(const container&, EqualOrUniqueTag)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test assign_move(const container&, EqualOrUniqueTag)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test assign_range_equal(InputIt, InputIt)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

PRINT("Test assign_range_unique(InputIt, InputIt)");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test NON-MEMBER comparison operators");
{
    using hash_table_type = sfl::dtl::hash_table
    <
        xint,
        xint,
        sfl::dtl::identity,
        sfl::test::hash<xint>,
        std::equal_to<xint>,
        TPARAM_ALLOCATOR<xint>,
        TPARAM_ALLOCATOR<xint>,
        sfl::dtl::hash_table_dynamic_basic_bucket_count_policy,
        sfl::dtl::hash_table_no_max_load_policy,
        void
    >;

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

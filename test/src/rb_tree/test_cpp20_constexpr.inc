#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

// Test container()
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const KeyCompare&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    typename tree_type::key_compare comp;

    tree_type tree(comp);

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    typename tree_type::allocator_type alloc;

    tree_type tree(alloc);

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const KeyCompare&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    typename tree_type::key_compare comp;

    typename tree_type::allocator_type alloc;

    tree_type tree(comp, alloc);

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);
}
END_STATIC_ASSERT

// Test container(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    tree_type tree2(tree1);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test container(const container&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    typename tree_type::allocator_type alloc;

    tree_type tree2(tree1, alloc);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test container(const container&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    tree_type tree2(std::move(tree1));

    CHECK(tree1.size() == 0);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test container(const container&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    typename tree_type::allocator_type alloc;

    tree_type tree2(std::move(tree1), alloc);

    CHECK(tree1.size() == 0);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test assign_copy(const container&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1, tree2;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    tree2.emplace_unique(40);
    tree2.emplace_unique(50);
    tree2.emplace_unique(60);
    tree2.emplace_unique(70);
    tree2.emplace_unique(80);
    tree2.emplace_unique(90);

    CHECK(tree2.size() == 6);
    CHECK(*NTH(tree2, 0) == 40);
    CHECK(*NTH(tree2, 1) == 50);
    CHECK(*NTH(tree2, 2) == 60);
    CHECK(*NTH(tree2, 3) == 70);
    CHECK(*NTH(tree2, 4) == 80);
    CHECK(*NTH(tree2, 5) == 90);

    tree2.assign_copy(tree1);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test assign_move(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1, tree2;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    tree2.emplace_unique(40);
    tree2.emplace_unique(50);
    tree2.emplace_unique(60);
    tree2.emplace_unique(70);
    tree2.emplace_unique(80);
    tree2.emplace_unique(90);

    CHECK(tree2.size() == 6);
    CHECK(*NTH(tree2, 0) == 40);
    CHECK(*NTH(tree2, 1) == 50);
    CHECK(*NTH(tree2, 2) == 60);
    CHECK(*NTH(tree2, 3) == 70);
    CHECK(*NTH(tree2, 4) == 80);
    CHECK(*NTH(tree2, 5) == 90);

    tree2.assign_move(tree1);

    CHECK(tree1.size() == 0);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

// Test assign_range_equal(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    tree.emplace_unique(10);
    tree.emplace_unique(20);
    tree.emplace_unique(30);

    CHECK(tree.size() == 3);
    CHECK(*NTH(tree, 0) == 10);
    CHECK(*NTH(tree, 1) == 20);
    CHECK(*NTH(tree, 2) == 30);

    std::vector<int> data({40, 50, 60, 70, 80, 90});

    tree.assign_range_equal(data.begin(), data.end());

    CHECK(tree.size() == 6);
    CHECK(*NTH(tree, 0) == 40);
    CHECK(*NTH(tree, 1) == 50);
    CHECK(*NTH(tree, 2) == 60);
    CHECK(*NTH(tree, 3) == 70);
    CHECK(*NTH(tree, 4) == 80);
    CHECK(*NTH(tree, 5) == 90);
}
END_STATIC_ASSERT

// Test assign_range_unique(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    tree.emplace_unique(10);
    tree.emplace_unique(20);
    tree.emplace_unique(30);

    CHECK(tree.size() == 3);
    CHECK(*NTH(tree, 0) == 10);
    CHECK(*NTH(tree, 1) == 20);
    CHECK(*NTH(tree, 2) == 30);

    std::vector<int> data({40, 50, 60, 70, 80, 90});

    tree.assign_range_unique(data.begin(), data.end());

    CHECK(tree.size() == 6);
    CHECK(*NTH(tree, 0) == 40);
    CHECK(*NTH(tree, 1) == 50);
    CHECK(*NTH(tree, 2) == 60);
    CHECK(*NTH(tree, 3) == 70);
    CHECK(*NTH(tree, 4) == 80);
    CHECK(*NTH(tree, 5) == 90);
}
END_STATIC_ASSERT

// Test lower_bound, upper_bound, equal_range, find, count_equal, count_unique, contains
BEGIN_STATIC_ASSERT
{
    // Equal keys
    {
        using key_type = int;
        using value_type = int;
        using key_of_value = sfl::dtl::identity;
        using key_compare = std::less<int>;
        using allocator_type = std::allocator<value_type>;
        using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

        tree_type tree;

        tree.emplace_equal(10);
        tree.emplace_equal(20);
        tree.emplace_equal(30);
        tree.emplace_equal(30);
        tree.emplace_equal(30);
        tree.emplace_equal(40);
        tree.emplace_equal(50);

        for (const auto x : {10, 20, 30, 40, 50})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = tree.lower_bound(x);
                auto it2 = tree.upper_bound(x);

                CHECK(std::distance(it1, it2) == (x == 30 ? 3 : 1));

                auto er = tree.equal_range(x);

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
                auto it = tree.find(x);
                CHECK(it != tree.end());
                CHECK(*it == x);
            }

            // Check count
            CHECK(tree.count_equal(x) == (x == 30 ? 3 : 1));

            // Check contains
            CHECK(tree.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35, 45, 55})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = tree.lower_bound(x);
                auto it2 = tree.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = tree.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = tree.find(x);
                CHECK(it == tree.end());
            }

            // Check count
            CHECK(tree.count_equal(x) == 0);

            // Check contains
            CHECK(tree.contains(x) == false);
        }
    }

    // Unique keys
    {
        using key_type = int;
        using value_type = int;
        using key_of_value = sfl::dtl::identity;
        using key_compare = std::less<int>;
        using allocator_type = std::allocator<value_type>;
        using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

        tree_type tree;

        tree.emplace_unique(10);
        tree.emplace_unique(20);
        tree.emplace_unique(30);
        tree.emplace_unique(40);
        tree.emplace_unique(50);

        for (const auto x : {10, 20, 30, 40, 50})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = tree.lower_bound(x);
                auto it2 = tree.upper_bound(x);

                CHECK(std::distance(it1, it2) == 1);

                auto er = tree.equal_range(x);

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
                auto it = tree.find(x);
                CHECK(it != tree.end());
                CHECK(*it == x);
            }

            // Check count
            CHECK(tree.count_unique(x) == 1);

            // Check contains
            CHECK(tree.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35, 45, 55})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = tree.lower_bound(x);
                auto it2 = tree.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = tree.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = tree.find(x);
                CHECK(it == tree.end());
            }

            // Check count
            CHECK(tree.count_unique(x) == 0);

            // Check contains
            CHECK(tree.contains(x) == false);
        }
    }
}
END_STATIC_ASSERT

// Test clear()
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    tree.emplace_unique(10);
    tree.emplace_unique(20);
    tree.emplace_unique(30);

    CHECK(tree.begin() != tree.end());
    CHECK(tree.size() == 3);

    tree.clear();

    CHECK(tree.begin() == tree.end());
    CHECK(tree.size() == 0);
}
END_STATIC_ASSERT

// Test emplace_hint_equal(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto hint = tree.begin();
        const auto res = tree.emplace_hint_equal(hint, 10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto hint = tree.begin();
        const auto res = tree.emplace_hint_equal(hint, 10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 2);
    }
}
END_STATIC_ASSERT

// Test emplace_hint_unique(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto hint = tree.begin();
        const auto res = tree.emplace_hint_unique(hint, 10);

        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto hint = tree.begin();
        const auto res = tree.emplace_hint_unique(hint, 10);

        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_equal(V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto res = tree.insert_equal(10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.insert_equal(10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 2);
    }
}
END_STATIC_ASSERT

// Test insert_unique(V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto res = tree.insert_unique(10);

        CHECK(res.second == true);
        CHECK(*res.first == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.insert_unique(10);

        CHECK(res.second == false);
        CHECK(*res.first == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_hint_equal(const_iterator, V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto hint = tree.begin();
        const auto res = tree.insert_hint_equal(hint, 10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto hint = tree.begin();
        const auto res = tree.insert_hint_equal(hint, 10);

        CHECK(res != tree.end());
        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 2);
    }
}
END_STATIC_ASSERT

// Test insert_hint_unique(const_iterator, V&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    {
        const auto hint = tree.begin();
        const auto res = tree.insert_hint_unique(hint, 10);

        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }

    {
        const auto hint = tree.begin();
        const auto res = tree.insert_hint_unique(hint, 10);

        CHECK(*res == 10);

        CHECK(tree.empty() == false);
        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign(K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<const int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    {
        const auto res = tree.insert_or_assign(1, 100);

        CHECK(res.second == true);
        CHECK(res.first->first == 1); CHECK(res.first->second == 100);

        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.insert_or_assign(1, 200);

        CHECK(res.second == false);
        CHECK(res.first->first == 1); CHECK(res.first->second == 200);

        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test insert_or_assign_hint(const_iterator, K&&, M&&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<const int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    {
        const auto res = tree.insert_or_assign_hint(tree.begin(), 1, 100);

        CHECK(res->first == 1); CHECK(res->second == 100);

        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.insert_or_assign_hint(tree.begin(), 1, 200);

        CHECK(res->first == 1); CHECK(res->second == 200);

        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace(K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<const int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    {
        const auto res = tree.try_emplace(1, 100);

        CHECK(res.second == true);
        CHECK(res.first->first == 1); CHECK(res.first->second == 100);

        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.try_emplace(1, 200);

        CHECK(res.second == false);
        CHECK(res.first->first == 1); CHECK(res.first->second == 100);

        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test try_emplace_hint(const_iterator, K&&, Args&&...)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<const int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    {
        const auto res = tree.try_emplace_hint(tree.begin(), 1, 100);

        CHECK(res->first == 1); CHECK(res->second == 100);

        CHECK(tree.size() == 1);
    }

    {
        const auto res = tree.try_emplace_hint(tree.begin(), 1, 200);

        CHECK(res->first == 1); CHECK(res->second == 100);

        CHECK(tree.size() == 1);
    }
}
END_STATIC_ASSERT

// Test erase(const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    tree.emplace_equal(10);
    tree.emplace_equal(20);
    tree.emplace_equal(30);
    tree.emplace_equal(40);
    tree.emplace_equal(50);

    CHECK(tree.size() == 5);
    CHECK(*NTH(tree, 0) == 10);
    CHECK(*NTH(tree, 1) == 20);
    CHECK(*NTH(tree, 2) == 30);
    CHECK(*NTH(tree, 3) == 40);
    CHECK(*NTH(tree, 4) == 50);

    {
        const auto res = tree.erase(NTH(tree, 2));

        CHECK(*res == 40);
        CHECK(tree.size() == 4);
        CHECK(*NTH(tree, 0) == 10);
        CHECK(*NTH(tree, 1) == 20);
        CHECK(*NTH(tree, 2) == 40);
        CHECK(*NTH(tree, 3) == 50);
    }

    {
        const auto res = tree.erase(NTH(tree, 3));

        CHECK(res == tree.end());
        CHECK(tree.size() == 3);
        CHECK(*NTH(tree, 0) == 10);
        CHECK(*NTH(tree, 1) == 20);
        CHECK(*NTH(tree, 2) == 40);
    }
}
END_STATIC_ASSERT

// Test erase(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree;

    CHECK(tree.empty() == true);
    CHECK(tree.size() == 0);
    CHECK(tree.max_size() > 0);

    tree.emplace_equal(10);
    tree.emplace_equal(20);
    tree.emplace_equal(30);
    tree.emplace_equal(40);
    tree.emplace_equal(50);

    CHECK(tree.size() == 5);
    CHECK(*NTH(tree, 0) == 10);
    CHECK(*NTH(tree, 1) == 20);
    CHECK(*NTH(tree, 2) == 30);
    CHECK(*NTH(tree, 3) == 40);
    CHECK(*NTH(tree, 4) == 50);

    {
        const auto res = tree.erase(NTH(tree, 1), NTH(tree, 3));

        CHECK(*res == 40);
        CHECK(tree.size() == 3);
        CHECK(*NTH(tree, 0) == 10);
        CHECK(*NTH(tree, 1) == 40);
        CHECK(*NTH(tree, 2) == 50);
    }

    {
        const auto res = tree.erase(NTH(tree, 1), NTH(tree, 3));

        CHECK(res == tree.end());
        CHECK(tree.size() == 1);
        CHECK(*NTH(tree, 0) == 10);
    }
}
END_STATIC_ASSERT

// Test erase_key_equal(const K&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using rb_tree = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    rb_tree tree;

    tree.emplace_equal(10, 1);
    tree.emplace_equal(20, 2);
    tree.emplace_equal(20, 3);
    tree.emplace_equal(30, 4);
    tree.emplace_equal(30, 5);
    tree.emplace_equal(30, 6);

    CHECK(tree.size() == 6);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 1);
    CHECK(COUNT_KV(tree, 20, 3) == 1);
    CHECK(COUNT_KV(tree, 30, 4) == 1);
    CHECK(COUNT_KV(tree, 30, 5) == 1);
    CHECK(COUNT_KV(tree, 30, 6) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_equal(30) == 3);
    CHECK(tree.erase_key_equal(30) == 0);

    CHECK(tree.size() == 3);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 1);
    CHECK(COUNT_KV(tree, 20, 3) == 1);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_equal(20) == 2);
    CHECK(tree.erase_key_equal(20) == 0);

    CHECK(tree.size() == 1);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 0);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_equal(10) == 1);
    CHECK(tree.erase_key_equal(10) == 0);

    CHECK(tree.size() == 0);
    CHECK(COUNT_KV(tree, 10, 1) == 0);
    CHECK(COUNT_KV(tree, 20, 2) == 0);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);
}
END_STATIC_ASSERT

// Test erase_key_unique(const K&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = std::pair<int, int>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using rb_tree = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    rb_tree tree;

    tree.emplace_unique(10, 1);
    tree.emplace_unique(20, 2);
    tree.emplace_unique(20, 3);
    tree.emplace_unique(30, 4);
    tree.emplace_unique(30, 5);
    tree.emplace_unique(30, 6);

    CHECK(tree.size() == 3);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 1);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 1);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_unique(30) == 1);
    CHECK(tree.erase_key_unique(30) == 0);

    CHECK(tree.size() == 2);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 1);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_unique(20) == 1);
    CHECK(tree.erase_key_unique(20) == 0);

    CHECK(tree.size() == 1);
    CHECK(COUNT_KV(tree, 10, 1) == 1);
    CHECK(COUNT_KV(tree, 20, 2) == 0);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(tree.erase_key_unique(10) == 1);
    CHECK(tree.erase_key_unique(10) == 0);

    CHECK(tree.size() == 0);
    CHECK(COUNT_KV(tree, 10, 1) == 0);
    CHECK(COUNT_KV(tree, 20, 2) == 0);
    CHECK(COUNT_KV(tree, 20, 3) == 0);
    CHECK(COUNT_KV(tree, 30, 4) == 0);
    CHECK(COUNT_KV(tree, 30, 5) == 0);
    CHECK(COUNT_KV(tree, 30, 6) == 0);
}
END_STATIC_ASSERT

// Test swap(container&)
BEGIN_STATIC_ASSERT
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = std::allocator<value_type>;
    using tree_type = sfl::dtl::rb_tree<key_type, value_type, key_of_value, key_compare, allocator_type>;

    tree_type tree1, tree2;

    tree1.emplace_unique(10);
    tree1.emplace_unique(20);
    tree1.emplace_unique(30);

    tree2.emplace_unique(40);
    tree2.emplace_unique(50);
    tree2.emplace_unique(60);
    tree2.emplace_unique(70);

    CHECK(tree1.size() == 3);
    CHECK(*NTH(tree1, 0) == 10);
    CHECK(*NTH(tree1, 1) == 20);
    CHECK(*NTH(tree1, 2) == 30);

    CHECK(tree2.size() == 4);
    CHECK(*NTH(tree2, 0) == 40);
    CHECK(*NTH(tree2, 1) == 50);
    CHECK(*NTH(tree2, 2) == 60);
    CHECK(*NTH(tree2, 3) == 70);

    tree1.swap(tree2);

    CHECK(tree1.size() == 4);
    CHECK(*NTH(tree1, 0) == 40);
    CHECK(*NTH(tree1, 1) == 50);
    CHECK(*NTH(tree1, 2) == 60);
    CHECK(*NTH(tree1, 3) == 70);

    CHECK(tree2.size() == 3);
    CHECK(*NTH(tree2, 0) == 10);
    CHECK(*NTH(tree2, 1) == 20);
    CHECK(*NTH(tree2, 2) == 30);
}
END_STATIC_ASSERT

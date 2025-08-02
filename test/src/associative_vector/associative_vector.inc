#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;
using sfl::test::xobj;

PRINT("Test PRIVATE calculate_position_for_insert_equal(const K&) [empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    auto res = vec.calculate_position_for_insert_equal(42);

    CHECK(res.pos == vec.end());
}

PRINT("Test PRIVATE calculate_position_for_insert_unique(const K&) [empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    auto res = vec.calculate_position_for_insert_unique(42);

    CHECK(res.pos == vec.end());
    CHECK(res.status == true);
}

PRINT("Test PRIVATE calculate_position_for_insert_hint_equal(const_iterator, const K&) [empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    auto res = vec.calculate_position_for_insert_hint_equal(vec.end(), 42);

    CHECK(res.pos == vec.end());
}

PRINT("Test PRIVATE calculate_position_for_insert_hint_unique(const_iterator, const K&) [empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    auto res = vec.calculate_position_for_insert_hint_unique(vec.end(), 42);

    CHECK(res.pos == vec.end());
    CHECK(res.status == true);
}

PRINT("Test PRIVATE calculate_position_for_insert_equal(const K&) [non-empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.ref_to_vector().emplace_back(10);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(30);

    {
        auto res = vec.calculate_position_for_insert_equal(5);
        CHECK(res.pos == NTH(vec, 0));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(10);
        CHECK(res.pos == NTH(vec, 0));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(15);
        CHECK(res.pos == NTH(vec, 1));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(20);
        CHECK(res.pos == NTH(vec, 1));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(25);
        CHECK(res.pos == NTH(vec, 2));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(30);
        CHECK(res.pos == NTH(vec, 2));
    }

    {
        auto res = vec.calculate_position_for_insert_equal(35);
        CHECK(res.pos == NTH(vec, 3));
    }
}

PRINT("Test PRIVATE calculate_position_for_insert_unique(const K&) [non-empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.ref_to_vector().emplace_back(10);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(30);

    {
        auto res = vec.calculate_position_for_insert_unique(5);
        CHECK(res.pos == NTH(vec, 0));
        CHECK(res.status == true);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(10);
        CHECK(res.pos == NTH(vec, 0));
        CHECK(res.status == false);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(15);
        CHECK(res.pos == NTH(vec, 1));
        CHECK(res.status == true);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(20);
        CHECK(res.pos == NTH(vec, 1));
        CHECK(res.status == false);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(25);
        CHECK(res.pos == NTH(vec, 2));
        CHECK(res.status == true);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(30);
        CHECK(res.pos == NTH(vec, 2));
        CHECK(res.status == false);
    }

    {
        auto res = vec.calculate_position_for_insert_unique(35);
        CHECK(res.pos == NTH(vec, 3));
        CHECK(res.status == true);
    }
}

PRINT("Test PRIVATE calculate_position_for_insert_hint_equal(const K&) [non-empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.ref_to_vector().emplace_back(10);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(30);

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 5);
        CHECK(res.pos == NTH(vec, 0));
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 10);
        if (i == 0 || i == 1)
        {
            CHECK(res.pos == NTH(vec, i));
        }
        else
        {
            CHECK(res.pos == NTH(vec, 0));
        }
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 15);
        CHECK(res.pos == NTH(vec, 1));
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 20);
        if (i == 1 || i == 2 || i == 3 || i == 4)
        {
            CHECK(res.pos == NTH(vec, i));
        }
        else
        {
            CHECK(res.pos == NTH(vec, 1));
        }
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 25);
        CHECK(res.pos == NTH(vec, 4));
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 30);
        if (i == 4 || i == 5)
        {
            CHECK(res.pos == NTH(vec, i));
        }
        else
        {
            CHECK(res.pos == NTH(vec, 4));
        }
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_equal(hint, 35);
        CHECK(res.pos == NTH(vec, 5));
    }
}

PRINT("Test PRIVATE calculate_position_for_insert_hint_unique(const K&) [non-empty vector]");
{
    using key_type = int;
    using value_type = int;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<int>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.ref_to_vector().emplace_back(10);
    vec.ref_to_vector().emplace_back(20);
    vec.ref_to_vector().emplace_back(30);

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 5);
        CHECK(res.pos == NTH(vec, 0));
        CHECK(res.status == true);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 10);
        CHECK(res.pos == NTH(vec, 0));
        CHECK(res.status == false);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 15);
        CHECK(res.pos == NTH(vec, 1));
        CHECK(res.status == true);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 20);
        CHECK(res.pos == NTH(vec, 1));
        CHECK(res.status == false);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 25);
        CHECK(res.pos == NTH(vec, 2));
        CHECK(res.status == true);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 30);
        CHECK(res.pos == NTH(vec, 2));
        CHECK(res.status == false);
    }

    for (int i = 0; i <= int(vec.size()); ++i)
    {
        auto hint = NTH(vec, i);
        auto res = vec.calculate_position_for_insert_hint_unique(hint, 35);
        CHECK(res.pos == NTH(vec, 3));
        CHECK(res.status == true);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test container()");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.available() == vec.capacity() - vec.size());
}

PRINT("Test container(const KeyCompare&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    typename associative_vector::key_compare less;

    associative_vector vec(less);

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.available() == vec.capacity() - vec.size());
}

PRINT("Test container(const Alloc&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    typename associative_vector::allocator_type alloc;

    associative_vector vec(alloc);

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.available() == vec.capacity() - vec.size());
}

PRINT("Test container(const KeyCompare&, const Alloc&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    typename associative_vector::key_compare less;

    typename associative_vector::allocator_type alloc;

    associative_vector vec(less, alloc);

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.available() == vec.capacity() - vec.size());
}

PRINT("Test container(const container&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Empty containers
    {
        associative_vector vec1;

        CHECK(vec1.empty() == true);
        CHECK(vec1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        associative_vector vec2(vec1);

        CHECK(vec2.empty() == true);
        CHECK(vec2.size() == 0);
    }

    // Non-empty containers
    {
        associative_vector vec1;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        ///////////////////////////////////////////////////////////////////////

        associative_vector vec2(vec1);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.empty() == false);
        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
}

PRINT("Test container(const container&, const Alloc&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Empty containers
    {
        associative_vector vec1;

        CHECK(vec1.empty() == true);
        CHECK(vec1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        typename associative_vector::allocator_type alloc;

        associative_vector vec2(vec1, alloc);

        CHECK(vec2.empty() == true);
        CHECK(vec2.size() == 0);
    }

    // Non-empty containers
    {
        associative_vector vec1;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        ///////////////////////////////////////////////////////////////////////

        typename associative_vector::allocator_type alloc;

        associative_vector vec2(vec1, alloc);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.empty() == false);
        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
}

PRINT("Test container(container&&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Empty containers
    {
        associative_vector vec1;

        CHECK(vec1.empty() == true);
        CHECK(vec1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        associative_vector vec2(std::move(vec1));

        CHECK(vec2.empty() == true);
        CHECK(vec2.size() == 0);
    }

    // Non-empty containers
    {
        associative_vector vec1;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        ///////////////////////////////////////////////////////////////////////

        associative_vector vec2(std::move(vec1));

        if (vec1.size() == 6)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.empty() == false);
        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
}

PRINT("Test container(container&&, const Alloc&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Empty containers
    {
        associative_vector vec1;

        CHECK(vec1.empty() == true);
        CHECK(vec1.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        typename associative_vector::allocator_type alloc;

        associative_vector vec2(std::move(vec1), alloc);

        CHECK(vec2.empty() == true);
        CHECK(vec2.size() == 0);
    }

    // Non-empty containers
    {
        associative_vector vec1;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.empty() == false);
        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        ///////////////////////////////////////////////////////////////////////

        typename associative_vector::allocator_type alloc;

        associative_vector vec2(std::move(vec1), alloc);

        if (vec1.size() == 6)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.empty() == false);
        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test assign_copy(const container&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    #define CONDITION vec1.size() == 0 && vec2.size() == 0
    {
        associative_vector vec1, vec2;

        CHECK(vec1.size() == 0);
        CHECK(vec2.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 0);
        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() == 0 && vec2.size() != 0
    {
        associative_vector vec1, vec2;

        vec2.emplace_equal(10);
        vec2.emplace_equal(20);
        vec2.emplace_equal(20);
        vec2.emplace_equal(30);
        vec2.emplace_equal(30);
        vec2.emplace_equal(30);

        CHECK(vec1.size() == 0);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 0);

        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() != 0 && vec2.size() == 0
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 0);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() == vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        vec2.emplace_equal(40);
        vec2.emplace_equal(50);
        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 40) == 1);
        CHECK(COUNT(vec2, 50) == 2);
        CHECK(COUNT(vec2, 60) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() < vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        vec2.emplace_equal(40);
        vec2.emplace_equal(50);
        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(70);
        vec2.emplace_equal(80);
        vec2.emplace_equal(90);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 9);
        CHECK(COUNT(vec2, 40) == 1);
        CHECK(COUNT(vec2, 50) == 2);
        CHECK(COUNT(vec2, 60) == 3);
        CHECK(COUNT(vec2, 70) == 1);
        CHECK(COUNT(vec2, 80) == 1);
        CHECK(COUNT(vec2, 90) == 1);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() > vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);

        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(70);
        vec2.emplace_equal(70);
        vec2.emplace_equal(70);

        CHECK(vec1.size() == 10);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);
        CHECK(COUNT(vec1, 40) == 4);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 50) == 1);
        CHECK(COUNT(vec2, 60) == 2);
        CHECK(COUNT(vec2, 70) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_copy(vec1);

        CHECK(vec1.size() == 10);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);
        CHECK(COUNT(vec1, 40) == 4);

        for (auto it1 = vec1.begin(), it2 = std::next(it1); it2 != vec1.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

        CHECK(vec2.size() == 10);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);
        CHECK(COUNT(vec2, 40) == 4);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION
}

PRINT("Test assign_move(const container&)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    #define CONDITION vec1.size() == 0 && vec2.size() == 0
    {
        associative_vector vec1, vec2;

        CHECK(vec1.size() == 0);
        CHECK(vec2.size() == 0);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        CHECK(vec1.size() == 0);
        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() == 0 && vec2.size() != 0
    {
        associative_vector vec1, vec2;

        vec2.emplace_equal(10);
        vec2.emplace_equal(20);
        vec2.emplace_equal(20);
        vec2.emplace_equal(30);
        vec2.emplace_equal(30);
        vec2.emplace_equal(30);

        CHECK(vec1.size() == 0);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        CHECK(vec1.size() == 0);

        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() != 0 && vec2.size() == 0
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 0);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        if (vec1.size() == 6)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() == vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        vec2.emplace_equal(40);
        vec2.emplace_equal(50);
        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 40) == 1);
        CHECK(COUNT(vec2, 50) == 2);
        CHECK(COUNT(vec2, 60) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        if (vec1.size() == 6)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() < vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);

        vec2.emplace_equal(40);
        vec2.emplace_equal(50);
        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(70);
        vec2.emplace_equal(80);
        vec2.emplace_equal(90);

        CHECK(vec1.size() == 6);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);

        CHECK(vec2.size() == 9);
        CHECK(COUNT(vec2, 40) == 1);
        CHECK(COUNT(vec2, 50) == 2);
        CHECK(COUNT(vec2, 60) == 3);
        CHECK(COUNT(vec2, 70) == 1);
        CHECK(COUNT(vec2, 80) == 1);
        CHECK(COUNT(vec2, 90) == 1);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        if (vec1.size() == 6)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION

    #define CONDITION vec1.size() > vec2.size()
    {
        associative_vector vec1, vec2;

        vec1.emplace_equal(10);
        vec1.emplace_equal(20);
        vec1.emplace_equal(20);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(30);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);
        vec1.emplace_equal(40);

        vec2.emplace_equal(50);
        vec2.emplace_equal(60);
        vec2.emplace_equal(60);
        vec2.emplace_equal(70);
        vec2.emplace_equal(70);
        vec2.emplace_equal(70);

        CHECK(vec1.size() == 10);
        CHECK(COUNT(vec1, 10) == 1);
        CHECK(COUNT(vec1, 20) == 2);
        CHECK(COUNT(vec1, 30) == 3);
        CHECK(COUNT(vec1, 40) == 4);

        CHECK(vec2.size() == 6);
        CHECK(COUNT(vec2, 50) == 1);
        CHECK(COUNT(vec2, 60) == 2);
        CHECK(COUNT(vec2, 70) == 3);

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec2.assign_move(vec1);

        if (vec1.size() == 10)
        {
            // Elements are moved one-by-one
            CHECK(COUNT(vec1, -10) == 1);
            CHECK(COUNT(vec1, -20) == 2);
            CHECK(COUNT(vec1, -30) == 3);
            CHECK(COUNT(vec1, -40) == 4);
        }
        else
        {
            CHECK(vec1.size() == 0);
        }

        CHECK(vec2.size() == 10);
        CHECK(COUNT(vec2, 10) == 1);
        CHECK(COUNT(vec2, 20) == 2);
        CHECK(COUNT(vec2, 30) == 3);
        CHECK(COUNT(vec2, 40) == 4);

        for (auto it1 = vec2.begin(), it2 = std::next(it1); it2 != vec2.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }
    #undef CONDITION
}

PRINT("Test assign_range_equal(InputIt, InputIt)");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    #define CONDITION n == vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_equal(data.begin(), data.end());

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    #define CONDITION n < vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);
        vec.emplace_unique(40);
        vec.emplace_unique(50);
        vec.emplace_unique(60);

        CHECK(vec.size() == 6);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        std::vector<int> data({70, 80, 90});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_equal(data.begin(), data.end());

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 70) == 1);
        CHECK(COUNT(vec, 80) == 1);
        CHECK(COUNT(vec, 90) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60, 70, 80, 90});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_equal(data.begin(), data.end());

        CHECK(vec.size() == 6);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);
        CHECK(COUNT(vec, 70) == 1);
        CHECK(COUNT(vec, 80) == 1);
        CHECK(COUNT(vec, 90) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    // Input iterator range with duplicates
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        vec.assign_range_equal(data.begin(), data.end());

        CHECK(vec.size() == 5);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 3);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }
    }

    // Move iterator range with duplicates
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<xint> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        vec.assign_range_equal(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));

        CHECK(vec.size() == 5);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 3);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 <= *it2);
        }

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
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    #define CONDITION n == vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_unique(data.begin(), data.end());

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    #define CONDITION n < vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);
        vec.emplace_unique(40);
        vec.emplace_unique(50);
        vec.emplace_unique(60);

        CHECK(vec.size() == 6);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        std::vector<int> data({70, 80, 90});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_unique(data.begin(), data.end());

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 70) == 1);
        CHECK(COUNT(vec, 80) == 1);
        CHECK(COUNT(vec, 90) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size()
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60, 70, 80, 90});

        const associative_vector::size_type n = data.size();

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec.assign_range_unique(data.begin(), data.end());

        CHECK(vec.size() == 6);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);
        CHECK(COUNT(vec, 70) == 1);
        CHECK(COUNT(vec, 80) == 1);
        CHECK(COUNT(vec, 90) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }
    #undef CONDITION

    // Input iterator range with duplicates
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<int> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        vec.assign_range_unique(data.begin(), data.end());

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }
    }

    // Move iterator range with duplicates
    {
        associative_vector vec;

        vec.emplace_unique(10);
        vec.emplace_unique(20);
        vec.emplace_unique(30);

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 10) == 1);
        CHECK(COUNT(vec, 20) == 1);
        CHECK(COUNT(vec, 30) == 1);

        std::vector<xint> data({40, 50, 60, 50, 50});

        ///////////////////////////////////////////////////////////////////////

        vec.assign_range_unique(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));

        CHECK(vec.size() == 3);
        CHECK(COUNT(vec, 40) == 1);
        CHECK(COUNT(vec, 50) == 1);
        CHECK(COUNT(vec, 60) == 1);

        for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
        {
            CHECK(*it1 < *it2);
        }

        CHECK(data.size() == 5);
        CHECK(data[0] == -40);
        CHECK(data[1] == -50);
        CHECK(data[2] == -60);
        CHECK(data[3] == +50);
        CHECK(data[4] == +50);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test clear()");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.emplace_equal(10, 1010);
    vec.emplace_equal(20, 1020);
    vec.emplace_equal(30, 1030);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 3);

    vec.clear();

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
}

PRINT("Test emplace_equal(Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            const auto res = vec.emplace_equal(key, value);

            ++size;

            // Check result
            CHECK(res != vec.end());
            CHECK(res->first == key);
            CHECK(res->second == value);

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(vec, key, key + 1000) == 1);
        CHECK(COUNT_KV(vec, key, key + 2000) == 1);
        CHECK(COUNT_KV(vec, key, key + 3000) == 1);
    }
}

PRINT("Test emplace_unique(Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            const auto res = vec.emplace_unique(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != vec.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(vec, key, key + 1000) == 1);
        CHECK(COUNT_KV(vec, key, key + 2000) == 0);
        CHECK(COUNT_KV(vec, key, key + 3000) == 0);
    }
}

PRINT("Test emplace_hint_equal(const_iterator, Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = vec.end();

                    const auto res = vec.emplace_hint_equal(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.emplace_hint_equal(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size() + 1));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
                else
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test emplace_hint_unique(const_iterator, Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = vec.end();

                    const auto res = vec.emplace_hint_unique(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.emplace_hint_unique(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(vec.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(vec.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 0);
                }
                else
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test insert_equal(V&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            typename associative_vector::value_type key_value(key, value);

            const auto res = vec.insert_equal(std::move(key_value));

            ++size;

            // Check result
            CHECK(res != vec.end());
            CHECK(res->first == key);
            CHECK(res->second == value);

            // Check original key-value
            CHECK(key_value.first == -key);
            CHECK(key_value.second == -value);

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(vec, key, key + 1000) == 1);
        CHECK(COUNT_KV(vec, key, key + 2000) == 1);
        CHECK(COUNT_KV(vec, key, key + 3000) == 1);
    }
}

PRINT("Test insert_unique(V&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            typename associative_vector::value_type key_value(key, value);

            const auto res = vec.insert_unique(std::move(key_value));

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != vec.end());
            CHECK(res.first->first == elem);
            CHECK(res.first->second == elem + 1000);

            // Check original key-value
            CHECK(key_value.first == (iter == 0 ? -key : +key));
            CHECK(key_value.second == (iter == 0 ? -value : +value));

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first <= it2->first);
            }
        }
    }

    // Check count
    for (const auto& key : data)
    {
        CHECK(COUNT_KV(vec, key, key + 1000) == 1);
        CHECK(COUNT_KV(vec, key, key + 2000) == 0);
        CHECK(COUNT_KV(vec, key, key + 3000) == 0);
    }
}

PRINT("Test insert_hint_equal(const_iterator, V&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename associative_vector::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = vec.end();

                    const auto res = vec.insert_hint_equal(hint, std::move(key_value));

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == -elem1);
                    CHECK(key_value.second == -(elem1 + 1000));
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename associative_vector::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.insert_hint_equal(hint, std::move(key_value));

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key-value
                    CHECK(key_value.first == -elem2);
                    CHECK(key_value.second == -(elem2 + 2000));
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size() + 1));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
                else
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test insert_hint_unique(const_iterator, V&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    typename associative_vector::value_type key_value(elem1, elem1 + 1000);

                    const auto hint = vec.end();

                    const auto res = vec.insert_hint_unique(hint, std::move(key_value));

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key-value
                    CHECK(key_value.first == -elem1);
                    CHECK(key_value.second == -(elem1 + 1000));
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    typename associative_vector::value_type key_value(elem2, elem2 + 2000);

                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.insert_hint_unique(hint, std::move(key_value));

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));

                    // Check original key-value
                    CHECK(key_value.first == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2));
                    CHECK(key_value.second == (CONTAINS(data1, elem2) ? +1 : -1) * (elem2 + 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(vec.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(vec.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first <= it2->first);
                }

                // Check count
                for (const auto& elem1 : data1)
                {
                    CHECK(COUNT_KV(vec, elem1, elem1 + 1000) == 1);
                }

                if (CONTAINS(data1, elem2))
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 1);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 0);
                }
                else
                {
                    CHECK(COUNT_KV(vec, elem2, elem2 + 1000) == 0);
                    CHECK(COUNT_KV(vec, elem2, elem2 + 2000) == 1);
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test insert_or_assign(K&&, M&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            const auto res = vec.insert_or_assign(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != vec.end());
            CHECK(res.first->first.value() == key);
            CHECK(res.first->second == value);

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first.value() <= it2->first.value());
            }
        }
    }
}

PRINT("Test insert_or_assign_hint(const_iterator, K&&, M&&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const int key = elem1;
                    const int value = elem1 + 1000;

                    const auto hint = vec.end();

                    const auto res = vec.insert_or_assign_hint(hint, key, value);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first.value() == elem1);
                    CHECK(res->second == elem1 + 1000);

                    // Check original key
                    CHECK(key == elem1);
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const int key = elem2;
                    const int value = elem2 + 2000;

                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.insert_or_assign_hint(hint, key, value);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first.value() == elem2);
                    CHECK(res->second == elem2 + 2000);

                    // Check original key
                    CHECK(key == elem2);
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(vec.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(vec.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }
            }
        }

        std::shuffle(data1.begin(), data1.end(), gen);
        std::shuffle(data2.begin(), data2.end(), gen);
    }
}

PRINT("Test try_emplace(K&&, Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // For shuffling
    std::random_device rd;
    std::mt19937 gen(rd());

    // Elements to be inserted into container
    std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    associative_vector vec;

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

            const auto res = vec.try_emplace(key, value);

            if (iter == 0)
            {
                ++size;
            }

            // Check result
            CHECK(res.second == (iter == 0));
            CHECK(res.first != vec.end());
            CHECK(res.first->first.value() == elem);
            CHECK(res.first->second == elem + 1000);

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check ordering
            for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
            {
                CHECK(it1->first.value() <= it2->first.value());
            }
        }
    }
}

PRINT("Test try_emplace_hint(const_iterator, K&&, Args&&...)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

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
                associative_vector vec;

                // Insert initial elements
                for (const auto& elem1 : data1)
                {
                    const auto hint = vec.end();

                    const auto res = vec.try_emplace_hint(hint, elem1, elem1 + 1000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first.value() == elem1);
                    CHECK(res->second == elem1 + 1000);
                }

                // Check size
                CHECK(int(vec.size()) == int(data1.size()));

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
                {
                    CHECK(it1->first.value() <= it2->first.value());
                }

                ///////////////////////////////////////////////////////////////

                // Insert additional element
                {
                    const auto hint = NTH(vec, insert_pos);

                    const auto res = vec.try_emplace_hint(hint, elem2, elem2 + 2000);

                    // Check result
                    CHECK(res != vec.end());
                    CHECK(res->first.value() == elem2);
                    CHECK(res->second == elem2 + (CONTAINS(data1, elem2) ? 1000 : 2000));
                }

                // Check size
                if (CONTAINS(data1, elem2))
                {
                    CHECK(int(vec.size()) == int(data1.size()));
                }
                else
                {
                    CHECK(int(vec.size()) == int(data1.size() + 1));
                }

                // Check ordering
                for (auto it1 = vec.begin(), it2 = std::next(it1); it2 != vec.end(); ++it1, ++it2)
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
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos = 0; erase_pos < size; ++erase_pos)
        {
            associative_vector vec;

            // Insert elements
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                vec.emplace_equal(elem, elem + 1000);
            }

            // Check size
            CHECK(int(vec.size()) == int(size));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                const auto& elem = data[i];
                CHECK(COUNT_KV(vec, elem, elem + 1000) == 1);
            }

            ///////////////////////////////////////////////////////////////////

            // Erase
            const auto it = NTH(vec, erase_pos);
            vec.erase(it);

            // Check size
            CHECK(int(vec.size()) == int(size - 1));

            // Check count
            for (int i = 0; i < size; ++i)
            {
                if (i == erase_pos)
                {
                    continue;
                }
                const auto& elem = data[i];
                CHECK(COUNT_KV(vec, elem, elem + 1000) == 1);
            }
        }
    }
}

PRINT("Test erase(const_iterator, const_iterator)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Elements to be inserted into container
    const std::vector<int> data({10, 20, 30, 40, 50, 60, 70, 80, 90});

    for (int size = 0; size < int(data.size()); ++size)
    {
        for (int erase_pos1 = 0; erase_pos1 < size; ++erase_pos1)
        {
            for (int erase_pos2 = erase_pos1; erase_pos2 < size; ++erase_pos2)
            {
                associative_vector vec;

                // Insert elements
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    vec.emplace_equal(elem, elem + 1000);
                }

                // Check size
                CHECK(int(vec.size()) == int(size));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(vec, elem, elem + 1000) == 1);
                }

                ///////////////////////////////////////////////////////////////////

                // Range to erase
                const auto it1 = NTH(vec, erase_pos1);
                const auto it2 = NTH(vec, erase_pos2);

                // Number of erased elements
                const int size_delta = int(std::distance(it1, it2));

                // Erase
                vec.erase(it1, it2);

                // Check size
                CHECK(int(vec.size()) == int(size - size_delta));

                // Check count
                for (int i = 0; i < size; ++i)
                {
                    if (i >= erase_pos1 && i < erase_pos2)
                    {
                        continue;
                    }
                    const auto& elem = data[i];
                    CHECK(COUNT_KV(vec, elem, elem + 1000) == 1);
                }
            }
        }
    }
}

PRINT("Test erase_key_equal(const K&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.emplace_equal(10, 1);
    vec.emplace_equal(20, 2);
    vec.emplace_equal(20, 3);
    vec.emplace_equal(30, 4);
    vec.emplace_equal(30, 5);
    vec.emplace_equal(30, 6);

    CHECK(vec.size() == 6);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 1);
    CHECK(COUNT_KV(vec, 20, 3) == 1);
    CHECK(COUNT_KV(vec, 30, 4) == 1);
    CHECK(COUNT_KV(vec, 30, 5) == 1);
    CHECK(COUNT_KV(vec, 30, 6) == 1);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_equal(30) == 3);
    CHECK(vec.erase_key_equal(30) == 0);

    CHECK(vec.size() == 3);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 1);
    CHECK(COUNT_KV(vec, 20, 3) == 1);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_equal(20) == 2);
    CHECK(vec.erase_key_equal(20) == 0);

    CHECK(vec.size() == 1);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 0);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_equal(10) == 1);
    CHECK(vec.erase_key_equal(10) == 0);

    CHECK(vec.size() == 0);
    CHECK(COUNT_KV(vec, 10, 1) == 0);
    CHECK(COUNT_KV(vec, 20, 2) == 0);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);
}

PRINT("Test erase_key_unique(const K&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec;

    vec.emplace_unique(10, 1);
    vec.emplace_unique(20, 2);
    vec.emplace_unique(20, 3);
    vec.emplace_unique(30, 4);
    vec.emplace_unique(30, 5);
    vec.emplace_unique(30, 6);

    CHECK(vec.size() == 3);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 1);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 1);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_unique(30) == 1);
    CHECK(vec.erase_key_unique(30) == 0);

    CHECK(vec.size() == 2);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 1);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_unique(20) == 1);
    CHECK(vec.erase_key_unique(20) == 0);

    CHECK(vec.size() == 1);
    CHECK(COUNT_KV(vec, 10, 1) == 1);
    CHECK(COUNT_KV(vec, 20, 2) == 0);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(vec.erase_key_unique(10) == 1);
    CHECK(vec.erase_key_unique(10) == 0);

    CHECK(vec.size() == 0);
    CHECK(COUNT_KV(vec, 10, 1) == 0);
    CHECK(COUNT_KV(vec, 20, 2) == 0);
    CHECK(COUNT_KV(vec, 20, 3) == 0);
    CHECK(COUNT_KV(vec, 30, 4) == 0);
    CHECK(COUNT_KV(vec, 30, 5) == 0);
    CHECK(COUNT_KV(vec, 30, 6) == 0);
}

PRINT("Test swap(container&)");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec1, vec2;

    vec1.emplace_equal(10, 1);
    vec1.emplace_equal(20, 1);
    vec1.emplace_equal(30, 1);

    vec2.emplace_equal(40, 2);
    vec2.emplace_equal(50, 2);
    vec2.emplace_equal(60, 2);
    vec2.emplace_equal(70, 2);

    CHECK(vec1.size() == 3);
    CHECK(COUNT_KV(vec1, 10, 1) == 1);
    CHECK(COUNT_KV(vec1, 20, 1) == 1);
    CHECK(COUNT_KV(vec1, 30, 1) == 1);

    CHECK(vec2.size() == 4);
    CHECK(COUNT_KV(vec2, 40, 2) == 1);
    CHECK(COUNT_KV(vec2, 50, 2) == 1);
    CHECK(COUNT_KV(vec2, 60, 2) == 1);
    CHECK(COUNT_KV(vec2, 70, 2) == 1);

    ///////////////////////////////////////////////////////////////////////

    vec1.swap(vec2);

    CHECK(vec1.size() == 4);
    CHECK(COUNT_KV(vec1, 40, 2) == 1);
    CHECK(COUNT_KV(vec1, 50, 2) == 1);
    CHECK(COUNT_KV(vec1, 60, 2) == 1);
    CHECK(COUNT_KV(vec1, 70, 2) == 1);

    CHECK(vec2.size() == 3);
    CHECK(COUNT_KV(vec2, 10, 1) == 1);
    CHECK(COUNT_KV(vec2, 20, 1) == 1);
    CHECK(COUNT_KV(vec2, 30, 1) == 1);

    ///////////////////////////////////////////////////////////////////////

    vec1.swap(vec2);

    CHECK(vec1.size() == 3);
    CHECK(COUNT_KV(vec1, 10, 1) == 1);
    CHECK(COUNT_KV(vec1, 20, 1) == 1);
    CHECK(COUNT_KV(vec1, 30, 1) == 1);

    CHECK(vec2.size() == 4);
    CHECK(COUNT_KV(vec2, 40, 2) == 1);
    CHECK(COUNT_KV(vec2, 50, 2) == 1);
    CHECK(COUNT_KV(vec2, 60, 2) == 1);
    CHECK(COUNT_KV(vec2, 70, 2) == 1);
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test lower_bound, upper_bound, equal_range, find, count_equal, count_unique, contains");
{
    using key_type = xint;
    using value_type = std::pair<xint, xint>;
    using key_of_value = sfl::dtl::first;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    // Equal keys
    {
        associative_vector vec;

        vec.emplace_equal(10, 1);
        vec.emplace_equal(20, 1);
        vec.emplace_equal(20, 2);
        vec.emplace_equal(30, 1);
        vec.emplace_equal(30, 2);
        vec.emplace_equal(30, 3);

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = vec.lower_bound(x);
                auto it2 = vec.upper_bound(x);

                CHECK(std::distance(it1, it2) == (x == 10 ? 1 : x == 20 ? 2 : 3));

                auto er = vec.equal_range(x);

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
                auto it = vec.find(x);
                CHECK(it != vec.end());
                CHECK(it->first == x);
            }

            // Check count
            CHECK(vec.count_equal(x) == (x == 10 ? 1 : x == 20 ? 2 : 3));

            // Check contains
            CHECK(vec.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = vec.lower_bound(x);
                auto it2 = vec.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = vec.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = vec.find(x);
                CHECK(it == vec.end());
            }

            // Check count
            CHECK(vec.count_equal(x) == 0);

            // Check contains
            CHECK(vec.contains(x) == false);
        }
    }

    // Unique keys
    {
        associative_vector vec;

        vec.emplace_unique(10, 1);
        vec.emplace_unique(20, 1);
        vec.emplace_unique(20, 2);
        vec.emplace_unique(30, 1);
        vec.emplace_unique(30, 2);
        vec.emplace_unique(30, 3);

        for (const auto x : {10, 20, 30})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = vec.lower_bound(x);
                auto it2 = vec.upper_bound(x);

                CHECK(std::distance(it1, it2) == 1);

                auto er = vec.equal_range(x);

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
                auto it = vec.find(x);
                CHECK(it != vec.end());
                CHECK(it->first == x);
            }

            // Check count
            CHECK(vec.count_unique(x) == 1);

            // Check contains
            CHECK(vec.contains(x) == true);
        }

        for (const auto x : {5, 15, 25, 35})
        {
            // Check lower_bound, upper_bound and equal_range
            {
                auto it1 = vec.lower_bound(x);
                auto it2 = vec.upper_bound(x);

                CHECK(std::distance(it1, it2) == 0);

                auto er = vec.equal_range(x);

                CHECK(std::distance(er.first, er.second) == 0);
            }

            // Check find
            {
                auto it = vec.find(x);
                CHECK(it == vec.end());
            }

            // Check count
            CHECK(vec.count_unique(x) == 0);

            // Check contains
            CHECK(vec.contains(x) == false);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test NON-MEMBER comparison operators");
{
    using key_type = xint;
    using value_type = xint;
    using key_of_value = sfl::dtl::identity;
    using key_compare = std::less<xint>;
    using allocator_type = TPARAM_ALLOCATOR<value_type>;
    using base_vector = sfl::vector<value_type, allocator_type>;
    using associative_vector = sfl::dtl::associative_vector<key_type, value_type, key_of_value, key_compare, base_vector>;

    associative_vector vec1, vec2;

    vec1.emplace_equal(10);
    vec1.emplace_equal(20);
    vec1.emplace_equal(30);

    vec2.emplace_equal(10);
    vec2.emplace_equal(20);
    vec2.emplace_equal(20);
    vec2.emplace_equal(30);
    vec2.emplace_equal(30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 == vec1) == true);
    CHECK((vec1 == vec2) == false);

    CHECK((vec2 == vec1) == false);
    CHECK((vec2 == vec2) == true);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 != vec1) == false);
    CHECK((vec1 != vec2) == true);

    CHECK((vec2 != vec1) == true);
    CHECK((vec2 != vec2) == false);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 < vec1) == false);
    CHECK((vec1 < vec2) == false);

    CHECK((vec2 < vec1) == true);
    CHECK((vec2 < vec2) == false);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 <= vec1) == true);
    CHECK((vec1 <= vec2) == false);

    CHECK((vec2 <= vec1) == true);
    CHECK((vec2 <= vec2) == true);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 > vec1) == false);
    CHECK((vec1 > vec2) == true);

    CHECK((vec2 > vec1) == false);
    CHECK((vec2 > vec2) == false);

    ///////////////////////////////////////////////////////////////////////////

    CHECK((vec1 >= vec1) == true);
    CHECK((vec1 >= vec2) == true);

    CHECK((vec2 >= vec1) == false);
    CHECK((vec2 >= vec2) == true);
}

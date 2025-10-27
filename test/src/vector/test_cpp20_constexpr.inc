#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

// Test container()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() == 0);
    CHECK(vec.available() == 0);

    CHECK(vec.begin() == vec.end());
    CHECK(vec.begin() == vec.cend());
    CHECK(vec.cbegin() == vec.cend());
    CHECK(vec.rbegin() == vec.rend());
    CHECK(vec.rbegin() == vec.crend());
    CHECK(vec.crbegin() == vec.crend());
}
END_STATIC_ASSERT

// Test container(const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    vector vec(alloc);

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() == 0);
    CHECK(vec.available() == 0);

    CHECK(vec.begin() == vec.end());
    CHECK(vec.begin() == vec.cend());
    CHECK(vec.cbegin() == vec.cend());
    CHECK(vec.rbegin() == vec.rend());
    CHECK(vec.rbegin() == vec.crend());
    CHECK(vec.crbegin() == vec.crend());
}
END_STATIC_ASSERT

// Test container(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec(4);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 0);
    CHECK(*vec.nth(1) == 0);
    CHECK(*vec.nth(2) == 0);
    CHECK(*vec.nth(3) == 0);
}
END_STATIC_ASSERT

// Test container(size_type, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    vector vec(4, alloc);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 0);
    CHECK(*vec.nth(1) == 0);
    CHECK(*vec.nth(2) == 0);
    CHECK(*vec.nth(3) == 0);
}
END_STATIC_ASSERT

// Test container(size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec(4, 12345);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 12345);
    CHECK(*vec.nth(1) == 12345);
    CHECK(*vec.nth(2) == 12345);
    CHECK(*vec.nth(3) == 12345);
}
END_STATIC_ASSERT

// Test container(size_type, const T&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    vector vec(4, 12345, alloc);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 12345);
    CHECK(*vec.nth(1) == 12345);
    CHECK(*vec.nth(2) == 12345);
    CHECK(*vec.nth(3) == 12345);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    std::vector<int> data({10, 20, 30, 40});

    vector vec(data.begin(), data.end());

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test container(InputIt, InputIt, const Allocator&))
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    std::vector<int> data({10, 20, 30, 40});

    vector vec(data.begin(), data.end(), alloc);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test container(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    std::initializer_list<int> ilist{10, 20, 30, 40};

    vector vec(ilist);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test container(std::initializer_list, const Allocator&))
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    std::initializer_list<int> ilist{10, 20, 30, 40};

    vector vec(ilist, alloc);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test container(const container&)"
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vector vec2(vec1);

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
}
END_STATIC_ASSERT

// Test container(const container&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    typename vector::allocator_type alloc;

    vector vec2(vec1, alloc);

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
}
END_STATIC_ASSERT

// Test container(container&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vector vec2(std::move(vec1));

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    // Storage was moved
    CHECK(vec1.size() == 0);
}
END_STATIC_ASSERT

// Test container(container&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    typename vector::allocator_type alloc;

    vector vec2(std::move(vec1), alloc);

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    // Storage was moved
    CHECK(vec1.size() == 0);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    std::vector<int> data({10, 20, 30, 40});

    vector vec(sfl::from_range_t(), std::views::all(data));

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test container(sfl::from_range_t, Range&&, const Allocator&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    std::vector<int> data({10, 20, 30, 40});

    typename vector::allocator_type alloc;

    vector vec(sfl::from_range_t(), std::views::all(data), alloc);

    CHECK(vec.empty() == false);
    CHECK(vec.size() == 4);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() >= 4);

    CHECK(vec.begin() != vec.end());
    CHECK(vec.begin() != vec.cend());
    CHECK(vec.cbegin() != vec.cend());
    CHECK(vec.rbegin() != vec.rend());
    CHECK(vec.rbegin() != vec.crend());
    CHECK(vec.crbegin() != vec.crend());

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test assign(size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION n < vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        int value(987654);

        vec.assign(n, value);

        CHECK(vec.size() == 4);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        int value(987654);

        vec.assign(n, value);

        CHECK(vec.size() == 5);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        int value(987654);

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        int value(987654);

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() + 1;

        CHECK(CONDITION);

        int value(987654);

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test assign(InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION n < vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < int(n); ++i)
        {
            data.emplace_back(i);
        }

        vec.assign(data.begin(), data.end());

        CHECK(vec.size() == n);
        for (int i = 0; i < int(n); ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < int(n); ++i)
        {
            data.emplace_back(i);
        }

        vec.assign(data.begin(), data.end());

        CHECK(vec.size() == n);
        for (int i = 0; i < int(n); ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < int(n); ++i)
        {
            data.emplace_back(i);
        }

        vec.assign(data.begin(), data.end());

        CHECK(vec.size() == n);
        for (int i = 0; i < int(n); ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < int(n); ++i)
        {
            data.emplace_back(i);
        }

        vec.assign(data.begin(), data.end());

        CHECK(vec.size() == n);
        for (int i = 0; i < int(n); ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() + 1;

        CHECK(CONDITION);

        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < int(n); ++i)
        {
            data.emplace_back(i);
        }

        vec.assign(data.begin(), data.end());

        CHECK(vec.size() == n);
        for (int i = 0; i < int(n); ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test assign(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);
    vec.emplace(vec.end(), 40);
    vec.emplace(vec.end(), 50);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
    CHECK(*vec.nth(4) == 50);

    std::initializer_list<int> ilist{1, 2, 3, 4, 5};

    vec.assign(ilist);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 1);
    CHECK(*vec.nth(1) == 2);
    CHECK(*vec.nth(2) == 3);
    CHECK(*vec.nth(3) == 4);
    CHECK(*vec.nth(4) == 5);
}
END_STATIC_ASSERT

// Test assign_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    std::vector<int> data({10, 20, 30, 40});

    vector vec;

    vec.assign_range(std::views::all(data));

    CHECK(vec.size() == 4);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test operator=(const container&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace_back(40);
        vec2.emplace_back(50);
        vec2.emplace_back(60);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
    }
    #undef CONDITION

    #define CONDITION vec1.size() < vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace_back(40);
        vec2.emplace_back(50);
        vec2.emplace_back(60);
        vec2.emplace_back(70);
        vec2.emplace_back(80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
    }
    #undef CONDITION

    #define CONDITION vec1.size() > vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);
        vec1.emplace_back(40);
        vec1.emplace_back(50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.emplace_back(60);
        vec2.emplace_back(70);
        vec2.emplace_back(80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test operator=(container&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace_back(40);
        vec2.emplace_back(50);
        vec2.emplace_back(60);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);

        // Storage was moved
        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() < vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace_back(40);
        vec2.emplace_back(50);
        vec2.emplace_back(60);
        vec2.emplace_back(70);
        vec2.emplace_back(80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);

        // Storage was moved
        CHECK(vec2.size() == 0);
    }
    #undef CONDITION

    #define CONDITION vec1.size() > vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);
        vec1.emplace_back(40);
        vec1.emplace_back(50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.emplace_back(60);
        vec2.emplace_back(70);
        vec2.emplace_back(80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        // Storage was moved
        CHECK(vec2.size() == 0);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test operator=(std::initializer_list)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION vec.size() == ilist.size()
    {
        vector vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        std::initializer_list<int> ilist{40, 50, 60};

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
    }
    #undef CONDITION

    #define CONDITION vec.size() < ilist.size()
    {
        vector vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        std::initializer_list<int> ilist{40, 50, 60, 70, 80};

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
    }
    #undef CONDITION

    #define CONDITION vec.size() > ilist.size()
    {
        vector vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<int> ilist{60, 70, 80};

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 60);
        CHECK(*vec.nth(1) == 70);
        CHECK(*vec.nth(2) == 80);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test get_allocator()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    auto alloc = vec.get_allocator();

    (void)alloc;
}
END_STATIC_ASSERT

// Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////

    auto it = vec.begin();
    CHECK(*it == 10); ++it;
    CHECK(*it == 20); ++it;
    CHECK(*it == 30); ++it;
    CHECK(it == vec.end());

    ///////////////////////////////////////////////////////////////////////

    auto cit = vec.cbegin();
    CHECK(*cit == 10); ++cit;
    CHECK(*cit == 20); ++cit;
    CHECK(*cit == 30); ++cit;
    CHECK(cit == vec.cend());

    ///////////////////////////////////////////////////////////////////////

    auto rit = vec.rbegin();
    CHECK(*rit == 30); ++rit;
    CHECK(*rit == 20); ++rit;
    CHECK(*rit == 10); ++rit;
    CHECK(rit == vec.rend());

    ///////////////////////////////////////////////////////////////////////

    auto crit = vec.crbegin();
    CHECK(*crit == 30); ++crit;
    CHECK(*crit == 20); ++crit;
    CHECK(*crit == 10); ++crit;
    CHECK(crit == vec.crend());

    ///////////////////////////////////////////////////////////////////////

    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(vec.nth(3) == vec.end());

    ///////////////////////////////////////////////////////////////////////

    CHECK(std::next(vec.begin(), 0) == vec.nth(0));
    CHECK(std::next(vec.begin(), 1) == vec.nth(1));
    CHECK(std::next(vec.begin(), 2) == vec.nth(2));
    CHECK(std::next(vec.begin(), 3) == vec.nth(3));

    ///////////////////////////////////////////////////////////////////////

    CHECK(std::next(vec.cbegin(), 0) == vec.nth(0));
    CHECK(std::next(vec.cbegin(), 1) == vec.nth(1));
    CHECK(std::next(vec.cbegin(), 2) == vec.nth(2));
    CHECK(std::next(vec.cbegin(), 3) == vec.nth(3));

    ///////////////////////////////////////////////////////////////////////

    CHECK(vec.nth(0) < vec.nth(1));
    CHECK(vec.nth(0) < vec.nth(2));
    CHECK(vec.nth(0) < vec.nth(3));

    CHECK(vec.nth(1) < vec.nth(2));
    CHECK(vec.nth(1) < vec.nth(3));

    CHECK(vec.nth(2) < vec.nth(3));

    ///////////////////////////////////////////////////////////////////////

    CHECK(vec.index_of(vec.nth(0)) == 0);
    CHECK(vec.index_of(vec.nth(1)) == 1);
    CHECK(vec.index_of(vec.nth(2)) == 2);
    CHECK(vec.index_of(vec.nth(3)) == 3);
}
END_STATIC_ASSERT

// Test reserve(size_type) and shrink_to_fit()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);
    vec.emplace(vec.end(), 40);
    vec.pop_back();

    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 4);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.shrink_to_fit();

    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.reserve(999);

    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 999);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.shrink_to_fit();

    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
}
END_STATIC_ASSERT

// Test at(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.at(0) == 10);
    CHECK(vec.at(1) == 20);
    CHECK(vec.at(2) == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec.at(0) = 40;
    vec.at(1) = 50;
    vec.at(2) = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);
}
END_STATIC_ASSERT

// Test operator[](size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec[0] == 10);
    CHECK(vec[1] == 20);
    CHECK(vec[2] == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec[0] = 40;
    vec[1] = 50;
    vec[2] = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);
}
END_STATIC_ASSERT

// Test front() and back()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.front() == 10);
    CHECK(vec.back()  == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec.front() = 40;
    vec.back()  = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 60);
}
END_STATIC_ASSERT

// Test data()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    auto data = vec.data();
    CHECK(*data == 10); ++data;
    CHECK(*data == 20); ++data;
    CHECK(*data == 30); ++data;
}
END_STATIC_ASSERT

// Test clear()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    CHECK(vec.size() == 0);

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);
    vec.emplace(vec.end(), 40);
    vec.emplace(vec.end(), 50);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
    CHECK(*vec.nth(4) == 50);

    vec.clear();

    CHECK(vec.size() == 0);

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec.clear();

    CHECK(vec.size() == 0);
}
END_STATIC_ASSERT

// Test emplace(const_iterator, Args&&...)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    // Emplace at end
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vec.emplace(vec.end(), i);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }

    // Emplace at begin
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vec.emplace(vec.begin(), n - i - 1);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    const int value = 12345;

    vec.insert(vec.end(), value);

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test insert(const_iterator, T&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    int value = 12345;

    vec.insert(vec.end(), std::move(value));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test insert(const_iterator, size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    // Insert at end
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vec.insert(vec.end(), 1, i);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }

    // Insert at begin
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vec.insert(vec.begin(), 1, n - i - 1);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, InputIt, InputIt)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    // Insert at end
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vector data;

            data.emplace_back(i);

            vec.insert(vec.end(), data.begin(), data.end());
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }

    // Insert at begin
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vector data;

            data.emplace_back(n - i - 1);

            vec.insert(vec.begin(), data.begin(), data.end());
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, std::initializer_list<T>)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    // Insert at end
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            std::initializer_list<int> ilist{i};

            vec.insert(vec.end(), ilist);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }

    // Insert at begin
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            std::initializer_list<int> ilist{n - i - 1};

            vec.insert(vec.begin(), ilist);
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
}
END_STATIC_ASSERT

// Test insert_range(const_iterator, Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    // Insert at end
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vector data;

            data.emplace_back(i);

            vec.insert_range(vec.end(), std::views::all(data));
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }

    // Insert at begin
    {
        vector vec;

        constexpr int n = 20;

        for (int i = 0; i < n; ++i)
        {
            vector data;

            data.emplace_back(n - i - 1);

            vec.insert_range(vec.begin(), std::views::all(data));
        }

        CHECK(int(vec.size()) == n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(*vec.nth(i) == i);
        }
    }
}
END_STATIC_ASSERT

// Test emplace_back(Args&&...)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    constexpr int n = 20;

    for (int i = 0; i < n; ++i)
    {
        vec.emplace_back(i);
    }

    CHECK(int(vec.size()) == n);

    for (int i = 0; i < n; ++i)
    {
        CHECK(*vec.nth(i) == i);
    }
}
END_STATIC_ASSERT

// Test push_back(const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    const int value = 12345;

    vec.push_back(value);

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test push_back(T&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    int value = 12345;

    vec.push_back(std::move(value));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test append_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vector data({10, 20, 30, 40});

    vec.append_range(std::views::all(data));

    CHECK(vec.size() == 4);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_STATIC_ASSERT

// Test pop_back()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 0);
}
END_STATIC_ASSERT

// Test erase(const_iterator)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.erase(vec.nth(1));

    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_STATIC_ASSERT

// Test erase(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.erase(vec.nth(1), vec.nth(2));

    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_STATIC_ASSERT

// Test resize(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION n < vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        for (size_type i = 7; i < n; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() + 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test resize(size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    #define CONDITION n < vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        int value(987654);

        vec.resize(n, value);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        int value(987654);

        vec.resize(n, value);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        int value(987654);

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        for (size_type i = 7; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        int value(987654);

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.capacity()
    {
        vector vec;

        using size_type = typename vector::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() + 1;

        CHECK(CONDITION);

        int value(987654);

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test swap(container&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1, vec2;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    vec2.emplace_back(40);
    vec2.emplace_back(50);
    vec2.emplace_back(60);
    vec2.emplace_back(70);

    CHECK(vec1.size() == 3);
    CHECK(vec1.capacity() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    CHECK(vec2.size() == 4);
    CHECK(vec2.capacity() == 4);
    CHECK(*vec2.nth(0) == 40);
    CHECK(*vec2.nth(1) == 50);
    CHECK(*vec2.nth(2) == 60);
    CHECK(*vec2.nth(3) == 70);

    ///////////////////////////////////////////////////////////////////////////

    vec1.swap(vec2);

    CHECK(vec1.size() == 4);
    CHECK(vec1.capacity() == 4);
    CHECK(*vec1.nth(0) == 40);
    CHECK(*vec1.nth(1) == 50);
    CHECK(*vec1.nth(2) == 60);
    CHECK(*vec1.nth(3) == 70);

    CHECK(vec2.size() == 3);
    CHECK(vec2.capacity() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec1.swap(vec2);

    CHECK(vec1.size() == 3);
    CHECK(vec1.capacity() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    CHECK(vec2.size() == 4);
    CHECK(vec2.capacity() == 4);
    CHECK(*vec2.nth(0) == 40);
    CHECK(*vec2.nth(1) == 50);
    CHECK(*vec2.nth(2) == 60);
    CHECK(*vec2.nth(3) == 70);
}
END_STATIC_ASSERT

// Test NON-MEMBER comparison operators
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1, vec2;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    vec2.emplace_back(10);
    vec2.emplace_back(20);
    vec2.emplace_back(30);
    vec2.emplace_back(40);
    vec2.emplace_back(50);

    CHECK((vec1 == vec1) == true);
    CHECK((vec1 == vec2) == false);
    CHECK((vec2 == vec1) == false);
    CHECK((vec2 == vec2) == true);

    CHECK((vec1 != vec1) == false);
    CHECK((vec1 != vec2) == true);
    CHECK((vec2 != vec1) == true);
    CHECK((vec2 != vec2) == false);

    CHECK((vec1 < vec1) == false);
    CHECK((vec1 < vec2) == true);
    CHECK((vec2 < vec1) == false);
    CHECK((vec2 < vec2) == false);

    CHECK((vec1 > vec1) == false);
    CHECK((vec1 > vec2) == false);
    CHECK((vec2 > vec1) == true);
    CHECK((vec2 > vec2) == false);

    CHECK((vec1 <= vec1) == true);
    CHECK((vec1 <= vec2) == true);
    CHECK((vec2 <= vec1) == false);
    CHECK((vec2 <= vec2) == true);

    CHECK((vec1 >= vec1) == true);
    CHECK((vec1 >= vec2) == false);
    CHECK((vec2 >= vec1) == true);
    CHECK((vec2 >= vec2) == true);
}
END_STATIC_ASSERT

// Test NON-MEMBER swap(container&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec1, vec2;

    vec1.emplace_back(10);
    vec1.emplace_back(20);
    vec1.emplace_back(30);

    vec2.emplace_back(40);
    vec2.emplace_back(50);
    vec2.emplace_back(60);
    vec2.emplace_back(70);
    vec2.emplace_back(80);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    CHECK(vec2.size() == 5);
    CHECK(*vec2.nth(0) == 40);
    CHECK(*vec2.nth(1) == 50);
    CHECK(*vec2.nth(2) == 60);
    CHECK(*vec2.nth(3) == 70);
    CHECK(*vec2.nth(4) == 80);

    ///////////////////////////////////////////////////////////////////////////

    swap(vec1, vec2);

    CHECK(vec1.size() == 5);
    CHECK(*vec1.nth(0) == 40);
    CHECK(*vec1.nth(1) == 50);
    CHECK(*vec1.nth(2) == 60);
    CHECK(*vec1.nth(3) == 70);
    CHECK(*vec1.nth(4) == 80);

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
}
END_STATIC_ASSERT

// Test NON-MEMBER erase(container&, const U&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 20);
    CHECK(*vec.nth(3) == 20);
    CHECK(*vec.nth(4) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_STATIC_ASSERT

// Test NON-MEMBER erase_if(container&, Predicate)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::vector<int, std::allocator<int>>;

    using const_reference = typename vector::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    vector vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 20);
    CHECK(*vec.nth(3) == 20);
    CHECK(*vec.nth(4) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_STATIC_ASSERT

// Test deduction guides
BEGIN_STATIC_ASSERT
{
    sfl::vector<int, std::allocator<int>> vec1({10, 20, 30, 40});

    sfl::vector vec2(vec1.begin(), vec1.end());

    CHECK(vec2.size() == 4);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
    CHECK(*vec2.nth(3) == 40);
}
END_STATIC_ASSERT

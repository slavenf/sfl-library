#define BEGIN_STATIC_ASSERT static_assert([](){
#define END_STATIC_ASSERT   return true;}());

// Test container()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() == 0);
    CHECK(vec.available_front() == 0);
    CHECK(vec.available_back() == 0);

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
    using vector = sfl::devector<int, std::allocator<int>>;

    typename vector::allocator_type alloc;

    vector vec(alloc);

    CHECK(vec.empty() == true);
    CHECK(vec.size() == 0);
    CHECK(vec.max_size() > 0);
    CHECK(vec.capacity() == 0);
    CHECK(vec.available_front() == 0);
    CHECK(vec.available_back() == 0);

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size();

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n < vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() + vec.available_back() - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n == vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() + vec.available_back();

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n < vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back() - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n == vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back();

        CHECK(CONDITION);

        const int value = 12345;

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n > vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back() + 1;

        CHECK(CONDITION);

        const int value = 12345;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

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

    #define CONDITION n > vec.size() && \
                      n < vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() + vec.available_back() - 1;

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

    #define CONDITION n > vec.size() && \
                      n == vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() + vec.available_back();

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

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n < vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back() - 1;

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

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n == vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back();

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

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n > vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.available_front() + vec.size() + vec.available_back() + 1;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);

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

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

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

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);
        vec1.emplace(vec1.end(), 40);
        vec1.emplace(vec1.end(), 50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

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
    using vector = sfl::devector<int, std::allocator<int>>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector vec1, vec2;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);

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

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

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

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);
        vec1.emplace(vec1.end(), 40);
        vec1.emplace(vec1.end(), 50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    auto alloc = vec.get_allocator();

    (void)alloc;
}
END_STATIC_ASSERT

// Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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

// Test reserve_front(size_type) and shrink_to_fit()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(8);
    vec.emplace_back(9);
    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);

    vec.pop_front();
    vec.pop_front();

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    {
        const auto available_front_before = vec.available_front();
        vec.shrink_to_fit();
        const auto available_front_after = vec.available_front();

        CHECK(available_front_after <= available_front_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto available_front_before = vec.available_front();
        vec.reserve_front(9999);
        const auto available_front_after = vec.available_front();

        CHECK(available_front_after > available_front_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto available_front_before = vec.available_front();
        vec.shrink_to_fit();
        const auto available_front_after = vec.available_front();

        CHECK(available_front_after < available_front_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }
}
END_STATIC_ASSERT

// Test reserve_back(size_type) and shrink_to_fit()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);
    vec.emplace_back(40);
    vec.emplace_back(50);

    vec.pop_back();
    vec.pop_back();

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    {
        const auto available_back_before = vec.available_back();
        vec.shrink_to_fit();
        const auto available_back_after = vec.available_back();

        CHECK(available_back_after <= available_back_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto available_back_before = vec.available_back();
        vec.reserve_back(9999);
        const auto available_back_after = vec.available_back();

        CHECK(available_back_after > available_back_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto available_back_before = vec.available_back();
        vec.shrink_to_fit();
        const auto available_back_after = vec.available_back();

        CHECK(available_back_after < available_back_before);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }
}
END_STATIC_ASSERT

// Test at(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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

// Test emplace(const_iterator, Args&&...) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(0), 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) ==  5);
        CHECK(*vec.nth(1) == 10);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(1), 15);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 15);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(2), 25);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 25);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(3), 35);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 35);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(4), 45);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 45);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(5), 55);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 55);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(6), 65);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 65);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(7), 75);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 75);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(8), 85);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 85);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(9), 95);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 95);
    }
}
END_STATIC_ASSERT

// Test emplace(const_iterator, Args&&...) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(0), 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 90);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) ==  5);
        CHECK(*vec.nth(1) == 10);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(1), 15);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 90);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 15);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(2), 25);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 90);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 25);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(3), 35);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 90);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 35);
        CHECK(*vec.nth(4) == 40);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(4), 45);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 90);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 45);
        CHECK(*vec.nth(5) == 50);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(5), 55);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 90);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 55);
        CHECK(*vec.nth(6) == 60);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(6), 65);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 90);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 65);
        CHECK(*vec.nth(7) == 70);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(7), 75);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 90);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 75);
        CHECK(*vec.nth(8) == 80);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(8), 85);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 90);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 85);
        CHECK(*vec.nth(9) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.emplace(vec.nth(9), 95);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 90);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 95);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    int value = 12345;

    vec.insert(vec.end(), std::move(value));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test insert(const_iterator, size_type, const T&) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(0), 3, 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) ==  5);
        CHECK(*vec.nth( 1) ==  5);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(1), 3, 5);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  5);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(2), 3, 5);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(3), 3, 5);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(4), 3, 5);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(5), 3, 5);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(6), 3, 5);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(7), 3, 5);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(8), 3, 5);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) ==  5);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(9), 3, 5);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) ==  5);
        CHECK(*vec.nth(11) ==  5);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, size_type, const T&) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(0), 3, 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) ==  5);
        CHECK(*vec.nth( 1) ==  5);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(1), 3, 5);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  5);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(2), 3, 5);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  5);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(3), 3, 5);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  5);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(4), 3, 5);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  5);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(5), 3, 5);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  5);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(6), 3, 5);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  5);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(7), 3, 5);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  5);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(8), 3, 5);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  5);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) ==  5);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.insert(vec.nth(9), 3, 5);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  5);
        CHECK(*vec.nth(10) ==  5);
        CHECK(*vec.nth(11) ==  5);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, InputIt, InputIt) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(0), data.begin(), data.end());

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) ==  1);
        CHECK(*vec.nth( 1) ==  2);
        CHECK(*vec.nth( 2) ==  3);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(1), data.begin(), data.end());

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  1);
        CHECK(*vec.nth( 2) ==  2);
        CHECK(*vec.nth( 3) ==  3);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(2), data.begin(), data.end());

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  1);
        CHECK(*vec.nth( 3) ==  2);
        CHECK(*vec.nth( 4) ==  3);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(3), data.begin(), data.end());

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  1);
        CHECK(*vec.nth( 4) ==  2);
        CHECK(*vec.nth( 5) ==  3);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(4), data.begin(), data.end());

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  1);
        CHECK(*vec.nth( 5) ==  2);
        CHECK(*vec.nth( 6) ==  3);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(5), data.begin(), data.end());

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  1);
        CHECK(*vec.nth( 6) ==  2);
        CHECK(*vec.nth( 7) ==  3);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(6), data.begin(), data.end());

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  1);
        CHECK(*vec.nth( 7) ==  2);
        CHECK(*vec.nth( 8) ==  3);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(7), data.begin(), data.end());

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  1);
        CHECK(*vec.nth( 8) ==  2);
        CHECK(*vec.nth( 9) ==  3);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(8), data.begin(), data.end());

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  1);
        CHECK(*vec.nth( 9) ==  2);
        CHECK(*vec.nth(10) ==  3);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(9), data.begin(), data.end());

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  1);
        CHECK(*vec.nth(10) ==  2);
        CHECK(*vec.nth(11) ==  3);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, InputIt, InputIt) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(0), data.begin(), data.end());

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) ==  1);
        CHECK(*vec.nth( 1) ==  2);
        CHECK(*vec.nth( 2) ==  3);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(1), data.begin(), data.end());

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  1);
        CHECK(*vec.nth( 2) ==  2);
        CHECK(*vec.nth( 3) ==  3);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(2), data.begin(), data.end());

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  1);
        CHECK(*vec.nth( 3) ==  2);
        CHECK(*vec.nth( 4) ==  3);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(3), data.begin(), data.end());

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  1);
        CHECK(*vec.nth( 4) ==  2);
        CHECK(*vec.nth( 5) ==  3);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(4), data.begin(), data.end());

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  1);
        CHECK(*vec.nth( 5) ==  2);
        CHECK(*vec.nth( 6) ==  3);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(5), data.begin(), data.end());

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  1);
        CHECK(*vec.nth( 6) ==  2);
        CHECK(*vec.nth( 7) ==  3);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(6), data.begin(), data.end());

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  1);
        CHECK(*vec.nth( 7) ==  2);
        CHECK(*vec.nth( 8) ==  3);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(7), data.begin(), data.end());

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  1);
        CHECK(*vec.nth( 8) ==  2);
        CHECK(*vec.nth( 9) ==  3);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(8), data.begin(), data.end());

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  1);
        CHECK(*vec.nth( 9) ==  2);
        CHECK(*vec.nth(10) ==  3);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::vector<int> data({1, 2, 3});

        auto res = vec.insert(vec.nth(9), data.begin(), data.end());

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  1);
        CHECK(*vec.nth(10) ==  2);
        CHECK(*vec.nth(11) ==  3);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, std::initializer_list) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(0), ilist);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) ==  1);
        CHECK(*vec.nth( 1) ==  2);
        CHECK(*vec.nth( 2) ==  3);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(1), ilist);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  1);
        CHECK(*vec.nth( 2) ==  2);
        CHECK(*vec.nth( 3) ==  3);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(2), ilist);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  1);
        CHECK(*vec.nth( 3) ==  2);
        CHECK(*vec.nth( 4) ==  3);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(3), ilist);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  1);
        CHECK(*vec.nth( 4) ==  2);
        CHECK(*vec.nth( 5) ==  3);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(4), ilist);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  1);
        CHECK(*vec.nth( 5) ==  2);
        CHECK(*vec.nth( 6) ==  3);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(5), ilist);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  1);
        CHECK(*vec.nth( 6) ==  2);
        CHECK(*vec.nth( 7) ==  3);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(6), ilist);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  1);
        CHECK(*vec.nth( 7) ==  2);
        CHECK(*vec.nth( 8) ==  3);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(7), ilist);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  1);
        CHECK(*vec.nth( 8) ==  2);
        CHECK(*vec.nth( 9) ==  3);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(8), ilist);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  1);
        CHECK(*vec.nth( 9) ==  2);
        CHECK(*vec.nth(10) ==  3);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(9), ilist);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(vec.available_back() == 1);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  1);
        CHECK(*vec.nth(10) ==  2);
        CHECK(*vec.nth(11) ==  3);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, std::initializer_list) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(0), ilist);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) ==  1);
        CHECK(*vec.nth( 1) ==  2);
        CHECK(*vec.nth( 2) ==  3);
        CHECK(*vec.nth( 3) == 10);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(1), ilist);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) ==  1);
        CHECK(*vec.nth( 2) ==  2);
        CHECK(*vec.nth( 3) ==  3);
        CHECK(*vec.nth( 4) == 20);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(2), ilist);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) ==  1);
        CHECK(*vec.nth( 3) ==  2);
        CHECK(*vec.nth( 4) ==  3);
        CHECK(*vec.nth( 5) == 30);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(3), ilist);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) ==  1);
        CHECK(*vec.nth( 4) ==  2);
        CHECK(*vec.nth( 5) ==  3);
        CHECK(*vec.nth( 6) == 40);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(4), ilist);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 88);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) ==  1);
        CHECK(*vec.nth( 5) ==  2);
        CHECK(*vec.nth( 6) ==  3);
        CHECK(*vec.nth( 7) == 50);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(5), ilist);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) ==  1);
        CHECK(*vec.nth( 6) ==  2);
        CHECK(*vec.nth( 7) ==  3);
        CHECK(*vec.nth( 8) == 60);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(6), ilist);

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) ==  1);
        CHECK(*vec.nth( 7) ==  2);
        CHECK(*vec.nth( 8) ==  3);
        CHECK(*vec.nth( 9) == 70);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(7), ilist);

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) ==  1);
        CHECK(*vec.nth( 8) ==  2);
        CHECK(*vec.nth( 9) ==  3);
        CHECK(*vec.nth(10) == 80);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(8), ilist);

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) ==  1);
        CHECK(*vec.nth( 9) ==  2);
        CHECK(*vec.nth(10) ==  3);
        CHECK(*vec.nth(11) == 90);
    }

    {
        vector vec;

        vec.reserve_back(9);

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.reserve_front(100);
        vec.reserve_back(100);

        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 91);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        std::initializer_list<int> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(9), ilist);

        CHECK(res == vec.nth(9));
        CHECK(vec.size() == 12);
        CHECK(vec.capacity() == 191);
        CHECK(vec.available_front() == 91);
        CHECK(vec.available_back() == 88);
        CHECK(*vec.nth( 0) == 10);
        CHECK(*vec.nth( 1) == 20);
        CHECK(*vec.nth( 2) == 30);
        CHECK(*vec.nth( 3) == 40);
        CHECK(*vec.nth( 4) == 50);
        CHECK(*vec.nth( 5) == 60);
        CHECK(*vec.nth( 6) == 70);
        CHECK(*vec.nth( 7) == 80);
        CHECK(*vec.nth( 8) == 90);
        CHECK(*vec.nth( 9) ==  1);
        CHECK(*vec.nth(10) ==  2);
        CHECK(*vec.nth(11) ==  3);
    }
}
END_STATIC_ASSERT

// Test insert(const_iterator, Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(60);

    std::vector<int> data({20, 30, 40, 50});

    vec.insert_range(vec.nth(1), std::views::all(data));

    CHECK(vec.size() == 6);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
    CHECK(*vec.nth(4) == 50);
    CHECK(*vec.nth(5) == 60);
}
END_STATIC_ASSERT

// Test emplace_front(Args&&...) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    {
        const auto& res = vec.emplace_front(100);

        CHECK(res == 100);
        CHECK(vec.size() == 1);
        CHECK(vec.capacity() == 1);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 100);
    }

    {
        const auto& res = vec.emplace_front(90);

        CHECK(res == 90);
        CHECK(vec.size() == 2);
        CHECK(vec.capacity() == 2);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 90);
        CHECK(*vec.nth(1) == 100);
    }

    {
        const auto& res = vec.emplace_front(80);

        CHECK(res == 80);
        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 3);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 80);
        CHECK(*vec.nth(1) == 90);
        CHECK(*vec.nth(2) == 100);
    }

    {
        const auto& res = vec.emplace_front(70);

        CHECK(res == 70);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 4);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 70);
        CHECK(*vec.nth(1) == 80);
        CHECK(*vec.nth(2) == 90);
        CHECK(*vec.nth(3) == 100);
    }

    {
        const auto& res = vec.emplace_front(60);

        CHECK(res == 60);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 6);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 60);
        CHECK(*vec.nth(1) == 70);
        CHECK(*vec.nth(2) == 80);
        CHECK(*vec.nth(3) == 90);
        CHECK(*vec.nth(4) == 100);
    }

    {
        const auto& res = vec.emplace_front(50);

        CHECK(res == 50);
        CHECK(vec.size() == 6);
        CHECK(vec.capacity() == 6);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 50);
        CHECK(*vec.nth(1) == 60);
        CHECK(*vec.nth(2) == 70);
        CHECK(*vec.nth(3) == 80);
        CHECK(*vec.nth(4) == 90);
        CHECK(*vec.nth(5) == 100);
    }

    {
        const auto& res = vec.emplace_front(40);

        CHECK(res == 40);
        CHECK(vec.size() == 7);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
        CHECK(*vec.nth(6) == 100);
    }

    {
        const auto& res = vec.emplace_front(30);

        CHECK(res == 30);
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        CHECK(*vec.nth(5) == 80);
        CHECK(*vec.nth(6) == 90);
        CHECK(*vec.nth(7) == 100);
    }

    {
        const auto& res = vec.emplace_front(20);

        CHECK(res == 20);
        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 20);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
        CHECK(*vec.nth(8) == 100);
    }

    {
        const auto& res = vec.emplace_front(10);

        CHECK(res == 10);
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_back() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 100);
    }
}
END_STATIC_ASSERT

// Test emplace_front(Args&&...) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    const std::size_t N = 999;

    vec.reserve_back(N);

    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == N);
    CHECK(vec.available_back() == N);

    {
        const auto& res = vec.emplace_front(100);

        CHECK(res == 100);
        CHECK(vec.size() == 1);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 1);
        CHECK(*vec.nth(0) == 100);
    }

    {
        const auto& res = vec.emplace_front(90);

        CHECK(res == 90);
        CHECK(vec.size() == 2);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 2);
        CHECK(*vec.nth(0) == 90);
        CHECK(*vec.nth(1) == 100);
    }

    {
        const auto& res = vec.emplace_front(80);

        CHECK(res == 80);
        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 3);
        CHECK(*vec.nth(0) == 80);
        CHECK(*vec.nth(1) == 90);
        CHECK(*vec.nth(2) == 100);
    }

    {
        const auto& res = vec.emplace_front(70);

        CHECK(res == 70);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 4);
        CHECK(*vec.nth(0) == 70);
        CHECK(*vec.nth(1) == 80);
        CHECK(*vec.nth(2) == 90);
        CHECK(*vec.nth(3) == 100);
    }

    {
        const auto& res = vec.emplace_front(60);

        CHECK(res == 60);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 6);
        CHECK(*vec.nth(0) == 60);
        CHECK(*vec.nth(1) == 70);
        CHECK(*vec.nth(2) == 80);
        CHECK(*vec.nth(3) == 90);
        CHECK(*vec.nth(4) == 100);
    }

    {
        const auto& res = vec.emplace_front(50);

        CHECK(res == 50);
        CHECK(vec.size() == 6);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 6);
        CHECK(*vec.nth(0) == 50);
        CHECK(*vec.nth(1) == 60);
        CHECK(*vec.nth(2) == 70);
        CHECK(*vec.nth(3) == 80);
        CHECK(*vec.nth(4) == 90);
        CHECK(*vec.nth(5) == 100);
    }

    {
        const auto& res = vec.emplace_front(40);

        CHECK(res == 40);
        CHECK(vec.size() == 7);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 9);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
        CHECK(*vec.nth(6) == 100);
    }

    {
        const auto& res = vec.emplace_front(30);

        CHECK(res == 30);
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 9);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        CHECK(*vec.nth(5) == 80);
        CHECK(*vec.nth(6) == 90);
        CHECK(*vec.nth(7) == 100);
    }

    {
        const auto& res = vec.emplace_front(20);

        CHECK(res == 20);
        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 9);
        CHECK(*vec.nth(0) == 20);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
        CHECK(*vec.nth(8) == 100);
    }

    {
        const auto& res = vec.emplace_front(10);

        CHECK(res == 10);
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_back() == N - 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 100);
    }
}
END_STATIC_ASSERT

// Test emplace_back(Args&&...) (1)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    {
        const auto& res = vec.emplace_back(10);

        CHECK(res == 10);
        CHECK(vec.size() == 1);
        CHECK(vec.capacity() == 1);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
    }

    {
        const auto& res = vec.emplace_back(20);

        CHECK(res == 20);
        CHECK(vec.size() == 2);
        CHECK(vec.capacity() == 2);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
    }

    {
        const auto& res = vec.emplace_back(30);

        CHECK(res == 30);
        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 3);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto& res = vec.emplace_back(40);

        CHECK(res == 40);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 4);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    {
        const auto& res = vec.emplace_back(50);

        CHECK(res == 50);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 6);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }

    {
        const auto& res = vec.emplace_back(60);

        CHECK(res == 60);
        CHECK(vec.size() == 6);
        CHECK(vec.capacity() == 6);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }

    {
        const auto& res = vec.emplace_back(70);

        CHECK(res == 70);
        CHECK(vec.size() == 7);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
    }

    {
        const auto& res = vec.emplace_back(80);

        CHECK(res == 80);
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
    }

    {
        const auto& res = vec.emplace_back(90);

        CHECK(res == 90);
        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == 9);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
    }

    {
        const auto& res = vec.emplace_back(100);

        CHECK(res == 100);
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == 13);
        CHECK(vec.available_front() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 100);
    }
}
END_STATIC_ASSERT

// Test emplace_back(Args&&...) (2)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    const std::size_t N = 999;

    vec.reserve_front(N);

    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == N);
    CHECK(vec.available_front() == N);

    {
        const auto& res = vec.emplace_back(10);

        CHECK(res == 10);
        CHECK(vec.size() == 1);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 1);
        CHECK(*vec.nth(0) == 10);
    }

    {
        const auto& res = vec.emplace_back(20);

        CHECK(res == 20);
        CHECK(vec.size() == 2);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 2);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
    }

    {
        const auto& res = vec.emplace_back(30);

        CHECK(res == 30);
        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto& res = vec.emplace_back(40);

        CHECK(res == 40);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    {
        const auto& res = vec.emplace_back(50);

        CHECK(res == 50);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }

    {
        const auto& res = vec.emplace_back(60);

        CHECK(res == 60);
        CHECK(vec.size() == 6);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }

    {
        const auto& res = vec.emplace_back(70);

        CHECK(res == 70);
        CHECK(vec.size() == 7);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
    }

    {
        const auto& res = vec.emplace_back(80);

        CHECK(res == 80);
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
    }

    {
        const auto& res = vec.emplace_back(90);

        CHECK(res == 90);
        CHECK(vec.size() == 9);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
    }

    {
        const auto& res = vec.emplace_back(100);

        CHECK(res == 100);
        CHECK(vec.size() == 10);
        CHECK(vec.capacity() == N);
        CHECK(vec.available_front() == N - 13);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);
        CHECK(*vec.nth(9) == 100);
    }
}
END_STATIC_ASSERT

// Test push_front(const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    const int value = 12345;

    vec.push_front(value);

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test push_front(T&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    int value = 12345;

    vec.push_front(std::move(value));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test push_back(const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    int value = 12345;

    vec.push_back(std::move(value));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 12345);
}
END_STATIC_ASSERT

// Test prepend_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(50);
    vec.emplace_back(60);

    std::vector<int> data({10, 20, 30, 40});

    vec.prepend_range(std::views::all(data));

    CHECK(vec.size() == 6);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
    CHECK(*vec.nth(4) == 50);
    CHECK(*vec.nth(5) == 60);
}
END_STATIC_ASSERT

// Test append_range(Range&&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);

    std::vector<int> data({30, 40, 50, 60});

    vec.append_range(std::views::all(data));

    CHECK(vec.size() == 6);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
    CHECK(*vec.nth(4) == 50);
    CHECK(*vec.nth(5) == 60);
}
END_STATIC_ASSERT

// Test pop_front()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_front();

    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 20);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_front();

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 30);

    ///////////////////////////////////////////////////////////////////////////

    vec.pop_front();

    CHECK(vec.size() == 0);
}
END_STATIC_ASSERT

// Test pop_back()
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    vector vec;

    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(30);

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
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(0));

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 20);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(1));

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(2));

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(3));

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 50);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(4));

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 60);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(5));

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 70);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(6));

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 80);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(7));

        CHECK(res == vec.nth(7));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(8));

        CHECK(res == vec.nth(8));
        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
    }
}
END_STATIC_ASSERT

// Test erase(const_iterator, const_iterator)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

    {
        vector vec;

        CHECK(vec.size() == 0);

        CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
        CHECK(vec.erase(vec.nth(1), vec.nth(1)) == vec.nth(1));
        CHECK(vec.erase(vec.nth(2), vec.nth(2)) == vec.nth(2));
        CHECK(vec.erase(vec.nth(3), vec.nth(3)) == vec.nth(3));
        CHECK(vec.erase(vec.nth(4), vec.nth(4)) == vec.nth(4));
        CHECK(vec.erase(vec.nth(5), vec.nth(5)) == vec.nth(5));
        CHECK(vec.erase(vec.nth(6), vec.nth(6)) == vec.nth(6));
        CHECK(vec.erase(vec.nth(7), vec.nth(7)) == vec.nth(7));
        CHECK(vec.erase(vec.nth(8), vec.nth(8)) == vec.nth(8));
        CHECK(vec.erase(vec.nth(9), vec.nth(9)) == vec.nth(9));
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(0), vec.nth(3));

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(1), vec.nth(4));

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(2), vec.nth(5));

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(3), vec.nth(6));

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(4), vec.nth(7));

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 80);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(5), vec.nth(8));

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 90);
    }

    {
        vector vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);
        vec.emplace_back(60);
        vec.emplace_back(70);
        vec.emplace_back(80);
        vec.emplace_back(90);

        CHECK(vec.size() == 9);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);
        CHECK(*vec.nth(7) == 80);
        CHECK(*vec.nth(8) == 90);

        auto res = vec.erase(vec.nth(6), vec.nth(9));

        CHECK(res == vec.nth(6));
        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
}
END_STATIC_ASSERT

// Test resize(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size();

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n < vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        for (size_type i = size; i < n; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n == vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        for (size_type i = size; i < n; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n < vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - (size + available_back); ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth(n - (size + available_back) + 0) == 30);
        CHECK(*vec.nth(n - (size + available_back) + 1) == 40);
        CHECK(*vec.nth(n - (size + available_back) + 2) == 50);
        CHECK(*vec.nth(n - (size + available_back) + 3) == 60);
        CHECK(*vec.nth(n - (size + available_back) + 4) == 70);
        for (size_type i = n - available_back; i < available_back; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n == vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - (size + available_back); ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth(n - (size + available_back) + 0) == 30);
        CHECK(*vec.nth(n - (size + available_back) + 1) == 40);
        CHECK(*vec.nth(n - (size + available_back) + 2) == 50);
        CHECK(*vec.nth(n - (size + available_back) + 3) == 60);
        CHECK(*vec.nth(n - (size + available_back) + 4) == 70);
        for (size_type i = n - available_back; i < available_back; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n > vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back + 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < available_front; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth(available_front + 0) == 30);
        CHECK(*vec.nth(available_front + 1) == 40);
        CHECK(*vec.nth(available_front + 2) == 50);
        CHECK(*vec.nth(available_front + 3) == 60);
        CHECK(*vec.nth(available_front + 4) == 70);
        for (size_type i = available_front + size; i < n; ++i)
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
    using vector = sfl::devector<int, std::allocator<int>>;

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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size();

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n < vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        for (size_type i = size; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n == vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
        for (size_type i = size; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n < vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - (size + available_back); ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth(n - (size + available_back) + 0) == 30);
        CHECK(*vec.nth(n - (size + available_back) + 1) == 40);
        CHECK(*vec.nth(n - (size + available_back) + 2) == 50);
        CHECK(*vec.nth(n - (size + available_back) + 3) == 60);
        CHECK(*vec.nth(n - (size + available_back) + 4) == 70);
        for (size_type i = n - available_back; i < available_back; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n == vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - (size + available_back); ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth(n - (size + available_back) + 0) == 30);
        CHECK(*vec.nth(n - (size + available_back) + 1) == 40);
        CHECK(*vec.nth(n - (size + available_back) + 2) == 50);
        CHECK(*vec.nth(n - (size + available_back) + 3) == 60);
        CHECK(*vec.nth(n - (size + available_back) + 4) == 70);
        for (size_type i = n - available_back; i < available_back; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && \
                      n > vec.size() + vec.available_back() && \
                      n > vec.available_front() + vec.size() + vec.available_back()
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
        vec.emplace_back(80);
        vec.emplace_back(90);

        vec.pop_front();
        vec.pop_front();

        vec.pop_back();
        vec.pop_back();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type available_front = vec.available_front();

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = available_front + size + available_back + 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < available_front; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth(available_front + 0) == 30);
        CHECK(*vec.nth(available_front + 1) == 40);
        CHECK(*vec.nth(available_front + 2) == 50);
        CHECK(*vec.nth(available_front + 3) == 60);
        CHECK(*vec.nth(available_front + 4) == 70);
        for (size_type i = available_front + size; i < n; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test resize_front(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        vec.resize_front(n);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size();

        CHECK(CONDITION);

        vec.resize_front(n);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front - 1;

        CHECK(CONDITION);

        vec.resize_front(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front;

        CHECK(CONDITION);

        vec.resize_front(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front + 1;

        CHECK(CONDITION);

        vec.resize_front(n);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == 0);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test resize_front(size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_front(n, value);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type n = vec.size();

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_front(n, value);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_front(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_front(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n > vec.size() + vec.available_front()
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

        vec.pop_front();
        vec.pop_front();

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 30);
        CHECK(*vec.nth(1) == 40);
        CHECK(*vec.nth(2) == 50);
        CHECK(*vec.nth(3) == 60);
        CHECK(*vec.nth(4) == 70);

        const size_type size = vec.size();

        const size_type available_front = vec.available_front();

        const size_type n = size + available_front + 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_front(n, value);

        CHECK(vec.size() == n);
        for (size_type i = 0; i < n - size; ++i)
        {
            CHECK(*vec.nth(i) == value);
        }
        CHECK(*vec.nth((n - size) + 0) == 30);
        CHECK(*vec.nth((n - size) + 1) == 40);
        CHECK(*vec.nth((n - size) + 2) == 50);
        CHECK(*vec.nth((n - size) + 3) == 60);
        CHECK(*vec.nth((n - size) + 4) == 70);
    }
    #undef CONDITION
}
END_STATIC_ASSERT

// Test resize_back(size_type)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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

        vec.resize_back(n);

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

        vec.resize_back(n);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back - 1;

        CHECK(CONDITION);

        vec.resize_back(n);

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

    #define CONDITION n > vec.size() && n == vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back;

        CHECK(CONDITION);

        vec.resize_back(n);

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

    #define CONDITION n > vec.size() && n > vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back + 1;

        CHECK(CONDITION);

        vec.resize_back(n);

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

// Test resize_back(size_type, const T&)
BEGIN_STATIC_ASSERT
{
    using vector = sfl::devector<int, std::allocator<int>>;

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

        const int value = 12345;

        vec.resize_back(n, value);

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

        const int value = 12345;

        vec.resize_back(n, value);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back - 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_back(n, value);

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

    #define CONDITION n > vec.size() && n == vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_back(n, value);

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

    #define CONDITION n > vec.size() && n > vec.size() + vec.available_back()
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

        const size_type size = vec.size();

        const size_type available_back = vec.available_back();

        const size_type n = size + available_back + 1;

        CHECK(CONDITION);

        const int value = 12345;

        vec.resize_back(n, value);

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    using vector = sfl::devector<int, std::allocator<int>>;

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
    sfl::devector<int, std::allocator<int>> vec1({10, 20, 30, 40});

    sfl::devector vec2(vec1.begin(), vec1.end());

    CHECK(vec2.size() == 4);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
    CHECK(*vec2.nth(3) == 40);
}
END_STATIC_ASSERT

using sfl::test::xint;

BEGIN_TEST("Test emplace_back(Args&&...)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 5;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    {
        CHECK(vec.empty() == true);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 0);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 5);
    }

    {
        const auto res = vec.emplace_back(10);

        CHECK(res == 10);
        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 1);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 4);
        CHECK(*vec.nth(0) == 10);
    }

    {
        const auto res = vec.emplace_back(20);

        CHECK(res == 20);
        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 2);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
    }

    {
        const auto res = vec.emplace_back(30);

        CHECK(res == 30);
        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 2);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    {
        const auto res = vec.emplace_back(40);

        CHECK(res == 40);
        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    {
        const auto res = vec.emplace_back(50);

        CHECK(res == 50);
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
}
END_TEST()

BEGIN_TEST("Test emplace(const_iterator, Args&&...)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 5;
    using vector_type = sfl::static_vector<T, N>;

    // Insert at the end
    {
        vector_type vec;

        {
            CHECK(vec.empty() == true);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 0);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 5);
        }

        {
            const auto res = vec.emplace(vec.end(), 10);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 1);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 4);
            CHECK(*vec.nth(0) == 10);
        }

        {
            const auto res = vec.emplace(vec.end(), 20);

            CHECK(res == vec.nth(1));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 2);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 3);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
        }

        {
            const auto res = vec.emplace(vec.end(), 30);

            CHECK(res == vec.nth(2));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 3);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 2);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
        }

        {
            const auto res = vec.emplace(vec.end(), 40);

            CHECK(res == vec.nth(3));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        {
            const auto res = vec.emplace(vec.end(), 50);

            CHECK(res == vec.nth(4));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
        }
    }

    // Insert at the begin
    {
        vector_type vec;

        {
            CHECK(vec.empty() == true);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 0);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 5);
        }

        {
            const auto res = vec.emplace(vec.begin(), 50);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 1);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 4);
            CHECK(*vec.nth(0) == 50);
        }

        {
            const auto res = vec.emplace(vec.begin(), 40);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 2);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 3);
            CHECK(*vec.nth(0) == 40);
            CHECK(*vec.nth(1) == 50);
        }

        {
            const auto res = vec.emplace(vec.begin(), 30);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 3);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 2);
            CHECK(*vec.nth(0) == 30);
            CHECK(*vec.nth(1) == 40);
            CHECK(*vec.nth(2) == 50);
        }

        {
            const auto res = vec.emplace(vec.begin(), 20);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 20);
            CHECK(*vec.nth(1) == 30);
            CHECK(*vec.nth(2) == 40);
            CHECK(*vec.nth(3) == 50);
        }

        {
            const auto res = vec.emplace(vec.begin(), 10);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
        }
    }

    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);

        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);

        const auto res = vec.emplace(vec.nth(0), 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) ==  5);
        CHECK(*vec.nth(1) == 10);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
    }

    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);

        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);

        const auto res = vec.emplace(vec.nth(1), 15);

        CHECK(res == vec.nth(1));
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 15);
        CHECK(*vec.nth(2) == 20);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
    }

    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);

        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);

        const auto res = vec.emplace(vec.nth(2), 25);

        CHECK(res == vec.nth(2));
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 25);
        CHECK(*vec.nth(3) == 30);
        CHECK(*vec.nth(4) == 40);
    }

    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);

        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);

        const auto res = vec.emplace(vec.nth(3), 35);

        CHECK(res == vec.nth(3));
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 35);
        CHECK(*vec.nth(4) == 40);
    }

    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);

        CHECK(vec.empty() == false);
        CHECK(vec.full() == false);
        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);

        const auto res = vec.emplace(vec.nth(4), 45);

        CHECK(res == vec.nth(4));
        CHECK(vec.empty() == false);
        CHECK(vec.full() == true);
        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 45);
    }
}
END_TEST()

BEGIN_TEST("Test static_capacity")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    CHECK((vector_type::static_capacity == 100));
}
END_TEST()

BEGIN_TEST("Test container()")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    CHECK(vec.size() == 0);
}
END_TEST()

BEGIN_TEST("Test container(size_type)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec(4);

    CHECK(vec.size() == 4);
    #ifndef TEST_CPP20_CONSTEXPR
    CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    #else
    CHECK(*vec.nth(0) == 0);
    CHECK(*vec.nth(1) == 0);
    CHECK(*vec.nth(2) == 0);
    CHECK(*vec.nth(3) == 0);
    #endif
}
END_TEST()

BEGIN_TEST("Test container(size_type, sfl::default_init_t)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec(4, sfl::default_init_t());

    CHECK(vec.size() == 4);
    #ifndef TEST_CPP20_CONSTEXPR
    CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
    CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    #else
    // *vec.nth(0) is undetermined
    // *vec.nth(1) is undetermined
    // *vec.nth(2) is undetermined
    // *vec.nth(3) is undetermined
    #endif
}
END_TEST()

BEGIN_TEST("Test container(size_type, const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    const T value(12345);

    vector_type vec(4, value);

    CHECK(vec.size() == 4);
    CHECK(*vec.nth(0) == value);
    CHECK(*vec.nth(1) == value);
    CHECK(*vec.nth(2) == value);
    CHECK(*vec.nth(3) == value);
}
END_TEST()

BEGIN_TEST("Test container(InputIt, InputIt)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 40");

        vector_type vec((std::istream_iterator<int>(iss)), (std::istream_iterator<int>()));

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #endif

    // Forward iterator
    {
        std::vector<T> data({10, 20, 30, 40});

        vector_type vec(data.begin(), data.end());

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
}
END_TEST()

BEGIN_TEST("Test container(std::initializer_list)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    std::initializer_list<T> ilist{10, 20, 30, 40};

    vector_type vec(ilist);

    CHECK(vec.size() == 4);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);
    CHECK(*vec.nth(3) == 40);
}
END_TEST()

BEGIN_TEST("Test container(const container&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec1;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////

    vector_type vec2(vec1);

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);
}
END_TEST()

BEGIN_TEST("Test container(container&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec1;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    CHECK(vec1.size() == 3);
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////

    vector_type vec2(std::move(vec1));

    CHECK(vec2.size() == 3);
    CHECK(*vec2.nth(0) == 10);
    CHECK(*vec2.nth(1) == 20);
    CHECK(*vec2.nth(2) == 30);

    CHECK(vec1.size() == 3);
    #ifndef TEST_CPP20_CONSTEXPR
    CHECK(*vec1.nth(0) == -10);
    CHECK(*vec1.nth(1) == -20);
    CHECK(*vec1.nth(2) == -30);
    #else
    CHECK(*vec1.nth(0) == 10);
    CHECK(*vec1.nth(1) == 20);
    CHECK(*vec1.nth(2) == 30);
    #endif
}
END_TEST()

BEGIN_TEST("Test container(sfl::from_range_t, Range&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        std::istringstream iss("10 20 30 40");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vector_type vec(sfl::from_range_t(), (std::views::istream<int>(iss)));
        #else
        vector_type vec(sfl::from_range_t(), (sfl::test::istream_view<int>(iss)));
        #endif

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #endif

    // Forward iterator
    {
        std::vector<int> data({10, 20, 30, 40});

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vector_type vec(sfl::from_range_t(), std::views::all(data));
        #else
        vector_type vec(sfl::from_range_t(), data);
        #endif

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
}
END_TEST()

BEGIN_TEST("Test assign(size_type, const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 10;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION n < vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

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

        const T value(12345);

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
        vector_type vec;

        using size_type = typename vector_type::size_type;

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

        const T value(12345);

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
        vector_type vec;

        using size_type = typename vector_type::size_type;

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

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        const T value(12345);

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
        vector_type vec;

        using size_type = typename vector_type::size_type;

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

        const T value(12345);

        vec.assign(n, value);

        CHECK(vec.size() == n);
        for (const auto& elem : vec)
        {
            CHECK(elem == value);
        }
    }
    #undef CONDITION
}
END_TEST()

BEGIN_TEST("Test assign(InputIt, InputIt)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 10;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        #define CONDITION n < vec.size()
        {
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::stringstream ss;
            for (int i = 0; i < int(n); ++i)
            {
                ss << i << " ";
            }

            vec.assign
            (
                (std::istream_iterator<int>(ss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == n);
            for (int i = 0; i < int(n); ++i)
            {
                CHECK(*vec.nth(i) == i);
            }
        }
        #undef CONDITION

        #define CONDITION n == vec.size()
        {
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::stringstream ss;
            for (int i = 0; i < int(n); ++i)
            {
                ss << i << " ";
            }

            vec.assign
            (
                (std::istream_iterator<int>(ss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == n);
            for (int i = 0; i < int(n); ++i)
            {
                CHECK(*vec.nth(i) == i);
            }
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n < vec.capacity()
        {
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            const size_type n = vec.capacity() - 1;

            CHECK(CONDITION);

            std::stringstream ss;
            for (int i = 0; i < int(n); ++i)
            {
                ss << i << " ";
            }

            vec.assign
            (
                (std::istream_iterator<int>(ss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == n);
            for (int i = 0; i < int(n); ++i)
            {
                CHECK(*vec.nth(i) == i);
            }
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n == vec.capacity()
        {
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::stringstream ss;
            for (int i = 0; i < int(n); ++i)
            {
                ss << i << " ";
            }

            vec.assign
            (
                (std::istream_iterator<int>(ss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == n);
            for (int i = 0; i < int(n); ++i)
            {
                CHECK(*vec.nth(i) == i);
            }
        }
        #undef CONDITION
    }
    #endif

    // Forward iterator
    {
        #define CONDITION n < vec.size()
        {
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::vector<T> data;
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
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::vector<T> data;
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
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            const size_type n = vec.capacity() - 1;

            CHECK(CONDITION);

            std::vector<T> data;
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
            vector_type vec;

            using size_type = typename vector_type::size_type;

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

            std::vector<T> data;
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
}
END_TEST()

BEGIN_TEST("Test assign(std::initializer_list")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 10;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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

    std::initializer_list<T> ilist{1, 2, 3, 4, 5};

    vec.assign(ilist);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 1);
    CHECK(*vec.nth(1) == 2);
    CHECK(*vec.nth(2) == 3);
    CHECK(*vec.nth(3) == 4);
    CHECK(*vec.nth(4) == 5);
}
END_TEST()

BEGIN_TEST("Test assign_range(Range&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        vector_type vec;

        std::istringstream iss("10 20 30 40");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.assign_range(std::views::istream<int>(iss));
        #else
        vec.assign_range(sfl::test::istream_view<int>(iss));
        #endif

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #endif

    // Forward iterator
    {
        std::vector<T> data({10, 20, 30, 40});

        vector_type vec;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.assign_range(std::views::all(data));
        #else
        vec.assign_range(data);
        #endif

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
}
END_TEST()

BEGIN_TEST("Test operator=(const container&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

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
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

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
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

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
END_TEST()

BEGIN_TEST("Test operator=(container&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION vec1.size() == vec2.size()
    {
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);

        CHECK(vec2.size() == 3);
        #ifndef TEST_CPP20_CONSTEXPR
        CHECK(*vec2.nth(0) == -40);
        CHECK(*vec2.nth(1) == -50);
        CHECK(*vec2.nth(2) == -60);
        #else
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        #endif
    }
    #undef CONDITION

    #define CONDITION vec1.size() < vec2.size()
    {
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);

        CHECK(vec2.size() == 5);
        #ifndef TEST_CPP20_CONSTEXPR
        CHECK(*vec2.nth(0) == -40);
        CHECK(*vec2.nth(1) == -50);
        CHECK(*vec2.nth(2) == -60);
        CHECK(*vec2.nth(3) == -70);
        CHECK(*vec2.nth(4) == -80);
        #else
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
        #endif
    }
    #undef CONDITION

    #define CONDITION vec1.size() > vec2.size()
    {
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = std::move(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        CHECK(vec2.size() == 3);
        #ifndef TEST_CPP20_CONSTEXPR
        CHECK(*vec2.nth(0) == -60);
        CHECK(*vec2.nth(1) == -70);
        CHECK(*vec2.nth(2) == -80);
        #else
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);
        #endif
    }
    #undef CONDITION
}
END_TEST()

BEGIN_TEST("Test operator=(std::initializer_list)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION vec.size() == ilist.size()
    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        std::initializer_list<T> ilist{40, 50, 60};

        ///////////////////////////////////////////////////////////////////

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
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        std::initializer_list<T> ilist{40, 50, 60, 70, 80};

        ///////////////////////////////////////////////////////////////////

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
        vector_type vec;

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

        std::initializer_list<T> ilist{60, 70, 80};

        ///////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 60);
        CHECK(*vec.nth(1) == 70);
        CHECK(*vec.nth(2) == 80);
    }
    #undef CONDITION
}
END_TEST()

BEGIN_TEST("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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
END_TEST()

BEGIN_TEST("Test clear()")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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
END_TEST()

BEGIN_TEST("Test insert(const_iterator, const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    T value_10(10);

    auto res = vec.insert(vec.nth(0), value_10);

    CHECK(res == vec.nth(0));
    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == 10);
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, T&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    T value_10(10);

    auto res = vec.insert(vec.nth(0), std::move(value_10));

    CHECK(res == vec.nth(0));
    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    #ifndef TEST_CPP20_CONSTEXPR
    CHECK(value_10 == -10);
    #else
    CHECK(value_10 == 10);
    #endif
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, size_type, const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(0), 3, 5);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) ==  5);
        CHECK(*vec.nth(1) ==  5);
        CHECK(*vec.nth(2) ==  5);
        CHECK(*vec.nth(3) == 10);
        CHECK(*vec.nth(4) == 20);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(1), 3, 15);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 15);
        CHECK(*vec.nth(2) == 15);
        CHECK(*vec.nth(3) == 15);
        CHECK(*vec.nth(4) == 20);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(2), 3, 25);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 25);
        CHECK(*vec.nth(3) == 25);
        CHECK(*vec.nth(4) == 25);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(3), 3, 35);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 35);
        CHECK(*vec.nth(4) == 35);
        CHECK(*vec.nth(5) == 35);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(4), 3, 45);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 45);
        CHECK(*vec.nth(5) == 45);
        CHECK(*vec.nth(6) == 45);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        auto res = vec.insert(vec.nth(5), 3, 55);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 55);
        CHECK(*vec.nth(6) == 55);
        CHECK(*vec.nth(7) == 55);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, InputIt, InputIt)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("1 2 3");

            auto res = vec.insert
            (
                vec.nth(0),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) ==  1);
            CHECK(*vec.nth(1) ==  2);
            CHECK(*vec.nth(2) ==  3);
            CHECK(*vec.nth(3) == 10);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("11 12 13");

            auto res = vec.insert
            (
                vec.nth(1),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 11);
            CHECK(*vec.nth(2) == 12);
            CHECK(*vec.nth(3) == 13);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("21 22 23");

            auto res = vec.insert
            (
                vec.nth(2),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 21);
            CHECK(*vec.nth(3) == 22);
            CHECK(*vec.nth(4) == 23);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("31 32 33");

            auto res = vec.insert
            (
                vec.nth(3),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 31);
            CHECK(*vec.nth(4) == 32);
            CHECK(*vec.nth(5) == 33);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("41 42 43");

            auto res = vec.insert
            (
                vec.nth(4),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 41);
            CHECK(*vec.nth(5) == 42);
            CHECK(*vec.nth(6) == 43);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("51 52 53");

            auto res = vec.insert
            (
                vec.nth(5),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 51);
            CHECK(*vec.nth(6) == 52);
            CHECK(*vec.nth(7) == 53);
        }
    }
    #endif

    // Forward iterator
    {
        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({1, 2, 3});

            auto res = vec.insert(vec.nth(0), data.begin(), data.end());

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) ==  1);
            CHECK(*vec.nth(1) ==  2);
            CHECK(*vec.nth(2) ==  3);
            CHECK(*vec.nth(3) == 10);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({11, 12, 13});

            auto res = vec.insert(vec.nth(1), data.begin(), data.end());

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 11);
            CHECK(*vec.nth(2) == 12);
            CHECK(*vec.nth(3) == 13);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({21, 22, 23});

            auto res = vec.insert(vec.nth(2), data.begin(), data.end());

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 21);
            CHECK(*vec.nth(3) == 22);
            CHECK(*vec.nth(4) == 23);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({31, 32, 33});

            auto res = vec.insert(vec.nth(3), data.begin(), data.end());

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 31);
            CHECK(*vec.nth(4) == 32);
            CHECK(*vec.nth(5) == 33);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({41, 42, 43});

            auto res = vec.insert(vec.nth(4), data.begin(), data.end());

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 41);
            CHECK(*vec.nth(5) == 42);
            CHECK(*vec.nth(6) == 43);
            CHECK(*vec.nth(7) == 50);
        }

        {
            vector_type vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<T> data({51, 52, 53});

            auto res = vec.insert(vec.nth(5), data.begin(), data.end());

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 51);
            CHECK(*vec.nth(6) == 52);
            CHECK(*vec.nth(7) == 53);
        }
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, std::initializer_list)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{1, 2, 3};

        auto res = vec.insert(vec.nth(0), ilist);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) ==  1);
        CHECK(*vec.nth(1) ==  2);
        CHECK(*vec.nth(2) ==  3);
        CHECK(*vec.nth(3) == 10);
        CHECK(*vec.nth(4) == 20);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{11, 12, 13};

        auto res = vec.insert(vec.nth(1), ilist);

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 11);
        CHECK(*vec.nth(2) == 12);
        CHECK(*vec.nth(3) == 13);
        CHECK(*vec.nth(4) == 20);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{21, 22, 23};

        auto res = vec.insert(vec.nth(2), ilist);

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 21);
        CHECK(*vec.nth(3) == 22);
        CHECK(*vec.nth(4) == 23);
        CHECK(*vec.nth(5) == 30);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{31, 32, 33};

        auto res = vec.insert(vec.nth(3), ilist);

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 31);
        CHECK(*vec.nth(4) == 32);
        CHECK(*vec.nth(5) == 33);
        CHECK(*vec.nth(6) == 40);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{41, 42, 43};

        auto res = vec.insert(vec.nth(4), ilist);

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 41);
        CHECK(*vec.nth(5) == 42);
        CHECK(*vec.nth(6) == 43);
        CHECK(*vec.nth(7) == 50);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<T> ilist{51, 52, 53};

        auto res = vec.insert(vec.nth(5), ilist);

        CHECK(res == vec.nth(5));
        CHECK(vec.size() == 8);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 92);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 51);
        CHECK(*vec.nth(6) == 52);
        CHECK(*vec.nth(7) == 53);
    }
}
END_TEST()

BEGIN_TEST("Test insert(const_iterator, Range&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(60);

        std::istringstream iss("20 30 40 50");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.insert_range(vec.nth(1), std::views::istream<int>(iss));
        #else
        vec.insert_range(vec.nth(1), sfl::test::istream_view<int>(iss));
        #endif

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
    #endif

    // Forward iterator
    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(60);

        std::vector<T> data({20, 30, 40, 50});

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.insert_range(vec.nth(1), std::views::all(data));
        #else
        vec.insert_range(vec.nth(1), data);
        #endif

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
}
END_TEST()

BEGIN_TEST("Test push_back(const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    T value_10(10);

    vec.push_back(value_10);

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == 10);
}
END_TEST()

BEGIN_TEST("Test push_back(T&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    T value_10(10);

    vec.push_back(std::move(value_10));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    #ifndef TEST_CPP20_CONSTEXPR
    CHECK(value_10 == -10);
    #else
    CHECK(value_10 == 10);
    #endif
}
END_TEST()

BEGIN_TEST("Test append_range(Range&&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Input iterator (exactly)
    #ifndef TEST_CPP20_CONSTEXPR
    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);

        std::istringstream iss("30 40 50 60");

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.append_range(std::views::istream<int>(iss));
        #else
        vec.append_range(sfl::test::istream_view<int>(iss));
        #endif

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
    #endif

    // Forward iterator
    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);

        std::vector<T> data({30, 40, 50, 60});

        #if SFL_CPP_VERSION >= SFL_CPP_20
        vec.append_range(std::views::all(data));
        #else
        vec.append_range(data);
        #endif

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
}
END_TEST()

BEGIN_TEST("Test pop_back()")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    ///////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);

    ///////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);

    ///////////////////////////////////////////////////////////////////////

    vec.pop_back();

    CHECK(vec.size() == 0);
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    {
        vector_type vec;

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

        auto res = vec.erase(vec.nth(0));

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 20);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        vector_type vec;

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

        auto res = vec.erase(vec.nth(1));

        CHECK(res == vec.nth(1));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        vector_type vec;

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

        auto res = vec.erase(vec.nth(2));

        CHECK(res == vec.nth(2));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        vector_type vec;

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

        auto res = vec.erase(vec.nth(3));

        CHECK(res == vec.nth(3));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 50);
    }

    {
        vector_type vec;

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

        auto res = vec.erase(vec.nth(4));

        CHECK(res == vec.nth(4));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
}
END_TEST()

BEGIN_TEST("Test erase(const_iterator, const_iterator)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    {
        vector_type vec;

        CHECK(vec.size() == 0);

        CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
        CHECK(vec.erase(vec.nth(1), vec.nth(1)) == vec.nth(1));
        CHECK(vec.erase(vec.nth(2), vec.nth(2)) == vec.nth(2));
        CHECK(vec.erase(vec.nth(3), vec.nth(3)) == vec.nth(3));
        CHECK(vec.erase(vec.nth(4), vec.nth(4)) == vec.nth(4));
        CHECK(vec.erase(vec.nth(5), vec.nth(5)) == vec.nth(5));
        CHECK(vec.erase(vec.nth(6), vec.nth(6)) == vec.nth(6));
        CHECK(vec.erase(vec.nth(7), vec.nth(7)) == vec.nth(7));
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(0), vec.nth(3)) == vec.nth(0));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(1), vec.nth(4)) == vec.nth(1));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(2), vec.nth(5)) == vec.nth(2));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(3), vec.nth(6)) == vec.nth(3));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 70);
    }

    {
        vector_type vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);
        vec.emplace(vec.end(), 60);
        vec.emplace(vec.end(), 70);

        CHECK(vec.size() == 7);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
        CHECK(*vec.nth(6) == 70);

        CHECK(vec.erase(vec.nth(4), vec.nth(7)) == vec.nth(4));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
}
END_TEST()

BEGIN_TEST("Test resize(size_type)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION n < vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 96);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            #ifndef TEST_CPP20_CONSTEXPR
            CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            #else
            CHECK(*vec.nth(i) == 0);
            #endif
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        vec.resize(n);

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            #ifndef TEST_CPP20_CONSTEXPR
            CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            #else
            CHECK(*vec.nth(i) == 0);
            #endif
        }
    }
    #undef CONDITION
}
END_TEST()

BEGIN_TEST("Test resize(size_type, sfl::default_init_t)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION n < vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        vec.resize(n, sfl::default_init_t());

        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 96);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        vec.resize(n, sfl::default_init_t());

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        vec.resize(n, sfl::default_init_t());

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            #ifndef TEST_CPP20_CONSTEXPR
            CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            #else
            // *vec.nth(i) is undetermined
            #endif
        }
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        vec.resize(n, sfl::default_init_t());

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 0);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        for (size_type i = 5; i < n; ++i)
        {
            #ifndef TEST_CPP20_CONSTEXPR
            CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            #else
            // *vec.nth(i) is undetermined
            #endif
        }
    }
    #undef CONDITION
}
END_TEST()

BEGIN_TEST("Test resize(size_type, const T&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    #define CONDITION n < vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size() - 1;

        CHECK(CONDITION);

        const T value(12345);

        vec.resize(n, value);

        CHECK(vec.size() == 4);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 96);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }
    #undef CONDITION

    #define CONDITION n == vec.size()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.size();

        CHECK(CONDITION);

        const T value(12345);

        vec.resize(n, value);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }
    #undef CONDITION

    #define CONDITION n > vec.size() && n < vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity() - 1;

        CHECK(CONDITION);

        const T value(12345);

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 1);
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

    #define CONDITION n > vec.size() && n == vec.capacity()
    {
        vector_type vec;

        using size_type = typename vector_type::size_type;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);
        vec.emplace_back(40);
        vec.emplace_back(50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 95);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        const size_type n = vec.capacity();

        CHECK(CONDITION);

        const T value(12345);

        vec.resize(n, value);

        CHECK(vec.size() == n);
        CHECK(vec.capacity() == 100);
        CHECK(vec.available() == 0);
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
END_TEST()

BEGIN_TEST("Test swap(container&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    // Swap with self
    {
        vector_type vec;

        vec.emplace_back(10);
        vec.emplace_back(20);
        vec.emplace_back(30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////

        vec.swap(vec);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    // vec1.size() == vec2.size()
    {
        vector_type vec1, vec2;

        vec1.emplace_back(10);
        vec1.emplace_back(20);
        vec1.emplace_back(30);

        vec2.emplace_back(40);
        vec2.emplace_back(50);
        vec2.emplace_back(60);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);

        ///////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
    }

    // vec1.size() != vec2.size()
    {
        vector_type vec1, vec2;

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

        ///////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

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

        ///////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

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
    }
}
END_TEST()

BEGIN_TEST("Test at(size_type)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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

    #ifndef TEST_CPP20_CONSTEXPR
    #ifndef SFL_NO_EXCEPTIONS
    bool caught_exception = false;

    try
    {
        vec.at(3) = 1;
    }
    catch (...)
    {
        caught_exception = true;
    }

    CHECK(caught_exception == true);
    #endif
    #endif

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);
}
END_TEST()

BEGIN_TEST("Test operator[](size_type)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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
END_TEST()

BEGIN_TEST("Test front() and back()")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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
END_TEST()

BEGIN_TEST("Test data()")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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
END_TEST()

BEGIN_TEST("Test NON-MEMBER comparison operators")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec1, vec2;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    vec2.emplace(vec2.end(), 10);
    vec2.emplace(vec2.end(), 20);
    vec2.emplace(vec2.end(), 30);
    vec2.emplace(vec2.end(), 40);
    vec2.emplace(vec2.end(), 50);

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
END_TEST()

BEGIN_TEST("Test NON-MEMBER swap(container&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec1, vec2;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    vec2.emplace(vec2.end(), 40);
    vec2.emplace(vec2.end(), 50);
    vec2.emplace(vec2.end(), 60);
    vec2.emplace(vec2.end(), 70);
    vec2.emplace(vec2.end(), 80);

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

    ///////////////////////////////////////////////////////////////////////

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
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase(container&, const U&)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    vector_type vec;

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

    ///////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_TEST()

BEGIN_TEST("Test NON-MEMBER erase_if(container&, Predicate)")
{
    #ifndef TEST_CPP20_CONSTEXPR
    using T = xint;
    #else
    using T = int;
    #endif
    constexpr std::size_t N = 100;
    using vector_type = sfl::static_vector<T, N>;

    using const_reference = typename vector_type::const_reference;

    ///////////////////////////////////////////////////////////////////////

    vector_type vec;

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

    ///////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
END_TEST()

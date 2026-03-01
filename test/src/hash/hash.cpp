#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/hash.hpp"

#include "check.hpp"

SFL_CONSTEXPR_20
bool test()
{
    {
        sfl::hash<bool> h;
        CHECK(h(true) != h(false));
    }

    {
        sfl::hash<char> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<signed char> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<unsigned char> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<wchar_t> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    #if SFL_CPP_VERSION >= SFL_CPP_20
    {
        sfl::hash<char8_t> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }
    #endif

    {
        sfl::hash<char16_t> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<char32_t> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<short> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<unsigned short> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<int> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<unsigned int> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<long> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<unsigned long> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<long long> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<unsigned long long> h;
        CHECK(h(11) == static_cast<std::size_t>(11));
        CHECK(h(99) == static_cast<std::size_t>(99));
    }

    {
        sfl::hash<float> h;
        CHECK(h(3.0f) != h(3.14f));
        CHECK(h(3.14f) != h(3.1415f));
        CHECK(h(3.1415f) != h(3.141592f));
    }

    {
        sfl::hash<double> h;
        CHECK(h(3.0) != h(3.14));
        CHECK(h(3.14) != h(3.1415));
        CHECK(h(3.1415) != h(3.141592));
    }

    #if !defined(__clang__)
    {
        sfl::hash<long double> h;
        CHECK(h(3.0l) != h(3.14l));
        CHECK(h(3.14l) != h(3.1415l));
        CHECK(h(3.1415l) != h(3.141592l));
    }
    #endif

    return true;
}

int main()
{
    test();
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test());
#endif

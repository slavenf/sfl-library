#undef NDEBUG // This is very important. Must be in the first line.

#include <sfl/detail/utility/compressed_pair.hpp>

#include "check.hpp"

SFL_CONSTEXPR_20
bool test1()
{
    sfl::dtl::compressed_pair<int, int> cp1(111, 222), cp2(333, 444);

    CHECK(cp1.first() == 111);
    CHECK(cp1.second() == 222);

    CHECK(cp2.first() == 333);
    CHECK(cp2.second() == 444);

    swap(cp1, cp2);

    CHECK(cp1.first() == 333);
    CHECK(cp1.second() == 444);

    CHECK(cp2.first() == 111);
    CHECK(cp2.second() == 222);

    return true;
}

SFL_CONSTEXPR_20
bool test2()
{
    struct S
    {
    private:

        int value_;

    public:

        SFL_CONSTEXPR_20
        S(int value) : value_(value)
        {}

        SFL_CONSTEXPR_20
        S(const S& other) : value_(other.value_)
        {}

        SFL_CONSTEXPR_20
        S& operator=(const S& other)
        {
            value_ = other.value_;
            return *this;
        }

        SFL_CONSTEXPR_20
        int value() const
        {
            return value_;
        }
    };

    sfl::dtl::compressed_pair<S, S> cp1(111, 222), cp2(333, 444);

    CHECK(cp1.first().value() == 111);
    CHECK(cp1.second().value() == 222);

    CHECK(cp2.first().value() == 333);
    CHECK(cp2.second().value() == 444);

    swap(cp1, cp2);

    CHECK(cp1.first().value() == 333);
    CHECK(cp1.second().value() == 444);

    CHECK(cp2.first().value() == 111);
    CHECK(cp2.second().value() == 222);

    return true;
}

int main()
{
    CHECK(test1());
    CHECK(test2());
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test1());
static_assert(test2());
#endif

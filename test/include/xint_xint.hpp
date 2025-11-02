#ifndef SFL_TEST_XINT_XINT_HPP
#define SFL_TEST_XINT_XINT_HPP

#include "xint.hpp"

#include <iosfwd>

namespace sfl
{

namespace test
{

class xint_xint
{
public:

    xint first;
    xint second;

public:

    SFL_CONSTEXPR_20
    xint_xint()
        : first()
        , second()
    {}

    SFL_CONSTEXPR_20
    xint_xint(int first_, int second_)
        : first(first_)
        , second(second_)
    {}

    SFL_CONSTEXPR_20
    xint_xint(const xint_xint& other)
        : first(other.first)
        , second(other.second)
    {}

    SFL_CONSTEXPR_20
    xint_xint(xint_xint&& other)
        : first(std::move(other.first))
        , second(std::move(other.second))
    {}

    SFL_CONSTEXPR_20
    xint_xint& operator=(const xint_xint& other)
    {
        first  = other.first;
        second = other.second;
        return *this;
    }

    SFL_CONSTEXPR_20
    xint_xint& operator=(xint_xint&& other)
    {
        first  = std::move(other.first);
        second = std::move(other.second);
        return *this;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(const xint_xint& x, const xint_xint& y)
    {
        return x.first == y.first;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(const xint_xint& x, int y)
    {
        return x.first == y;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(int x, const xint_xint& y)
    {
        return x == y.first;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(const xint_xint& x, const xint_xint& y)
    {
        return x.first < y.first;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(const xint_xint& x, int y)
    {
        return x.first < y;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(int x, const xint_xint& y)
    {
        return x < y.first;
    }
};

} // namespace test

} // namespace sfl

namespace std
{

template <>
struct hash<sfl::test::xint_xint>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(const sfl::test::xint_xint& x)
    {
        return static_cast<std::size_t>(x.first.value());
    }
};

istream& operator>>(istream& is, sfl::test::xint_xint& x)
{
    return is >> x.first >> x.second;
}

} // namespace std

#endif // SFL_TEST_XINT_XINT_HPP

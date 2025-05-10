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

    xint_xint()
        : first()
        , second()
    {}

    xint_xint(int first_, int second_)
        : first(first_)
        , second(second_)
    {}

    xint_xint(const xint_xint& other)
        : first(other.first)
        , second(other.second)
    {}

    xint_xint(xint_xint&& other)
        : first(std::move(other.first))
        , second(std::move(other.second))
    {}

    xint_xint& operator=(const xint_xint& other)
    {
        first  = other.first;
        second = other.second;
        return *this;
    }

    xint_xint& operator=(xint_xint&& other)
    {
        first  = std::move(other.first);
        second = std::move(other.second);
        return *this;
    }

    friend bool operator==(const xint_xint& x, const xint_xint& y)
    {
        return x.first == y.first;
    }

    friend bool operator==(const xint_xint& x, int y)
    {
        return x.first == y;
    }

    friend bool operator==(int x, const xint_xint& y)
    {
        return x == y.first;
    }

    friend bool operator<(const xint_xint& x, const xint_xint& y)
    {
        return x.first < y.first;
    }

    friend bool operator<(const xint_xint& x, int y)
    {
        return x.first < y;
    }

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

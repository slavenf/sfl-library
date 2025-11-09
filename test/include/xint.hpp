#ifndef SFL_TEST_XINT_HPP
#define SFL_TEST_XINT_HPP

#include <sfl/detail/cpp.hpp>

#include "hash.hpp"
#include "print.hpp"

#include <iosfwd>

#define SFL_TEST_XINT_DEFAULT_VALUE 789456123

namespace sfl
{

namespace test
{

class xint
{
    template <typename>
    friend struct std::hash;

    template <typename>
    friend struct hash;

private:

    int* value_;

public:

    SFL_CONSTEXPR_20
    xint() noexcept
    {
        value_ = new int(SFL_TEST_XINT_DEFAULT_VALUE);

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::xint() [value = " << *value_ << "]");
        }
        #endif
    }

    SFL_CONSTEXPR_20
    xint(int value) noexcept
    {
        value_ = new int(value);

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::xint(int) [value = " << *value_ << "]");
        }
        #endif
    }

    SFL_CONSTEXPR_20
    xint(const xint& other) noexcept
    {
        value_ = new int(*other.value_);

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::xint(const xint&) [value = " << *value_ << "]");
        }
        #endif
    }

    SFL_CONSTEXPR_20
    xint(xint&& other) noexcept
    {
        value_ = new int(*other.value_);
        *other.value_ = -*other.value_;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::xint(xint&&) [value = " << *value_ << "]");
        }
        #endif
    }

    SFL_CONSTEXPR_20
    xint& operator=(const xint& other) noexcept
    {
        *value_ = *other.value_;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::operator=(const xint&) [value = " << *value_ << "]");
        }
        #endif

        return *this;
    }

    SFL_CONSTEXPR_20
    xint& operator=(xint&& other) noexcept
    {
        *value_ = *other.value_;
        *other.value_ = -*other.value_;

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::operator=(xint&&) [value = " << *value_ << "]");
        }
        #endif

        return *this;
    }

    SFL_CONSTEXPR_20
    ~xint()
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (!std::is_constant_evaluated())
        {
            PRINT("  ++ xint::~xint() [value = " << *value_ << "]");
        }
        #endif

        delete value_;
    }

    SFL_CONSTEXPR_20
    int value() const
    {
        return *value_;
    }

    SFL_CONSTEXPR_20
    int& value()
    {
        return *value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(const xint& x, const xint& y)
    {
        return *x.value_ == *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(int x, const xint& y)
    {
        return x == *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator==(const xint& x, int y)
    {
        return *x.value_ == y;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(const xint& x, const xint& y)
    {
        return *x.value_ < *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(int x, const xint& y)
    {
        return x < *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator<(const xint& x, int y)
    {
        return *x.value_ < y;
    }

    SFL_CONSTEXPR_20
    friend bool operator<=(const xint& x, const xint& y)
    {
        return *x.value_ <= *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator<=(int x, const xint& y)
    {
        return x <= *y.value_;
    }

    SFL_CONSTEXPR_20
    friend bool operator<=(const xint& x, int y)
    {
        return *x.value_ <= y;
    }
};

template <>
struct hash<xint>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(const xint& x) const
    {
        return static_cast<std::size_t>(*x.value_);
    }
};

} // namespace test

} // namespace sfl

namespace std
{

template <>
struct hash<sfl::test::xint>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(const sfl::test::xint& x) const
    {
        return static_cast<std::size_t>(*x.value_);
    }
};

istream& operator>>(istream& is, sfl::test::xint& x)
{
    return is >> x.value();
}

} // namespace std

#endif // SFL_TEST_XINT_HPP

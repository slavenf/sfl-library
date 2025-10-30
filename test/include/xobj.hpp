#ifndef SFL_TEST_XOBJ_HPP
#define SFL_TEST_XOBJ_HPP

#include <sfl/detail/cpp.hpp>

namespace sfl
{

namespace test
{

class xobj
{
private:

    int* value_;

public:

    SFL_CONSTEXPR_20
    explicit xobj(int value) noexcept
    {
        value_ = new int(value);
    }

    SFL_CONSTEXPR_20
    xobj(const xobj& other) noexcept
    {
        value_ = new int(*other.value_);
    }

    SFL_CONSTEXPR_20
    xobj(xobj&& other) noexcept
    {
        value_ = new int(*other.value_);
        *other.value_ = -*other.value_;
    }

    SFL_CONSTEXPR_20
    xobj& operator=(const xobj& other) noexcept
    {
        *value_ = *other.value_;
        return *this;
    }

    SFL_CONSTEXPR_20
    xobj& operator=(xobj&& other) noexcept
    {
        *value_ = *other.value_;
        *other.value_ = -*other.value_;
        return *this;
    }

    SFL_CONSTEXPR_20
    ~xobj()
    {
        delete value_;
    }

    SFL_CONSTEXPR_20
    int value() const
    {
        return *value_;
    }

public:

    struct less
    {
        using is_transparent = void;

        SFL_CONSTEXPR_20
        bool operator()(const xobj& a, const xobj& b) const
        {
            return a.value() < b.value();
        }

        SFL_CONSTEXPR_20
        bool operator()(const xobj& a, int b) const
        {
            return a.value() < b;
        }

        SFL_CONSTEXPR_20
        bool operator()(int a, const xobj& b) const
        {
            return a < b.value();
        }
    };

    struct equal
    {
        using is_transparent = void;

        SFL_CONSTEXPR_20
        bool operator()(const xobj& a, const xobj& b) const
        {
            return a.value() == b.value();
        }

        SFL_CONSTEXPR_20
        bool operator()(const xobj& a, int b) const
        {
            return a.value() == b;
        }

        SFL_CONSTEXPR_20
        bool operator()(int a, const xobj& b) const
        {
            return a == b.value();
        }
    };

    struct hash
    {
        using is_transparent = void;

        SFL_CONSTEXPR_20
        std::size_t operator()(const xobj& x) const
        {
            return x.value();
        }

        SFL_CONSTEXPR_20
        std::size_t operator()(int x) const
        {
            return x;
        }
    };
};

} // namespace test

} // namespace sfl

#endif // SFL_TEST_XOBJ_HPP

#ifndef SFL_XINT_HPP
#define SFL_XINT_HPP

#include <iostream>
#include <functional>

#define SFL_MY_INT_DEFAULT_VALUE 999

namespace sfl
{
namespace test
{

class xint
{
private:

    static int counter_;
    int* value_;

public:

    xint() noexcept
    {
        ++counter_;
        value_ = new int(SFL_MY_INT_DEFAULT_VALUE);
        std::cout << "  ++ xint::xint() [value = " << *value_ << "]\n";
    }

    xint(int value) noexcept
    {
        ++counter_;
        value_ = new int(value);
        std::cout << "  ++ xint::xint(int) [value = " << *value_ << "]\n";
    }

    xint(const xint& other) noexcept
    {
        ++counter_;
        value_ = new int(*other.value_);
        std::cout << "  ++ xint::xint(const xint&) [value = " << *value_ << "]\n";
    }

    xint(xint&& other) noexcept
    {
        ++counter_;
        value_ = new int(*other.value_);
        *other.value_ = -(*other.value_);
        std::cout << "  ++ xint::xint(xint&&) [value = " << *value_ << "]\n";
    }

    xint& operator=(const xint& other) noexcept
    {
        *value_ = *other.value_;
        std::cout << "  ++ xint::operator=(const xint&) [value = " << *value_ << "]\n";
        return *this;
    }

    xint& operator=(xint&& other) noexcept
    {
        *value_ = *other.value_;
        *other.value_ = -(*other.value_);
        std::cout << "  ++ xint::operator=(xint&&) [value = " << *value_ << "]\n";
        return *this;
    }

    ~xint()
    {
        std::cout << "  ++ xint::~xint() [value = " << *value_ << "]\n";
        delete value_;

        --counter_;

        if (counter_ < 0)
        {
            std::cout << "ERROR: xint::~xint(): counter = " << counter_ << " < 0.\n";
            std::abort();
        }
    }

    int value() const
    {
        return *value_;
    }
};

int xint::counter_ = 0;

bool operator==(const xint& x, const xint& y)
{
    return x.value() == y.value();
}

bool operator==(int x, const xint& y)
{
    return x == y.value();
}

bool operator==(const xint& x, int y)
{
    return x.value() == y;
}

bool operator<(const xint& x, const xint& y)
{
    return x.value() < y.value();
}

bool operator<(int x, const xint& y)
{
    return x < y.value();
}

bool operator<(const xint& x, int y)
{
    return x.value() < y;
}

std::ostream& operator<<(std::ostream& os, const xint& x)
{
    return os << x.value();
}

} // namespace test
} // namespace sfl

#endif // SFL_XINT_HPP

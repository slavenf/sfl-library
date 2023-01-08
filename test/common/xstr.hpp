#ifndef SFL_XSTR_HPP
#define SFL_XSTR_HPP

#include <iostream>
#include <string>

namespace sfl
{
namespace test
{

class xstr
{
private:

    static int counter_;
    std::string value_;

public:
    xstr() noexcept
    {
        ++counter_;
        std::cout << "  ++ xstr::xstr() [value = `" << value_ << "`]\n";
    }

    xstr(const char* s) noexcept
    {
        ++counter_;
        value_ = s;
        std::cout << "  ++ xstr::xstr(const char*) [value = `" << value_ << "`]\n";
    }

    xstr(const xstr& other) noexcept
    {
        ++counter_;
        value_ = other.value_;
        std::cout << "  ++ xstr::xstr(const xstr&) [value = `" << value_ << "`]\n";
    }

    xstr(xstr&& other) noexcept
    {
        ++counter_;
        value_ = other.value_;
        other.value_.clear();
        std::cout << "  ++ xstr::xstr(xstr&&) [value = `" << value_ << "`]\n";
    }

    xstr& operator=(const xstr& other) noexcept
    {
        value_ = other.value_;
        std::cout << "  ++ xstr::operator=(const xstr&) [value = `" << value_ << "`]\n";
        return *this;
    }

    xstr& operator=(xstr&& other) noexcept
    {
        value_ = other.value_;
        other.value_.clear();
        std::cout << "  ++ xstr::operator=(xstr&&) [value = `" << value_ << "`]\n";
        return *this;
    }

    ~xstr()
    {
        std::cout << "  ++ xstr::~xstr() [value = `" << value_ << "`]\n";

        --counter_;

        if (counter_ < 0)
        {
            std::cout << "ERROR: xstr::~xstr(): counter = " << counter_ << " < 0.\n";
            std::abort();
        }
    }

    const std::string& value() const
    {
        return value_;
    }
};

int xstr::counter_ = 0;

bool operator==(const xstr& x, const xstr& y)
{
    return x.value() == y.value();
}

bool operator==(const char* x, const xstr& y)
{
    return x == y.value();
}

bool operator==(const xstr& x, const char* y)
{
    return x.value() == y;
}

bool operator<(const xstr& x, const xstr& y)
{
    return x.value() < y.value();
}

bool operator<(const char* x, const xstr& y)
{
    return x < y.value();
}

bool operator<(const xstr& x, const char* y)
{
    return x.value() < y;
}

std::ostream& operator<<(std::ostream& os, const xstr& x)
{
    return os << x.value();
}

} // namespace test
} // namespace sfl

#endif // SFL_XSTR_HPP

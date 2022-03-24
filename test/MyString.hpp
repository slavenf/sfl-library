#ifndef SFL_MY_STRING_HPP
#define SFL_MY_STRING_HPP

#include <iostream>
#include <string>

class MyString
{
private:

    static int counter_;
    std::string value_;

public:
    MyString() noexcept
    {
        ++counter_;
        std::cout << "  ++ MyString::MyString() [value = `" << value_ << "`]\n";
    }

    MyString(const char* s) noexcept
    {
        ++counter_;
        value_ = s;
        std::cout << "  ++ MyString::MyString(const char*) [value = `" << value_ << "`]\n";
    }

    MyString(const MyString& other) noexcept
    {
        ++counter_;
        value_ = other.value_;
        std::cout << "  ++ MyString::MyString(const MyString&) [value = `" << value_ << "`]\n";
    }

    MyString(MyString&& other) noexcept
    {
        ++counter_;
        value_ = other.value_;
        other.value_.clear();
        std::cout << "  ++ MyString::MyString(MyString&&) [value = `" << value_ << "`]\n";
    }

    MyString& operator=(const MyString& other) noexcept
    {
        value_ = other.value_;
        std::cout << "  ++ MyString::operator=(const MyString&) [value = `" << value_ << "`]\n";
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept
    {
        value_ = other.value_;
        other.value_.clear();
        std::cout << "  ++ MyString::operator=(MyString&&) [value = `" << value_ << "`]\n";
        return *this;
    }

    ~MyString()
    {
        std::cout << "  ++ MyString::~MyString() [value = `" << value_ << "`]\n";

        --counter_;

        if (counter_ < 0)
        {
            std::cout << "ERROR: MyString::~MyString(): counter = " << counter_ << " < 0.\n";
            std::abort();
        }
    }

    const std::string& value() const
    {
        return value_;
    }
};

int MyString::counter_ = 0;

bool operator==(const MyString& x, const MyString& y)
{
    return x.value() == y.value();
}

bool operator==(const char* x, const MyString& y)
{
    return x == y.value();
}

bool operator==(const MyString& x, const char* y)
{
    return x.value() == y;
}

bool operator<(const MyString& x, const MyString& y)
{
    return x.value() < y.value();
}

bool operator<(const char* x, const MyString& y)
{
    return x < y.value();
}

bool operator<(const MyString& x, const char* y)
{
    return x.value() < y;
}

std::ostream& operator<<(std::ostream& os, const MyString& x)
{
    return os << x.value();
}

#endif // SFL_MY_STRING_HPP

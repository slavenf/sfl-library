#ifndef SFL_MY_INT_HPP
#define SFL_MY_INT_HPP

#include <iostream>
#include <functional>

#define SFL_MY_INT_DEFAULT_VALUE 999

class MyInt
{
private:

    static int counter_;
    int* value_;

public:

    MyInt() noexcept
    {
        ++counter_;
        value_ = new int(SFL_MY_INT_DEFAULT_VALUE);
        std::cout << "  ++ MyInt::MyInt() [value = " << *value_ << "]\n";
    }

    MyInt(int value) noexcept
    {
        ++counter_;
        value_ = new int(value);
        std::cout << "  ++ MyInt::MyInt(int) [value = " << *value_ << "]\n";
    }

    MyInt(const MyInt& other) noexcept
    {
        ++counter_;
        value_ = new int(*other.value_);
        std::cout << "  ++ MyInt::MyInt(const MyInt&) [value = " << *value_ << "]\n";
    }

    MyInt(MyInt&& other) noexcept
    {
        ++counter_;
        value_ = new int(*other.value_);
        *other.value_ = -(*other.value_);
        std::cout << "  ++ MyInt::MyInt(MyInt&&) [value = " << *value_ << "]\n";
    }

    MyInt& operator=(const MyInt& other) noexcept
    {
        *value_ = *other.value_;
        std::cout << "  ++ MyInt::operator=(const MyInt&) [value = " << *value_ << "]\n";
        return *this;
    }

    MyInt& operator=(MyInt&& other) noexcept
    {
        *value_ = *other.value_;
        *other.value_ = -(*other.value_);
        std::cout << "  ++ MyInt::operator=(MyInt&&) [value = " << *value_ << "]\n";
        return *this;
    }

    ~MyInt()
    {
        std::cout << "  ++ MyInt::~MyInt() [value = " << *value_ << "]\n";
        delete value_;

        --counter_;

        if (counter_ < 0)
        {
            std::cout << "ERROR: MyInt::~MyInt(): counter = " << counter_ << " < 0.\n";
            std::abort();
        }
    }

    int value() const
    {
        return *value_;
    }
};

int MyInt::counter_ = 0;

bool operator==(const MyInt& x, const MyInt& y)
{
    return x.value() == y.value();
}

bool operator==(int x, const MyInt& y)
{
    return x == y.value();
}

bool operator==(const MyInt& x, int y)
{
    return x.value() == y;
}

bool operator<(const MyInt& x, const MyInt& y)
{
    return x.value() < y.value();
}

bool operator<(int x, const MyInt& y)
{
    return x < y.value();
}

bool operator<(const MyInt& x, int y)
{
    return x.value() < y;
}

std::ostream& operator<<(std::ostream& os, const MyInt& x)
{
    return os << x.value();
}

#endif // SFL_MY_INT_HPP

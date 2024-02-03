#ifndef SFL_TEST_FANCY_PTR_HPP
#define SFL_TEST_FANCY_PTR_HPP

#include <cstddef>

namespace sfl
{
namespace test
{

template <typename T>
class fancy_ptr
{
private:

    T* ptr_;

public:

    using element_type      = T;
    using difference_type   = std::ptrdiff_t;
    using value_type        = element_type;
    using pointer           = element_type*;
    using reference         = element_type&;
    using iterator_category = std::random_access_iterator_tag;

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

private:

    fancy_ptr(T *ptr, bool /*dummy*/) noexcept
        : ptr_(ptr)
    {};

public:

    static fancy_ptr pointer_to(element_type &r) noexcept
    {
        return fancy_ptr(&r, false);
    }

    fancy_ptr() noexcept
    {}

    fancy_ptr(std::nullptr_t) noexcept
        : ptr_(nullptr)
    {}

    fancy_ptr(const fancy_ptr& other) noexcept
        : ptr_(other.ptr_)
    {}

    template <typename U = T, typename std::enable_if<std::is_const<U>::value>::type* = nullptr>
    fancy_ptr(const fancy_ptr<typename std::remove_const<T>::type>& other) noexcept
        : ptr_(other.operator->()  /* std::to_address(other) in C++20 */)
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    fancy_ptr& operator=(std::nullptr_t) noexcept
    {
        ptr_ = nullptr;
        return *this;
    }

    fancy_ptr& operator=(const fancy_ptr& other) noexcept
    {
        ptr_ = other.ptr_;
        return *this;
    }

    //
    // ---- OBSERVERS ---------------------------------------------------------
    //

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    reference operator*() const noexcept
    {
        return *ptr_;
    }

    reference operator[](difference_type n) const noexcept
    {
        return *(ptr_ + n);
    }

    pointer operator->() const noexcept
    {
        return ptr_;
    }

    //
    // ---- INCREMENT AND DECREMENT -------------------------------------------
    //

    fancy_ptr& operator++() noexcept
    {
        ++ptr_;
        return *this;
    }

    fancy_ptr operator++(int) noexcept
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    fancy_ptr& operator--() noexcept
    {
        --ptr_;
        return *this;
    }

    fancy_ptr operator--(int) noexcept
    {
        auto temp = *this;
        --(*this);
        return temp;
    }

    fancy_ptr& operator+=(difference_type n) noexcept
    {
        ptr_ += n;
        return *this;
    }

    fancy_ptr& operator-=(difference_type n) noexcept
    {
        ptr_ -= n;
        return *this;
    }

    friend
    fancy_ptr operator+(const fancy_ptr& p, difference_type n) noexcept
    {
        auto temp = p;
        temp += n;
        return temp;
    }

    friend
    fancy_ptr operator-(const fancy_ptr& p, difference_type n) noexcept
    {
        auto temp = p;
        temp -= n;
        return temp;
    }

    friend
    difference_type operator-(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return x.ptr_ - y.ptr_;
    }

    //
    // ---- COMPARISONS -------------------------------------------------------
    //

    friend
    bool operator==(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return x.ptr_ == y.ptr_;
    }

    friend
    bool operator!=(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return !(x == y);
    }

    friend
    bool operator<(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return x.ptr_ < y.ptr_;
    }

    friend
    bool operator>(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return y < x;
    }

    friend
    bool operator<=(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return !(y < x);
    }

    friend
    bool operator>=(const fancy_ptr& x, const fancy_ptr& y) noexcept
    {
        return !(x < y);
    }
};

} // namespace test
} // namespace sfl

#endif // SFL_TEST_FANCY_PTR_HPP

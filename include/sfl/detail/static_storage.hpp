//
// Copyright (c) 2022 Slaven Falandys
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SFL_DETAIL_STATIC_STORAGE_HPP_INCLUDED
#define SFL_DETAIL_STATIC_STORAGE_HPP_INCLUDED

#include <sfl/detail/memory/to_address.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/cpp.hpp>

#include <algorithm> // copy, fill, move, move_backward
#include <cstddef> // size_t, nullptrt_t, ptrdiff_t
#include <iterator> // random_access_iterator_tag
#include <memory> // addressof
#include <type_traits> // add_lvalue_reference, is_constant_evaluated, remove_cv

namespace sfl
{

namespace dtl
{

#if SFL_CPP_VERSION >= SFL_CPP_20

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STATIC STORAGE BUCKET
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
union static_storage_bucket
{
    T value_;

    SFL_CONSTEXPR_20
    static_storage_bucket() noexcept
    {}

    SFL_CONSTEXPR_20
    ~static_storage_bucket()
    {}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STATIC STORAGE POINTER
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
class static_storage_pointer
{
    template <typename>
    friend class static_storage_pointer;

public:

    using element_type = T;

    using difference_type = std::ptrdiff_t;

    using value_type = typename std::remove_cv<T>::type;

    using pointer = typename std::add_pointer<T>::type;

    using reference = typename std::add_lvalue_reference<T>::type;

    using iterator_category = std::random_access_iterator_tag;

    #if SFL_CPP_VERSION >= SFL_CPP_20
    using iterator_concept = std::contiguous_iterator_tag;
    #endif

private:

    sfl::dtl::static_storage_bucket<value_type>* ptr_;

public:

    // Default constructor
    SFL_CONSTEXPR_20
    static_storage_pointer() noexcept
    {}

    // Construct from null pointer
    SFL_CONSTEXPR_20
    static_storage_pointer(std::nullptr_t) noexcept
        : ptr_(nullptr)
    {}

    // Construct from raw pointer to bucket
    SFL_CONSTEXPR_20
    static_storage_pointer(sfl::dtl::static_storage_bucket<value_type>* ptr) noexcept
        : ptr_(ptr)
    {}

    // Construct from raw pointer to const bucket
    SFL_CONSTEXPR_20
    static_storage_pointer(const sfl::dtl::static_storage_bucket<value_type>* ptr) noexcept
        : ptr_(const_cast<sfl::dtl::static_storage_bucket<value_type>*>(ptr))
    {}

    // Converting constructor from pointer to const_pointer
    template <typename U = T,
              sfl::dtl::enable_if_t<!std::is_const<U>::value>* = nullptr>
    SFL_CONSTEXPR_20
    static_storage_pointer(const static_storage_pointer<U>& other) noexcept
        : ptr_(other.ptr_)
    {}

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    reference operator*() const noexcept
    {
        return ptr_->value_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer operator->() const noexcept
    {
        return std::addressof(ptr_->value_);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    reference operator[](difference_type n) const noexcept
    {
        return ptr_[n]->value_;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer& operator++() noexcept
    {
        ++ptr_;
        return *this;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer operator++(int) noexcept
    {
        auto temp = *this;
        ++ptr_;
        return temp;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer& operator--() noexcept
    {
        --ptr_;
        return *this;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer operator--(int) noexcept
    {
        auto temp = *this;
        --ptr_;
        return temp;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer& operator+=(difference_type n) noexcept
    {
        ptr_ += n;
        return *this;
    }

    SFL_CONSTEXPR_20
    static_storage_pointer& operator-=(difference_type n) noexcept
    {
        ptr_ -= n;
        return *this;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static_storage_pointer operator+(difference_type n) const noexcept
    {
        return static_storage_pointer(ptr_ + n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static_storage_pointer operator-(difference_type n) const noexcept
    {
        return static_storage_pointer(ptr_ - n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend static_storage_pointer operator+(difference_type n, const static_storage_pointer& ptr) noexcept
    {
        return ptr + n;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend difference_type operator-(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return x.ptr_ - y.ptr_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator==(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return x.ptr_ == y.ptr_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator!=(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return x.ptr_ != y.ptr_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator<(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return x.ptr_ < y.ptr_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator>(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return y < x;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator<=(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return !(y < x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator>=(const static_storage_pointer& x, const static_storage_pointer& y) noexcept
    {
        return !(x < y);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STATIC STORAGE
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
class static_storage
{
private:

    sfl::dtl::static_storage_bucket<T> buckets_[N];

public:

    using pointer = sfl::dtl::static_storage_pointer<T>;

    using const_pointer = sfl::dtl::static_storage_pointer<const T>;

public:

    SFL_CONSTEXPR_20
    static_storage() noexcept
    {}

    SFL_CONSTEXPR_20
    ~static_storage()
    {}

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer data() noexcept
    {
        return std::addressof(buckets_[0]);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer data() const noexcept
    {
        return std::addressof(buckets_[0]);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ALGORITHMS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> copy
(
    sfl::dtl::static_storage_pointer<T> first,
    sfl::dtl::static_storage_pointer<T> last,
    sfl::dtl::static_storage_pointer<T> d_first
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::copy(first, last, d_first);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::copy
                (
                    sfl::dtl::to_address(first),
                    sfl::dtl::to_address(last),
                    sfl::dtl::to_address(d_first)
                )
            )
        );
    }
}

template <typename InputIt, typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> copy
(
    InputIt first,
    InputIt last,
    sfl::dtl::static_storage_pointer<T> d_first
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::copy(first, last, d_first);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::copy
                (
                    first,
                    last,
                    sfl::dtl::to_address(d_first)
                )
            )
        );
    }
}

template <typename T>
SFL_CONSTEXPR_20
void fill
(
    sfl::dtl::static_storage_pointer<T> first,
    sfl::dtl::static_storage_pointer<T> last,
    const T& value
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        std::fill(first, last, value);
    }
    else
    #endif
    {
        std::fill
        (
            sfl::dtl::to_address(first),
            sfl::dtl::to_address(last),
            value
        );
    }
}

template <typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> move
(
    sfl::dtl::static_storage_pointer<T> first,
    sfl::dtl::static_storage_pointer<T> last,
    sfl::dtl::static_storage_pointer<T> d_first
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::move(first, last, d_first);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::move
                (
                    sfl::dtl::to_address(first),
                    sfl::dtl::to_address(last),
                    sfl::dtl::to_address(d_first)
                )
            )
        );
    }
}

template <typename InputIt, typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> move
(
    InputIt first,
    InputIt last,
    sfl::dtl::static_storage_pointer<T> d_first
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::move(first, last, d_first);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::move
                (
                    first,
                    last,
                    sfl::dtl::to_address(d_first)
                )
            )
        );
    }
}

template <typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> move_backward
(
    sfl::dtl::static_storage_pointer<T> first,
    sfl::dtl::static_storage_pointer<T> last,
    sfl::dtl::static_storage_pointer<T> d_last
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::move_backward(first, last, d_last);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::move_backward
                (
                    sfl::dtl::to_address(first),
                    sfl::dtl::to_address(last),
                    sfl::dtl::to_address(d_last)
                )
            )
        );
    }
}

template <typename InputIt, typename T>
SFL_CONSTEXPR_20
sfl::dtl::static_storage_pointer<T> move_backward
(
    InputIt first,
    InputIt last,
    sfl::dtl::static_storage_pointer<T> d_last
)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return std::move_backward(first, last, d_last);
    }
    else
    #endif
    {
        return sfl::dtl::static_storage_pointer<T>
        (
            reinterpret_cast<sfl::dtl::static_storage_bucket<T>*>
            (
                std::move_backward
                (
                    first,
                    last,
                    sfl::dtl::to_address(d_last)
                )
            )
        );
    }
}

#else // before C++20

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STATIC STORAGE
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
union static_storage
{
private:

    T storage_[N];

public:

    using pointer = T*;

    using const_pointer = const T*;

public:

    SFL_CONSTEXPR_20
    static_storage() noexcept
    {}

    SFL_CONSTEXPR_20
    ~static_storage()
    {}

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer data() noexcept
    {
        return pointer(storage_);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer data() const noexcept
    {
        return pointer(storage_);
    }
};

#endif // before C++20

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_STATIC_STORAGE_HPP_INCLUDED

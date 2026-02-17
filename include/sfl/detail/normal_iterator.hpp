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

#ifndef SFL_DETAIL_NORMAL_ITERATOR_HPP_INCLUDED
#define SFL_DETAIL_NORMAL_ITERATOR_HPP_INCLUDED

#include <sfl/detail/memory/to_address.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/cpp.hpp>

#include <iterator>     // iterator_traits
#include <memory>       // pointer_traits
#include <type_traits>  // conditional

namespace sfl
{

namespace dtl
{

template <typename Iterator, bool IsConst>
class normal_iterator
{
    template <typename, bool>
    friend class normal_iterator;

private:

    Iterator it_;

public:

    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    using value_type = typename std::iterator_traits<Iterator>::value_type;

    using pointer = typename std::conditional
    <
        IsConst,
        typename std::pointer_traits<Iterator>::template rebind<const value_type>,
        Iterator
    >::type;

    using reference = typename std::iterator_traits<pointer>::reference;

    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

    #if SFL_CPP_VERSION >= SFL_CPP_20
    using iterator_concept = std::contiguous_iterator_tag;
    #endif

public:

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    Iterator& base() noexcept
    {
        return it_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const Iterator& base() const noexcept
    {
        return it_;
    }

    SFL_CONSTEXPR_20
    explicit normal_iterator(const Iterator& it) noexcept
        : it_(it)
    {}

public:

    // Default constructor
    SFL_CONSTEXPR_20
    normal_iterator() noexcept
        : it_()
    {}

    // Converting constructor (from iterator to const_iterator)
    template <bool IsConst2 = IsConst,
              sfl::dtl::enable_if_t<IsConst2 == false>* = nullptr>
    SFL_CONSTEXPR_20
    normal_iterator(const normal_iterator<Iterator, IsConst2>& other) noexcept
        : it_(other.it_)
    {}

    // Converting assignment operator (from iterator to const_iterator)
    template <bool IsConst2 = IsConst,
              sfl::dtl::enable_if_t<IsConst2 == false>* = nullptr>
    SFL_CONSTEXPR_20
    normal_iterator& operator=(const normal_iterator<Iterator, IsConst2>& other) noexcept
    {
        it_ = other.it_;
        return *this;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    reference operator*() const noexcept
    {
        return *it_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    pointer operator->() const noexcept
    {
        return it_;
    }

    SFL_CONSTEXPR_20
    normal_iterator& operator++() noexcept
    {
        ++it_;
        return *this;
    }

    SFL_CONSTEXPR_20
    normal_iterator operator++(int) noexcept
    {
        auto temp = *this;
        ++it_;
        return temp;
    }

    SFL_CONSTEXPR_20
    normal_iterator& operator--() noexcept
    {
        --it_;
        return *this;
    }

    SFL_CONSTEXPR_20
    normal_iterator operator--(int) noexcept
    {
        auto temp = *this;
        --it_;
        return temp;
    }

    SFL_CONSTEXPR_20
    normal_iterator& operator+=(difference_type n) noexcept
    {
        it_ += n;
        return *this;
    }

    SFL_CONSTEXPR_20
    normal_iterator& operator-=(difference_type n) noexcept
    {
        it_ -= n;
        return *this;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    normal_iterator operator+(difference_type n) const noexcept
    {
        return normal_iterator(it_ + n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    normal_iterator operator-(difference_type n) const noexcept
    {
        return normal_iterator(it_ - n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    reference operator[](difference_type n) const noexcept
    {
        return it_[n];
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend normal_iterator operator+(difference_type n, const normal_iterator& it) noexcept
    {
        return it + n;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend difference_type operator-(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return x.it_ - y.it_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator==(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return x.it_ == y.it_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator!=(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return !(x == y);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator<(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return x.it_ < y.it_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator>(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return y < x;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator<=(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return !(y < x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    friend bool operator>=(const normal_iterator& x, const normal_iterator& y) noexcept
    {
        return !(x < y);
    }
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_NORMAL_ITERATOR_HPP_INCLUDED

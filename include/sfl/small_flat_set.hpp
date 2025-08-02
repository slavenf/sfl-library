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

#ifndef SFL_SMALL_FLAT_SET_HPP_INCLUDED
#define SFL_SMALL_FLAT_SET_HPP_INCLUDED

#include <sfl/detail/associative_vector.hpp>
#include <sfl/detail/container_compatible_range.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/exceptions.hpp>
#include <sfl/detail/functional.hpp>
#include <sfl/detail/tags.hpp>
#include <sfl/detail/type_traits.hpp>
#include <sfl/small_vector.hpp>

#include <cstddef>          // size_t
#include <functional>       // less
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           std::size_t N,
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<Key> >
class small_flat_set
{
    static_assert
    (
        std::is_same<typename Allocator::value_type, Key>::value,
        "Allocator::value_type must be Key."
    );

public:

    using allocator_type = Allocator;
    using key_type       = Key;
    using value_type     = Key;
    using key_compare    = Compare;
    using value_compare  = Compare;

private:

    using associative_vector = sfl::dtl::associative_vector
    <
        key_type,
        value_type,
        sfl::dtl::identity,
        key_compare,
        sfl::small_vector<value_type, N, allocator_type>
    >;

    associative_vector impl_;

public:

    using size_type              = typename associative_vector::size_type;
    using difference_type        = typename associative_vector::difference_type;
    using reference              = typename associative_vector::reference;
    using const_reference        = typename associative_vector::const_reference;
    using pointer                = typename associative_vector::pointer;
    using const_pointer          = typename associative_vector::const_pointer;
    using iterator               = typename associative_vector::const_iterator; // MUST BE const
    using const_iterator         = typename associative_vector::const_iterator;
    using reverse_iterator       = typename associative_vector::const_reverse_iterator; // MUST BE const
    using const_reverse_iterator = typename associative_vector::const_reverse_iterator;

public:

    static constexpr size_type static_capacity = N;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    small_flat_set() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : impl_()
    {}

    explicit small_flat_set(const Compare& comp) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : impl_(comp)
    {}

    explicit small_flat_set(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : impl_(alloc)
    {}

    explicit small_flat_set(const Compare& comp, const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : impl_(comp, alloc)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_flat_set(InputIt first, InputIt last)
        : impl_()
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_flat_set(InputIt first, InputIt last, const Compare& comp)
        : impl_(comp)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_flat_set(InputIt first, InputIt last, const Allocator& alloc)
        : impl_(alloc)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_flat_set(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert(first, last);
    }

    small_flat_set(std::initializer_list<value_type> ilist)
        : small_flat_set(ilist.begin(), ilist.end())
    {}

    small_flat_set(std::initializer_list<value_type> ilist, const Compare& comp)
        : small_flat_set(ilist.begin(), ilist.end(), comp)
    {}

    small_flat_set(std::initializer_list<value_type> ilist, const Allocator& alloc)
        : small_flat_set(ilist.begin(), ilist.end(), alloc)
    {}

    small_flat_set(std::initializer_list<value_type> ilist, const Compare& comp, const Allocator& alloc)
        : small_flat_set(ilist.begin(), ilist.end(), comp, alloc)
    {}

    small_flat_set(const small_flat_set& other)
        : impl_(other.impl_)
    {}

    small_flat_set(const small_flat_set& other, const Allocator& alloc)
        : impl_(other.impl_, alloc)
    {}

    small_flat_set(small_flat_set&& other)
        : impl_(std::move(other.impl_))
    {}

    small_flat_set(small_flat_set&& other, const Allocator& alloc)
        : impl_(std::move(other.impl_), alloc)
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_flat_set(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    small_flat_set(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_flat_set(sfl::from_range_t, Range&& range, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    ~small_flat_set()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    small_flat_set& operator=(const small_flat_set& other)
    {
        impl_.assign_copy(other.impl_);
        return *this;
    }

    small_flat_set& operator=(small_flat_set&& other)
    {
        impl_.assign_move(other.impl_);
        return *this;
    }

    small_flat_set& operator=(std::initializer_list<Key> ilist)
    {
        impl_.assign_range_unique(ilist.begin(), ilist.end());
        return *this;
    }

    //
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    allocator_type get_allocator() const noexcept
    {
        return impl_.ref_to_vector().get_allocator();
    }

    //
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    key_compare key_comp() const
    {
        return impl_.ref_to_key_compare();
    }

    //
    // ---- VALUE COMPARE -----------------------------------------------------
    //

    SFL_NODISCARD
    value_compare value_comp() const
    {
        return impl_.ref_to_key_compare();
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return impl_.begin();
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return impl_.begin();
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return impl_.cbegin();
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return impl_.end();
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return impl_.end();
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return impl_.cend();
    }

    SFL_NODISCARD
    reverse_iterator rbegin() noexcept
    {
        return impl_.rbegin();
    }

    SFL_NODISCARD
    const_reverse_iterator rbegin() const noexcept
    {
        return impl_.rbegin();
    }

    SFL_NODISCARD
    const_reverse_iterator crbegin() const noexcept
    {
        return impl_.crbegin();
    }

    SFL_NODISCARD
    reverse_iterator rend() noexcept
    {
        return impl_.rend();
    }

    SFL_NODISCARD
    const_reverse_iterator rend() const noexcept
    {
        return impl_.rend();
    }

    SFL_NODISCARD
    const_reverse_iterator crend() const noexcept
    {
        return impl_.crend();
    }

    SFL_NODISCARD
    iterator nth(size_type pos) noexcept
    {
        SFL_ASSERT(pos <= size());
        return impl_.nth(pos);
    }

    SFL_NODISCARD
    const_iterator nth(size_type pos) const noexcept
    {
        SFL_ASSERT(pos <= size());
        return impl_.nth(pos);
    }

    SFL_NODISCARD
    size_type index_of(const_iterator pos) const noexcept
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return impl_.index_of(pos);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return impl_.empty();
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return impl_.size();
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return impl_.max_size();
    }

    SFL_NODISCARD
    size_type capacity() const noexcept
    {
        return impl_.capacity();
    }

    SFL_NODISCARD
    size_type available() const noexcept
    {
        return impl_.available();
    }

    void reserve(size_type new_cap)
    {
        impl_.reserve(new_cap);
    }

    void shrink_to_fit()
    {
        impl_.shrink_to_fit();
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear() noexcept
    {
        impl_.clear();
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        return impl_.emplace_unique(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.emplace_hint_unique(hint, std::forward<Args>(args)...);
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        return impl_.insert_unique(value);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        return impl_.insert_unique(std::move(value));
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    std::pair<iterator, bool> insert(K&& x)
    {
        return impl_.insert_unique(std::forward<K>(x));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::move(value));
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Compare, K>::value &&
                                    !std::is_convertible<K&&, const_iterator>::value &&
                                    !std::is_convertible<K&&, iterator>::value >* = nullptr>
    iterator insert(const_iterator hint, K&& x)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::forward<K>(x));
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void insert(InputIt first, InputIt last)
    {
        insert_range_aux(first, last);
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        insert_range_aux(ilist.begin(), ilist.end());
    }

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    void insert_range(Range&& range)
    {
        insert_range_aux(std::ranges::begin(range), std::ranges::end(range));
    }

#else // before C++20

    template <typename Range>
    void insert_range(Range&& range)
    {
        using std::begin;
        using std::end;
        insert_range_aux(begin(range), end(range));
    }

#endif // before C++20

    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());
        return impl_.erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());
        return impl_.erase(first, last);
    }

    size_type erase(const Key& key)
    {
        return impl_.erase_key_unique(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    size_type erase(K&& x)
    {
        return impl_.erase_key_unique(x);
    }

    void swap(small_flat_set& other)
    {
        impl_.swap(other.impl_);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    iterator lower_bound(const Key& key)
    {
        return impl_.lower_bound(key);
    }

    SFL_NODISCARD
    const_iterator lower_bound(const Key& key) const
    {
        return impl_.lower_bound(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator lower_bound(const K& x)
    {
        return impl_.lower_bound(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator lower_bound(const K& x) const
    {
        return impl_.lower_bound(x);
    }

    SFL_NODISCARD
    iterator upper_bound(const Key& key)
    {
        return impl_.upper_bound(key);
    }

    SFL_NODISCARD
    const_iterator upper_bound(const Key& key) const
    {
        return impl_.upper_bound(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator upper_bound(const K& x)
    {
        return impl_.upper_bound(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator upper_bound(const K& x) const
    {
        return impl_.upper_bound(x);
    }

    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return impl_.equal_range(key);
    }

    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return impl_.equal_range(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& x)
    {
        return impl_.equal_range(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const
    {
        return impl_.equal_range(x);
    }

    SFL_NODISCARD
    iterator find(const Key& key)
    {
        return impl_.find(key);
    }

    SFL_NODISCARD
    const_iterator find(const Key& key) const
    {
        return impl_.find(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator find(const K& x)
    {
        return impl_.find(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        return impl_.find(x);
    }

    SFL_NODISCARD
    size_type count(const Key& key) const
    {
        return impl_.count_unique(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        return impl_.count_unique(x);
    }

    SFL_NODISCARD
    bool contains(const Key& key) const
    {
        return impl_.contains(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    bool contains(const K& x) const
    {
        return impl_.contains(x);
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

    SFL_NODISCARD
    value_type* data() noexcept
    {
        return impl_.data();
    }

    SFL_NODISCARD
    const value_type* data() const noexcept
    {
        return impl_.data();
    }

private:

    template <typename InputIt, typename Sentinel>
    void insert_range_aux(InputIt first, Sentinel last)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator==(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator!=(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator<(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator>(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator<=(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);

    template <typename K2, std::size_t N2, typename C2, typename A2>
    friend bool operator>=(const small_flat_set<K2, N2, C2, A2>& x, const small_flat_set<K2, N2, C2, A2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator==
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ == y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ != y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ < y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ > y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ <= y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.impl_ >= y.impl_;
}

template <typename K, std::size_t N, typename C, typename A>
void swap
(
    small_flat_set<K, N, C, A>& x,
    small_flat_set<K, N, C, A>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, typename C, typename A, typename Predicate>
typename small_flat_set<K, N, C, A>::size_type
    erase_if(small_flat_set<K, N, C, A>& c, Predicate pred)
{
    auto old_size = c.size();

    for (auto it = c.begin(); it != c.end(); )
    {
        if (pred(*it))
        {
            it = c.erase(it);
        }
        else
        {
            ++it;
        }
    }

    return old_size - c.size();
}

} // namespace sfl

#endif // SFL_SMALL_FLAT_SET_HPP_INCLUDED

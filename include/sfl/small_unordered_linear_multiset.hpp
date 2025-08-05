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

#ifndef SFL_SMALL_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED
#define SFL_SMALL_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED

#include <sfl/detail/concepts/container_compatible_range.hpp>
#include <sfl/detail/functional/identity.hpp>
#include <sfl/detail/tags/from_range_t.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/has_is_transparent.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/exceptions.hpp>
#include <sfl/detail/unordered_associative_vector.hpp>
#include <sfl/small_vector.hpp>

#include <cstddef>          // size_t
#include <functional>       // equal_to
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           std::size_t N,
           typename KeyEqual = std::equal_to<Key>,
           typename Allocator = std::allocator<Key> >
class small_unordered_flat_multiset
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
    using key_equal      = KeyEqual;

private:

    using unordered_associative_vector = sfl::dtl::unordered_associative_vector
    <
        key_type,
        value_type,
        sfl::dtl::identity,
        key_equal,
        sfl::small_vector<value_type, N, allocator_type>
    >;

    unordered_associative_vector impl_;

public:

    using size_type       = typename unordered_associative_vector::size_type;
    using difference_type = typename unordered_associative_vector::difference_type;
    using reference       = typename unordered_associative_vector::reference;
    using const_reference = typename unordered_associative_vector::const_reference;
    using pointer         = typename unordered_associative_vector::pointer;
    using const_pointer   = typename unordered_associative_vector::const_pointer;
    using iterator        = typename unordered_associative_vector::const_iterator; // MUST BE const
    using const_iterator  = typename unordered_associative_vector::const_iterator;

public:

    static constexpr size_type static_capacity = N;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    small_unordered_flat_multiset() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    )
        : impl_()
    {}

    explicit small_unordered_flat_multiset(const KeyEqual& equal) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    )
        : impl_(equal)
    {}

    explicit small_unordered_flat_multiset(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    )
        : impl_(alloc)
    {}

    explicit small_unordered_flat_multiset(const KeyEqual& equal, const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    )
        : impl_(equal, alloc)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_flat_multiset(InputIt first, InputIt last)
        : impl_()
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_flat_multiset(InputIt first, InputIt last, const KeyEqual& equal)
        : impl_(equal)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_flat_multiset(InputIt first, InputIt last, const Allocator& alloc)
        : impl_(alloc)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_flat_multiset(InputIt first, InputIt last, const KeyEqual& equal, const Allocator& alloc)
        : impl_(equal, alloc)
    {
        insert(first, last);
    }

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end())
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const KeyEqual& equal)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), equal)
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const Allocator& alloc)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), alloc)
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const KeyEqual& equal, const Allocator& alloc)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), equal, alloc)
    {}

    small_unordered_flat_multiset(const small_unordered_flat_multiset& other)
        : impl_(other.impl_)
    {}

    small_unordered_flat_multiset(const small_unordered_flat_multiset& other, const Allocator& alloc)
        : impl_(other.impl_, alloc)
    {}

    small_unordered_flat_multiset(small_unordered_flat_multiset&& other)
        : impl_(std::move(other.impl_))
    {}

    small_unordered_flat_multiset(small_unordered_flat_multiset&& other, const Allocator& alloc)
        : impl_(std::move(other.impl_), alloc)
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal)
        : impl_(equal)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal, const Allocator& alloc)
        : impl_(equal, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal)
        : impl_(equal)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_flat_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal, const Allocator& alloc)
        : impl_(equal, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    ~small_unordered_flat_multiset()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    small_unordered_flat_multiset& operator=(const small_unordered_flat_multiset& other)
    {
        impl_.assign_copy(other.impl_);
        return *this;
    }

    small_unordered_flat_multiset& operator=(small_unordered_flat_multiset&& other)
    {
        impl_.assign_move(other.impl_);
        return *this;
    }

    small_unordered_flat_multiset& operator=(std::initializer_list<Key> ilist)
    {
        impl_.assign_range_equal(ilist.begin(), ilist.end());
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
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    key_equal key_eq() const
    {
        return impl_.ref_to_key_equal();
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
    iterator emplace(Args&&... args)
    {
        return impl_.emplace_equal(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.emplace_hint_equal(hint, std::forward<Args>(args)...);
    }

    iterator insert(const value_type& value)
    {
        return impl_.insert_equal(value);
    }

    iterator insert(value_type&& value)
    {
        return impl_.insert_equal(std::move(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_equal(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_equal(hint, std::move(value));
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
        return impl_.erase_key_equal(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    size_type erase(K&& x)
    {
        return impl_.erase_key_equal(x);
    }

    void swap(small_unordered_flat_multiset& other)
    {
        impl_.swap(other.impl_);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

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
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator find(const K& x)
    {
        return impl_.find(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        return impl_.find(x);
    }

    SFL_NODISCARD
    size_type count(const Key& key) const
    {
        return impl_.count_equal(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        return impl_.count_equal(x);
    }

    SFL_NODISCARD
    bool contains(const Key& key) const
    {
        return impl_.contains(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
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

    template <typename K2, std::size_t N2, typename E2, typename A2>
    friend bool operator==(const small_unordered_flat_multiset<K2, N2, E2, A2>& x, const small_unordered_flat_multiset<K2, N2, E2, A2>& y);

    template <typename K2, std::size_t N2, typename E2, typename A2>
    friend bool operator!=(const small_unordered_flat_multiset<K2, N2, E2, A2>& x, const small_unordered_flat_multiset<K2, N2, E2, A2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, typename E, typename A>
SFL_NODISCARD
bool operator==
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
)
{
    return x.impl_ == y.impl_;
}

template <typename K, std::size_t N, typename E, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
)
{
    return x.impl_ != y.impl_;
}

template <typename K, std::size_t N, typename E, typename A>
void swap
(
    small_unordered_flat_multiset<K, N, E, A>& x,
    small_unordered_flat_multiset<K, N, E, A>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, typename E, typename A,
          typename Predicate>
typename small_unordered_flat_multiset<K, N, E, A>::size_type
    erase_if(small_unordered_flat_multiset<K, N, E, A>& c, Predicate pred)
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

#endif // SFL_SMALL_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED

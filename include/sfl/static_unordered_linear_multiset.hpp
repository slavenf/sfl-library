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

#ifndef SFL_STATIC_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED
#define SFL_STATIC_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED

#include <sfl/detail/concepts/container_compatible_range.hpp>
#include <sfl/detail/functional/identity.hpp>
#include <sfl/detail/tags/from_range_t.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/has_is_transparent.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/exceptions.hpp>
#include <sfl/detail/unordered_associative_vector.hpp>
#include <sfl/static_vector.hpp>

#include <cstddef>          // size_t
#include <functional>       // equal_to
#include <initializer_list> // initializer_list
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           std::size_t N,
           typename KeyEqual = std::equal_to<Key> >
class static_unordered_linear_multiset
{
    static_assert(N > 0, "N must be greater than zero.");

public:

    using key_type    = Key;
    using value_type  = Key;
    using key_equal   = KeyEqual;

private:

    using unordered_associative_vector = sfl::dtl::unordered_associative_vector
    <
        key_type,
        value_type,
        sfl::dtl::identity,
        key_equal,
        sfl::static_vector<value_type, N>
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

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset() noexcept(std::is_nothrow_default_constructible<KeyEqual>::value)
        : impl_()
    {}

    SFL_CONSTEXPR_20
    explicit static_unordered_linear_multiset(const KeyEqual& equal) noexcept(std::is_nothrow_copy_constructible<KeyEqual>::value)
        : impl_(equal)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(InputIt first, InputIt last)
        : impl_()
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(InputIt first, InputIt last, const KeyEqual& equal)
        : impl_(equal)
    {
        insert(first, last);
    }

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(std::initializer_list<value_type> ilist)
        : static_unordered_linear_multiset(ilist.begin(), ilist.end())
    {}

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(std::initializer_list<value_type> ilist, const KeyEqual& equal)
        : static_unordered_linear_multiset(ilist.begin(), ilist.end(), equal)
    {}

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(const static_unordered_linear_multiset& other)
        : impl_(other.impl_)
    {}

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(static_unordered_linear_multiset&& other)
        : impl_(std::move(other.impl_))
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    static_unordered_linear_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal)
        : impl_(equal)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    static_unordered_linear_multiset(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    static_unordered_linear_multiset(sfl::from_range_t, Range&& range, const KeyEqual& equal)
        : impl_(equal)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    SFL_CONSTEXPR_20
    ~static_unordered_linear_multiset()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset& operator=(const static_unordered_linear_multiset& other)
    {
        impl_.assign_copy(other.impl_);
        return *this;
    }

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset& operator=(static_unordered_linear_multiset&& other)
    {
        impl_.assign_move(other.impl_);
        return *this;
    }

    SFL_CONSTEXPR_20
    static_unordered_linear_multiset& operator=(std::initializer_list<value_type> ilist)
    {
        SFL_ASSERT(size_type(ilist.size()) <= capacity());
        impl_.assign_range_equal(ilist.begin(), ilist.end());
        return *this;
    }

    //
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    key_equal key_eq() const
    {
        return impl_.ref_to_key_equal();
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator begin() noexcept
    {
        return impl_.begin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator begin() const noexcept
    {
        return impl_.begin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator cbegin() const noexcept
    {
        return impl_.cbegin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator end() noexcept
    {
        return impl_.end();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator end() const noexcept
    {
        return impl_.end();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator cend() const noexcept
    {
        return impl_.cend();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator nth(size_type pos) noexcept
    {
        SFL_ASSERT(pos <= size());
        return impl_.nth(pos);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator nth(size_type pos) const noexcept
    {
        SFL_ASSERT(pos <= size());
        return impl_.nth(pos);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type index_of(const_iterator pos) const noexcept
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return impl_.index_of(pos);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool empty() const noexcept
    {
        return impl_.empty();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool full() const noexcept
    {
        return impl_.ref_to_vector().full();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type size() const noexcept
    {
        return impl_.size();
    }

    SFL_NODISCARD
    static constexpr size_type max_size() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    static constexpr size_type capacity() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type available() const noexcept
    {
        return impl_.available();
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    SFL_CONSTEXPR_20
    void clear() noexcept
    {
        impl_.clear();
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace(Args&&... args)
    {
        SFL_ASSERT(!full());
        return impl_.emplace_equal(std::forward<Args>(args)...);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.emplace_hint_equal(hint, std::forward<Args>(args)...);
    }

    SFL_CONSTEXPR_20
    iterator insert(const value_type& value)
    {
        SFL_ASSERT(!full());
        return impl_.insert_equal(value);
    }

    SFL_CONSTEXPR_20
    iterator insert(value_type&& value)
    {
        SFL_ASSERT(!full());
        return impl_.insert_equal(std::move(value));
    }

    SFL_CONSTEXPR_20
    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_equal(hint, value);
    }

    SFL_CONSTEXPR_20
    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_equal(hint, std::move(value));
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    void insert(InputIt first, InputIt last)
    {
        insert_range_aux(first, last);
    }

    SFL_CONSTEXPR_20
    void insert(std::initializer_list<value_type> ilist)
    {
        insert_range_aux(ilist.begin(), ilist.end());
    }

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
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

    SFL_CONSTEXPR_20
    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());
        return impl_.erase(pos);
    }

    SFL_CONSTEXPR_20
    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());
        return impl_.erase(first, last);
    }

    SFL_CONSTEXPR_20
    size_type erase(const Key& key)
    {
        return impl_.erase_key_equal(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_CONSTEXPR_20
    size_type erase(K&& x)
    {
        return impl_.erase_key_equal(x);
    }

    SFL_CONSTEXPR_20
    void swap(static_unordered_linear_multiset& other)
    {
        impl_.swap(other.impl_);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator find(const Key& key)
    {
        return impl_.find(key);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator find(const Key& key) const
    {
        return impl_.find(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator find(const K& x)
    {
        return impl_.find(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator find(const K& x) const
    {
        return impl_.find(x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type count(const Key& key) const
    {
        return impl_.count_equal(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type count(const K& x) const
    {
        return impl_.count_equal(x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool contains(const Key& key) const
    {
        return impl_.contains(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool contains(const K& x) const
    {
        return impl_.contains(x);
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    value_type* data() noexcept
    {
        return impl_.data();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const value_type* data() const noexcept
    {
        return impl_.data();
    }

private:

    template <typename InputIt, typename Sentinel>
    SFL_CONSTEXPR_20
    void insert_range_aux(InputIt first, Sentinel last)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <typename K2, std::size_t N2, typename E2>
    SFL_CONSTEXPR_20
    friend bool operator==(const static_unordered_linear_multiset<K2, N2, E2>& x, const static_unordered_linear_multiset<K2, N2, E2>& y);

    template <typename K2, std::size_t N2, typename E2>
    SFL_CONSTEXPR_20
    friend bool operator!=(const static_unordered_linear_multiset<K2, N2, E2>& x, const static_unordered_linear_multiset<K2, N2, E2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, typename E>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator==
(
    const static_unordered_linear_multiset<K, N, E>& x,
    const static_unordered_linear_multiset<K, N, E>& y
)
{
    return x.impl_ == y.impl_;
}

template <typename K, std::size_t N, typename E>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator!=
(
    const static_unordered_linear_multiset<K, N, E>& x,
    const static_unordered_linear_multiset<K, N, E>& y
)
{
    return x.impl_ != y.impl_;
}

template <typename K, std::size_t N, typename E>
SFL_CONSTEXPR_20
void swap
(
    static_unordered_linear_multiset<K, N, E>& x,
    static_unordered_linear_multiset<K, N, E>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, typename E, typename Predicate>
SFL_CONSTEXPR_20
typename static_unordered_linear_multiset<K, N, E>::size_type
    erase_if(static_unordered_linear_multiset<K, N, E>& c, Predicate pred)
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

#endif // SFL_STATIC_UNORDERED_LINEAR_MULTISET_HPP_INCLUDED

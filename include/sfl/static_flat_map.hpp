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

#ifndef SFL_STATIC_FLAT_MAP_HPP_INCLUDED
#define SFL_STATIC_FLAT_MAP_HPP_INCLUDED

#include <sfl/detail/concepts/container_compatible_range.hpp>
#include <sfl/detail/functional/first.hpp>
#include <sfl/detail/tags/from_range_t.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/has_is_transparent.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/type_traits/remove_cvref_t.hpp>
#include <sfl/detail/associative_vector.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/exceptions.hpp>
#include <sfl/static_vector.hpp>

#include <cstddef>          // size_t
#include <functional>       // less
#include <initializer_list> // initializer_list
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           typename T,
           std::size_t N,
           typename Compare = std::less<Key> >
class static_flat_map
{
    static_assert(N > 0, "N must be greater than zero.");

public:

    using key_type    = Key;
    using mapped_type = T;
    using value_type  = std::pair<Key, T>;
    using key_compare = Compare;

private:

    using associative_vector = sfl::dtl::associative_vector
    <
        key_type,
        value_type,
        sfl::dtl::first,
        key_compare,
        sfl::static_vector<value_type, N>
    >;

    associative_vector impl_;

public:

    using size_type              = typename associative_vector::size_type;
    using difference_type        = typename associative_vector::difference_type;
    using reference              = typename associative_vector::reference;
    using const_reference        = typename associative_vector::const_reference;
    using pointer                = typename associative_vector::pointer;
    using const_pointer          = typename associative_vector::const_pointer;
    using iterator               = typename associative_vector::iterator;
    using const_iterator         = typename associative_vector::const_iterator;
    using reverse_iterator       = typename associative_vector::reverse_iterator;
    using const_reverse_iterator = typename associative_vector::const_reverse_iterator;

    class value_compare : protected key_compare
    {
        friend class static_flat_map;

    private:

        value_compare(const key_compare& c)
            : key_compare(c)
        {}

    public:

        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_compare::operator()(x.first, y.first);
        }
    };

public:

    static constexpr size_type static_capacity = N;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_flat_map() noexcept(std::is_nothrow_default_constructible<Compare>::value)
        : impl_()
    {}

    explicit static_flat_map(const Compare& comp) noexcept(std::is_nothrow_copy_constructible<Compare>::value)
        : impl_(comp)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    static_flat_map(InputIt first, InputIt last)
        : impl_()
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    static_flat_map(InputIt first, InputIt last, const Compare& comp)
        : impl_(comp)
    {
        insert(first, last);
    }

    static_flat_map(std::initializer_list<value_type> ilist)
        : static_flat_map(ilist.begin(), ilist.end())
    {}

    static_flat_map(std::initializer_list<value_type> ilist, const Compare& comp)
        : static_flat_map(ilist.begin(), ilist.end(), comp)
    {}

    static_flat_map(const static_flat_map& other)
        : impl_(other.impl_)
    {}

    static_flat_map(static_flat_map&& other)
        : impl_(std::move(other.impl_))
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    static_flat_map(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    static_flat_map(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    static_flat_map(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    static_flat_map(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    ~static_flat_map()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    static_flat_map& operator=(const static_flat_map& other)
    {
        impl_.assign_copy(other.impl_);
        return *this;
    }

    static_flat_map& operator=(static_flat_map&& other)
    {
        impl_.assign_move(other.impl_);
        return *this;
    }

    static_flat_map& operator=(std::initializer_list<value_type> ilist)
    {
        SFL_ASSERT(size_type(ilist.size()) <= capacity());
        impl_.assign_range_unique(ilist.begin(), ilist.end());
        return *this;
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
        return value_compare(impl_.ref_to_key_compare());
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
    bool full() const noexcept
    {
        return impl_.ref_to_vector().full();
    }

    SFL_NODISCARD
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
    size_type available() const noexcept
    {
        return impl_.available();
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
        SFL_ASSERT(!full());
        return impl_.emplace_unique(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.emplace_hint_unique(hint, std::forward<Args>(args)...);
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        SFL_ASSERT(!full());
        return impl_.insert_unique(value);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        SFL_ASSERT(!full());
        return impl_.insert_unique(std::move(value));
    }

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P&&>::value>* = nullptr>
    std::pair<iterator, bool> insert(P&& value)
    {
        SFL_ASSERT(!full());
        return impl_.insert_unique(std::forward<P>(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::move(value));
    }

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P>::value>* = nullptr>
    iterator insert(const_iterator hint, P&& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::forward<P>(value));
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

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj)
    {
        SFL_ASSERT(!full());
        return impl_.insert_or_assign(key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        return impl_.insert_or_assign(std::move(key), std::forward<M>(obj));
    }

    template <typename K, typename M,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Compare, K>::value &&
                                     std::is_assignable<mapped_type&, M&&>::value >* = nullptr>
    std::pair<iterator, bool> insert_or_assign(K&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        return impl_.insert_or_assign(std::forward<K>(key), std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    iterator insert_or_assign(const_iterator hint, const Key& key, M&& obj)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    iterator insert_or_assign(const_iterator hint, Key&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, std::move(key), std::forward<M>(obj));
    }

    template <typename K, typename M,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Compare, K>::value &&
                                     std::is_assignable<mapped_type&, M&&>::value >* = nullptr>
    iterator insert_or_assign(const_iterator hint, K&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, std::forward<K>(key), std::forward<M>(obj));
    }

    template <typename... Args>
    std::pair<iterator, bool> try_emplace(const Key& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        return impl_.try_emplace(key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    std::pair<iterator, bool> try_emplace(Key&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        return impl_.try_emplace(std::move(key), std::forward<Args>(args)...);
    }

    template <typename K, typename... Args,
              sfl::dtl::enable_if_t<
                #if defined(__GNUC__) && !defined(__clang__) && (__GNUC__ < 7)
                // This is workaround for GCC 4 bug on CentOS 7.
                !std::is_same<sfl::dtl::remove_cvref_t<Key>, sfl::dtl::remove_cvref_t<K>>::value &&
                #endif
                sfl::dtl::has_is_transparent<Compare, K>::value &&
                !std::is_convertible<K&&, const_iterator>::value &&
                !std::is_convertible<K&&, iterator>::value
              >* = nullptr>
    std::pair<iterator, bool> try_emplace(K&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        return impl_.try_emplace(std::forward<K>(key), std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator try_emplace(const_iterator hint, const Key& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.try_emplace_hint(hint, key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator try_emplace(const_iterator hint, Key&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.try_emplace_hint(hint, std::move(key), std::forward<Args>(args)...);
    }

    template <typename K, typename... Args,
              sfl::dtl::enable_if_t<
                #if defined(__GNUC__) && !defined(__clang__) && (__GNUC__ < 7)
                // This is workaround for GCC 4 bug on CentOS 7.
                !std::is_same<sfl::dtl::remove_cvref_t<Key>, sfl::dtl::remove_cvref_t<K>>::value &&
                #endif
                sfl::dtl::has_is_transparent<Compare, K>::value
              >* = nullptr>
    iterator try_emplace(const_iterator hint, K&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.try_emplace_hint(hint, std::forward<K>(key), std::forward<Args>(args)...);
    }

    iterator erase(iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());
        return impl_.erase(pos);
    }

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

    void swap(static_flat_map& other)
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
    T& at(const Key& key)
    {
        auto it = find(key);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::static_flat_map::at");
        }

        return it->second;
    }

    SFL_NODISCARD
    const T& at(const Key& key) const
    {
        auto it = find(key);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::static_flat_map::at");
        }

        return it->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    T& at(const K& x)
    {
        auto it = find(x);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::static_flat_map::at");
        }

        return it->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const T& at(const K& x) const
    {
        auto it = find(x);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::static_flat_map::at");
        }

        return it->second;
    }

    SFL_NODISCARD
    T& operator[](const Key& key)
    {
        return try_emplace(key).first->second;
    }

    SFL_NODISCARD
    T& operator[](Key&& key)
    {
        return try_emplace(std::move(key)).first->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    T& operator[](K&& key)
    {
        return try_emplace(std::forward<K>(key)).first->second;
    }

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

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator==(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator!=(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator<(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator>(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator<=(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);

    template <typename K2, typename T2, std::size_t N2, typename C2>
    friend bool operator>=(const static_flat_map<K2, T2, N2, C2>& x, const static_flat_map<K2, T2, N2, C2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator==
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ == y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator!=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ != y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator<
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ < y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator>
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ > y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator<=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ <= y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
SFL_NODISCARD
bool operator>=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
)
{
    return x.impl_ >= y.impl_;
}

template <typename K, typename T, std::size_t N, typename C>
void swap
(
    static_flat_map<K, T, N, C>& x,
    static_flat_map<K, T, N, C>& y
)
{
    x.swap(y);
}

template <typename K, typename T, std::size_t N, typename C, typename Predicate>
typename static_flat_map<K, T, N, C>::size_type
    erase_if(static_flat_map<K, T, N, C>& c, Predicate pred)
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

#endif // SFL_STATIC_FLAT_MAP_HPP_INCLUDED

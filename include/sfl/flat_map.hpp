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

#ifndef SFL_FLAT_MAP_HPP_INCLUDED
#define SFL_FLAT_MAP_HPP_INCLUDED

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
#include <sfl/vector.hpp>

#include <functional>       // less
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           typename T,
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<std::pair<Key, T>> >
class flat_map
{
    static_assert
    (
        std::is_same<typename Allocator::value_type, std::pair<Key, T>>::value,
        "Allocator::value_type must be std::pair<Key, T>."
    );

public:

    using allocator_type = Allocator;
    using key_type       = Key;
    using mapped_type    = T;
    using value_type     = std::pair<Key, T>;
    using key_compare    = Compare;

private:

    using associative_vector = sfl::dtl::associative_vector
    <
        key_type,
        value_type,
        sfl::dtl::first,
        key_compare,
        sfl::vector<value_type, allocator_type>
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
        friend class flat_map;

    private:

        SFL_CONSTEXPR_20
        value_compare(const key_compare& c) : key_compare(c)
        {}

    public:

        SFL_CONSTEXPR_20
        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_compare::operator()(x.first, y.first);
        }
    };

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    SFL_CONSTEXPR_20
    flat_map() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : impl_()
    {}

    SFL_CONSTEXPR_20
    explicit flat_map(const Compare& comp) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : impl_(comp)
    {}

    SFL_CONSTEXPR_20
    explicit flat_map(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : impl_(alloc)
    {}

    SFL_CONSTEXPR_20
    explicit flat_map(const Compare& comp, const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : impl_(comp, alloc)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    flat_map(InputIt first, InputIt last)
        : impl_()
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    flat_map(InputIt first, InputIt last, const Compare& comp)
        : impl_(comp)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    flat_map(InputIt first, InputIt last, const Allocator& alloc)
        : impl_(alloc)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    flat_map(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert(first, last);
    }

    SFL_CONSTEXPR_20
    flat_map(std::initializer_list<value_type> ilist)
        : flat_map(ilist.begin(), ilist.end())
    {}

    SFL_CONSTEXPR_20
    flat_map(std::initializer_list<value_type> ilist, const Compare& comp)
        : flat_map(ilist.begin(), ilist.end(), comp)
    {}

    SFL_CONSTEXPR_20
    flat_map(std::initializer_list<value_type> ilist, const Allocator& alloc)
        : flat_map(ilist.begin(), ilist.end(), alloc)
    {}

    SFL_CONSTEXPR_20
    flat_map(std::initializer_list<value_type> ilist, const Compare& comp, const Allocator& alloc)
        : flat_map(ilist.begin(), ilist.end(), comp, alloc)
    {}

    SFL_CONSTEXPR_20
    flat_map(const flat_map& other)
        : impl_(other.impl_)
    {}

    SFL_CONSTEXPR_20
    flat_map(const flat_map& other, const Allocator& alloc)
        : impl_(other.impl_, alloc)
    {}

    SFL_CONSTEXPR_20
    flat_map(flat_map&& other)
        : impl_(std::move(other.impl_))
    {}

    SFL_CONSTEXPR_20
    flat_map(flat_map&& other, const Allocator& alloc)
        : impl_(std::move(other.impl_), alloc)
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    flat_map(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    flat_map(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    flat_map(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    SFL_CONSTEXPR_20
    flat_map(sfl::from_range_t, Range&& range, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    flat_map(sfl::from_range_t, Range&& range)
        : impl_()
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    flat_map(sfl::from_range_t, Range&& range, const Compare& comp)
        : impl_(comp)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    flat_map(sfl::from_range_t, Range&& range, const Allocator& alloc)
        : impl_(alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    flat_map(sfl::from_range_t, Range&& range, const Compare& comp, const Allocator& alloc)
        : impl_(comp, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    SFL_CONSTEXPR_20
    ~flat_map()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    SFL_CONSTEXPR_20
    flat_map& operator=(const flat_map& other)
    {
        impl_.assign_copy(other.impl_);
        return *this;
    }

    SFL_CONSTEXPR_20
    flat_map& operator=(flat_map&& other)
    {
        impl_.assign_move(other.impl_);
        return *this;
    }

    SFL_CONSTEXPR_20
    flat_map& operator=(std::initializer_list<value_type> ilist)
    {
        impl_.assign_range_unique(ilist.begin(), ilist.end());
        return *this;
    }

    //
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    allocator_type get_allocator() const noexcept
    {
        return impl_.ref_to_vector().get_allocator();
    }

    //
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    key_compare key_comp() const
    {
        return impl_.ref_to_key_compare();
    }

    //
    // ---- VALUE COMPARE -----------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    value_compare value_comp() const
    {
        return value_compare(impl_.ref_to_key_compare());
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
    reverse_iterator rbegin() noexcept
    {
        return impl_.rbegin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_reverse_iterator rbegin() const noexcept
    {
        return impl_.rbegin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_reverse_iterator crbegin() const noexcept
    {
        return impl_.crbegin();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    reverse_iterator rend() noexcept
    {
        return impl_.rend();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_reverse_iterator rend() const noexcept
    {
        return impl_.rend();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_reverse_iterator crend() const noexcept
    {
        return impl_.crend();
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
    size_type size() const noexcept
    {
        return impl_.size();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type max_size() const noexcept
    {
        return impl_.max_size();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type capacity() const noexcept
    {
        return impl_.capacity();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type available() const noexcept
    {
        return impl_.available();
    }

    SFL_CONSTEXPR_20
    void reserve(size_type new_cap)
    {
        impl_.reserve(new_cap);
    }

    SFL_CONSTEXPR_20
    void shrink_to_fit()
    {
        impl_.shrink_to_fit();
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
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        return impl_.emplace_unique(std::forward<Args>(args)...);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.emplace_hint_unique(hint, std::forward<Args>(args)...);
    }

    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert(const value_type& value)
    {
        return impl_.insert_unique(value);
    }

    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert(value_type&& value)
    {
        return impl_.insert_unique(std::move(value));
    }

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P&&>::value>* = nullptr>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert(P&& value)
    {
        return impl_.insert_unique(std::forward<P>(value));
    }

    SFL_CONSTEXPR_20
    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, value);
    }

    SFL_CONSTEXPR_20
    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::move(value));
    }

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P>::value>* = nullptr>
    SFL_CONSTEXPR_20
    iterator insert(const_iterator hint, P&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_hint_unique(hint, std::forward<P>(value));
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

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj)
    {
        return impl_.insert_or_assign(key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj)
    {
        return impl_.insert_or_assign(std::move(key), std::forward<M>(obj));
    }

    template <typename K, typename M,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Compare, K>::value &&
                                     std::is_assignable<mapped_type&, M&&>::value >* = nullptr>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_or_assign(K&& key, M&& obj)
    {
        return impl_.insert_or_assign(std::forward<K>(key), std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    SFL_CONSTEXPR_20
    iterator insert_or_assign(const_iterator hint, const Key& key, M&& obj)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    SFL_CONSTEXPR_20
    iterator insert_or_assign(const_iterator hint, Key&& key, M&& obj)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, std::move(key), std::forward<M>(obj));
    }

    template <typename K, typename M,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Compare, K>::value &&
                                     std::is_assignable<mapped_type&, M&&>::value >* = nullptr>
    SFL_CONSTEXPR_20
    iterator insert_or_assign(const_iterator hint, K&& key, M&& obj)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.insert_or_assign_hint(hint, std::forward<K>(key), std::forward<M>(obj));
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> try_emplace(const Key& key, Args&&... args)
    {
        return impl_.try_emplace(key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> try_emplace(Key&& key, Args&&... args)
    {
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
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> try_emplace(K&& key, Args&&... args)
    {
        return impl_.try_emplace(std::forward<K>(key), std::forward<Args>(args)...);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator try_emplace(const_iterator hint, const Key& key, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.try_emplace_hint(hint, key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator try_emplace(const_iterator hint, Key&& key, Args&&... args)
    {
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
    SFL_CONSTEXPR_20
    iterator try_emplace(const_iterator hint, K&& key, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return impl_.try_emplace_hint(hint, std::forward<K>(key), std::forward<Args>(args)...);
    }

    SFL_CONSTEXPR_20
    iterator erase(iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());
        return impl_.erase(pos);
    }

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
        return impl_.erase_key_unique(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_CONSTEXPR_20
    size_type erase(K&& x)
    {
        return impl_.erase_key_unique(x);
    }

    SFL_CONSTEXPR_20
    void swap(flat_map& other)
    {
        impl_.swap(other.impl_);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator lower_bound(const Key& key)
    {
        return impl_.lower_bound(key);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator lower_bound(const Key& key) const
    {
        return impl_.lower_bound(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator lower_bound(const K& x)
    {
        return impl_.lower_bound(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator lower_bound(const K& x) const
    {
        return impl_.lower_bound(x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator upper_bound(const Key& key)
    {
        return impl_.upper_bound(key);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator upper_bound(const Key& key) const
    {
        return impl_.upper_bound(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator upper_bound(const K& x)
    {
        return impl_.upper_bound(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator upper_bound(const K& x) const
    {
        return impl_.upper_bound(x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return impl_.equal_range(key);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return impl_.equal_range(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<iterator, iterator> equal_range(const K& x)
    {
        return impl_.equal_range(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const
    {
        return impl_.equal_range(x);
    }

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
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator find(const K& x)
    {
        return impl_.find(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
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
        return impl_.count_unique(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type count(const K& x) const
    {
        return impl_.count_unique(x);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool contains(const Key& key) const
    {
        return impl_.contains(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
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
    T& at(const Key& key)
    {
        auto it = find(key);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::flat_map::at");
        }

        return it->second;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const T& at(const Key& key) const
    {
        auto it = find(key);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::flat_map::at");
        }

        return it->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    T& at(const K& x)
    {
        auto it = find(x);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::flat_map::at");
        }

        return it->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const T& at(const K& x) const
    {
        auto it = find(x);

        if (it == end())
        {
            sfl::dtl::throw_out_of_range("sfl::flat_map::at");
        }

        return it->second;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    T& operator[](const Key& key)
    {
        return try_emplace(key).first->second;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    T& operator[](Key&& key)
    {
        return try_emplace(std::move(key)).first->second;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    T& operator[](K&& key)
    {
        return try_emplace(std::forward<K>(key)).first->second;
    }

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

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator==(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator!=(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator<(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator>(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator<=(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);

    template <typename K2, typename T2, typename C2, typename A2>
    SFL_CONSTEXPR_20
    friend bool operator>=(const flat_map<K2, T2, C2, A2>& x, const flat_map<K2, T2, C2, A2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator==
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ == y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator!=
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ != y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator<
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ < y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator>
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ > y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator<=
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ <= y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator>=
(
    const flat_map<K, T, C, A>& x,
    const flat_map<K, T, C, A>& y
)
{
    return x.impl_ >= y.impl_;
}

template <typename K, typename T, typename C, typename A>
SFL_CONSTEXPR_20
void swap
(
    flat_map<K, T, C, A>& x,
    flat_map<K, T, C, A>& y
)
{
    x.swap(y);
}

template <typename K, typename T, typename C, typename A, typename Predicate>
SFL_CONSTEXPR_20
typename flat_map<K, T, C, A>::size_type
    erase_if(flat_map<K, T, C, A>& c, Predicate pred)
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

#endif // SFL_FLAT_MAP_HPP_INCLUDED

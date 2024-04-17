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

#ifndef SFL_STATIC_FLAT_SET_HPP_INCLUDED
#define SFL_STATIC_FLAT_SET_HPP_INCLUDED

#include "private.hpp"

#include <algorithm>        // copy, move, lower_bound, swap, swap_ranges
#include <cstddef>          // size_t
#include <functional>       // equal_to, less
#include <initializer_list> // initializer_list
#include <iterator>         // distance, next, reverse_iterator
#include <limits>           // numeric_limits
#include <memory>           // allocator, allocator_traits, pointer_traits
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

#ifdef SFL_TEST_STATIC_FLAT_SET
void test_static_flat_set();
#endif

namespace sfl
{

template < typename Key,
           std::size_t N,
           typename Compare = std::less<Key> >
class static_flat_set
{
    #ifdef SFL_TEST_STATIC_FLAT_SET
    friend void ::test_static_flat_set();
    #endif

public:

    using key_type               = Key;
    using value_type             = Key;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using key_compare            = Compare;
    using value_compare          = Compare;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = const_pointer; // MUST BE const_pointer
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:

    class data_base
    {
    public:

        union
        {
            value_type first_[N];
        };

        pointer last_;

        data_base() noexcept
            : last_(first_)
        {}

        ~data_base() noexcept
        {}
    };

    class data : public data_base, public value_compare
    {
    public:

        data() noexcept(std::is_nothrow_default_constructible<value_compare>::value)
            : value_compare()
        {}

        data(const value_compare& comp) noexcept(std::is_nothrow_copy_constructible<value_compare>::value)
            : value_compare(comp)
        {}

        data(value_compare&& comp) noexcept(std::is_nothrow_move_constructible<value_compare>::value)
            : value_compare(std::move(comp))
        {}

        value_compare& ref_to_comp() noexcept
        {
            return *this;
        }

        const value_compare& ref_to_comp() const noexcept
        {
            return *this;
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_flat_set() noexcept(std::is_nothrow_default_constructible<Compare>::value)
        : data_()
    {}

    ~static_flat_set()
    {
        sfl::dtl::destroy(data_.first_, data_.last_);
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    //
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    key_compare key_comp() const
    {
        return data_.ref_to_comp();
    }

    //
    // ---- VALUE COMPARE -----------------------------------------------------
    //

    SFL_NODISCARD
    value_compare value_comp() const
    {
        return data_.ref_to_comp();
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return data_.first_;
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return data_.first_;
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return data_.first_;
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return data_.last_;
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return data_.last_;
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return data_.last_;
    }

    SFL_NODISCARD
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    SFL_NODISCARD
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    SFL_NODISCARD
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    SFL_NODISCARD
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    SFL_NODISCARD
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    SFL_NODISCARD
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    SFL_NODISCARD
    iterator nth(size_type pos) noexcept
    {
        SFL_ASSERT(pos <= size());
        return data_.first_ + pos;
    }

    SFL_NODISCARD
    const_iterator nth(size_type pos) const noexcept
    {
        SFL_ASSERT(pos <= size());
        return data_.first_ + pos;
    }

    SFL_NODISCARD
    size_type index_of(const_iterator pos) const noexcept
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return std::distance(cbegin(), pos);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return data_.first_ == data_.last_;
    }

    SFL_NODISCARD
    bool full() const noexcept
    {
        return std::distance(begin(), end()) == N;
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return std::distance(begin(), end());
    }

    SFL_NODISCARD
    static size_type max_size() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    static size_type capacity() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    size_type available() const noexcept
    {
        return capacity() - size();
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear() noexcept
    {
        sfl::dtl::destroy(data_.first_, data_.last_);
        data_.last_ = data_.first_;
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        SFL_ASSERT(!full());
        return insert_aux(value_type(std::forward<Args>(args)...));
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_aux(hint, value_type(std::forward<Args>(args)...));
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        SFL_ASSERT(!full());
        return insert_aux(value);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        SFL_ASSERT(!full());
        return insert_aux(std::move(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_aux(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_aux(hint, std::move(value));
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void insert(InputIt first, InputIt last)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        insert(ilist.begin(), ilist.end());
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    iterator lower_bound(const Key& key)
    {
        return std::lower_bound(begin(), end(), key, data_.ref_to_comp());
    }

    SFL_NODISCARD
    const_iterator lower_bound(const Key& key) const
    {
        return std::lower_bound(begin(), end(), key, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator lower_bound(const K& x)
    {
        return std::lower_bound(begin(), end(), x, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator lower_bound(const K& x) const
    {
        return std::lower_bound(begin(), end(), x, data_.ref_to_comp());
    }

    SFL_NODISCARD
    iterator upper_bound(const Key& key)
    {
        return std::upper_bound(begin(), end(), key, data_.ref_to_comp());
    }

    SFL_NODISCARD
    const_iterator upper_bound(const Key& key) const
    {
        return std::upper_bound(begin(), end(), key, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator upper_bound(const K& x)
    {
        return std::upper_bound(begin(), end(), x, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator upper_bound(const K& x) const
    {
        return std::upper_bound(begin(), end(), x, data_.ref_to_comp());
    }

    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return std::equal_range(begin(), end(), key, data_.ref_to_comp());
    }

    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return std::equal_range(begin(), end(), key, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& x)
    {
        return std::equal_range(begin(), end(), x, data_.ref_to_comp());
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const
    {
        return std::equal_range(begin(), end(), x, data_.ref_to_comp());
    }

    SFL_NODISCARD
    iterator find(const Key& key)
    {
        auto it = lower_bound(key);

        if (it != end() && data_.ref_to_comp()(key, *it))
        {
            it = end();
        }

        return it;
    }

    SFL_NODISCARD
    const_iterator find(const Key& key) const
    {
        auto it = lower_bound(key);

        if (it != end() && data_.ref_to_comp()(key, *it))
        {
            it = end();
        }

        return it;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator find(const K& x)
    {
        auto it = lower_bound(x);

        if (it != end() && data_.ref_to_comp()(x, *it))
        {
            it = end();
        }

        return it;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        auto it = lower_bound(x);

        if (it != end() && data_.ref_to_comp()(x, *it))
        {
            it = end();
        }

        return it;
    }

    SFL_NODISCARD
    size_type count(const Key& key) const
    {
        return find(key) != end();
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        return find(x) != end();
    }

    SFL_NODISCARD
    bool contains(const Key& key) const
    {
        return find(key) != end();
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    bool contains(const K& x) const
    {
        return find(x) != end();
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

private:

    template <typename Value>
    std::pair<iterator, bool> insert_aux(Value&& value)
    {
        auto it = lower_bound(value);

        if (it == end() || data_.ref_to_comp()(value, *it))
        {
            return std::make_pair(insert_exactly_at(it, std::forward<Value>(value)), true);
        }

        return std::make_pair(it, false);
    }

    template <typename Value>
    iterator insert_aux(const_iterator hint, Value&& value)
    {
        if (is_insert_hint_good(hint, value))
        {
            return insert_exactly_at(hint, std::forward<Value>(value));
        }

        // Hint is not good. Use non-hinted function.
        return insert_aux(std::forward<Value>(value)).first;
    }

    template <typename... Args>
    iterator insert_exactly_at(const_iterator pos, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= pos && pos <= cend());

        const pointer p1 = data_.first_ + std::distance(cbegin(), pos);

        if (p1 == data_.last_)
        {
            sfl::dtl::construct_at
            (
                p1,
                std::forward<Args>(args)...
            );

            ++data_.last_;
        }
        else
        {
            const pointer p2 = data_.last_ - 1;

            const pointer old_last = data_.last_;

            sfl::dtl::construct_at
            (
                data_.last_,
                std::move(*p2)
            );

            ++data_.last_;

            sfl::dtl::move_backward
            (
                p1,
                p2,
                old_last
            );

            *p1 = value_type(std::forward<Args>(args)...);
        }

        return p1;
    }

    template <typename Value>
    bool is_insert_hint_good(const_iterator hint, const Value& value)
    {
        return (hint == begin() || data_.ref_to_comp()(*(hint - 1), value))
            && (hint == end()   || data_.ref_to_comp()(value, *hint));
    }
};

} // namespace sfl

#endif // SFL_STATIC_FLAT_SET_HPP_INCLUDED

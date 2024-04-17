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

#ifndef SFL_STATIC_FLAT_MULTIMAP_HPP_INCLUDED
#define SFL_STATIC_FLAT_MULTIMAP_HPP_INCLUDED

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

#ifdef SFL_TEST_STATIC_FLAT_MULTIMAP
void test_static_flat_multimap();
#endif

namespace sfl
{

template < typename Key,
           typename T,
           std::size_t N,
           typename Compare = std::less<Key> >
class static_flat_multimap
{
    #ifdef SFL_TEST_STATIC_FLAT_MULTIMAP
    friend void ::test_static_flat_multimap();
    #endif

    static_assert(N > 0, "N must be greater than zero.");

public:

    using key_type               = Key;
    using mapped_type            = T;
    using value_type             = std::pair<Key, T>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using key_compare            = Compare;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    class value_compare : protected key_compare
    {
        friend class static_flat_multimap;

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

private:

    // Like `value_compare` but with additional operators.
    // For internal use only.
    class ultra_compare : public key_compare
    {
    public:

        ultra_compare() noexcept(std::is_nothrow_default_constructible<key_compare>::value)
        {}

        ultra_compare(const key_compare& c) noexcept(std::is_nothrow_copy_constructible<key_compare>::value)
            : key_compare(c)
        {}

        ultra_compare(key_compare&& c) noexcept(std::is_nothrow_move_constructible<key_compare>::value)
            : key_compare(std::move(c))
        {}

        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_compare::operator()(x.first, y.first);
        }

        template <typename K>
        bool operator()(const value_type& x, const K& y) const
        {
            return key_compare::operator()(x.first, y);
        }

        template <typename K>
        bool operator()(const K& x, const value_type& y) const
        {
            return key_compare::operator()(x, y.first);
        }
    };

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

    class data : public data_base, public ultra_compare
    {
    public:

        data() noexcept(std::is_nothrow_default_constructible<ultra_compare>::value)
            : ultra_compare()
        {}

        data(const ultra_compare& comp) noexcept(std::is_nothrow_copy_constructible<ultra_compare>::value)
            : ultra_compare(comp)
        {}

        data(ultra_compare&& comp) noexcept(std::is_nothrow_move_constructible<ultra_compare>::value)
            : ultra_compare(std::move(comp))
        {}

        ultra_compare& ref_to_comp() noexcept
        {
            return *this;
        }

        const ultra_compare& ref_to_comp() const noexcept
        {
            return *this;
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_flat_multimap() noexcept(std::is_nothrow_default_constructible<Compare>::value)
        : data_()
    {}

    explicit static_flat_multimap(const Compare& comp) noexcept(std::is_nothrow_copy_constructible<Compare>::value)
        : data_(comp)
    {}

    ~static_flat_multimap()
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
        return value_compare(data_.ref_to_comp());
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
    iterator emplace(Args&&... args)
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

    iterator insert(const value_type& value)
    {
        SFL_ASSERT(!full());
        return insert_aux(value);
    }

    iterator insert(value_type&& value)
    {
        SFL_ASSERT(!full());
        return insert_aux(std::move(value));
    }

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P&&>::value>* = nullptr>
    iterator insert(P&& value)
    {
        SFL_ASSERT(!full());
        return insert_aux(value_type(std::forward<P>(value)));
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

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P>::value>* = nullptr>
    iterator insert(const_iterator hint, P&& value)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_aux(hint, value_type(std::forward<P>(value)));
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

    iterator erase(iterator pos)
    {
        return erase(const_iterator(pos));
    }

    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());

        const pointer p = data_.first_ + std::distance(cbegin(), pos);

        data_.last_ = sfl::dtl::move(p + 1, data_.last_, p);

        sfl::dtl::destroy_at(data_.last_);

        return p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        if (first == last)
        {
            return begin() + std::distance(cbegin(), first);
        }

        const pointer p1 = data_.first_ + std::distance(cbegin(), first);
        const pointer p2 = data_.first_ + std::distance(cbegin(), last);

        const pointer new_last = sfl::dtl::move(p2, data_.last_, p1);

        sfl::dtl::destroy(new_last, data_.last_);

        data_.last_ = new_last;

        return p1;
    }

    size_type erase(const Key& key)
    {
        const auto er = equal_range(key);
        const auto n = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return n;
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    size_type erase(K&& x)
    {
        const auto er = equal_range(x);
        const auto n = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return n;
    }

    void swap(static_flat_multimap& other)
    {
        if (this == &other)
        {
            return;
        }

        const size_type this_size  = this->size();
        const size_type other_size = other.size();

        if (this_size <= other_size)
        {
            std::swap_ranges
            (
                this->data_.first_,
                this->data_.first_ + this_size,
                other.data_.first_
            );

            sfl::dtl::uninitialized_move
            (
                other.data_.first_ + this_size,
                other.data_.first_ + other_size,
                this->data_.first_ + this_size
            );

            sfl::dtl::destroy
            (
                other.data_.first_ + this_size,
                other.data_.first_ + other_size
            );
        }
        else
        {
            std::swap_ranges
            (
                other.data_.first_,
                other.data_.first_ + other_size,
                this->data_.first_
            );

            sfl::dtl::uninitialized_move
            (
                this->data_.first_ + other_size,
                this->data_.first_ + this_size,
                other.data_.first_ + other_size
            );

            sfl::dtl::destroy
            (
                this->data_.first_ + other_size,
                this->data_.first_ + this_size
            );
        }

        data_.last_ = data_.first_ + other_size;
        other.data_.last_ = other.data_.first_ + this_size;
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
        const auto er = equal_range(key);
        return std::distance(er.first, er.second);
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<Compare, K>::value>* = nullptr>
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        const auto er = equal_range(x);
        return std::distance(er.first, er.second);
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

    SFL_NODISCARD
    value_type* data() noexcept
    {
        return data_.first_;
    }

    SFL_NODISCARD
    const value_type* data() const noexcept
    {
        return data_.first_;
    }

private:

    template <typename Value>
    iterator insert_aux(Value&& value)
    {
        return insert_exactly_at(lower_bound(value.first), std::forward<Value>(value));
    }

    template <typename Value>
    iterator insert_aux(const_iterator hint, Value&& value)
    {
        if (is_insert_hint_good(hint, value))
        {
            return insert_exactly_at(hint, std::forward<Value>(value));
        }

        // Hint is not good. Use non-hinted function.
        return insert_aux(std::forward<Value>(value));
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
            // This container can contain duplicates so we must
            // create new element now as a temporary value.
            value_type tmp(std::forward<Args>(args)...);

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

            *p1 = std::move(tmp);
        }

        return p1;
    }

    template <typename Value>
    bool is_insert_hint_good(const_iterator hint, const Value& value)
    {
        return
            // If `hint` == `value`
            (
                hint != end() &&
                !data_.ref_to_comp()(*hint, value) &&
                !data_.ref_to_comp()(value, *hint)
            )
            ||
            // If `hint - 1` == `value`
            (
                hint != begin() &&
                !data_.ref_to_comp()(*(hint - 1), value) &&
                !data_.ref_to_comp()(value, *(hint - 1))
            )
            ||
            // If `hint - 1` < `value` and `value` < `hint`
            (
                (hint == begin() || data_.ref_to_comp()(*(hint - 1), value)) &&
                (hint == end()   || data_.ref_to_comp()(value, *hint))
            );
    }
};

} // namespace sfl

#endif // SFL_STATIC_FLAT_MULTIMAP_HPP_INCLUDED
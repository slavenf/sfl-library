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

#ifndef SFL_STATIC_UNORDERED_FLAT_MAP_HPP_INCLUDED
#define SFL_STATIC_UNORDERED_FLAT_MAP_HPP_INCLUDED

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

#ifdef SFL_TEST_STATIC_UNORDERED_FLAT_MAP
void test_static_unordered_flat_map();
#endif

namespace sfl
{

template < typename Key,
           typename T,
           std::size_t N,
           typename KeyEqual = std::equal_to<Key> >
class static_unordered_flat_map
{
    #ifdef SFL_TEST_STATIC_UNORDERED_FLAT_MAP
    friend void ::test_static_unordered_flat_map();
    #endif

    static_assert(N > 0, "N must be greater than zero.");

public:

    using key_type         = Key;
    using mapped_type      = T;
    using value_type       = std::pair<Key, T>;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;
    using key_equal        = KeyEqual;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using pointer          = value_type*;
    using const_pointer    = const value_type*;
    using iterator         = pointer;
    using const_iterator   = const_pointer;

    class value_equal : protected key_equal
    {
        friend class static_unordered_flat_map;

    private:

        value_equal(const key_equal& e)
            : key_equal(e)
        {}

    public:

        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_equal::operator()(x.first, y.first);
        }
    };

private:

    // Like `value_equal` but with additional operators.
    // For internal use only.
    class ultra_equal : public key_equal
    {
    public:

        ultra_equal() noexcept(std::is_nothrow_default_constructible<key_equal>::value)
        {}

        ultra_equal(const key_equal& e) noexcept(std::is_nothrow_copy_constructible<key_equal>::value)
            : key_equal(e)
        {}

        ultra_equal(key_equal&& e) noexcept(std::is_nothrow_move_constructible<key_equal>::value)
            : key_equal(std::move(e))
        {}

        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_equal::operator()(x.first, y.first);
        }

        template <typename K>
        bool operator()(const value_type& x, const K& y) const
        {
            return key_equal::operator()(x.first, y);
        }

        template <typename K>
        bool operator()(const K& x, const value_type& y) const
        {
            return key_equal::operator()(x, y.first);
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

        #if defined(__clang__) && (__clang_major__ == 3) // For CentOS 7
        ~data_base()
        {}
        #else
        ~data_base() noexcept
        {}
        #endif
    };

    class data : public data_base, public ultra_equal
    {
    public:

        data() noexcept(std::is_nothrow_default_constructible<ultra_equal>::value)
            : ultra_equal()
        {}

        data(const ultra_equal& comp) noexcept(std::is_nothrow_copy_constructible<ultra_equal>::value)
            : ultra_equal(comp)
        {}

        data(ultra_equal&& comp) noexcept(std::is_nothrow_move_constructible<ultra_equal>::value)
            : ultra_equal(std::move(comp))
        {}

        ultra_equal& ref_to_equal() noexcept
        {
            return *this;
        }

        const ultra_equal& ref_to_equal() const noexcept
        {
            return *this;
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_unordered_flat_map() noexcept(std::is_nothrow_default_constructible<KeyEqual>::value)
        : data_()
    {}

    explicit static_unordered_flat_map(const KeyEqual& comp) noexcept(std::is_nothrow_copy_constructible<KeyEqual>::value)
        : data_(comp)
    {}

    ~static_unordered_flat_map()
    {
        sfl::dtl::destroy(data_.first_, data_.last_);
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    //
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    key_equal key_eq() const
    {
        return data_.ref_to_equal();
    }

    //
    // ---- VALUE EQUAL -------------------------------------------------------
    //

    SFL_NODISCARD
    value_equal value_eq() const
    {
        return value_equal(data_.ref_to_equal());
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

    template <typename P,
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P&&>::value>* = nullptr>
    std::pair<iterator, bool> insert(P&& value)
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
              sfl::dtl::enable_if_t<std::is_constructible<value_type, P&&>::value>* = nullptr>
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

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj)
    {
        SFL_ASSERT(!full());
        return insert_or_assign_aux(key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        return insert_or_assign_aux(std::move(key), std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    iterator insert_or_assign(const_iterator hint, const Key& key, M&& obj)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_or_assign_aux(hint, key, std::forward<M>(obj));
    }

    template <typename M,
              sfl::dtl::enable_if_t<std::is_assignable<mapped_type&, M&&>::value>* = nullptr>
    iterator insert_or_assign(const_iterator hint, Key&& key, M&& obj)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return insert_or_assign_aux(hint, std::move(key), std::forward<M>(obj));
    }

    template <typename... Args>
    std::pair<iterator, bool> try_emplace(const Key& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        return try_emplace_aux(key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    std::pair<iterator, bool> try_emplace(Key&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        return try_emplace_aux(std::move(key), std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator try_emplace(const_iterator hint, const Key& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return try_emplace_aux(hint, key, std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator try_emplace(const_iterator hint, Key&& key, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return try_emplace_aux(hint, std::move(key), std::forward<Args>(args)...);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    iterator find(const Key& key)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, key))
            {
                return it;
            }
        }

        return end();
    }

    SFL_NODISCARD
    const_iterator find(const Key& key) const
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, key))
            {
                return it;
            }
        }

        return end();
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    iterator find(const K& x)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, x))
            {
                return it;
            }
        }

        return end();
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, x))
            {
                return it;
            }
        }

        return end();
    }

    SFL_NODISCARD
    size_type count(const Key& key) const
    {
        return find(key) != end();
    }

    template <typename K,
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
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
              sfl::dtl::enable_if_t<sfl::dtl::has_is_transparent<KeyEqual, K>::value>* = nullptr>
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
        auto it = find(value.first);

        if (it == end())
        {
            return std::make_pair(insert_unordered(std::forward<Value>(value)), true);
        }

        return std::make_pair(it, false);
    }

    template <typename Value>
    iterator insert_aux(const_iterator hint, Value&& value)
    {
        sfl::dtl::ignore_unused(hint);
        return insert_aux(std::forward<Value>(value)).first;
    }

    template <typename K, typename M>
    std::pair<iterator, bool> insert_or_assign_aux(K&& key, M&& obj)
    {
        auto it = find(key);

        if (it == end())
        {
            return std::make_pair
            (
                insert_unordered
                (
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(key)),
                    std::forward_as_tuple(std::forward<M>(obj))
                ),
                true
            );
        }

        it->second = std::forward<M>(obj);
        return std::make_pair(it, false);
    }

    template <typename K, typename M>
    iterator insert_or_assign_aux(const_iterator hint, K&& key, M&& obj)
    {
        sfl::dtl::ignore_unused(hint);
        return insert_or_assign_aux(std::forward<K>(key), std::forward<M>(obj)).first;
    }

    template <typename K, typename... Args>
    std::pair<iterator, bool> try_emplace_aux(K&& key, Args&&... args)
    {
        auto it = find(key);

        if (it == end())
        {
            return std::make_pair
            (
                insert_unordered
                (
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(key)),
                    std::forward_as_tuple(std::forward<Args>(args)...)
                ),
                true
            );
        }

        return std::make_pair(it, false);
    }

    template <typename K, typename... Args>
    iterator try_emplace_aux(const_iterator hint, K&& key, Args&&... args)
    {
        sfl::dtl::ignore_unused(hint);
        return try_emplace_aux(std::forward<K>(key), std::forward<Args>(args)...).first;
    }

    template <typename... Args>
    iterator insert_unordered(Args&&... args)
    {
        SFL_ASSERT(!full());

        const pointer old_last = data_.last_;

        sfl::dtl::construct_at
        (
            data_.last_,
            std::forward<Args>(args)...
        );

        ++data_.last_;

        return old_last;
    }
};

} // namespace sfl

#endif // SFL_STATIC_UNORDERED_FLAT_MAP_HPP_INCLUDED

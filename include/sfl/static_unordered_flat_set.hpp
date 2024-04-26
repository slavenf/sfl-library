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

#ifndef SFL_STATIC_UNORDERED_FLAT_SET_HPP_INCLUDED
#define SFL_STATIC_UNORDERED_FLAT_SET_HPP_INCLUDED

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

#ifdef SFL_TEST_STATIC_UNORDERED_FLAT_SET
void test_static_unordered_flat_set();
#endif

namespace sfl
{

template < typename Key,
           std::size_t N,
           typename KeyEqual = std::equal_to<Key> >
class static_unordered_flat_set
{
    #ifdef SFL_TEST_STATIC_UNORDERED_FLAT_SET
    friend void ::test_static_unordered_flat_set();
    #endif

    static_assert(N > 0, "N must be greater than zero.");

public:

    using key_type         = Key;
    using value_type       = Key;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;
    using key_equal        = KeyEqual;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using pointer          = value_type*;
    using const_pointer    = const value_type*;
    using iterator         = const_pointer; // MUST BE const_pointer
    using const_iterator   = const_pointer;

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

        #if defined(__clang__) && (__clang_major__ == 3) // For CentOS 7
        ~data_base()
        {}
        #else
        ~data_base() noexcept
        {}
        #endif
    };

    class data : public data_base, public key_equal
    {
    public:

        data() noexcept(std::is_nothrow_default_constructible<key_equal>::value)
            : key_equal()
        {}

        data(const key_equal& equal) noexcept(std::is_nothrow_copy_constructible<key_equal>::value)
            : key_equal(equal)
        {}

        data(key_equal&& equal) noexcept(std::is_nothrow_move_constructible<key_equal>::value)
            : key_equal(std::move(equal))
        {}

        key_equal& ref_to_equal() noexcept
        {
            return *this;
        }

        const key_equal& ref_to_equal() const noexcept
        {
            return *this;
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_unordered_flat_set() noexcept(std::is_nothrow_default_constructible<KeyEqual>::value)
        : data_()
    {}

    explicit static_unordered_flat_set(const KeyEqual& equal) noexcept(std::is_nothrow_copy_constructible<KeyEqual>::value)
        : data_(equal)
    {}

    ~static_unordered_flat_set()
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
        return emplace_aux(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        return emplace_hint_aux(hint, std::forward<Args>(args)...);
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

    template <typename... Args>
    std::pair<iterator, bool> emplace_aux(Args&&... args)
    {
        const auto it1 = emplace_back(std::forward<Args>(args)...);
        const auto it2 = find(*it1);

        const bool is_unique = it1 == it2;

        if (!is_unique)
        {
            pop_back();
        }

        return std::make_pair(it2, is_unique);
    }

    template <typename... Args>
    iterator emplace_hint_aux(const_iterator hint, Args&&... args)
    {
        sfl::dtl::ignore_unused(hint);
        return emplace_aux(std::forward<Args>(args)...).first;
    }

    template <typename Value>
    std::pair<iterator, bool> insert_aux(Value&& value)
    {
        const auto it = find(value);

        if (it == end())
        {
            return std::make_pair(emplace_back(std::forward<Value>(value)), true);
        }

        return std::make_pair(it, false);
    }

    template <typename Value>
    iterator insert_aux(const_iterator hint, Value&& value)
    {
        sfl::dtl::ignore_unused(hint);
        return insert_aux(std::forward<Value>(value)).first;
    }

    template <typename... Args>
    iterator emplace_back(Args&&... args)
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

    void pop_back()
    {
        SFL_ASSERT(!empty());

        --data_.last_;

        sfl::dtl::destroy_at(data_.last_);
    }
};

} // namespace sfl

#endif // SFL_STATIC_UNORDERED_FLAT_SET_HPP_INCLUDED

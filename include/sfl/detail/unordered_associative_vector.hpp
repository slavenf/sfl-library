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

#ifndef SFL_DETAIL_UNORDERED_ASSOCIATIVE_VECTOR_HPP_INCLUDED
#define SFL_DETAIL_UNORDERED_ASSOCIATIVE_VECTOR_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/ignore_unused.hpp>
#include <sfl/detail/initialized_memory_algorithms.hpp>

#include <algorithm>    // is_permutation
#include <iterator>     // distance, next, prev
#include <tuple>        // forward_as_tuple
#include <type_traits>  // is_same
#include <utility>      // forward, move, pair, piecewise_construct

#ifdef SFL_TEST_UNORDERED_ASSOCIATIVE_VECTOR
template <int>
void test_unordered_associative_vector();
#endif

namespace sfl
{

namespace dtl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// UNORDERED ASSOCIATIVE VECTOR
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyEqual,
           typename Vector >
class unordered_associative_vector : private KeyEqual, private Vector
{
    static_assert
    (
        std::is_same<typename Vector::value_type, Value>::value,
        "Vector::value_type must be same as Value."
    );

    #ifdef SFL_TEST_UNORDERED_ASSOCIATIVE_VECTOR
    template <int>
    friend void ::test_unordered_associative_vector();
    #endif

public:

    using key_type = Key;

    using value_type = Value;

    using size_type = typename Vector::size_type;

    using difference_type = typename Vector::difference_type;

    using key_equal = KeyEqual;

    using reference = typename Vector::reference;

    using const_reference = typename Vector::const_reference;

    using pointer = typename Vector::pointer;

    using const_pointer = typename Vector::const_pointer;

    using iterator = typename Vector::iterator;

    using const_iterator = typename Vector::const_iterator;

    using vector = Vector;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    unordered_associative_vector()
        : KeyEqual()
        , Vector()
    {}

    unordered_associative_vector(const KeyEqual& equal)
        : KeyEqual(equal)
        , Vector()
    {}

    template <typename Alloc>
    unordered_associative_vector(const Alloc& alloc)
        : KeyEqual()
        , Vector(alloc)
    {}

    template <typename Alloc>
    unordered_associative_vector(const KeyEqual& equal, const Alloc& alloc)
        : KeyEqual(equal)
        , Vector(alloc)
    {}

    unordered_associative_vector(const unordered_associative_vector& other)
        : KeyEqual(other.ref_to_key_equal())
        , Vector(other.ref_to_vector())
    {}

    template <typename Alloc>
    unordered_associative_vector(const unordered_associative_vector& other, const Alloc& alloc)
        : KeyEqual(other.ref_to_key_equal())
        , Vector(other.ref_to_vector(), alloc)
    {}

    unordered_associative_vector(unordered_associative_vector&& other)
        : KeyEqual(std::move(other.ref_to_key_equal()))
        , Vector(std::move(other.ref_to_vector()))
    {}

    template <typename Alloc>
    unordered_associative_vector(unordered_associative_vector&& other, const Alloc& alloc)
        : KeyEqual(std::move(other.ref_to_key_equal()))
        , Vector(std::move(other.ref_to_vector()), alloc)
    {}

    ~unordered_associative_vector()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    // This is deleted. Use `assign_copy` instead.
    unordered_associative_vector& operator=(const unordered_associative_vector& other) = delete;

    // This is deleted. Use `assign_move` instead.
    unordered_associative_vector& operator=(unordered_associative_vector&& other) = delete;

    void assign_copy(const unordered_associative_vector& other)
    {
        if (this != &other)
        {
            ref_to_key_equal() = other.ref_to_key_equal();
            ref_to_vector() = other.ref_to_vector();
        }
    }

    void assign_move(unordered_associative_vector& other)
    {
        ref_to_key_equal() = std::move(other.ref_to_key_equal());
        ref_to_vector() = std::move(other.ref_to_vector());
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void assign_range_equal(InputIt first, InputIt last)
    {
        auto it = begin();

        while (first != last && it != end())
        {
            *it = *first;
            ++it;
            ++first;
        }

        if (first != last)
        {
            do
            {
                emplace_equal(*first);
                ++first;
            }
            while (first != last);
        }
        else if (it != end())
        {
            erase(it, end());
        }
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void assign_range_unique(InputIt first, InputIt last)
    {
        clear();

        while (first != last)
        {
            insert_unique(*first);
            ++first;
        }
    }

    //
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    KeyEqual& ref_to_key_equal() noexcept
    {
        return *this;
    }

    SFL_NODISCARD
    const KeyEqual& ref_to_key_equal() const noexcept
    {
        return *this;
    }

    //
    // ---- VECTOR ------------------------------------------------------------
    //

    SFL_NODISCARD
    Vector& ref_to_vector() noexcept
    {
        return *this;
    }

    SFL_NODISCARD
    const Vector& ref_to_vector() const noexcept
    {
        return *this;
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return ref_to_vector().begin();
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return ref_to_vector().begin();
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return ref_to_vector().cbegin();
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return ref_to_vector().end();
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return ref_to_vector().end();
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return ref_to_vector().cend();
    }

    SFL_NODISCARD
    iterator nth(size_type pos) noexcept
    {
        return ref_to_vector().nth(pos);
    }

    SFL_NODISCARD
    const_iterator nth(size_type pos) const noexcept
    {
        return ref_to_vector().nth(pos);
    }

    SFL_NODISCARD
    size_type index_of(const_iterator pos) const noexcept
    {
        return ref_to_vector().index_of(pos);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return ref_to_vector().empty();
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return ref_to_vector().size();
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return ref_to_vector().max_size();
    }

    SFL_NODISCARD
    size_type capacity() const noexcept
    {
        return ref_to_vector().capacity();
    }

    SFL_NODISCARD
    size_type available() const noexcept
    {
        return ref_to_vector().available();
    }

    void reserve(size_type new_cap)
    {
        ref_to_vector().reserve(new_cap);
    }

    void shrink_to_fit()
    {
        ref_to_vector().shrink_to_fit();
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear() noexcept
    {
        ref_to_vector().clear();
    }

    template <typename... Args>
    iterator emplace_equal(Args&&... args)
    {
        return ref_to_vector().emplace(end(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace_unique(Args&&... args)
    {
        auto it1 = ref_to_vector().emplace(end(), std::forward<Args>(args)...);
        auto it2 = find(KeyOfValue()(*it1));

        bool is_unique = it1 == it2;

        if (!is_unique)
        {
            ref_to_vector().pop_back();
        }

        return std::make_pair(it2, is_unique);
    }

    template <typename... Args>
    iterator emplace_hint_equal(const_iterator hint, Args&&... args)
    {
        sfl::dtl::ignore_unused(hint);
        return ref_to_vector().emplace(end(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint_unique(const_iterator hint, Args&&... args)
    {
        sfl::dtl::ignore_unused(hint);

        auto it1 = ref_to_vector().emplace(end(), std::forward<Args>(args)...);
        auto it2 = find(KeyOfValue()(*it1));

        bool is_unique = it1 == it2;

        if (!is_unique)
        {
            ref_to_vector().pop_back();
        }

        return it2;
    }

    template <typename V>
    iterator insert_equal(V&& value)
    {
        return ref_to_vector().emplace(end(), std::forward<V>(value));
    }

    template <typename V>
    std::pair<iterator, bool> insert_unique(V&& value)
    {
        auto it = find(KeyOfValue()(value));
        if (it == end())
        {
            return std::make_pair(ref_to_vector().emplace(end(), std::forward<V>(value)), true);
        }
        else
        {
            return std::make_pair(it, false);
        }
    }

    template <typename V>
    iterator insert_hint_equal(const_iterator hint, V&& value)
    {
        sfl::dtl::ignore_unused(hint);
        return ref_to_vector().emplace(end(), std::forward<V>(value));
    }

    template <typename V>
    iterator insert_hint_unique(const_iterator hint, V&& value)
    {
        auto it = find_hint(hint, KeyOfValue()(value));
        if (it == end())
        {
            return ref_to_vector().emplace(end(), std::forward<V>(value));
        }
        else
        {
            return it;
        }
    }

    template <typename K, typename M>
    std::pair<iterator, bool> insert_or_assign(K&& k, M&& obj)
    {
        auto it = find(k);
        if (it != end())
        {
            it->second = std::forward<M>(obj);
            return std::make_pair(it, false);
        }
        else
        {
            return std::make_pair
            (
                ref_to_vector().emplace
                (
                    end(),
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(k)),
                    std::forward_as_tuple(std::forward<M>(obj))
                ),
                true
            );
        }
    }

    template <typename K, typename M>
    iterator insert_or_assign_hint(const_iterator hint, K&& k, M&& obj)
    {
        auto it = find_hint(hint, k);
        if (it != end())
        {
            it->second = std::forward<M>(obj);
            return it;
        }
        else
        {
            return ref_to_vector().emplace
            (
                end(),
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<M>(obj))
            );
        }
    }

    template <typename K, typename... Args>
    std::pair<iterator, bool> try_emplace(K&& k, Args&&... args)
    {
        auto it = find(k);
        if (it != end())
        {
            return std::make_pair(it, false);
        }
        else
        {
            return std::make_pair
            (
                ref_to_vector().emplace
                (
                    end(),
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(k)),
                    std::forward_as_tuple(std::forward<Args>(args)...)
                ),
                true
            );
        }
    }

    template <typename K, typename... Args>
    iterator try_emplace_hint(const_iterator hint, K&& k, Args&&... args)
    {
        auto it = find_hint(hint, k);
        if (it != end())
        {
            return it;
        }
        else
        {
            return ref_to_vector().emplace
            (
                end(),
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<Args>(args)...)
            );
        }
    }

    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());

        auto it = std::next(begin(), std::distance(cbegin(), pos));

        auto last = std::prev(end());

        if (it != last)
        {
            *it = std::move(*last);
        }

        ref_to_vector().pop_back();

        return it;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        auto it1 = std::next(begin(), std::distance(cbegin(), first));

        if (first == last)
        {
            return it1;
        }

        auto count1 = std::distance(first, last);
        auto count2 = std::distance(last, cend());

        if (count1 >= count2)
        {
            ref_to_vector().erase(first, last);
        }
        else
        {
            auto it2 = std::next(it1, count2);

            sfl::dtl::move(it2, end(), it1);

            ref_to_vector().erase(it2, end());
        }

        return it1;
    }

    template <typename K>
    size_type erase_key_equal(const K& k)
    {
        size_type n = 0;

        for (auto it = begin(); it != end();)
        {
            if (ref_to_key_equal()(KeyOfValue()(*it), k))
            {
                it = erase(it);
                ++n;
            }
            else
            {
                ++it;
            }
        }

        return n;
    }

    template <typename K>
    size_type erase_key_unique(const K& k)
    {
        auto it = find(k);

        if (it != end())
        {
            erase(it);
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void swap(unordered_associative_vector& other)
    {
        using std::swap;
        swap(ref_to_key_equal(), other.ref_to_key_equal());
        swap(ref_to_vector(), other.ref_to_vector());
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    template <typename K>
    SFL_NODISCARD
    iterator find(const K& k)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (ref_to_key_equal()(KeyOfValue()(*it), k))
            {
                return it;
            }
        }

        return end();
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator find(const K& k) const
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (ref_to_key_equal()(KeyOfValue()(*it), k))
            {
                return it;
            }
        }

        return end();
    }

    template <typename K>
    SFL_NODISCARD
    size_type count_equal(const K& k) const
    {
        size_type n = 0;

        for (auto it = begin(); it != end(); ++it)
        {
            if (ref_to_key_equal()(KeyOfValue()(*it), k))
            {
                ++n;
            }
        }

        return n;
    }

    template <typename K>
    SFL_NODISCARD
    size_type count_unique(const K& k) const
    {
        return find(k) != end() ? 1 : 0;
    }

    template <typename K>
    SFL_NODISCARD
    bool contains(const K& k) const
    {
        return find(k) != end();
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

    SFL_NODISCARD
    value_type* data() noexcept
    {
        return ref_to_vector().data();
    }

    SFL_NODISCARD
    const value_type* data() const noexcept
    {
        return ref_to_vector().data();
    }

private:

    template <typename K>
    iterator find_hint(const_iterator hint, const K& k)
    {
        if (hint != end() && ref_to_key_equal()(KeyOfValue()(*hint), k))
        {
            return std::next(begin(), std::distance(cbegin(), hint));
        }

        for (auto it = begin(); it != end(); ++it)
        {
            if (ref_to_key_equal()(KeyOfValue()(*it), k))
            {
                return it;
            }
        }

        return end();
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// NON-MEMBER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator==
(
    const unordered_associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const unordered_associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return x.size() == y.size() && std::is_permutation(x.begin(), x.end(), y.begin());
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator!=
(
    const unordered_associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const unordered_associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return !(x == y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_UNORDERED_ASSOCIATIVE_VECTOR_HPP_INCLUDED

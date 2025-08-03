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

#ifndef SFL_DETAIL_ASSOCIATIVE_VECTOR_HPP_INCLUDED
#define SFL_DETAIL_ASSOCIATIVE_VECTOR_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/type_traits.hpp>

#include <algorithm>    // lexicographical_compare, lower_bound, upper_bound
#include <iterator>     // distance, next, prev
#include <tuple>        // forward_as_tuple
#include <type_traits>  // is_same
#include <utility>      // forward, move, pair, piecewise_construct

#ifdef SFL_TEST_ASSOCIATIVE_VECTOR
template <int>
void test_associative_vector();
#endif

namespace sfl
{

namespace dtl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ASSOCIATIVE VECTOR
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Vector >
class associative_vector : private KeyCompare, private Vector
{
    static_assert
    (
        std::is_same<typename Vector::value_type, Value>::value,
        "Vector::value_type must be same as Value."
    );

    #ifdef SFL_TEST_ASSOCIATIVE_VECTOR
    template <int>
    friend void ::test_associative_vector();
    #endif

public:

    using key_type = Key;

    using value_type = Value;

    using size_type = typename Vector::size_type;

    using difference_type = typename Vector::difference_type;

    using key_compare = KeyCompare;

    using reference = typename Vector::reference;

    using const_reference = typename Vector::const_reference;

    using pointer = typename Vector::pointer;

    using const_pointer = typename Vector::const_pointer;

    using iterator = typename Vector::iterator;

    using const_iterator = typename Vector::const_iterator;

    using reverse_iterator = typename Vector::reverse_iterator;

    using const_reverse_iterator = typename Vector::const_reverse_iterator;

    using vector = Vector;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    associative_vector()
        : KeyCompare()
        , Vector()
    {}

    associative_vector(const KeyCompare& comp)
        : KeyCompare(comp)
        , Vector()
    {}

    template <typename Alloc>
    associative_vector(const Alloc& alloc)
        : KeyCompare()
        , Vector(alloc)
    {}

    template <typename Alloc>
    associative_vector(const KeyCompare& comp, const Alloc& alloc)
        : KeyCompare(comp)
        , Vector(alloc)
    {}

    associative_vector(const associative_vector& other)
        : KeyCompare(other.ref_to_key_compare())
        , Vector(other.ref_to_vector())
    {}

    template <typename Alloc>
    associative_vector(const associative_vector& other, const Alloc& alloc)
        : KeyCompare(other.ref_to_key_compare())
        , Vector(other.ref_to_vector(), alloc)
    {}

    associative_vector(associative_vector&& other)
        : KeyCompare(std::move(other.ref_to_key_compare()))
        , Vector(std::move(other.ref_to_vector()))
    {}

    template <typename Alloc>
    associative_vector(associative_vector&& other, const Alloc& alloc)
        : KeyCompare(std::move(other.ref_to_key_compare()))
        , Vector(std::move(other.ref_to_vector()), alloc)
    {}

    ~associative_vector()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    // This is deleted. Use `assign_copy` instead.
    associative_vector& operator=(const associative_vector& other) = delete;

    // This is deleted. Use `assign_move` instead.
    associative_vector& operator=(associative_vector&& other) = delete;

    void assign_copy(const associative_vector& other)
    {
        if (this != &other)
        {
            ref_to_key_compare() = other.ref_to_key_compare();
            ref_to_vector() = other.ref_to_vector();
        }
    }

    void assign_move(associative_vector& other)
    {
        ref_to_key_compare() = std::move(other.ref_to_key_compare());
        ref_to_vector() = std::move(other.ref_to_vector());
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void assign_range_equal(InputIt first, InputIt last)
    {
        clear();

        while (first != last)
        {
            insert_equal(*first);
            ++first;
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
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    KeyCompare& ref_to_key_compare() noexcept
    {
        return *this;
    }

    SFL_NODISCARD
    const KeyCompare& ref_to_key_compare() const noexcept
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
    reverse_iterator rbegin() noexcept
    {
        return ref_to_vector().rbegin();
    }

    SFL_NODISCARD
    const_reverse_iterator rbegin() const noexcept
    {
        return ref_to_vector().rbegin();
    }

    SFL_NODISCARD
    const_reverse_iterator crbegin() const noexcept
    {
        return ref_to_vector().crbegin();
    }

    SFL_NODISCARD
    reverse_iterator rend() noexcept
    {
        return ref_to_vector().rend();
    }

    SFL_NODISCARD
    const_reverse_iterator rend() const noexcept
    {
        return ref_to_vector().rend();
    }

    SFL_NODISCARD
    const_reverse_iterator crend() const noexcept
    {
        return ref_to_vector().crend();
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
        value_type v(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_equal(KeyOfValue()(v));
        return ref_to_vector().emplace(res.pos, std::move(v));
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace_unique(Args&&... args)
    {
        value_type v(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_unique(KeyOfValue()(v));
        if (res.status)
        {
            return std::make_pair(ref_to_vector().emplace(res.pos, std::move(v)), true);
        }
        else
        {
            return std::make_pair(res.pos, false);
        }
    }

    template <typename... Args>
    iterator emplace_hint_equal(const_iterator hint, Args&&... args)
    {
        value_type v(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_hint_equal(hint, KeyOfValue()(v));
        return ref_to_vector().emplace(res.pos, std::move(v));
    }

    template <typename... Args>
    iterator emplace_hint_unique(const_iterator hint, Args&&... args)
    {
        value_type v(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_hint_unique(hint, KeyOfValue()(v));
        if (res.status)
        {
            return ref_to_vector().emplace(res.pos, std::move(v));
        }
        else
        {
            return res.pos;
        }
    }

    template <typename V>
    iterator insert_equal(V&& value)
    {
        auto res = calculate_position_for_insert_equal(KeyOfValue()(value));
        return ref_to_vector().emplace(res.pos, std::forward<V>(value));
    }

    template <typename V>
    std::pair<iterator, bool> insert_unique(V&& value)
    {
        auto res = calculate_position_for_insert_unique(KeyOfValue()(value));
        if (res.status)
        {
            return std::make_pair(ref_to_vector().emplace(res.pos, std::forward<V>(value)), true);
        }
        else
        {
            return std::make_pair(res.pos, false);
        }
    }

    template <typename V>
    iterator insert_hint_equal(const_iterator hint, V&& value)
    {
        auto res = calculate_position_for_insert_hint_equal(hint, KeyOfValue()(value));
        return ref_to_vector().emplace(res.pos, std::forward<V>(value));
    }

    template <typename V>
    iterator insert_hint_unique(const_iterator hint, V&& value)
    {
        auto res = calculate_position_for_insert_hint_unique(hint, KeyOfValue()(value));
        if (res.status)
        {
            return ref_to_vector().emplace(res.pos, std::forward<V>(value));
        }
        else
        {
            return res.pos;
        }
    }

    template <typename K, typename M>
    std::pair<iterator, bool> insert_or_assign(K&& k, M&& obj)
    {
        auto res = calculate_position_for_insert_unique(k);
        if (res.status)
        {
            return std::make_pair
            (
                ref_to_vector().emplace
                (
                    res.pos,
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(k)),
                    std::forward_as_tuple(std::forward<M>(obj))
                ),
                true
            );
        }
        else
        {
            res.pos->second = std::forward<M>(obj);
            return std::make_pair(res.pos, false);
        }
    }

    template <typename K, typename M>
    iterator insert_or_assign_hint(const_iterator hint, K&& k, M&& obj)
    {
        auto res = calculate_position_for_insert_hint_unique(hint, k);
        if (res.status)
        {
            return ref_to_vector().emplace
            (
                res.pos,
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<M>(obj))
            );
        }
        else
        {
            res.pos->second = std::forward<M>(obj);
            return res.pos;
        }
    }

    template <typename K, typename... Args>
    std::pair<iterator, bool> try_emplace(K&& k, Args&&... args)
    {
        auto res = calculate_position_for_insert_unique(k);
        if (res.status)
        {
            return std::make_pair
            (
                ref_to_vector().emplace
                (
                    res.pos,
                    std::piecewise_construct,
                    std::forward_as_tuple(std::forward<K>(k)),
                    std::forward_as_tuple(std::forward<Args>(args)...)
                ),
                true
            );
        }
        else
        {
            return std::make_pair(res.pos, false);
        }
    }

    template <typename K, typename... Args>
    iterator try_emplace_hint(const_iterator hint, K&& k, Args&&... args)
    {
        auto res = calculate_position_for_insert_hint_unique(hint, k);
        if (res.status)
        {
            return ref_to_vector().emplace
            (
                res.pos,
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<Args>(args)...)
            );
        }
        else
        {
            return res.pos;
        }
    }

    iterator erase(const_iterator pos)
    {
        return ref_to_vector().erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        return ref_to_vector().erase(first, last);
    }

    template <typename K>
    size_type erase_key_equal(const K& k)
    {
        auto er = equal_range(k);
        auto sz = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return sz;
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

    void swap(associative_vector& other)
    {
        using std::swap;
        swap(ref_to_key_compare(), other.ref_to_key_compare());
        swap(ref_to_vector(), other.ref_to_vector());
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    template <typename K>
    SFL_NODISCARD
    iterator lower_bound(const K& k)
    {
        return std::lower_bound
        (
            begin(),
            end(),
            k,
            [&](const value_type& v, const K& k)
            {
                return ref_to_key_compare()(KeyOfValue()(v), k);
            }
        );
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator lower_bound(const K& k) const
    {
        return std::lower_bound
        (
            begin(),
            end(),
            k,
            [&](const value_type& v, const K& k)
            {
                return ref_to_key_compare()(KeyOfValue()(v), k);
            }
        );
    }

    template <typename K>
    SFL_NODISCARD
    iterator upper_bound(const K& k)
    {
        return std::upper_bound
        (
            begin(),
            end(),
            k,
            [&](const K& k, const value_type& v)
            {
                return ref_to_key_compare()(k, KeyOfValue()(v));
            }
        );
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator upper_bound(const K& k) const
    {
        return std::upper_bound
        (
            begin(),
            end(),
            k,
            [&](const K& k, const value_type& v)
            {
                return ref_to_key_compare()(k, KeyOfValue()(v));
            }
        );
    }

    template <typename K>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& k)
    {
        return std::make_pair(lower_bound(k), upper_bound(k));
    }

    template <typename K>
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& k) const
    {
        return std::make_pair(lower_bound(k), upper_bound(k));
    }

    template <typename K>
    SFL_NODISCARD
    iterator find(const K& k)
    {
        auto it = lower_bound(k);

        if (it != end() && ref_to_key_compare()(k, KeyOfValue()(*it)))
        {
            it = end();
        }

        return it;
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator find(const K& k) const
    {
        auto it = lower_bound(k);

        if (it != end() && ref_to_key_compare()(k, KeyOfValue()(*it)))
        {
            it = end();
        }

        return it;
    }

    template <typename K>
    SFL_NODISCARD
    size_type count_equal(const K& k) const
    {
        auto er = equal_range(k);
        return std::distance(er.first, er.second);
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

    struct position_for_insert_equal
    {
        iterator pos;
    };

    struct position_for_insert_unique
    {
        iterator pos;
        bool     status;
    };

    template <typename K>
    position_for_insert_equal calculate_position_for_insert_equal(const K& k)
    {
        return position_for_insert_equal{lower_bound(k)};
    }

    template <typename K>
    position_for_insert_unique calculate_position_for_insert_unique(const K& k)
    {
        iterator it = lower_bound(k);

        if (it == end() || ref_to_key_compare()(k, KeyOfValue()(*it)))
        {
            return position_for_insert_unique{it, true};
        }
        else
        {
            return position_for_insert_unique{it, false};
        }
    }

    template <typename K>
    position_for_insert_equal calculate_position_for_insert_hint_equal(const_iterator hint, const K& k)
    {
        if
        (
            (hint == begin() || !ref_to_key_compare()(k, KeyOfValue()(*std::prev(hint)))) && // prev(hint) <= k
            (hint == end()   || !ref_to_key_compare()(KeyOfValue()(*hint), k))               // k <= hint
        )
        {
            return position_for_insert_equal{std::next(begin(), std::distance(cbegin(), hint))};
        }
        else
        {
            return calculate_position_for_insert_equal(k);
        }
    }

    template <typename K>
    position_for_insert_unique calculate_position_for_insert_hint_unique(const_iterator hint, const K& k)
    {
        if
        (
            (hint == begin() || ref_to_key_compare()(KeyOfValue()(*std::prev(hint)), k)) && // prev(hint) < k
            (hint == end()   || ref_to_key_compare()(k, KeyOfValue()(*hint)))               // k < hint
        )
        {
            return position_for_insert_unique{std::next(begin(), std::distance(cbegin(), hint)), true};
        }
        else
        {
            return calculate_position_for_insert_unique(k);
        }
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
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator!=
(
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return !(x == y);
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator<
(
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator>
(
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return y < x;
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator<=
(
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return !(y < x);
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
SFL_NODISCARD
bool operator>=
(
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& x,
    const associative_vector<TP1, TP2, TP3, TP4, TP5>& y
)
{
    return !(x < y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_ASSOCIATIVE_VECTOR_HPP_INCLUDED

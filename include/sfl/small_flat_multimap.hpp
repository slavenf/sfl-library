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

#ifndef SFL_SMALL_FLAT_MULTIMAP_HPP
#define SFL_SMALL_FLAT_MULTIMAP_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#define SFL_ASSERT(x) assert(x)

#define SFL_DTL_BEGIN  namespace dtl { namespace small_flat_multimap_dtl {
#define SFL_DTL_END    } }
#define SFL_DTL        dtl::small_flat_multimap_dtl

#if __cplusplus >= 201703L
    #define SFL_NODISCARD [[nodiscard]]
#else
    #define SFL_NODISCARD
#endif

#define SFL_UNUSED(x)

namespace sfl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SFL_DTL_BEGIN /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// ---- UNINITIALIZED MEMORY ALGORITHMS ---------------------------------------
//

template <typename Allocator, typename Size>
inline auto allocate(Allocator& a, Size n)
-> typename std::allocator_traits<Allocator>::pointer
{
    if (n != 0)
    {
        return std::allocator_traits<Allocator>::allocate(a, n);
    }
    return nullptr;
}

template <typename Allocator, typename Pointer, typename Size>
inline void deallocate(Allocator& a, Pointer p, Size n)
{
    if (p != nullptr)
    {
        std::allocator_traits<Allocator>::deallocate(a, p, n);
    }
}

template <typename Allocator, typename Pointer, typename... Args>
inline void construct_at(Allocator& a, Pointer p, Args&&... args)
{
    std::allocator_traits<Allocator>::construct(a, p, std::forward<Args>(args)...);
}

template <typename Allocator, typename Pointer>
inline void destroy_at(Allocator& a, Pointer p)
{
    std::allocator_traits<Allocator>::destroy(a, p);
}

template <typename Allocator, typename ForwardIt>
inline void destroy(Allocator& a, ForwardIt first, ForwardIt last)
{
    while (first != last)
    {
        destroy_at(a, std::addressof(*first));
        ++first;
    }
}

template <typename Allocator, typename ForwardIt, typename Size>
inline void destroy_n(Allocator& a, ForwardIt first, Size n)
{
    while (n > 0)
    {
        destroy_at(a, std::addressof(*first));
        ++first;
        --n;
    }
}

template <typename Allocator, typename ForwardIt, typename Size>
inline ForwardIt uninitialized_default_construct_n
(
    Allocator& a, ForwardIt first, Size n
)
{
    ForwardIt curr = first;
    try
    {
        while (n > 0)
        {
            construct_at(a, std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    catch (...)
    {
        destroy(a, first, curr);
        throw;
    }
}

template <typename Allocator, typename ForwardIt, typename Size, typename T>
inline ForwardIt uninitialized_fill_n
(
    Allocator& a, ForwardIt first, Size n, const T& value
)
{
    ForwardIt curr = first;
    try
    {
        while (n > 0)
        {
            construct_at(a, std::addressof(*curr), value);
            ++curr;
            --n;
        }
        return curr;
    }
    catch (...)
    {
        destroy(a, first, curr);
        throw;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_copy
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    try
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), *first);
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    catch (...)
    {
        destroy(a, d_first, d_curr);
        throw;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_move
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    try
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), std::move(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    catch (...)
    {
        destroy(a, d_first, d_curr);
        throw;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_move_if_noexcept
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    try
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), std::move_if_noexcept(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    catch (...)
    {
        destroy(a, d_first, d_curr);
        throw;
    }
}

//
// ---- TYPE TRAITS -----------------------------------------------------------
//

template <typename Iterator, typename = void>
struct is_input_iterator : std::false_type {};

template <typename Iterator>
struct is_input_iterator<
    Iterator,
    typename std::enable_if<
        std::is_convertible<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::input_iterator_tag
        >::value
    >::type
> : std::true_type {};

template <typename...>
using void_t = void;

template <typename Type, typename SfinaeType, typename = void>
struct has_is_transparent : std::false_type {};

template <typename Type, typename SfinaeType>
struct has_is_transparent<
    Type, SfinaeType, void_t<typename Type::is_transparent>
> : std::true_type {};

//
// ---- EXCEPTIONS ------------------------------------------------------------
//

[[noreturn]]
inline void throw_length_error(const char* msg)
{
    throw std::length_error(msg);
}

[[noreturn]]
inline void throw_out_of_range(const char* msg)
{
    throw std::out_of_range(msg);
}

//
// ---- SMALL FLAT MULTIMAP ---------------------------------------------------
//

template <typename T, typename Pointer, std::size_t N>
class small_flat_multimap_data
{
private:

    alignas(T) unsigned char internal_storage_[N * sizeof(T)];

public:

    Pointer first_;
    Pointer last_;
    Pointer end_;

    small_flat_multimap_data() noexcept
        : first_(reinterpret_cast<Pointer>(internal_storage_))
        , last_(first_)
        , end_(first_ + N)
    {}

    Pointer internal_storage() noexcept
    {
        return reinterpret_cast<Pointer>(internal_storage_);
    }
};

template <typename T, typename Pointer>
class small_flat_multimap_data<T, Pointer, 0>
{
public:

    Pointer first_;
    Pointer last_;
    Pointer end_;

    small_flat_multimap_data() noexcept
        : first_(nullptr)
        , last_(nullptr)
        , end_(nullptr)
    {}

    Pointer internal_storage() noexcept
    {
        return nullptr;
    }
};

template <typename Key, typename T, typename Compare>
class small_flat_multimap_compare : public Compare
{
public:

    small_flat_multimap_compare() noexcept
    (
        std::is_nothrow_default_constructible<Compare>::value
    )
    {}

    small_flat_multimap_compare(const Compare& c) noexcept
    (
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : Compare(c)
    {}

    bool operator()(const std::pair<Key, T>& x, const std::pair<Key, T>& y) const
    {
        return Compare::operator()(x.first, y.first);
    }

    template <typename K>
    bool operator()(const std::pair<Key, T>& x, const K& y) const
    {
        return Compare::operator()(x.first, y);
    }

    template <typename K>
    bool operator()(const K& x, const std::pair<Key, T>& y) const
    {
        return Compare::operator()(x, y.first);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SFL_DTL_END ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// ---- SMALL FLAT MULTIMAP ---------------------------------------------------
//

template < typename Key,
           typename T,
           std::size_t N,
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<std::pair<Key, T>> >
class small_flat_multimap
    : private Allocator
    , private SFL_DTL::small_flat_multimap_compare<Key, T, Compare>
{
private:

    using MyCompare = SFL_DTL::small_flat_multimap_compare<Key, T, Compare>;

public:

    using allocator_type         = Allocator;
    using allocator_traits       = std::allocator_traits<allocator_type>;
    using key_type               = Key;
    using mapped_type            = T;
    using value_type             = std::pair<Key, T>;
    using size_type              = typename allocator_traits::size_type;
    using difference_type        = typename allocator_traits::difference_type;
    using key_compare            = Compare;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = typename allocator_traits::pointer;
    using const_pointer          = typename allocator_traits::const_pointer;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    class value_compare : private key_compare
    {
        friend class small_flat_multimap;

    private:

        value_compare(const key_compare& c) : key_compare(c)
        {}

    public:

        bool operator()(const value_type& x, const value_type& y) const
        {
            return key_compare::operator()(x.first, y.first);
        }
    };

    static_assert
    (
        std::is_same<typename Allocator::value_type, value_type>::value,
        "Allocator::value_type must be same as sfl::small_flat_multimap::value_type."
    );

private:

    SFL_DTL::small_flat_multimap_data<value_type, pointer, N> data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    small_flat_multimap() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : Allocator()
        , MyCompare()
    {}

    explicit small_flat_multimap(const Compare& comp) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : Allocator()
        , MyCompare(comp)
    {}

    explicit small_flat_multimap(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : Allocator(alloc)
        , MyCompare()
    {}

    explicit small_flat_multimap(const Compare& comp, const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : Allocator(alloc)
        , MyCompare(comp)
    {}

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_multimap(InputIt first, InputIt last)
        : Allocator()
        , MyCompare()
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_multimap(InputIt first, InputIt last, const Compare& comp)
        : Allocator()
        , MyCompare(comp)
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_multimap(InputIt first, InputIt last, const Allocator& alloc)
        : Allocator(alloc)
        , MyCompare()
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_multimap(InputIt first, InputIt last, const Compare& comp,
                                                     const Allocator& alloc)
        : Allocator(alloc)
        , MyCompare(comp)
    {
        initialize_range(first, last);
    }

    small_flat_multimap(std::initializer_list<value_type> ilist)
        : small_flat_multimap(ilist.begin(), ilist.end())
    {}

    small_flat_multimap(std::initializer_list<value_type> ilist,
                   const Compare& comp)
        : small_flat_multimap(ilist.begin(), ilist.end(), comp)
    {}

    small_flat_multimap(std::initializer_list<value_type> ilist,
                   const Allocator& alloc)
        : small_flat_multimap(ilist.begin(), ilist.end(), alloc)
    {}

    small_flat_multimap(std::initializer_list<value_type> ilist,
                        const Compare& comp, const Allocator& alloc)
        : small_flat_multimap(ilist.begin(), ilist.end(), comp, alloc)
    {}

    small_flat_multimap(const small_flat_multimap& other)
        : Allocator
        (
            allocator_traits::select_on_container_copy_construction
            (
                other.ref_to_alloc()
            )
        )
        , MyCompare(other.ref_to_comp())
    {
        initialize_copy(other);
    }

    small_flat_multimap(const small_flat_multimap& other, const Allocator& alloc)
        : Allocator(alloc)
        , MyCompare(other.ref_to_comp())
    {
        initialize_copy(other);
    }

    small_flat_multimap(small_flat_multimap&& other)
        : Allocator(std::move(other.ref_to_alloc()))
        , MyCompare(std::move(other.ref_to_comp()))
    {
        initialize_move(other);
    }

    small_flat_multimap(small_flat_multimap&& other, const Allocator& alloc)
        : Allocator(alloc)
        , MyCompare(std::move(other.ref_to_comp()))
    {
        initialize_move(other);
    }

    ~small_flat_multimap()
    {
        SFL_DTL::destroy
        (
            ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        if (data_.first_ != data_.internal_storage())
        {
            SFL_DTL::deallocate
            (
                ref_to_alloc(),
                data_.first_,
                data_.end_ - data_.first_
            );
        }
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    small_flat_multimap& operator=(const small_flat_multimap& other)
    {
        assign_copy(other);
        return *this;
    }

    small_flat_multimap& operator=(small_flat_multimap&& other)
    {
        assign_move(other);
        return *this;
    }

    small_flat_multimap& operator=(std::initializer_list<value_type> ilist)
    {
        clear();
        insert(ilist.begin(), ilist.end());
        return *this;
    }

    //
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    allocator_type get_allocator() const noexcept
    {
        return ref_to_alloc();
    }

    //
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    key_compare key_comp() const
    {
        return ref_to_comp();
    }

    //
    // ---- VALUE COMPARE -----------------------------------------------------
    //

    SFL_NODISCARD
    value_compare value_comp() const
    {
        return value_compare(ref_to_comp());
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
        return pos - cbegin();
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return data_.last_ == data_.first_;
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return data_.last_ - data_.first_;
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return std::min<size_type>
        (
            allocator_traits::max_size(ref_to_alloc()),
            std::numeric_limits<difference_type>::max() / sizeof(value_type)
        );
    }

    SFL_NODISCARD
    size_type capacity() const noexcept
    {
        return data_.end_ - data_.first_;
    }

    void reserve(size_type new_cap)
    {
        check_size(new_cap, "sfl::small_flat_multimap::reserve");

        if (new_cap > capacity())
        {
            if (new_cap <= N)
            {
                if (data_.first_ == data_.internal_storage())
                {
                    // Do nothing. We are already using internal storage.
                }
                else
                {
                    // We are not using internal storage but new capacity
                    // can fit in internal storage.

                    pointer new_first = data_.internal_storage();
                    pointer new_last  = new_first;
                    pointer new_end   = new_first + N;

                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );

                    SFL_DTL::destroy
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_
                    );

                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.end_ - data_.first_
                    );

                    data_.first_ = new_first;
                    data_.last_  = new_last;
                    data_.end_   = new_end;
                }
            }
            else
            {
                pointer new_first = SFL_DTL::allocate(ref_to_alloc(), new_cap);
                pointer new_last  = new_first;
                pointer new_end   = new_first + new_cap;

                try
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                catch (...)
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    throw;
                }

                SFL_DTL::destroy
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.last_
                );

                if (data_.first_ != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.end_ - data_.first_
                    );
                }

                data_.first_ = new_first;
                data_.last_  = new_last;
                data_.end_   = new_end;
            }
        }
    }

    void shrink_to_fit()
    {
        const size_type new_cap = size();

        if (new_cap < capacity())
        {
            if (new_cap <= N)
            {
                if (data_.first_ == data_.internal_storage())
                {
                    // Do nothing. We are already using internal storage.
                }
                else
                {
                    // We are not using internal storage but new capacity
                    // can fit in internal storage.

                    pointer new_first = data_.internal_storage();
                    pointer new_last  = new_first;
                    pointer new_end   = new_first + N;

                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );

                    SFL_DTL::destroy
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_
                    );

                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.end_ - data_.first_
                    );

                    data_.first_ = new_first;
                    data_.last_  = new_last;
                    data_.end_   = new_end;
                }
            }
            else
            {
                pointer new_first = SFL_DTL::allocate(ref_to_alloc(), new_cap);
                pointer new_last  = new_first;
                pointer new_end   = new_first + new_cap;

                try
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                catch (...)
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    throw;
                }

                SFL_DTL::destroy
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.last_
                );

                if (data_.first_ != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.end_ - data_.first_
                    );
                }

                data_.first_ = new_first;
                data_.last_  = new_last;
                data_.end_   = new_end;
            }
        }
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear() noexcept
    {
        SFL_DTL::destroy
        (
            ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        data_.last_ = data_.first_;
    }

    template <typename... Args>
    iterator emplace(Args&&... args)
    {
        temporary_value tmp(ref_to_alloc(), std::forward<Args>(args)...);

        auto it = lower_bound(tmp.value().first);

        return insert_aux(it, std::move(tmp.value()));
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        temporary_value tmp(ref_to_alloc(), std::forward<Args>(args)...);

        if
        (
            // If `hint` == `value`
            (
                hint != end() &&
                !ref_to_comp()(*hint, tmp.value()) &&
                !ref_to_comp()(tmp.value(), *hint)
            )
            ||
            // If `hint - 1` == `value`
            (
                hint != begin() &&
                !ref_to_comp()(*(hint - 1), tmp.value()) &&
                !ref_to_comp()(tmp.value(), *(hint - 1))
            )
            ||
            // If `hint - 1` < `value` and `value` < `hint`
            (
                (hint == begin() || ref_to_comp()(*(hint - 1), tmp.value())) &&
                (hint == end()   || ref_to_comp()(tmp.value(), *hint))
            )
        )
        {
            return insert_aux(hint, std::move(tmp.value()));
        }

        auto it = lower_bound(tmp.value().first);

        return insert_aux(it, std::move(tmp.value()));
    }

    iterator insert(const value_type& value)
    {
        auto it = lower_bound(value.first);

        return insert_aux(it, value);
    }

    iterator insert(value_type&& value)
    {
        auto it = lower_bound(value.first);

        return insert_aux(it, std::move(value));
    }

    template <typename P,
        typename std::enable_if
        <
            std::is_constructible<value_type, P&&>::value
        >::type* = nullptr
    >
    iterator insert(P&& value)
    {
        temporary_value tmp(ref_to_alloc(), std::forward<P>(value));

        auto it = lower_bound(tmp.value().first);

        return insert_aux(it, std::move(tmp.value()));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        if
        (
            // If `hint` == `value`
            (
                hint != end() &&
                !ref_to_comp()(*hint, value) &&
                !ref_to_comp()(value, *hint)
            )
            ||
            // If `hint - 1` == `value`
            (
                hint != begin() &&
                !ref_to_comp()(*(hint - 1), value) &&
                !ref_to_comp()(value, *(hint - 1))
            )
            ||
            // If `hint - 1` < `value` and `value` < `hint`
            (
                (hint == begin() || ref_to_comp()(*(hint - 1), value)) &&
                (hint == end()   || ref_to_comp()(value, *hint))
            )
        )
        {
            return insert_aux(hint, value);
        }

        auto it = lower_bound(value.first);

        return insert_aux(it, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        if
        (
            // If `hint` == `value`
            (
                hint != end() &&
                !ref_to_comp()(*hint, value) &&
                !ref_to_comp()(value, *hint)
            )
            ||
            // If `hint - 1` == `value`
            (
                hint != begin() &&
                !ref_to_comp()(*(hint - 1), value) &&
                !ref_to_comp()(value, *(hint - 1))
            )
            ||
            // If `hint - 1` < `value` and `value` < `hint`
            (
                (hint == begin() || ref_to_comp()(*(hint - 1), value)) &&
                (hint == end()   || ref_to_comp()(value, *hint))
            )
        )
        {
            return insert_aux(hint, std::move(value));
        }

        auto it = lower_bound(value.first);

        return insert_aux(it, std::move(value));
    }

    template <typename P,
        typename std::enable_if
        <
            std::is_constructible<value_type, P&&>::value
        >::type* = nullptr
    >
    iterator insert(const_iterator hint, P&& value)
    {
        return emplace_hint(hint, std::forward<P>(value));
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
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

        const difference_type offset = std::distance(cbegin(), pos);

        pointer p = data_.first_ + offset;

        if (p < data_.last_ - 1)
        {
            std::move(p + 1, data_.last_, p);
        }

        --data_.last_;

        SFL_DTL::destroy_at(ref_to_alloc(), data_.last_);

        return p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        const difference_type offset = std::distance(cbegin(), first);

        if (first == last)
        {
            return begin() + offset;
        }

        const difference_type n = std::distance(first, last);

        pointer p = data_.first_ + offset;

        if (p + n < data_.last_)
        {
            std::move(p + n, data_.last_, p);
        }

        pointer new_last = data_.last_ - n;

        SFL_DTL::destroy(ref_to_alloc(), new_last, data_.last_);

        data_.last_ = new_last;

        return p;
    }

    size_type erase(const Key& key)
    {
        const auto er = equal_range(key);
        const auto n = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return n;
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    size_type erase(K&& x)
    {
        const auto er = equal_range(x);
        const auto n = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return n;
    }

    void swap(small_flat_multimap& other)
    {
        if (this == &other)
        {
            return;
        }

        using std::swap;

        SFL_ASSERT
        (
            allocator_traits::propagate_on_container_swap::value ||
            this->ref_to_alloc() == other.ref_to_alloc()
        );

        // If this and other allocator compares equal then one allocator
        // can deallocate memory allocated by another allocator.
        // One allocator can safely destroy elements constructed by other
        // allocator regardless the two allocators compare equal or not.

        if (allocator_traits::propagate_on_container_swap::value)
        {
            swap(this->ref_to_alloc(), other.ref_to_alloc());
        }

        swap(this->ref_to_comp(), other.ref_to_comp());

        if
        (
            this->data_.first_ == this->data_.internal_storage() &&
            other.data_.first_ == other.data_.internal_storage()
        )
        {
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

                SFL_DTL::uninitialized_move
                (
                    this->ref_to_alloc(),
                    other.data_.first_ + this_size,
                    other.data_.first_ + other_size,
                    this->data_.first_ + this_size
                );

                SFL_DTL::destroy
                (
                    other.ref_to_alloc(),
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

                SFL_DTL::uninitialized_move
                (
                    other.ref_to_alloc(),
                    this->data_.first_ + other_size,
                    this->data_.first_ + this_size,
                    other.data_.first_ + other_size
                );

                SFL_DTL::destroy
                (
                    this->ref_to_alloc(),
                    this->data_.first_ + other_size,
                    this->data_.first_ + this_size
                );
            }

            data_.last_ = data_.first_ + other_size;
            other.data_.last_ = other.data_.first_ + this_size;
        }
        else if
        (
            this->data_.first_ == this->data_.internal_storage() &&
            other.data_.first_ != other.data_.internal_storage()
        )
        {
            pointer new_other_first = other.data_.internal_storage();
            pointer new_other_last  = new_other_first;
            pointer new_other_end   = new_other_first + N;

            new_other_last = SFL_DTL::uninitialized_move
            (
                other.ref_to_alloc(),
                this->data_.first_,
                this->data_.last_,
                new_other_first
            );

            SFL_DTL::destroy
            (
                this->ref_to_alloc(),
                this->data_.first_,
                this->data_.last_
            );

            this->data_.first_ = other.data_.first_;
            this->data_.last_  = other.data_.last_;
            this->data_.end_   = other.data_.end_;

            other.data_.first_ = new_other_first;
            other.data_.last_  = new_other_last;
            other.data_.end_   = new_other_end;
        }
        else if
        (
            this->data_.first_ != this->data_.internal_storage() &&
            other.data_.first_ == other.data_.internal_storage()
        )
        {
            pointer new_this_first = this->data_.internal_storage();
            pointer new_this_last  = new_this_first;
            pointer new_this_end   = new_this_first + N;

            new_this_last = SFL_DTL::uninitialized_move
            (
                this->ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                new_this_first
            );

            SFL_DTL::destroy
            (
                other.ref_to_alloc(),
                other.data_.first_,
                other.data_.last_
            );

            other.data_.first_ = this->data_.first_;
            other.data_.last_  = this->data_.last_;
            other.data_.end_   = this->data_.end_;

            this->data_.first_ = new_this_first;
            this->data_.last_  = new_this_last;
            this->data_.end_   = new_this_end;
        }
        else
        {
            swap(this->data_.first_, other.data_.first_);
            swap(this->data_.last_,  other.data_.last_);
            swap(this->data_.end_,   other.data_.end_);
        }
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    iterator lower_bound(const Key& key)
    {
        return std::lower_bound(begin(), end(), key, ref_to_comp());
    }

    SFL_NODISCARD
    const_iterator lower_bound(const Key& key) const
    {
        return std::lower_bound(begin(), end(), key, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    iterator lower_bound(const K& x)
    {
        return std::lower_bound(begin(), end(), x, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    const_iterator lower_bound(const K& x) const
    {
        return std::lower_bound(begin(), end(), x, ref_to_comp());
    }

    SFL_NODISCARD
    iterator upper_bound(const Key& key)
    {
        return std::upper_bound(begin(), end(), key, ref_to_comp());
    }

    SFL_NODISCARD
    const_iterator upper_bound(const Key& key) const
    {
        return std::upper_bound(begin(), end(), key, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    iterator upper_bound(const K& x)
    {
        return std::upper_bound(begin(), end(), x, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    const_iterator upper_bound(const K& x) const
    {
        return std::upper_bound(begin(), end(), x, ref_to_comp());
    }

    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return std::equal_range(begin(), end(), key, ref_to_comp());
    }

    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return std::equal_range(begin(), end(), key, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& x)
    {
        return std::equal_range(begin(), end(), x, ref_to_comp());
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const
    {
        return std::equal_range(begin(), end(), x, ref_to_comp());
    }

    SFL_NODISCARD
    iterator find(const Key& key)
    {
        auto it = lower_bound(key);

        if (it != end() && ref_to_comp()(key, *it))
        {
            it = end();
        }

        return it;
    }

    SFL_NODISCARD
    const_iterator find(const Key& key) const
    {
        auto it = lower_bound(key);

        if (it != end() && ref_to_comp()(key, *it))
        {
            it = end();
        }

        return it;
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    iterator find(const K& x)
    {
        auto it = lower_bound(x);

        if (it != end() && ref_to_comp()(x, *it))
        {
            it = end();
        }

        return it;
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        auto it = lower_bound(x);

        if (it != end() && ref_to_comp()(x, *it))
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
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
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
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
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

    Allocator& ref_to_alloc() noexcept
    {
        return *this;
    }

    const Allocator& ref_to_alloc() const noexcept
    {
        return *this;
    }

    MyCompare& ref_to_comp() noexcept
    {
        return *this;
    }

    const MyCompare& ref_to_comp() const noexcept
    {
        return *this;
    }

    void check_size(size_type n, const char* msg)
    {
        if (n > max_size())
        {
            SFL_DTL::throw_length_error(msg);
        }
    }

    size_type recommend_size(size_type n, const char* msg)
    {
        const size_type max_size = this->max_size();
        const size_type size = this->size();

        if (max_size - size < n)
        {
            SFL_DTL::throw_length_error(msg);
        }

        const size_type new_size = std::max(N, size + std::max(size, n));

        if (new_size < size || new_size > max_size)
        {
            return max_size;
        }

        return new_size;
    }

    void reset(size_type new_cap = N)
    {
        SFL_DTL::destroy
        (
            ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        if (data_.first_ != data_.internal_storage())
        {
            SFL_DTL::deallocate
            (
                ref_to_alloc(),
                data_.first_,
                data_.end_ - data_.first_
            );
        }

        data_.first_ = data_.internal_storage();
        data_.last_  = data_.first_;
        data_.end_   = data_.first_ + N;

        if (new_cap > N)
        {
            data_.first_ = SFL_DTL::allocate(ref_to_alloc(), new_cap);
            data_.last_  = data_.first_;
            data_.end_   = data_.first_ + new_cap;

            // If allocation throws, first_, last_ and end_ will be valid
            // (they will be pointing to internal_storage).
        }
    }

    class temporary_value
    {
    private:

        Allocator& alloc_;

        alignas(value_type) unsigned char buffer_[sizeof(value_type)];

        value_type* buffer()
        {
            return reinterpret_cast<value_type*>(buffer_);
        }

    public:

        template <typename... Args>
        explicit temporary_value(Allocator& a, Args&&... args) : alloc_(a)
        {
            SFL_DTL::construct_at
            (
                alloc_,
                buffer(),
                std::forward<Args>(args)...
            );
        }

        ~temporary_value()
        {
            SFL_DTL::destroy_at(alloc_, buffer());
        }

        value_type& value()
        {
            return *buffer();
        }
    };

    template <typename InputIt>
    void initialize_range(InputIt first, InputIt last)
    {
        try
        {
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }
        catch (...)
        {
            SFL_DTL::destroy
            (
                ref_to_alloc(),
                data_.first_,
                data_.last_
            );

            if (data_.first_ != data_.internal_storage())
            {
                SFL_DTL::deallocate
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.end_ - data_.first_
                );
            }

            throw;
        }
    }

    void initialize_copy(const small_flat_multimap& other)
    {
        const size_type n = other.size();

        check_size(n, "sfl::small_flat_multimap::initialize_copy");

        if (n > N)
        {
            data_.first_ = SFL_DTL::allocate(ref_to_alloc(), n);
            data_.last_  = data_.first_;
            data_.end_   = data_.first_ + n;
        }

        try
        {
            data_.last_ = SFL_DTL::uninitialized_copy
            (
                ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                data_.first_
            );
        }
        catch (...)
        {
            if (n > N)
            {
                SFL_DTL::deallocate(ref_to_alloc(), data_.first_, n);
            }

            throw;
        }
    }

    void initialize_move(small_flat_multimap& other)
    {
        if (other.data_.first_ == other.data_.internal_storage())
        {
            data_.last_ = SFL_DTL::uninitialized_move
            (
                ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                data_.first_
            );
        }
        else if (ref_to_alloc() == other.ref_to_alloc())
        {
            data_.first_ = other.data_.first_;
            data_.last_  = other.data_.last_;
            data_.end_   = other.data_.end_;

            other.data_.first_ = nullptr;
            other.data_.last_  = nullptr;
            other.data_.end_   = nullptr;
        }
        else
        {
            const size_type n = other.size();

            check_size(n, "sfl::small_flat_multimap::initialize_move");

            if (n > N)
            {
                data_.first_ = SFL_DTL::allocate(ref_to_alloc(), n);
                data_.last_  = data_.first_;
                data_.end_   = data_.first_ + n;
            }

            try
            {
                data_.last_ = SFL_DTL::uninitialized_move
                (
                    ref_to_alloc(),
                    other.data_.first_,
                    other.data_.last_,
                    data_.first_
                );
            }
            catch (...)
            {
                if (n > N)
                {
                    SFL_DTL::deallocate(ref_to_alloc(), data_.first_, n);
                }

                throw;
            }
        }

        other.reset();
    }

    template <typename ForwardIt>
    void assign_range(ForwardIt first, ForwardIt last)
    {
        const size_type n = std::distance(first, last);

        check_size(n, "sfl::small_flat_multimap::assign_range");

        if (n <= capacity())
        {
            const size_type s = size();

            if (n <= s)
            {
                pointer new_last = std::copy
                (
                    first,
                    last,
                    data_.first_
                );

                SFL_DTL::destroy
                (
                    ref_to_alloc(),
                    new_last,
                    data_.last_
                );

                data_.last_ = new_last;
            }
            else
            {
                ForwardIt mid = std::next(first, s);

                std::copy
                (
                    first,
                    mid,
                    data_.first_
                );

                data_.last_ = SFL_DTL::uninitialized_copy
                (
                    ref_to_alloc(),
                    mid,
                    last,
                    data_.last_
                );
            }
        }
        else
        {
            reset(n);

            data_.last_ = SFL_DTL::uninitialized_copy
            (
                ref_to_alloc(),
                first,
                last,
                data_.first_
            );
        }
    }

    void assign_copy(const small_flat_multimap& other)
    {
        if (this != &other)
        {
            if (allocator_traits::propagate_on_container_copy_assignment::value)
            {
                if (ref_to_alloc() != other.ref_to_alloc())
                {
                    reset();
                }

                ref_to_alloc() = other.ref_to_alloc();
            }

            ref_to_comp() = other.ref_to_comp();

            assign_range(other.data_.first_, other.data_.last_);
        }
    }

    void assign_move(small_flat_multimap& other)
    {
        if (allocator_traits::propagate_on_container_move_assignment::value)
        {
            if (ref_to_alloc() != other.ref_to_alloc())
            {
                reset();
            }

            ref_to_alloc() = std::move(other.ref_to_alloc());
        }

        ref_to_comp() = other.ref_to_comp();

        if (other.data_.first_ == other.data_.internal_storage())
        {
            assign_range
            (
                std::make_move_iterator(other.data_.first_),
                std::make_move_iterator(other.data_.last_)
            );
        }
        else if (ref_to_alloc() == other.ref_to_alloc())
        {
            reset();

            data_.first_ = other.data_.first_;
            data_.last_  = other.data_.last_;
            data_.end_   = other.data_.end_;

            other.data_.first_ = nullptr;
            other.data_.last_  = nullptr;
            other.data_.end_   = nullptr;
        }
        else
        {
            assign_range
            (
                std::make_move_iterator(other.data_.first_),
                std::make_move_iterator(other.data_.last_)
            );
        }

        other.reset();
    }

    template <typename... Args>
    iterator insert_aux(const_iterator pos, Args&&... args)
    {
        const difference_type offset = std::distance(cbegin(), pos);

        if (data_.last_ != data_.end_)
        {
            pointer p = data_.first_ + offset;

            if (p == data_.last_)
            {
                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    p,
                    std::forward<Args>(args)...
                );

                ++data_.last_;
            }
            else
            {
                // The order of operations is critical. First we will construct
                // temporary value because arguments `args...` can contain
                // reference to element in this container and after that
                // we will move elements and insert new element.

                temporary_value tmp(ref_to_alloc(), std::forward<Args>(args)...);

                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    data_.last_,
                    std::move(*(data_.last_ - 1))
                );

                ++data_.last_;

                std::move_backward
                (
                    p,
                    data_.last_ - 2,
                    data_.last_ - 1
                );

                *p = std::move(tmp.value());
            }
        }
        else
        {
            const size_type new_cap =
                recommend_size(1, "sfl::small_flat_multimap::insert_aux");

            pointer new_first;
            pointer new_last;
            pointer new_end;

            if (new_cap <= N && data_.first_ != data_.internal_storage())
            {
                new_first = data_.internal_storage();
                new_last  = new_first;
                new_end   = new_first + N;
            }
            else
            {
                new_first = SFL_DTL::allocate(ref_to_alloc(), new_cap);
                new_last  = new_first;
                new_end   = new_first + new_cap;
            }

            try
            {
                // The order of operations is critical. First we will construct
                // new element in new storage because arguments `args...` can
                // contain reference to element in this container and after
                // that we will move elements from old to new storage.

                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    new_first + offset,
                    std::forward<Args>(args)...
                );

                new_last = nullptr;

                new_last = SFL_DTL::uninitialized_move_if_noexcept
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.first_ + offset,
                    new_first
                );

                ++new_last;

                new_last = SFL_DTL::uninitialized_move_if_noexcept
                (
                    ref_to_alloc(),
                    data_.first_ + offset,
                    data_.last_,
                    new_last
                );
            }
            catch (...)
            {
                if (new_last == nullptr)
                {
                    SFL_DTL::destroy_at
                    (
                        ref_to_alloc(),
                        new_first + offset
                    );
                }
                else
                {
                    SFL_DTL::destroy
                    (
                        ref_to_alloc(),
                        new_first,
                        new_last
                    );
                }

                if (new_first != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );
                }

                throw;
            }

            SFL_DTL::destroy
            (
                ref_to_alloc(),
                data_.first_,
                data_.last_
            );

            if (data_.first_ != data_.internal_storage())
            {
                SFL_DTL::deallocate
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.end_ - data_.first_
                );
            }

            data_.first_ = new_first;
            data_.last_  = new_last;
            data_.end_   = new_end;
        }

        return begin() + offset;
    }
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator==
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return !(x == y);
}

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return y < x;
}

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<=
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return !(y < x);
}

template <typename K, typename T, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>=
(
    const small_flat_multimap<K, T, N, C, A>& x,
    const small_flat_multimap<K, T, N, C, A>& y
)
{
    return !(x < y);
}

template <typename K, typename T, std::size_t N, typename C, typename A>
void swap
(
    small_flat_multimap<K, T, N, C, A>& x,
    small_flat_multimap<K, T, N, C, A>& y
)
{
    x.swap(y);
}

template <typename K, typename T, std::size_t N, typename C, typename A,
          typename Predicate>
typename small_flat_multimap<K, T, N, C, A>::size_type
    erase_if(small_flat_multimap<K, T, N, C, A>& c, Predicate pred)
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

#undef SFL_ASSERT
#undef SFL_DTL_BEGIN
#undef SFL_DTL_END
#undef SFL_DTL
#undef SFL_NODISCARD
#undef SFL_UNUSED

#endif // SFL_SMALL_FLAT_MULTIMAP_HPP

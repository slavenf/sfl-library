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

#ifndef SFL_SMALL_FLAT_SET_HPP
#define SFL_SMALL_FLAT_SET_HPP

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

#define SFL_DTL_BEGIN  namespace dtl { namespace small_flat_set_dtl {
#define SFL_DTL_END    } }
#define SFL_DTL        dtl::small_flat_set_dtl

#if __cplusplus >= 201402L
    #define SFL_CONSTEXPR_14 constexpr
#else
    #define SFL_CONSTEXPR_14
#endif

#if __cplusplus >= 201703L
    #define SFL_NODISCARD [[nodiscard]]
#else
    #define SFL_NODISCARD
#endif

#define SFL_UNUSED(x)

#ifdef SFL_NO_EXCEPTIONS
    #define SFL_TRY      if (true)
    #define SFL_CATCH(x) if (false)
    #define SFL_RETHROW
#else
    #define SFL_TRY      try
    #define SFL_CATCH(x) catch (x)
    #define SFL_RETHROW  throw
#endif

namespace sfl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SFL_DTL_BEGIN /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// ---- UTILITY FUNCTIONS -----------------------------------------------------
//

/// This function is used for silencing warnings about unused variables.
///
template <typename... Args>
SFL_CONSTEXPR_14
void ignore_unused(Args&&...)
{
    // Do nothing.
}

//
// ---- POINTER TRAITS --------------------------------------------------------
//

/// Raw pointer overload.
/// Obtains a dereferenceable pointer to its argument.
///
template <typename T>
T* to_address(T* p) noexcept
{
    static_assert(!std::is_function<T>::value, "not a function pointer");
    return p;
}

/// Fancy pointer overload.
/// Obtains a raw pointer from a fancy pointer.
///
template <typename Pointer>
auto to_address(const Pointer& p) noexcept
-> typename std::pointer_traits<Pointer>::element_type*
{
    return p == nullptr ? nullptr : SFL_DTL::to_address(p.operator->());
}

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
    std::allocator_traits<Allocator>::construct
    (
        a,
        SFL_DTL::to_address(p),
        std::forward<Args>(args)...
    );
}

template <typename Allocator, typename Pointer>
inline void destroy_at(Allocator& a, Pointer p)
{
    std::allocator_traits<Allocator>::destroy
    (
        a,
        SFL_DTL::to_address(p)
    );
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
    SFL_TRY
    {
        while (n > 0)
        {
            construct_at(a, std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        destroy(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename Size, typename T>
inline ForwardIt uninitialized_fill_n
(
    Allocator& a, ForwardIt first, Size n, const T& value
)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            construct_at(a, std::addressof(*curr), value);
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        destroy(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_copy
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), *first);
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        destroy(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_move
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), std::move(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        destroy(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
inline ForwardIt uninitialized_move_if_noexcept
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            construct_at(a, std::addressof(*d_curr), std::move_if_noexcept(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        destroy(a, d_first, d_curr);
        SFL_RETHROW;
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
    #ifdef SFL_NO_EXCEPTIONS
    SFL_DTL::ignore_unused(msg);
    SFL_ASSERT(!"std::length_error thrown");
    std::abort();
    #else
    throw std::length_error(msg);
    #endif
}

[[noreturn]]
inline void throw_out_of_range(const char* msg)
{
    #ifdef SFL_NO_EXCEPTIONS
    SFL_DTL::ignore_unused(msg);
    SFL_ASSERT(!"std::out_of_range thrown");
    std::abort();
    #else
    throw std::out_of_range(msg);
    #endif
}

//
// ---- SMALL FLAT SET --------------------------------------------------------
//

template <typename T, typename Pointer, std::size_t N>
class small_flat_set_data
{
private:

    alignas(T) unsigned char internal_storage_[N * sizeof(T)];

public:

    Pointer first_;
    Pointer last_;
    Pointer end_;

    small_flat_set_data() noexcept
        : first_
        (
            std::pointer_traits<Pointer>::pointer_to
            (
                *reinterpret_cast<T*>(internal_storage_)
            )
        )
        , last_(first_)
        , end_(first_ + N)
    {}

    Pointer internal_storage() noexcept
    {
        return std::pointer_traits<Pointer>::pointer_to
        (
            *reinterpret_cast<T*>(internal_storage_)
        );
    }
};

template <typename T, typename Pointer>
class small_flat_set_data<T, Pointer, 0>
{
public:

    Pointer first_;
    Pointer last_;
    Pointer end_;

    small_flat_set_data() noexcept
        : first_(nullptr)
        , last_(nullptr)
        , end_(nullptr)
    {}

    Pointer internal_storage() noexcept
    {
        return nullptr;
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SFL_DTL_END ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// ---- SMALL FLAT SET --------------------------------------------------------
//

template < typename Key,
           std::size_t N,
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<Key> >
class small_flat_set : private Allocator, private Compare
{
public:

    using allocator_type         = Allocator;
    using allocator_traits       = std::allocator_traits<allocator_type>;
    using key_type               = Key;
    using value_type             = Key;
    using size_type              = typename allocator_traits::size_type;
    using difference_type        = typename allocator_traits::difference_type;
    using key_compare            = Compare;
    using value_compare          = Compare;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = typename allocator_traits::pointer;
    using const_pointer          = typename allocator_traits::const_pointer;
    using iterator               = const_pointer; // MUST BE const_pointer
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static_assert
    (
        std::is_same<typename Allocator::value_type, value_type>::value,
        "Allocator::value_type must be same as sfl::small_flat_set::value_type."
    );

private:

    SFL_DTL::small_flat_set_data<value_type, pointer, N> data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    small_flat_set() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : Allocator()
        , Compare()
    {}

    explicit small_flat_set(const Compare& comp) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : Allocator()
        , Compare(comp)
    {}

    explicit small_flat_set(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    )
        : Allocator(alloc)
        , Compare()
    {}

    explicit small_flat_set(const Compare& comp, const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    )
        : Allocator(alloc)
        , Compare(comp)
    {}

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_set(InputIt first, InputIt last)
        : Allocator()
        , Compare()
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_set(InputIt first, InputIt last, const Compare& comp)
        : Allocator()
        , Compare(comp)
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_set(InputIt first, InputIt last, const Allocator& alloc)
        : Allocator(alloc)
        , Compare()
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_flat_set(InputIt first, InputIt last, const Compare& comp,
                                                const Allocator& alloc)
        : Allocator(alloc)
        , Compare(comp)
    {
        initialize_range(first, last);
    }

    small_flat_set(std::initializer_list<value_type> ilist)
        : small_flat_set(ilist.begin(), ilist.end())
    {}

    small_flat_set(std::initializer_list<value_type> ilist,
                   const Compare& comp)
        : small_flat_set(ilist.begin(), ilist.end(), comp)
    {}

    small_flat_set(std::initializer_list<value_type> ilist,
                   const Allocator& alloc)
        : small_flat_set(ilist.begin(), ilist.end(), alloc)
    {}

    small_flat_set(std::initializer_list<value_type> ilist,
                   const Compare& comp, const Allocator& alloc)
        : small_flat_set(ilist.begin(), ilist.end(), comp, alloc)
    {}

    small_flat_set(const small_flat_set& other)
        : Allocator
        (
            allocator_traits::select_on_container_copy_construction
            (
                other.ref_to_alloc()
            )
        )
        , Compare(other.ref_to_comp())
    {
        initialize_copy(other);
    }

    small_flat_set(const small_flat_set& other, const Allocator& alloc)
        : Allocator(alloc)
        , Compare(other.ref_to_comp())
    {
        initialize_copy(other);
    }

    small_flat_set(small_flat_set&& other)
        : Allocator(std::move(other.ref_to_alloc()))
        , Compare(std::move(other.ref_to_comp()))
    {
        initialize_move(other);
    }

    small_flat_set(small_flat_set&& other, const Allocator& alloc)
        : Allocator(alloc)
        , Compare(std::move(other.ref_to_comp()))
    {
        initialize_move(other);
    }

    ~small_flat_set()
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

    small_flat_set& operator=(const small_flat_set& other)
    {
        assign_copy(other);
        return *this;
    }

    small_flat_set& operator=(small_flat_set&& other)
    {
        assign_move(other);
        return *this;
    }

    small_flat_set& operator=(std::initializer_list<Key> ilist)
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
        return ref_to_comp();
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
        check_size(new_cap, "sfl::small_flat_set::reserve");

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

                SFL_TRY
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                SFL_CATCH (...)
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    SFL_RETHROW;
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

                SFL_TRY
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                SFL_CATCH (...)
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    SFL_RETHROW;
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
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        temporary_value tmp(ref_to_alloc(), std::forward<Args>(args)...);

        auto it = lower_bound(tmp.value());

        if (it == end() || ref_to_comp()(tmp.value(), *it))
        {
            return std::make_pair(insert_aux(it, std::move(tmp.value())), true);
        }

        return std::make_pair(it, false);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        temporary_value tmp(ref_to_alloc(), std::forward<Args>(args)...);

        if
        (
            (hint == begin() || ref_to_comp()(*(hint - 1), tmp.value())) &&
            (hint == end()   || ref_to_comp()(tmp.value(), *hint))
        )
        {
            return insert_aux(hint, std::move(tmp.value()));
        }

        auto it = lower_bound(tmp.value());

        if (it == end() || ref_to_comp()(tmp.value(), *it))
        {
            return insert_aux(it, std::move(tmp.value()));
        }

        return it;
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        auto it = lower_bound(value);

        if (it == end() || ref_to_comp()(value, *it))
        {
            return std::make_pair(insert_aux(it, value), true);
        }

        return std::make_pair(it, false);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        auto it = lower_bound(value);

        if (it == end() || ref_to_comp()(value, *it))
        {
            return std::make_pair(insert_aux(it, std::move(value)), true);
        }

        return std::make_pair(it, false);
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        if
        (
            (hint == begin() || ref_to_comp()(*(hint - 1), value)) &&
            (hint == end()   || ref_to_comp()(value, *hint))
        )
        {
            return insert_aux(hint, value);
        }

        auto it = lower_bound(value);

        if (it == end() || ref_to_comp()(value, *it))
        {
            return insert_aux(it, value);
        }

        return it;
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());

        if
        (
            (hint == begin() || ref_to_comp()(*(hint - 1), value)) &&
            (hint == end()   || ref_to_comp()(value, *hint))
        )
        {
            return insert_aux(hint, std::move(value));
        }

        auto it = lower_bound(value);

        if (it == end() || ref_to_comp()(value, *it))
        {
            return insert_aux(it, std::move(value));
        }

        return it;
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
        auto it = find(key);
        if (it == cend())
        {
            return 0;
        }
        erase(it);
        return 1;
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<Compare, K>::value
        >::type* = nullptr
    >
    size_type erase(K&& x)
    {
        auto it = find(x);
        if (it == cend())
        {
            return 0;
        }
        erase(it);
        return 1;
    }

    void swap(small_flat_set& other)
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
        return find(key) != end();
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
        return find(x) != end();
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
        return SFL_DTL::to_address(data_.first_);
    }

    SFL_NODISCARD
    const value_type* data() const noexcept
    {
        return SFL_DTL::to_address(data_.first_);
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

    Compare& ref_to_comp() noexcept
    {
        return *this;
    }

    const Compare& ref_to_comp() const noexcept
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
        SFL_TRY
        {
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }
        SFL_CATCH (...)
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

            SFL_RETHROW;
        }
    }

    void initialize_copy(const small_flat_set& other)
    {
        const size_type n = other.size();

        check_size(n, "sfl::small_flat_set::initialize_copy");

        if (n > N)
        {
            data_.first_ = SFL_DTL::allocate(ref_to_alloc(), n);
            data_.last_  = data_.first_;
            data_.end_   = data_.first_ + n;
        }

        SFL_TRY
        {
            data_.last_ = SFL_DTL::uninitialized_copy
            (
                ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                data_.first_
            );
        }
        SFL_CATCH (...)
        {
            if (n > N)
            {
                SFL_DTL::deallocate(ref_to_alloc(), data_.first_, n);
            }

            SFL_RETHROW;
        }
    }

    void initialize_move(small_flat_set& other)
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

            check_size(n, "sfl::small_flat_set::initialize_move");

            if (n > N)
            {
                data_.first_ = SFL_DTL::allocate(ref_to_alloc(), n);
                data_.last_  = data_.first_;
                data_.end_   = data_.first_ + n;
            }

            SFL_TRY
            {
                data_.last_ = SFL_DTL::uninitialized_move
                (
                    ref_to_alloc(),
                    other.data_.first_,
                    other.data_.last_,
                    data_.first_
                );
            }
            SFL_CATCH (...)
            {
                if (n > N)
                {
                    SFL_DTL::deallocate(ref_to_alloc(), data_.first_, n);
                }

                SFL_RETHROW;
            }
        }

        other.reset();
    }

    template <typename ForwardIt>
    void assign_range(ForwardIt first, ForwardIt last)
    {
        const size_type n = std::distance(first, last);

        check_size(n, "sfl::small_flat_set::assign_range");

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

    void assign_copy(const small_flat_set& other)
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

    void assign_move(small_flat_set& other)
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
                // This container cannot contains duplicates so we are sure
                // that arguments `args...` do not contain reference to
                // element in this container.
                // Because of that, order of operations is not critical like
                // in case of vectors and multimaps and multisets.
                // First we will move elements one place to the right and
                // after that we will construct new element.

                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    data_.last_,
                    std::move(*(data_.last_ - 1))
                );

                ++data_.last_;

                std::move_backward(p, data_.last_ - 2, data_.last_ - 1);

                SFL_DTL::destroy_at
                (
                    ref_to_alloc(),
                    p
                );

                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    p,
                    std::forward<Args>(args)...
                );
            }
        }
        else
        {
            const size_type new_cap =
                recommend_size(1, "sfl::small_flat_set::insert_aux");

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

            SFL_TRY
            {
                // This container cannot contains duplicates so we are sure
                // that arguments `args...` do not contain reference to
                // element in this container.
                // Because of that, order of operations is not critical like
                // in case of vectors or multimaps or multisets.
                // First we will move first chunk of elements from old to new
                // storage, after that we will construct new element in new
                // storage and finally move second chunk of elements from old
                // to new storage.

                new_last = SFL_DTL::uninitialized_move_if_noexcept
                (
                    ref_to_alloc(),
                    data_.first_,
                    data_.first_ + offset,
                    new_first
                );

                SFL_DTL::construct_at
                (
                    ref_to_alloc(),
                    new_last,
                    std::forward<Args>(args)...
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
            SFL_CATCH (...)
            {
                SFL_DTL::destroy
                (
                    ref_to_alloc(),
                    new_first,
                    new_last
                );

                if (new_first != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        ref_to_alloc(),
                        new_first,
                        new_cap
                    );
                }

                SFL_RETHROW;
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

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator==
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return !(x == y);
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return y < x;
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator<=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return !(y < x);
}

template <typename K, std::size_t N, typename C, typename A>
SFL_NODISCARD
bool operator>=
(
    const small_flat_set<K, N, C, A>& x,
    const small_flat_set<K, N, C, A>& y
)
{
    return !(x < y);
}

template <typename K, std::size_t N, typename C, typename A>
void swap
(
    small_flat_set<K, N, C, A>& x,
    small_flat_set<K, N, C, A>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, typename C, typename A,
          typename Predicate>
typename small_flat_set<K, N, C, A>::size_type
    erase_if(small_flat_set<K, N, C, A>& c, Predicate pred)
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
#undef SFL_TRY
#undef SFL_CATCH
#undef SFL_RETHROW

#endif // SFL_SMALL_FLAT_SET_HPP

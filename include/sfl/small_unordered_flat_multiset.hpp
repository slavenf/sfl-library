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

#ifndef SFL_SMALL_UNORDERED_FLAT_MULTISET_HPP
#define SFL_SMALL_UNORDERED_FLAT_MULTISET_HPP

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

#define SFL_DTL_BEGIN  namespace dtl { namespace small_unordered_flat_multiset_dtl {
#define SFL_DTL_END    } }
#define SFL_DTL        ::sfl::dtl::small_unordered_flat_multiset_dtl

#define SFL_ASSERT(x) assert(x)

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

#ifdef SFL_NO_EXCEPTIONS
    #define SFL_TRY      if (true)
    #define SFL_CATCH(x) if (false)
    #define SFL_RETHROW
#else
    #define SFL_TRY      try
    #define SFL_CATCH(x) catch (x)
    #define SFL_RETHROW  throw
#endif

#ifdef SFL_TEST_SMALL_UNORDERED_FLAT_MULTISET
void test_small_unordered_flat_multiset();
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
constexpr
T* to_address(T* p) noexcept
{
    static_assert(!std::is_function<T>::value, "not a function pointer");
    return p;
}

/// Fancy pointer overload.
/// Obtains a raw pointer from a fancy pointer.
///
template <typename Pointer>
constexpr
auto to_address(const Pointer& p) noexcept
-> typename std::pointer_traits<Pointer>::element_type*
{
    return SFL_DTL::to_address(p.operator->());
}

//
// ---- UNINITIALIZED MEMORY ALGORITHMS ---------------------------------------
//

template <typename Allocator, typename Size>
auto allocate(Allocator& a, Size n)
-> typename std::allocator_traits<Allocator>::pointer
{
    if (n != 0)
    {
        return std::allocator_traits<Allocator>::allocate(a, n);
    }
    return nullptr;
}

template <typename Allocator, typename Pointer, typename Size>
void deallocate(Allocator& a, Pointer p, Size n) noexcept
{
    if (p != nullptr)
    {
        std::allocator_traits<Allocator>::deallocate(a, p, n);
    }
}

template <typename Allocator, typename Pointer, typename... Args>
void construct_at(Allocator& a, Pointer p, Args&&... args)
{
    std::allocator_traits<Allocator>::construct
    (
        a,
        SFL_DTL::to_address(p),
        std::forward<Args>(args)...
    );
}

template <typename Allocator, typename Pointer>
void destroy_at(Allocator& a, Pointer p) noexcept
{
    std::allocator_traits<Allocator>::destroy
    (
        a,
        SFL_DTL::to_address(p)
    );
}

template <typename Allocator, typename ForwardIt>
void destroy(Allocator& a, ForwardIt first, ForwardIt last) noexcept
{
    while (first != last)
    {
        SFL_DTL::destroy_at(a, std::addressof(*first));
        ++first;
    }
}

template <typename Allocator, typename ForwardIt, typename Size>
void destroy_n(Allocator& a, ForwardIt first, Size n) noexcept
{
    while (n > 0)
    {
        SFL_DTL::destroy_at(a, std::addressof(*first));
        ++first;
        --n;
    }
}

template <typename Allocator, typename ForwardIt, typename Size>
ForwardIt uninitialized_default_construct_n
(
    Allocator& a, ForwardIt first, Size n
)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            SFL_DTL::construct_at(a, std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        SFL_DTL::destroy(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename Size, typename T>
ForwardIt uninitialized_fill_n
(
    Allocator& a, ForwardIt first, Size n, const T& value
)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            SFL_DTL::construct_at(a, std::addressof(*curr), value);
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        SFL_DTL::destroy(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
ForwardIt uninitialized_copy
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            SFL_DTL::construct_at(a, std::addressof(*d_curr), *first);
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        SFL_DTL::destroy(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
ForwardIt uninitialized_move
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            SFL_DTL::construct_at(a, std::addressof(*d_curr), std::move(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        SFL_DTL::destroy(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt>
ForwardIt uninitialized_move_if_noexcept
(
    Allocator& a, InputIt first, InputIt last, ForwardIt d_first
)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            SFL_DTL::construct_at(a, std::addressof(*d_curr), std::move_if_noexcept(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        SFL_DTL::destroy(a, d_first, d_curr);
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SFL_DTL_END ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// ---- SMALL UNORDERED FLAT SET ----------------------------------------------
//

template < typename Key,
           std::size_t N,
           typename KeyEqual = std::equal_to<Key>,
           typename Allocator = std::allocator<Key> >
class small_unordered_flat_multiset
{
    #ifdef SFL_TEST_SMALL_UNORDERED_FLAT_MULTISET
    friend void ::test_small_unordered_flat_multiset();
    #endif

public:

    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<allocator_type>;
    using key_type         = Key;
    using value_type       = Key;
    using size_type        = typename allocator_traits::size_type;
    using difference_type  = typename allocator_traits::difference_type;
    using key_equal        = KeyEqual;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using pointer          = typename allocator_traits::pointer;
    using const_pointer    = typename allocator_traits::const_pointer;
    using iterator         = const_pointer; // MUST BE const_pointer
    using const_iterator   = const_pointer;

    static_assert
    (
        std::is_same<typename Allocator::value_type, value_type>::value,
        "Allocator::value_type must be same as sfl::small_unordered_flat_multiset::value_type."
    );

private:

    template <bool WithInternalStorage = true, typename = void>
    class data_base
    {
    private:

        alignas(value_type) unsigned char internal_storage_[N * sizeof(value_type)];

    public:

        pointer first_;
        pointer last_;
        pointer end_;

        data_base() noexcept
            : first_
            (
                std::pointer_traits<pointer>::pointer_to
                (
                    *reinterpret_cast<value_type*>(internal_storage_)
                )
            )
            , last_(first_)
            , end_(first_ + N)
        {}

        pointer internal_storage() noexcept
        {
            return std::pointer_traits<pointer>::pointer_to
            (
                *reinterpret_cast<value_type*>(internal_storage_)
            );
        }
    };

    template <typename Dummy>
    class data_base<false, Dummy>
    {
    public:

        pointer first_;
        pointer last_;
        pointer end_;

        data_base() noexcept
            : first_(nullptr)
            , last_(nullptr)
            , end_(nullptr)
        {}

        pointer internal_storage() noexcept
        {
            return nullptr;
        }
    };

    class data
        : public data_base<(N > 0)>
        , public allocator_type
        , public key_equal
    {
    public:

        data() noexcept
        (
            std::is_nothrow_default_constructible<allocator_type>::value &&
            std::is_nothrow_default_constructible<key_equal>::value
        )
            : allocator_type()
            , key_equal()
        {}

        data(const allocator_type& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<allocator_type>::value &&
            std::is_nothrow_default_constructible<key_equal>::value
        )
            : allocator_type(alloc)
            , key_equal()
        {}

        data(const key_equal& equal) noexcept
        (
            std::is_nothrow_default_constructible<allocator_type>::value &&
            std::is_nothrow_copy_constructible<key_equal>::value
        )
            : allocator_type()
            , key_equal(equal)
        {}

        data(const key_equal& equal, const allocator_type& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<allocator_type>::value &&
            std::is_nothrow_copy_constructible<key_equal>::value
        )
            : allocator_type(alloc)
            , key_equal(equal)
        {}

        data(key_equal&& equal, allocator_type&& alloc) noexcept
        (
            std::is_nothrow_move_constructible<allocator_type>::value &&
            std::is_nothrow_move_constructible<key_equal>::value
        )
            : allocator_type(std::move(alloc))
            , key_equal(std::move(equal))
        {}

        data(key_equal&& equal, const allocator_type& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<allocator_type>::value &&
            std::is_nothrow_move_constructible<key_equal>::value
        )
            : allocator_type(alloc)
            , key_equal(std::move(equal))
        {}

        allocator_type& ref_to_alloc() noexcept
        {
            return *this;
        }

        const allocator_type& ref_to_alloc() const noexcept
        {
            return *this;
        }

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

    small_unordered_flat_multiset() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    )
        : data_()
    {}

    explicit small_unordered_flat_multiset(const KeyEqual& equal) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    )
        : data_(equal)
    {}

    explicit small_unordered_flat_multiset(const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    )
        : data_(alloc)
    {}

    explicit small_unordered_flat_multiset(const KeyEqual& equal,
                                      const Allocator& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    )
        : data_(equal, alloc)
    {}

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_unordered_flat_multiset(InputIt first, InputIt last)
        : data_()
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_unordered_flat_multiset(InputIt first, InputIt last,
                             const KeyEqual& equal)
        : data_(equal)
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_unordered_flat_multiset(InputIt first, InputIt last,
                             const Allocator& alloc)
        : data_(alloc)
    {
        initialize_range(first, last);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    small_unordered_flat_multiset(InputIt first, InputIt last,
                             const KeyEqual& equal, const Allocator& alloc)
        : data_(equal, alloc)
    {
        initialize_range(first, last);
    }

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end())
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist,
                             const KeyEqual& equal)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), equal)
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist,
                             const Allocator& alloc)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), alloc)
    {}

    small_unordered_flat_multiset(std::initializer_list<value_type> ilist,
                             const KeyEqual& equal, const Allocator& alloc)
        : small_unordered_flat_multiset(ilist.begin(), ilist.end(), equal, alloc)
    {}

    small_unordered_flat_multiset(const small_unordered_flat_multiset& other)
        : data_
        (
            other.data_.ref_to_equal(),
            allocator_traits::select_on_container_copy_construction
            (
                other.data_.ref_to_alloc()
            )
        )
    {
        initialize_copy(other);
    }

    small_unordered_flat_multiset(const small_unordered_flat_multiset& other,
                             const Allocator& alloc)
        : data_
        (
            other.data_.ref_to_equal(),
            alloc
        )
    {
        initialize_copy(other);
    }

    small_unordered_flat_multiset(small_unordered_flat_multiset&& other)
        : data_
        (
            std::move(other.data_.ref_to_equal()),
            std::move(other.data_.ref_to_alloc())
        )
    {
        initialize_move(other);
    }

    small_unordered_flat_multiset(small_unordered_flat_multiset&& other,
                             const Allocator& alloc)
        : data_
        (
            std::move(other.data_.ref_to_equal()),
            alloc
        )
    {
        initialize_move(other);
    }

    ~small_unordered_flat_multiset()
    {
        SFL_DTL::destroy
        (
            data_.ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        if (data_.first_ != data_.internal_storage())
        {
            SFL_DTL::deallocate
            (
                data_.ref_to_alloc(),
                data_.first_,
                data_.end_ - data_.first_
            );
        }
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    small_unordered_flat_multiset& operator=(const small_unordered_flat_multiset& other)
    {
        assign_copy(other);
        return *this;
    }

    small_unordered_flat_multiset& operator=(small_unordered_flat_multiset&& other)
    {
        assign_move(other);
        return *this;
    }

    small_unordered_flat_multiset& operator=(std::initializer_list<Key> ilist)
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
        return data_.ref_to_alloc();
    }

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
            allocator_traits::max_size(data_.ref_to_alloc()),
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
        check_size(new_cap, "sfl::small_unordered_flat_multiset::reserve");

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
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );

                    SFL_DTL::destroy
                    (
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_
                    );

                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
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
                pointer new_first = SFL_DTL::allocate(data_.ref_to_alloc(), new_cap);
                pointer new_last  = new_first;
                pointer new_end   = new_first + new_cap;

                SFL_TRY
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                SFL_CATCH (...)
                {
                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    SFL_RETHROW;
                }

                SFL_DTL::destroy
                (
                    data_.ref_to_alloc(),
                    data_.first_,
                    data_.last_
                );

                if (data_.first_ != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
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
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );

                    SFL_DTL::destroy
                    (
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_
                    );

                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
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
                pointer new_first = SFL_DTL::allocate(data_.ref_to_alloc(), new_cap);
                pointer new_last  = new_first;
                pointer new_end   = new_first + new_cap;

                SFL_TRY
                {
                    new_last = SFL_DTL::uninitialized_move_if_noexcept
                    (
                        data_.ref_to_alloc(),
                        data_.first_,
                        data_.last_,
                        new_first
                    );
                }
                SFL_CATCH (...)
                {
                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
                        new_first,
                        new_cap
                    );

                    SFL_RETHROW;
                }

                SFL_DTL::destroy
                (
                    data_.ref_to_alloc(),
                    data_.first_,
                    data_.last_
                );

                if (data_.first_ != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
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
            data_.ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        data_.last_ = data_.first_;
    }

    template <typename... Args>
    iterator emplace(Args&&... args)
    {
        return insert_unordered(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        SFL_DTL::ignore_unused(hint);
        return insert_unordered(std::forward<Args>(args)...);
    }

    iterator insert(const value_type& value)
    {
        return insert_unordered(value);
    }

    iterator insert(value_type&& value)
    {
        return insert_unordered(std::move(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        SFL_DTL::ignore_unused(hint);
        return insert_unordered(value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(cbegin() <= hint && hint <= cend());
        SFL_DTL::ignore_unused(hint);
        return insert_unordered(std::move(value));
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

        const pointer p = data_.first_ + offset;

        if (p < data_.last_ - 1)
        {
            *p = std::move(*(data_.last_ - 1));
        }

        --data_.last_;

        SFL_DTL::destroy_at(data_.ref_to_alloc(), data_.last_);

        return p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        if (first == last)
        {
            return begin() + std::distance(cbegin(), first);
        }

        const difference_type count1 = std::distance(first, last);
        const difference_type count2 = std::distance(last, cend());

        const difference_type offset = std::distance(cbegin(), first);

        const pointer p1 = data_.first_ + offset;

        if (count1 >= count2)
        {
            const pointer p2 = p1 + count1;

            const pointer new_last = std::move(p2, data_.last_, p1);

            SFL_DTL::destroy(data_.ref_to_alloc(), new_last, data_.last_);

            data_.last_ = new_last;
        }
        else
        {
            const pointer p2 = p1 + count2;

            std::move(p2, data_.last_, p1);

            const pointer new_last = p2;

            SFL_DTL::destroy(data_.ref_to_alloc(), new_last, data_.last_);

            data_.last_ = new_last;
        }

        return p1;
    }

    size_type erase(const Key& key)
    {
        size_type n = 0;

        for (auto it = begin(); it != end();)
        {
            if (data_.ref_to_equal()(*it, key))
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

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<KeyEqual, K>::value
        >::type* = nullptr
    >
    size_type erase(K&& x)
    {
        size_type n = 0;

        for (auto it = begin(); it != end();)
        {
            if (data_.ref_to_equal()(*it, x))
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

    void swap(small_unordered_flat_multiset& other)
    {
        if (this == &other)
        {
            return;
        }

        using std::swap;

        SFL_ASSERT
        (
            allocator_traits::propagate_on_container_swap::value ||
            this->data_.ref_to_alloc() == other.data_.ref_to_alloc()
        );

        // If this and other allocator compares equal then one allocator
        // can deallocate memory allocated by another allocator.
        // One allocator can safely destroy elements constructed by other
        // allocator regardless the two allocators compare equal or not.

        if (allocator_traits::propagate_on_container_swap::value)
        {
            swap(this->data_.ref_to_alloc(), other.data_.ref_to_alloc());
        }

        swap(this->data_.ref_to_equal(), other.data_.ref_to_equal());

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
                    this->data_.ref_to_alloc(),
                    other.data_.first_ + this_size,
                    other.data_.first_ + other_size,
                    this->data_.first_ + this_size
                );

                SFL_DTL::destroy
                (
                    other.data_.ref_to_alloc(),
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
                    other.data_.ref_to_alloc(),
                    this->data_.first_ + other_size,
                    this->data_.first_ + this_size,
                    other.data_.first_ + other_size
                );

                SFL_DTL::destroy
                (
                    this->data_.ref_to_alloc(),
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
                other.data_.ref_to_alloc(),
                this->data_.first_,
                this->data_.last_,
                new_other_first
            );

            SFL_DTL::destroy
            (
                this->data_.ref_to_alloc(),
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
                this->data_.ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                new_this_first
            );

            SFL_DTL::destroy
            (
                other.data_.ref_to_alloc(),
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
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<KeyEqual, K>::value
        >::type* = nullptr
    >
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
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<KeyEqual, K>::value
        >::type* = nullptr
    >
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
        size_type n = 0;

        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, key))
            {
                ++n;
            }
        }

        return n;
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<KeyEqual, K>::value
        >::type* = nullptr
    >
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        size_type n = 0;

        for (auto it = begin(); it != end(); ++it)
        {
            if (data_.ref_to_equal()(*it, x))
            {
                ++n;
            }
        }

        return n;
    }

    SFL_NODISCARD
    bool contains(const Key& key) const
    {
        return find(key) != end();
    }

    template <typename K,
        typename std::enable_if
        <
            SFL_DTL::has_is_transparent<KeyEqual, K>::value
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
            data_.ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        if (data_.first_ != data_.internal_storage())
        {
            SFL_DTL::deallocate
            (
                data_.ref_to_alloc(),
                data_.first_,
                data_.end_ - data_.first_
            );
        }

        data_.first_ = data_.internal_storage();
        data_.last_  = data_.first_;
        data_.end_   = data_.first_ + N;

        if (new_cap > N)
        {
            data_.first_ = SFL_DTL::allocate(data_.ref_to_alloc(), new_cap);
            data_.last_  = data_.first_;
            data_.end_   = data_.first_ + new_cap;

            // If allocation throws, first_, last_ and end_ will be valid
            // (they will be pointing to internal_storage).
        }
    }

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
                data_.ref_to_alloc(),
                data_.first_,
                data_.last_
            );

            if (data_.first_ != data_.internal_storage())
            {
                SFL_DTL::deallocate
                (
                    data_.ref_to_alloc(),
                    data_.first_,
                    data_.end_ - data_.first_
                );
            }

            SFL_RETHROW;
        }
    }

    void initialize_copy(const small_unordered_flat_multiset& other)
    {
        const size_type n = other.size();

        check_size(n, "sfl::small_unordered_flat_multiset::initialize_copy");

        if (n > N)
        {
            data_.first_ = SFL_DTL::allocate(data_.ref_to_alloc(), n);
            data_.last_  = data_.first_;
            data_.end_   = data_.first_ + n;
        }

        SFL_TRY
        {
            data_.last_ = SFL_DTL::uninitialized_copy
            (
                data_.ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                data_.first_
            );
        }
        SFL_CATCH (...)
        {
            if (n > N)
            {
                SFL_DTL::deallocate(data_.ref_to_alloc(), data_.first_, n);
            }

            SFL_RETHROW;
        }
    }

    void initialize_move(small_unordered_flat_multiset& other)
    {
        if (other.data_.first_ == other.data_.internal_storage())
        {
            data_.last_ = SFL_DTL::uninitialized_move
            (
                data_.ref_to_alloc(),
                other.data_.first_,
                other.data_.last_,
                data_.first_
            );
        }
        else if (data_.ref_to_alloc() == other.data_.ref_to_alloc())
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

            check_size(n, "sfl::small_unordered_flat_multiset::initialize_move");

            if (n > N)
            {
                data_.first_ = SFL_DTL::allocate(data_.ref_to_alloc(), n);
                data_.last_  = data_.first_;
                data_.end_   = data_.first_ + n;
            }

            SFL_TRY
            {
                data_.last_ = SFL_DTL::uninitialized_move
                (
                    data_.ref_to_alloc(),
                    other.data_.first_,
                    other.data_.last_,
                    data_.first_
                );
            }
            SFL_CATCH (...)
            {
                if (n > N)
                {
                    SFL_DTL::deallocate(data_.ref_to_alloc(), data_.first_, n);
                }

                SFL_RETHROW;
            }
        }
    }

    template <typename ForwardIt>
    void assign_range(ForwardIt first, ForwardIt last)
    {
        const size_type n = std::distance(first, last);

        check_size(n, "sfl::small_unordered_flat_multiset::assign_range");

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
                    data_.ref_to_alloc(),
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
                    data_.ref_to_alloc(),
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
                data_.ref_to_alloc(),
                first,
                last,
                data_.first_
            );
        }
    }

    void assign_copy(const small_unordered_flat_multiset& other)
    {
        if (this != &other)
        {
            if (allocator_traits::propagate_on_container_copy_assignment::value)
            {
                if (data_.ref_to_alloc() != other.data_.ref_to_alloc())
                {
                    reset();
                }

                data_.ref_to_alloc() = other.data_.ref_to_alloc();
            }

            data_.ref_to_equal() = other.data_.ref_to_equal();

            assign_range(other.data_.first_, other.data_.last_);
        }
    }

    void assign_move(small_unordered_flat_multiset& other)
    {
        if (allocator_traits::propagate_on_container_move_assignment::value)
        {
            if (data_.ref_to_alloc() != other.data_.ref_to_alloc())
            {
                reset();
            }

            data_.ref_to_alloc() = std::move(other.data_.ref_to_alloc());
        }

        data_.ref_to_equal() = other.data_.ref_to_equal();

        if (other.data_.first_ == other.data_.internal_storage())
        {
            assign_range
            (
                std::make_move_iterator(other.data_.first_),
                std::make_move_iterator(other.data_.last_)
            );
        }
        else if (data_.ref_to_alloc() == other.data_.ref_to_alloc())
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
    }

    template <typename... Args>
    iterator insert_unordered(Args&&... args)
    {
        iterator result;

        if (data_.last_ != data_.end_)
        {
            SFL_DTL::construct_at
            (
                data_.ref_to_alloc(),
                data_.last_,
                std::forward<Args>(args)...
            );

            result = data_.last_;

            ++data_.last_;
        }
        else
        {
            const size_type new_cap =
                recommend_size(1, "sfl::small_unordered_flat_map::insert_unordered");

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
                new_first = SFL_DTL::allocate(data_.ref_to_alloc(), new_cap);
                new_last  = new_first;
                new_end   = new_first + new_cap;
            }

            SFL_TRY
            {
                // This is unordered container. We will first construct
                // new element in new storage and after that we will move
                // elements from old storage to new storage.

                SFL_DTL::construct_at
                (
                    data_.ref_to_alloc(),
                    new_last,
                    std::forward<Args>(args)...
                );

                result = new_last;

                ++new_last;

                new_last = SFL_DTL::uninitialized_move_if_noexcept
                (
                    data_.ref_to_alloc(),
                    data_.first_,
                    data_.last_,
                    new_last
                );
            }
            SFL_CATCH (...)
            {
                SFL_DTL::destroy
                (
                    data_.ref_to_alloc(),
                    new_first,
                    new_last
                );

                if (new_first != data_.internal_storage())
                {
                    SFL_DTL::deallocate
                    (
                        data_.ref_to_alloc(),
                        new_first,
                        new_cap
                    );
                }

                SFL_RETHROW;
            }

            SFL_DTL::destroy
            (
                data_.ref_to_alloc(),
                data_.first_,
                data_.last_
            );

            if (data_.first_ != data_.internal_storage())
            {
                SFL_DTL::deallocate
                (
                    data_.ref_to_alloc(),
                    data_.first_,
                    data_.end_ - data_.first_
                );
            }

            data_.first_ = new_first;
            data_.last_  = new_last;
            data_.end_   = new_end;
        }

        return result;
    }
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, typename E, typename A>
SFL_NODISCARD
bool operator==
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
)
{
    return x.size() == y.size() && std::is_permutation(x.begin(), x.end(), y.begin());
}

template <typename K, std::size_t N, typename E, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
)
{
    return !(x == y);
}

template <typename K, std::size_t N, typename E, typename A>
void swap
(
    small_unordered_flat_multiset<K, N, E, A>& x,
    small_unordered_flat_multiset<K, N, E, A>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, typename E, typename A,
          typename Predicate>
typename small_unordered_flat_multiset<K, N, E, A>::size_type
    erase_if(small_unordered_flat_multiset<K, N, E, A>& c, Predicate pred)
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

#undef SFL_DTL_BEGIN
#undef SFL_DTL_END
#undef SFL_DTL
#undef SFL_ASSERT
#undef SFL_CONSTEXPR_14
#undef SFL_NODISCARD
#undef SFL_TRY
#undef SFL_CATCH
#undef SFL_RETHROW

#endif // SFL_SMALL_UNORDERED_FLAT_MULTISET_HPP

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

#ifndef SFL_PRIVATE_HPP_INCLUDED
#define SFL_PRIVATE_HPP_INCLUDED

#include <algorithm>    // move, copy, etc.
#include <cassert>      // assert
#include <cstdlib>      // abort
#include <iterator>     // iterator_traits, xxxxx_iterator_tag
#include <memory>       // addressof, allocator_traits, pointer_traits
#include <stdexcept>    // length_error, out_of_range
#include <type_traits>  // enable_if, is_convertible, is_function, true_type...
#include <utility>      // forward, move, move_if_noexcept

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// MACROS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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

namespace sfl
{

namespace dtl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// This function is used for silencing warnings about unused variables.
//
template <typename... Args>
SFL_CONSTEXPR_14
void ignore_unused(Args&&...)
{
    // Do nothing.
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// TYPE TRAITS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename...>
using void_t = void;

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

//
// This struct provides information about segmented iterators.
//
// The architecture about segmented iterator traits is based on this article:
// "Segmented Iterators and Hierarchical Algorithms", Matthew H. Austern.
//
template <typename T>
struct segmented_iterator_traits
{
    using is_segmented_iterator = std::false_type;

    //
    // Specialized struct must define the following types and functions:
    //
    // using iterator         = xxxxx; (it is usually `T`)
    // using segment_iterator = xxxxx;
    // using local_iterator   = xxxxx;
    //
    // static segment_iterator segment(iterator);
    // static local_iterator   local(iterator);
    //
    // static local_iterator begin(segment_iterator);
    // static local_iterator end(segment_iterator);
    //
    // static iterator compose(segment_iterator, local_iterator);
    //
};

//
// Checks if `T` is segmented iterator.
//
template <typename T>
struct is_segmented_iterator :
    sfl::dtl::segmented_iterator_traits<T>::is_segmented_iterator {};

//
// Checks if `T` is input iterator.
//
template <typename Iterator, typename = void>
struct is_input_iterator : std::false_type {};

template <typename Iterator>
struct is_input_iterator<
    Iterator,
    sfl::dtl::enable_if_t<
        std::is_convertible<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::input_iterator_tag
        >::value
    >
> : std::true_type {};

//
// Checks if `T` is exactly input iterator.
//
template <typename T, typename = void>
struct is_exactly_input_iterator : std::false_type {};

template <typename T>
struct is_exactly_input_iterator<
    T,
    sfl::dtl::enable_if_t<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category,
            std::input_iterator_tag
        >::value
        &&
       !std::is_convertible<
            typename std::iterator_traits<T>::iterator_category,
            std::forward_iterator_tag
        >::value
    >
> : std::true_type {};

//
// Checks if `T` is forward iterator.
//
template <typename T, typename = void>
struct is_forward_iterator : std::false_type {};

template <typename T>
struct is_forward_iterator<
    T,
    sfl::dtl::enable_if_t<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category,
            std::forward_iterator_tag
        >::value
    >
> : std::true_type {};

//
// Checks if `T` is random access iterator.
//
template <typename T, typename = void>
struct is_random_access_iterator : std::false_type {};

template <typename T>
struct is_random_access_iterator<
    T,
    sfl::dtl::enable_if_t<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category,
            std::random_access_iterator_tag
        >::value
    >
> : std::true_type {};

//
// Checks if `Type` has member `is_transparent`.
//
template <typename Type, typename SfinaeType, typename = void>
struct has_is_transparent : std::false_type {};

template <typename Type, typename SfinaeType>
struct has_is_transparent<
    Type, SfinaeType, sfl::dtl::void_t<typename Type::is_transparent>
> : std::true_type {};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// POINTER TRAITS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// Raw pointer overload.
// Obtains a dereferenceable pointer to its argument.
//
template <typename T>
constexpr
T* to_address(T* p) noexcept
{
    static_assert(!std::is_function<T>::value, "not a function pointer");
    return p;
}

//
// Fancy pointer overload.
// Obtains a raw pointer from a fancy pointer.
//
template <typename Pointer>
constexpr
auto to_address(const Pointer& p) noexcept -> typename std::pointer_traits<Pointer>::element_type*
{
    return sfl::dtl::to_address(p.operator->());
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// INITIALIZED MEMORY ALGORITHMS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  !sfl::dtl::is_segmented_iterator<OutputIt>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                   sfl::dtl::is_segmented_iterator<OutputIt>::value &&
                                  !sfl::dtl::is_random_access_iterator<InputIt>::value) >* = nullptr>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    return std::copy(first, last, d_first);
}

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  sfl::dtl::is_segmented_iterator<OutputIt>::value &&
                                  sfl::dtl::is_random_access_iterator<InputIt>::value >* = nullptr>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<OutputIt>;

    if (first == last)
    {
        return d_first;
    }
    else
    {
        auto curr = first;

        auto d_local = traits::local(d_first);
        auto d_seg   = traits::segment(d_first);

        while (true)
        {
            using difference_type =
                typename std::iterator_traits<InputIt>::difference_type;

            const auto count = std::min<difference_type>
            (
                std::distance(curr, last),
                std::distance(d_local, traits::end(d_seg))
            );

            const auto next = curr + count;

            d_local = sfl::dtl::copy
            (
                curr,
                next,
                d_local
            );

            curr = next;

            if (curr == last)
            {
                return traits::compose(d_seg, d_local);
            }

            ++d_seg;

            d_local = traits::begin(d_seg);
        }
    }
}

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<InputIt>::value >* = nullptr>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<InputIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::copy
        (
            traits::local(first),
            traits::local(last),
            d_first
        );
    }
    else
    {
        d_first = sfl::dtl::copy
        (
            traits::local(first),
            traits::end(first_seg),
            d_first
        );

        ++first_seg;

        while (first_seg != last_seg)
        {
            d_first = sfl::dtl::copy
            (
                traits::begin(first_seg),
                traits::end(first_seg),
                d_first
            );

            ++first_seg;
        }

        d_first = sfl::dtl::copy
        (
            traits::begin(last_seg),
            traits::local(last),
            d_first
        );

        return d_first;
    }
}

template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt d_first)
{
    return std::copy_n(first, count, d_first);
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                  !sfl::dtl::is_segmented_iterator<BidirIt2>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                   sfl::dtl::is_segmented_iterator<BidirIt2>::value &&
                                  !sfl::dtl::is_random_access_iterator<BidirIt1>::value) >* = nullptr>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    return std::copy_backward(first, last, d_last);
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                  sfl::dtl::is_segmented_iterator<BidirIt2>::value &&
                                  sfl::dtl::is_random_access_iterator<BidirIt1>::value>* = nullptr>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    using traits = sfl::dtl::segmented_iterator_traits<BidirIt2>;

    if (first == last)
    {
        return d_last;
    }
    else
    {
        auto curr = last;

        auto d_local = traits::local(d_last);
        auto d_seg   = traits::segment(d_last);

        while (true)
        {
            using difference_type =
                typename std::iterator_traits<BidirIt1>::difference_type;

            const auto count = std::min<difference_type>
            (
                std::distance(first, curr),
                std::distance(traits::begin(d_seg), d_local)
            );

            const auto prev = curr - count;

            d_local = sfl::dtl::copy_backward
            (
                prev,
                curr,
                d_local
            );

            curr = prev;

            if (curr == first)
            {
                return traits::compose(d_seg, d_local);
            }

            --d_seg;

            d_local = traits::end(d_seg);
        }
    }
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<BidirIt1>::value >* = nullptr>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    using traits = sfl::dtl::segmented_iterator_traits<BidirIt1>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::copy_backward
        (
            traits::local(first),
            traits::local(last),
            d_last
        );
    }
    else
    {
        d_last = sfl::dtl::copy_backward
        (
            traits::begin(last_seg),
            traits::local(last),
            d_last
        );

        --last_seg;

        while (first_seg != last_seg)
        {
            d_last = sfl::dtl::copy_backward
            (
                traits::begin(last_seg),
                traits::end(last_seg),
                d_last
            );

            --last_seg;
        }

        d_last = sfl::dtl::copy_backward
        (
            traits::local(first),
            traits::end(last_seg),
            d_last
        );

        return d_last;
    }
}

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  !sfl::dtl::is_segmented_iterator<OutputIt>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                   sfl::dtl::is_segmented_iterator<OutputIt>::value &&
                                  !sfl::dtl::is_random_access_iterator<InputIt>::value) >* = nullptr>
OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
    return std::move(first, last, d_first);
}

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  sfl::dtl::is_segmented_iterator<OutputIt>::value &&
                                  sfl::dtl::is_random_access_iterator<InputIt>::value >* = nullptr>
OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<OutputIt>;

    if (first == last)
    {
        return d_first;
    }
    else
    {
        auto curr = first;

        auto d_local = traits::local(d_first);
        auto d_seg   = traits::segment(d_first);

        while (true)
        {
            using difference_type =
                typename std::iterator_traits<InputIt>::difference_type;

            const auto count = std::min<difference_type>
            (
                std::distance(curr, last),
                std::distance(d_local, traits::end(d_seg))
            );

            const auto next = curr + count;

            d_local = sfl::dtl::move
            (
                curr,
                next,
                d_local
            );

            curr = next;

            if (curr == last)
            {
                return traits::compose(d_seg, d_local);
            }

            ++d_seg;

            d_local = traits::begin(d_seg);
        }
    }
}

template <typename InputIt, typename OutputIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<InputIt>::value >* = nullptr>
OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<InputIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::move
        (
            traits::local(first),
            traits::local(last),
            d_first
        );
    }
    else
    {
        d_first = sfl::dtl::move
        (
            traits::local(first),
            traits::end(first_seg),
            d_first
        );

        ++first_seg;

        while (first_seg != last_seg)
        {
            d_first = sfl::dtl::move
            (
                traits::begin(first_seg),
                traits::end(first_seg),
                d_first
            );

            ++first_seg;
        }

        d_first = sfl::dtl::move
        (
            traits::begin(last_seg),
            traits::local(last),
            d_first
        );

        return d_first;
    }
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                  !sfl::dtl::is_segmented_iterator<BidirIt2>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                   sfl::dtl::is_segmented_iterator<BidirIt2>::value &&
                                  !sfl::dtl::is_random_access_iterator<BidirIt1>::value) >* = nullptr>
BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    return std::move_backward(first, last, d_last);
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<BidirIt1>::value &&
                                  sfl::dtl::is_segmented_iterator<BidirIt2>::value &&
                                  sfl::dtl::is_random_access_iterator<BidirIt1>::value >* = nullptr>
BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    using traits = sfl::dtl::segmented_iterator_traits<BidirIt2>;

    if (first == last)
    {
        return d_last;
    }
    else
    {
        auto curr = last;

        auto d_local = traits::local(d_last);
        auto d_seg   = traits::segment(d_last);

        while (true)
        {
            using difference_type =
                typename std::iterator_traits<BidirIt1>::difference_type;

            const auto count = std::min<difference_type>
            (
                std::distance(first, curr),
                std::distance(traits::begin(d_seg), d_local)
            );

            const auto prev = curr - count;

            d_local = sfl::dtl::move_backward
            (
                prev,
                curr,
                d_local
            );

            curr = prev;

            if (curr == first)
            {
                return traits::compose(d_seg, d_local);
            }

            --d_seg;

            d_local = traits::end(d_seg);
        }
    }
}

template <typename BidirIt1, typename BidirIt2,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<BidirIt1>::value >* = nullptr>
BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    using traits = sfl::dtl::segmented_iterator_traits<BidirIt1>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::move_backward
        (
            traits::local(first),
            traits::local(last),
            d_last
        );
    }
    else
    {
        d_last = sfl::dtl::move_backward
        (
            traits::begin(last_seg),
            traits::local(last),
            d_last
        );

        --last_seg;

        while (first_seg != last_seg)
        {
            d_last = sfl::dtl::move_backward
            (
                traits::begin(last_seg),
                traits::end(last_seg),
                d_last
            );

            --last_seg;
        }

        d_last = sfl::dtl::move_backward
        (
            traits::local(first),
            traits::end(last_seg),
            d_last
        );

        return d_last;
    }
}

template <typename ForwardIt, typename T,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    std::fill(first, last, value);
}

template <typename ForwardIt, typename T,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        sfl::dtl::fill
        (
            traits::local(first),
            traits::local(last),
            value
        );
    }
    else
    {
        sfl::dtl::fill
        (
            traits::local(first),
            traits::end(first_seg),
            value
        );

        ++first_seg;

        while (first_seg != last_seg)
        {
            sfl::dtl::fill
            (
                traits::begin(first_seg),
                traits::end(first_seg),
                value
            );

            ++first_seg;
        }

        sfl::dtl::fill
        (
            traits::begin(last_seg),
            traits::local(last),
            value
        );
    }
}

template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size count, const T& value)
{
    return std::fill_n(first, count, value);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// UNINITIALIZED MEMORY ALGORITHMS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename Allocator, typename Size>
auto allocate(Allocator& a, Size n) -> typename std::allocator_traits<Allocator>::pointer
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
void construct_at_a(Allocator& a, Pointer p, Args&&... args)
{
    std::allocator_traits<Allocator>::construct
    (
        a,
        sfl::dtl::to_address(p),
        std::forward<Args>(args)...
    );
}

template <typename Allocator, typename Pointer>
void destroy_at_a(Allocator& a, Pointer p) noexcept
{
    std::allocator_traits<Allocator>::destroy
    (
        a,
        sfl::dtl::to_address(p)
    );
}

template <typename Allocator, typename ForwardIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void destroy_a(Allocator& a, ForwardIt first, ForwardIt last) noexcept
{
    while (first != last)
    {
        sfl::dtl::destroy_at_a(a, std::addressof(*first));
        ++first;
    }
}

template <typename Allocator, typename ForwardIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void destroy_a(Allocator& a, ForwardIt first, ForwardIt last) noexcept
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        sfl::dtl::destroy_a
        (
            a,
            traits::local(first),
            traits::local(last)
        );
    }
    else
    {
        sfl::dtl::destroy_a
        (
            a,
            traits::local(first),
            traits::end(first_seg)
        );

        ++first_seg;

        while (first_seg != last_seg)
        {
            sfl::dtl::destroy_a
            (
                a,
                traits::begin(first_seg),
                traits::end(first_seg)
            );

            ++first_seg;
        }

        sfl::dtl::destroy_a
        (
            a,
            traits::begin(last_seg),
            traits::local(last)
        );
    }
}

template <typename Allocator, typename ForwardIt, typename Size,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt destroy_n_a(Allocator& a, ForwardIt first, Size n) noexcept
{
    while (n > 0)
    {
        sfl::dtl::destroy_at_a(a, std::addressof(*first));
        ++first;
        --n;
    }
    return first;
}

template <typename Allocator, typename ForwardIt, typename Size,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt destroy_n_a(Allocator& a, ForwardIt first, Size n) noexcept
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto curr_local = traits::local(first);
    auto curr_seg   = traits::segment(first);

    auto remainining = n;

    while (true)
    {
        using difference_type =
            typename std::iterator_traits<typename traits::local_iterator>::difference_type;

        const auto count = std::min<difference_type>
        (
            remainining,
            std::distance(curr_local, traits::end(curr_seg))
        );

        curr_local = sfl::dtl::destroy_n_a
        (
            a,
            curr_local,
            count
        );

        remainining -= count;

        SFL_ASSERT(remainining <= n && "Bug in algorithm. Please report it.");

        if (remainining == 0)
        {
            return traits::compose(curr_seg, curr_local);
        }

        ++curr_seg;

        curr_local = traits::begin(curr_seg);
    }
}

template <typename Allocator, typename ForwardIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void uninitialized_default_construct_a(Allocator& a, ForwardIt first, ForwardIt last)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (curr != last)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*curr));
            ++curr;
        }
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void uninitialized_default_construct_a(Allocator& a, ForwardIt first, ForwardIt last)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        sfl::dtl::uninitialized_default_construct_a
        (
            a,
            traits::local(first),
            traits::local(last)
        );
    }
    else
    {
        sfl::dtl::uninitialized_default_construct_a
        (
            a,
            traits::local(first),
            traits::end(first_seg)
        );

        ++first_seg;

        SFL_TRY
        {
            while (first_seg != last_seg)
            {
                sfl::dtl::uninitialized_default_construct_a
                (
                    a,
                    traits::begin(first_seg),
                    traits::end(first_seg)
                );

                ++first_seg;
            }

            sfl::dtl::uninitialized_default_construct_a
            (
                a,
                traits::begin(last_seg),
                traits::local(last)
            );
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                first,
                traits::compose(first_seg, traits::begin(first_seg))
            );

            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename ForwardIt, typename Size,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt uninitialized_default_construct_n_a(Allocator& a, ForwardIt first, Size n)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename Size,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt uninitialized_default_construct_n_a(Allocator& a, ForwardIt first, Size n)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto curr_local = traits::local(first);
    auto curr_seg   = traits::segment(first);

    auto remainining = n;

    SFL_TRY
    {
        while (true)
        {
            using difference_type =
                typename std::iterator_traits<typename traits::local_iterator>::difference_type;

            const auto count = std::min<difference_type>
            (
                remainining,
                std::distance(curr_local, traits::end(curr_seg))
            );

            curr_local = sfl::dtl::uninitialized_default_construct_n_a
            (
                a,
                curr_local,
                count
            );

            remainining -= count;

            SFL_ASSERT(remainining <= n && "Bug in algorithm. Please report it.");

            if (remainining == 0)
            {
                return traits::compose(curr_seg, curr_local);
            }

            ++curr_seg;

            curr_local = traits::begin(curr_seg);
        }
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_n_a(a, first, n - remainining);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename T,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void uninitialized_fill_a(Allocator& a, ForwardIt first, ForwardIt last, const T& value)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (curr != last)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*curr), value);
            ++curr;
        }
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename T,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
void uninitialized_fill_a(Allocator& a, ForwardIt first, ForwardIt last, const T& value)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        sfl::dtl::uninitialized_fill_a
        (
            a,
            traits::local(first),
            traits::local(last),
            value
        );
    }
    else
    {
        sfl::dtl::uninitialized_fill_a
        (
            a,
            traits::local(first),
            traits::end(first_seg),
            value
        );

        ++first_seg;

        SFL_TRY
        {
            while (first_seg != last_seg)
            {
                sfl::dtl::uninitialized_fill_a
                (
                    a,
                    traits::begin(first_seg),
                    traits::end(first_seg),
                    value
                );

                ++first_seg;
            }

            sfl::dtl::uninitialized_fill_a
            (
                a,
                traits::begin(last_seg),
                traits::local(last),
                value
            );
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                first,
                traits::compose(first_seg, traits::begin(first_seg))
            );

            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename ForwardIt, typename Size, typename T,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt uninitialized_fill_n_a(Allocator& a, ForwardIt first, Size n, const T& value)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*curr), value);
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, first, curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename ForwardIt, typename Size, typename T,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<ForwardIt>::value >* = nullptr>
ForwardIt uninitialized_fill_n_a(Allocator& a, ForwardIt first, Size n, const T& value)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    auto curr_local = traits::local(first);
    auto curr_seg   = traits::segment(first);

    auto remainining = n;

    SFL_TRY
    {
        while (true)
        {
            using difference_type =
                typename std::iterator_traits<typename traits::local_iterator>::difference_type;

            const auto count = std::min<difference_type>
            (
                remainining,
                std::distance(curr_local, traits::end(curr_seg))
            );

            curr_local = sfl::dtl::uninitialized_fill_n_a
            (
                a,
                curr_local,
                count,
                value
            );

            remainining -= count;

            SFL_ASSERT(remainining <= n && "Bug in algorithm. Please report it.");

            if (remainining == 0)
            {
                return traits::compose(curr_seg, curr_local);
            }

            ++curr_seg;

            curr_local = traits::begin(curr_seg);
        }
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_n_a(a, first, n - remainining);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  !sfl::dtl::is_segmented_iterator<ForwardIt>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                   sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  !sfl::dtl::is_random_access_iterator<InputIt>::value) >* = nullptr>
ForwardIt uninitialized_copy_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*d_curr), *first);
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  sfl::dtl::is_random_access_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_copy_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    if (first == last)
    {
        return d_first;
    }
    else
    {
        auto curr = first;

        auto d_local = traits::local(d_first);
        auto d_seg   = traits::segment(d_first);

        SFL_TRY
        {
            while (true)
            {
                using difference_type =
                    typename std::iterator_traits<InputIt>::difference_type;

                const auto count = std::min<difference_type>
                (
                    std::distance(curr, last),
                    std::distance(d_local, traits::end(d_seg))
                );

                const auto next = curr + count;

                d_local = sfl::dtl::uninitialized_copy_a
                (
                    a,
                    curr,
                    next,
                    d_local
                );

                curr = next;

                if (curr == last)
                {
                    return traits::compose(d_seg, d_local);
                }

                ++d_seg;

                d_local = traits::begin(d_seg);
            }
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                traits::compose(d_seg, d_local)
            );
            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_copy_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<InputIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::uninitialized_copy_a
        (
            a,
            traits::local(first),
            traits::local(last),
            d_first
        );
    }
    else
    {
        auto d_curr = d_first;

        d_curr = sfl::dtl::uninitialized_copy_a
        (
            a,
            traits::local(first),
            traits::end(first_seg),
            d_curr
        );

        ++first_seg;

        SFL_TRY
        {
            while (first_seg != last_seg)
            {
                d_curr = sfl::dtl::uninitialized_copy_a
                (
                    a,
                    traits::begin(first_seg),
                    traits::end(first_seg),
                    d_curr
                );

                ++first_seg;
            }

            d_curr = sfl::dtl::uninitialized_copy_a
            (
                a,
                traits::begin(last_seg),
                traits::local(last),
                d_curr
            );

            return d_curr;
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                d_curr
            );
            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  !sfl::dtl::is_segmented_iterator<ForwardIt>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                   sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  !sfl::dtl::is_random_access_iterator<InputIt>::value) >* = nullptr>
ForwardIt uninitialized_move_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*d_curr), std::move(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  sfl::dtl::is_random_access_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_move_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    if (first == last)
    {
        return d_first;
    }
    else
    {
        auto curr = first;

        auto d_local = traits::local(d_first);
        auto d_seg   = traits::segment(d_first);

        SFL_TRY
        {
            while (true)
            {
                using difference_type =
                    typename std::iterator_traits<InputIt>::difference_type;

                const auto count = std::min<difference_type>
                (
                    std::distance(curr, last),
                    std::distance(d_local, traits::end(d_seg))
                );

                const auto next = curr + count;

                d_local = sfl::dtl::uninitialized_move_a
                (
                    a,
                    curr,
                    next,
                    d_local
                );

                curr = next;

                if (curr == last)
                {
                    return traits::compose(d_seg, d_local);
                }

                ++d_seg;

                d_local = traits::begin(d_seg);
            }
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                traits::compose(d_seg, d_local)
            );
            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_move_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<InputIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::uninitialized_move_a
        (
            a,
            traits::local(first),
            traits::local(last),
            d_first
        );
    }
    else
    {
        auto d_curr = d_first;

        d_curr = sfl::dtl::uninitialized_move_a
        (
            a,
            traits::local(first),
            traits::end(first_seg),
            d_curr
        );

        ++first_seg;

        SFL_TRY
        {
            while (first_seg != last_seg)
            {
                d_curr = sfl::dtl::uninitialized_move_a
                (
                    a,
                    traits::begin(first_seg),
                    traits::end(first_seg),
                    d_curr
                );

                ++first_seg;
            }

            d_curr = sfl::dtl::uninitialized_move_a
            (
                a,
                traits::begin(last_seg),
                traits::local(last),
                d_curr
            );

            return d_curr;
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                d_curr
            );
            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  !sfl::dtl::is_segmented_iterator<ForwardIt>::value) ||
                                 (!sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                   sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  !sfl::dtl::is_random_access_iterator<InputIt>::value) >* = nullptr>
ForwardIt uninitialized_move_if_noexcept_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            sfl::dtl::construct_at_a(a, std::addressof(*d_curr), std::move_if_noexcept(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy_a(a, d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< !sfl::dtl::is_segmented_iterator<InputIt>::value &&
                                  sfl::dtl::is_segmented_iterator<ForwardIt>::value &&
                                  sfl::dtl::is_random_access_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_move_if_noexcept_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<ForwardIt>;

    if (first == last)
    {
        return d_first;
    }
    else
    {
        auto curr = first;

        auto d_local = traits::local(d_first);
        auto d_seg   = traits::segment(d_first);

        SFL_TRY
        {
            while (true)
            {
                using difference_type =
                    typename std::iterator_traits<InputIt>::difference_type;

                const auto count = std::min<difference_type>
                (
                    std::distance(curr, last),
                    std::distance(d_local, traits::end(d_seg))
                );

                const auto next = curr + count;

                d_local = sfl::dtl::uninitialized_move_if_noexcept_a
                (
                    a,
                    curr,
                    next,
                    d_local
                );

                curr = next;

                if (curr == last)
                {
                    return traits::compose(d_seg, d_local);
                }

                ++d_seg;

                d_local = traits::begin(d_seg);
            }
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                traits::compose(d_seg, d_local)
            );
            SFL_RETHROW;
        }
    }
}

template <typename Allocator, typename InputIt, typename ForwardIt,
          sfl::dtl::enable_if_t< sfl::dtl::is_segmented_iterator<InputIt>::value >* = nullptr>
ForwardIt uninitialized_move_if_noexcept_a(Allocator& a, InputIt first, InputIt last, ForwardIt d_first)
{
    using traits = sfl::dtl::segmented_iterator_traits<InputIt>;

    auto first_seg = traits::segment(first);
    auto last_seg  = traits::segment(last);

    if (first_seg == last_seg)
    {
        return sfl::dtl::uninitialized_move_if_noexcept_a
        (
            a,
            traits::local(first),
            traits::local(last),
            d_first
        );
    }
    else
    {
        auto d_curr = d_first;

        d_curr = sfl::dtl::uninitialized_move_if_noexcept_a
        (
            a,
            traits::local(first),
            traits::end(first_seg),
            d_curr
        );

        ++first_seg;

        SFL_TRY
        {
            while (first_seg != last_seg)
            {
                d_curr = sfl::dtl::uninitialized_move_if_noexcept_a
                (
                    a,
                    traits::begin(first_seg),
                    traits::end(first_seg),
                    d_curr
                );

                ++first_seg;
            }

            d_curr = sfl::dtl::uninitialized_move_if_noexcept_a
            (
                a,
                traits::begin(last_seg),
                traits::local(last),
                d_curr
            );

            return d_curr;
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_a
            (
                a,
                d_first,
                d_curr
            );
            SFL_RETHROW;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
void default_construct_at(T* p)
{
    ::new (static_cast<void*>(p)) T;
}

template <typename T>
void value_construct_at(T* p)
{
    ::new (static_cast<void*>(p)) T();
}

template <typename T, typename... Args>
void construct_at(T* p, Args&&... args)
{
    ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
}

template <typename T>
void destroy_at(T* p) noexcept
{
    p->~T();
}

template <typename ForwardIt>
void destroy(ForwardIt first, ForwardIt last) noexcept
{
    while (first != last)
    {
        sfl::dtl::destroy_at(std::addressof(*first));
        ++first;
    }
}

template <typename ForwardIt, typename Size>
ForwardIt uninitialized_default_construct_n(ForwardIt first, Size n)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            sfl::dtl::default_construct_at(std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(first, curr);
        SFL_RETHROW;
    }
}

template <typename ForwardIt, typename Size>
ForwardIt uninitialized_value_construct_n(ForwardIt first, Size n)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            sfl::dtl::value_construct_at(std::addressof(*curr));
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(first, curr);
        SFL_RETHROW;
    }
}

template <typename ForwardIt, typename T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (curr != last)
        {
            sfl::dtl::construct_at(std::addressof(*curr), value);
            ++curr;
        }
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(first, curr);
        SFL_RETHROW;
    }
}

template <typename ForwardIt, typename Size, typename T>
ForwardIt uninitialized_fill_n(ForwardIt first, Size n, const T& value)
{
    ForwardIt curr = first;
    SFL_TRY
    {
        while (n > 0)
        {
            sfl::dtl::construct_at(std::addressof(*curr), value);
            ++curr;
            --n;
        }
        return curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(first, curr);
        SFL_RETHROW;
    }
}

template <typename InputIt, typename ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            sfl::dtl::construct_at(std::addressof(*d_curr), *first);
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(d_first, d_curr);
        SFL_RETHROW;
    }
}

template <typename InputIt, typename ForwardIt>
ForwardIt uninitialized_move(InputIt first, InputIt last, ForwardIt d_first)
{
    ForwardIt d_curr = d_first;
    SFL_TRY
    {
        while (first != last)
        {
            sfl::dtl::construct_at(std::addressof(*d_curr), std::move(*first));
            ++d_curr;
            ++first;
        }
        return d_curr;
    }
    SFL_CATCH (...)
    {
        sfl::dtl::destroy(d_first, d_curr);
        SFL_RETHROW;
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// EXCEPTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

[[noreturn]]
inline void throw_length_error(const char* msg)
{
    #ifdef SFL_NO_EXCEPTIONS
    sfl::dtl::ignore_unused(msg);
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
    sfl::dtl::ignore_unused(msg);
    SFL_ASSERT(!"std::out_of_range thrown");
    std::abort();
    #else
    throw std::out_of_range(msg);
    #endif
}

} // namespace dtl

// Type used to tag that the inserted values should be default initialized.
struct default_init_t { };

} // namespace sfl

#endif // SFL_PRIVATE_HPP_INCLUDED

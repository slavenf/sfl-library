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

#ifndef SFL_SEGMENTED_VECTOR_HPP
#define SFL_SEGMENTED_VECTOR_HPP

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

#define SFL_DTL_BEGIN  namespace dtl { namespace segmented_vector_dtl {
#define SFL_DTL_END    } }
#define SFL_DTL        ::sfl::dtl::segmented_vector_dtl

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
// ---- SEGMENTED VECTOR ------------------------------------------------------
//

template < typename ValueType,      // std::iterator_traits<Iter>::value_type
           typename Pointer,        // std::iterator_traits<Iter>::pointer
           typename Reference,      // std::iterator_traits<Iter>::reference
           typename DifferenceType, // std::iterator_traits<Iter>::difference_type
           typename SegmentPointer, // Non-const pointer to segment.
           typename ElementPointer, // Non-const pointer to element.
           std::size_t N >
class segmented_vector_iterator
{
    template <typename, typename, typename, typename, typename, typename, std::size_t>
    friend class segmented_vector_iterator;

    template <typename, std::size_t, typename>
    friend class segmented_vector;

public:

    using value_type        = ValueType;
    using pointer           = Pointer;
    using reference         = Reference;
    using difference_type   = DifferenceType;
    using iterator_category = std::random_access_iterator_tag;

private:

    using segment_pointer = SegmentPointer;
    using element_pointer = ElementPointer;

    segment_pointer seg_;
    element_pointer elem_;

public:

    /// Default constructor.
    segmented_vector_iterator() noexcept
    {}

    /// Copy constructor.
    segmented_vector_iterator(const segmented_vector_iterator& other) noexcept
        : seg_(other.seg_)
        , elem_(other.elem_)
    {}

    /// Converting constructor (from iterator to const_iterator).
    template <
        typename OtherPointer,
        typename OtherReference,
        typename std::enable_if<
            std::is_convertible<OtherPointer, Pointer>::value
        >::type* = nullptr
    >
    segmented_vector_iterator
    (
        const segmented_vector_iterator<
            ValueType,
            OtherPointer,
            OtherReference,
            DifferenceType,
            SegmentPointer,
            ElementPointer,
            N
        >& other
    ) noexcept
        : seg_(other.seg_)
        , elem_(other.elem_)
    {}

    /// Copy assignment operator.
    segmented_vector_iterator& operator=(const segmented_vector_iterator& other) noexcept
    {
        seg_ = other.seg_;
        elem_ = other.elem_;
        return *this;
    }

    SFL_NODISCARD
    reference operator*() const noexcept
    {
        return *elem_;
    }

    SFL_NODISCARD
    pointer operator->() const noexcept
    {
        return elem_;
    }

    segmented_vector_iterator& operator++() noexcept
    {
        increment_once();
        return *this;
    }

    segmented_vector_iterator operator++(int) noexcept
    {
        auto temp = *this;
        increment_once();
        return temp;
    }

    segmented_vector_iterator& operator--() noexcept
    {
        decrement_once();
        return *this;
    }

    segmented_vector_iterator operator--(int) noexcept
    {
        auto temp = *this;
        decrement_once();
        return temp;
    }

    segmented_vector_iterator& operator+=(difference_type n) noexcept
    {
        advance(n);
        return *this;
    }

    segmented_vector_iterator& operator-=(difference_type n) noexcept
    {
        advance(-n);
        return *this;
    }

    SFL_NODISCARD
    segmented_vector_iterator operator+(difference_type n) const noexcept
    {
        auto temp = *this;
        temp.advance(n);
        return temp;
    }

    SFL_NODISCARD
    segmented_vector_iterator operator-(difference_type n) const noexcept
    {
        auto temp = *this;
        temp.advance(-n);
        return temp;
    }

    SFL_NODISCARD
    reference operator[](difference_type n) const noexcept
    {
        auto temp = *this;
        temp.advance(n);
        return *temp;
    }

    SFL_NODISCARD
    friend segmented_vector_iterator operator+
    (
        difference_type n,
        const segmented_vector_iterator& it
    ) noexcept
    {
        return it + n;
    }

    SFL_NODISCARD
    friend difference_type operator-
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return (x.seg_ - y.seg_) * difference_type(N)
            + (x.elem_ - *x.seg_) - (y.elem_ - *y.seg_);
    }

    SFL_NODISCARD
    friend bool operator==
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return x.elem_ == y.elem_;
    }

    SFL_NODISCARD
    friend bool operator!=
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return !(x == y);
    }

    SFL_NODISCARD
    friend bool operator<
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return (x.seg_ == y.seg_) ? (x.elem_ < y.elem_) : (x.seg_ < y.seg_);
    }

    SFL_NODISCARD
    friend bool operator>
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return y < x;
    }

    SFL_NODISCARD
    friend bool operator<=
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return !(y < x);
    }

    SFL_NODISCARD
    friend bool operator>=
    (
        const segmented_vector_iterator& x,
        const segmented_vector_iterator& y
    ) noexcept
    {
        return !(x < y);
    }

private:

    segmented_vector_iterator(segment_pointer seg, element_pointer elem) noexcept
        : seg_(seg)
        , elem_(elem)
    {}

    void increment_once() noexcept
    {
        ++elem_;

        if (elem_ == *seg_ + N)
        {
            ++seg_;
            elem_ = *seg_;
        }
    }

    void decrement_once() noexcept
    {
        if (elem_ == *seg_)
        {
            --seg_;
            elem_ = *seg_ + N;
        }

        --elem_;
    }

    void advance(difference_type n) noexcept
    {
        const difference_type offset = n + (elem_ - *seg_);

        if (offset >= 0 && offset < difference_type(N))
        {
            elem_ += n;
        }
        else
        {
            const difference_type seg_offset =
                offset > 0 ? offset / difference_type(N)
                           : -difference_type((-offset - 1) / N) - 1;

            seg_ += seg_offset;

            elem_ = *seg_ + (offset - seg_offset * difference_type(N));
        }
    }
};

template < typename T,
           std::size_t N,
           typename Allocator = std::allocator<T> >
class segmented_vector
{
    static_assert(N > 0, "N must be greater than zero.");

public:

    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;
    using value_type       = T;
    using size_type        = typename allocator_traits::size_type;
    using difference_type  = typename allocator_traits::difference_type;
    using reference        = T&;
    using const_reference  = const T&;
    using pointer          = typename allocator_traits::pointer;
    using const_pointer    = typename allocator_traits::const_pointer;

    static_assert
    (
        std::is_same<typename Allocator::value_type, value_type>::value,
        "Allocator::value_type must be same as sfl::segmented_vector::value_type."
    );

private:

    using segment_allocator =
        typename std::allocator_traits<allocator_type>::template rebind_alloc<pointer>;

    using segment_pointer =
        typename std::allocator_traits<segment_allocator>::pointer;

public:

    using iterator =
        sfl::segmented_vector_iterator<
            value_type,
            pointer,
            reference,
            difference_type,
            segment_pointer,
            pointer,
            N
        >;

    using const_iterator =
        sfl::segmented_vector_iterator<
            value_type,
            const_pointer,
            const_reference,
            difference_type,
            segment_pointer,
            pointer,
            N
        >;

    using reverse_iterator =
        std::reverse_iterator<iterator>;

    using const_reverse_iterator =
        std::reverse_iterator<const_iterator>;

private:

    class data_base
    {
    public:

        segment_pointer seg_first_;
        segment_pointer seg_last_;
        segment_pointer seg_end_;

        iterator first_;
        iterator last_;
        iterator end_;
    };

    class data
        : public data_base
        , public allocator_type
    {
    public:

        data() noexcept
        (
            std::is_nothrow_default_constructible<allocator_type>::value
        )
            : allocator_type()
        {}

        data(const allocator_type& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<allocator_type>::value
        )
            : allocator_type(alloc)
        {}

        data(allocator_type&& other) noexcept
        (
            std::is_nothrow_move_constructible<allocator_type>::value
        )
            : allocator_type(std::move(other))
        {}

        allocator_type& ref_to_alloc() noexcept
        {
            return *this;
        }

        const allocator_type& ref_to_alloc() const noexcept
        {
            return *this;
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    segmented_vector()
        : data_()
    {
        initialize_empty();
    }

    explicit segmented_vector(const Allocator& alloc)
        : data_(alloc)
    {
        initialize_empty();
    }

    segmented_vector(size_type n)
        : data_()
    {
        initialize_default_n(n);
    }

    explicit segmented_vector(size_type n, const Allocator& alloc)
        : data_(alloc)
    {
        initialize_default_n(n);
    }

    segmented_vector(size_type n, const T& value)
        : data_()
    {
        initialize_fill_n(n, value);
    }

    segmented_vector(size_type n, const T& value, const Allocator& alloc)
        : data_(alloc)
    {
        initialize_fill_n(n, value);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    segmented_vector(InputIt first, InputIt last)
        : data_()
    {
        initialize_range
        (
            first,
            last,
            typename std::iterator_traits<InputIt>::iterator_category()
        );
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    segmented_vector(InputIt first, InputIt last, const Allocator& alloc)
        : data_(alloc)
    {
        initialize_range
        (
            first,
            last,
            typename std::iterator_traits<InputIt>::iterator_category()
        );
    }

    segmented_vector(std::initializer_list<T> ilist)
        : segmented_vector(ilist.begin(), ilist.end())
    {}

    segmented_vector(std::initializer_list<T> ilist, const Allocator& alloc)
        : segmented_vector(ilist.begin(), ilist.end(), alloc)
    {}

    segmented_vector(const segmented_vector& other)
        : data_
        (
            allocator_traits::select_on_container_copy_construction
            (
                other.data_.ref_to_alloc()
            )
        )
    {
        initialize_copy(other);
    }

    segmented_vector(const segmented_vector& other, const Allocator& alloc)
        : data_(alloc)
    {
        initialize_copy(other);
    }

    segmented_vector(segmented_vector&& other)
        : data_(std::move(other.data_.ref_to_alloc()))
    {
        initialize_move(other);
    }

    segmented_vector(segmented_vector&& other, const Allocator& alloc)
        : data_(alloc)
    {
        initialize_move(other);
    }

    ~segmented_vector()
    {
        SFL_DTL::destroy
        (
            data_.ref_to_alloc(),
            data_.first_,
            data_.last_
        );

        destroy_storage();
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    void assign(size_type n, const T& value)
    {
        assign_fill_n(n, value);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    void assign(InputIt first, InputIt last)
    {
        assign_range
        (
            first,
            last,
            typename std::iterator_traits<InputIt>::iterator_category()
        );
    }

    void assign(std::initializer_list<T> ilist)
    {
        assign_range
        (
            ilist.begin(),
            ilist.end(),
            std::random_access_iterator_tag()
        );
    }

    segmented_vector& operator=(const segmented_vector& other)
    {
        assign_copy(other);
        return *this;
    }

    segmented_vector& operator=(segmented_vector&& other)
    {
        assign_move(other);
        return *this;
    }

    segmented_vector& operator=(std::initializer_list<T> ilist)
    {
        assign_range
        (
            ilist.begin(),
            ilist.end(),
            std::random_access_iterator_tag()
        );
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

        const auto i = pos / N;
        const auto j = pos - i * N;

        const auto seg = data_.seg_first_ + i;
        const auto elem = *seg + j;

        return iterator(seg, elem);
    }

    SFL_NODISCARD
    const_iterator nth(size_type pos) const noexcept
    {
        SFL_ASSERT(pos <= size());

        const auto i = pos / N;
        const auto j = pos - i * N;

        const auto seg = data_.seg_first_ + i;
        const auto elem = *seg + j;

        return iterator(seg, elem);
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
        const size_type cap = capacity();

        if (new_cap > cap)
        {
            grow_storage(new_cap - cap);
        }
    }

    void shrink_to_fit()
    {
        shrink_storage();
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

    SFL_NODISCARD
    reference at(size_type pos)
    {
        if (pos >= size())
        {
            SFL_DTL::throw_out_of_range("sfl::segmented_vector::at");
        }

        const auto i = pos / N;
        const auto j = pos - i * N;

        return *(*(data_.seg_first_ + i) + j);
    }

    SFL_NODISCARD
    const_reference at(size_type pos) const
    {
        if (pos >= size())
        {
            SFL_DTL::throw_out_of_range("sfl::segmented_vector::at");
        }

        const auto i = pos / N;
        const auto j = pos - i * N;

        return *(*(data_.seg_first_ + i) + j);
    }

    SFL_NODISCARD
    reference operator[](size_type pos) noexcept
    {
        SFL_ASSERT(pos < size());

        const auto i = pos / N;
        const auto j = pos - i * N;

        return *(*(data_.seg_first_ + i) + j);
    }

    SFL_NODISCARD
    const_reference operator[](size_type pos) const noexcept
    {
        SFL_ASSERT(pos < size());

        const auto i = pos / N;
        const auto j = pos - i * N;

        return *(*(data_.seg_first_ + i) + j);
    }

    SFL_NODISCARD
    reference front() noexcept
    {
        SFL_ASSERT(!empty());
        return *data_.first_;
    }

    SFL_NODISCARD
    const_reference front() const noexcept
    {
        SFL_ASSERT(!empty());
        return *data_.first_;
    }

    SFL_NODISCARD
    reference back() noexcept
    {
        SFL_ASSERT(!empty());
        auto temp = data_.last_;
        --temp;
        return *temp;
    }

    SFL_NODISCARD
    const_reference back() const noexcept
    {
        SFL_ASSERT(!empty());
        auto temp = data_.last_;
        --temp;
        return *temp;
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
    iterator emplace(const_iterator pos, Args&&... args)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());

        iterator p(pos.seg_, pos.elem_);

        if (data_.last_ == data_.end_)
        {
            const size_type offset = pos - cbegin();

            grow_storage(1);

            p = nth(offset);
        }

        if (p == data_.last_)
        {
            SFL_DTL::construct_at
            (
                data_.ref_to_alloc(),
                data_.last_.elem_,
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

            value_type tmp(std::forward<Args>(args)...);

            SFL_DTL::construct_at
            (
                data_.ref_to_alloc(),
                data_.last_.elem_,
                std::move(*(data_.last_ - 1))
            );

            ++data_.last_;

            std::move_backward
            (
                p,
                data_.last_ - 2,
                data_.last_ - 1
            );

            *p = std::move(tmp);
        }

        return p;
    }

    iterator insert(const_iterator pos, const T& value)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return emplace(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type n, const T& value)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return insert_fill_n(pos, n, value);
    }

    template <typename InputIt,
        typename std::enable_if
        <
            SFL_DTL::is_input_iterator<InputIt>::value
        >::type* = nullptr
    >
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return insert_range
        (
            pos,
            first,
            last,
            typename std::iterator_traits<InputIt>::iterator_category()
        );
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        SFL_ASSERT(cbegin() <= pos && pos <= cend());
        return insert_range
        (
            pos,
            ilist.begin(),
            ilist.end(),
            std::random_access_iterator_tag()
        );
    }

    template <typename... Args>
    reference emplace_back(Args&&... args)
    {
        return *emplace(cend(), std::forward<Args>(args)...);
    }

    void push_back(const T& value)
    {
        emplace(cend(), value);
    }

    void push_back(T&& value)
    {
        emplace(cend(), std::move(value));
    }

    void pop_back()
    {
        SFL_ASSERT(!empty());

        --data_.last_;

        SFL_DTL::destroy_at(data_.ref_to_alloc(), data_.last_.elem_);
    }

    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());

        iterator p(pos.seg_, pos.elem_);

        if (p < data_.last_ - 1)
        {
            std::move(p + 1, data_.last_, p);
        }

        --data_.last_;

        SFL_DTL::destroy_at(data_.ref_to_alloc(), data_.last_.elem_);

        return p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        iterator p(first.seg_, first.elem_);

        if (first == last)
        {
            return p;
        }

        const difference_type n = std::distance(first, last);

        if (p + n < data_.last_)
        {
            std::move(p + n, data_.last_, p);
        }

        iterator new_last = data_.last_ - n;

        SFL_DTL::destroy(data_.ref_to_alloc(), new_last, data_.last_);

        data_.last_ = new_last;

        return p;
    }

    void resize(size_type n)
    {
        const size_type s = size();

        if (n > s)
        {
            const size_type delta = n - s;

            const size_type c = capacity();

            if (n > c)
            {
                grow_storage(n - c);
            }

            data_.last_ = SFL_DTL::uninitialized_default_construct_n
            (
                data_.ref_to_alloc(),
                data_.last_,
                delta
            );
        }
        else if (n < s)
        {
            iterator new_last = nth(n);

            SFL_DTL::destroy
            (
                data_.ref_to_alloc(),
                new_last,
                data_.last_
            );

            data_.last_ = new_last;
        }
    }

    void resize(size_type n, const T& value)
    {
        const size_type s = size();

        if (n > s)
        {
            const size_type delta = n - s;

            const size_type c = capacity();

            if (n > c)
            {
                grow_storage(n - c);
            }

            data_.last_ = SFL_DTL::uninitialized_fill_n
            (
                data_.ref_to_alloc(),
                data_.last_,
                delta,
                value
            );
        }
        else if (n < s)
        {
            iterator new_last = nth(n);

            SFL_DTL::destroy
            (
                data_.ref_to_alloc(),
                new_last,
                data_.last_
            );

            data_.last_ = new_last;
        }
    }

    void swap(segmented_vector& other) noexcept
    {
        SFL_ASSERT
        (
            allocator_traits::propagate_on_container_swap::value ||
            data_.ref_to_alloc() == other.data_.ref_to_alloc()
        );

        if (this == &other)
        {
            return;
        }

        using std::swap;

        if (allocator_traits::propagate_on_container_swap::value)
        {
            swap(data_.ref_to_alloc(), other.data_.ref_to_alloc());
        }

        swap(data_, other.data_);
    }

private:

    /// Alocates table for `n` segments.
    /// Does not allocate segments, it only allocates memory for table.
    /// Returns pointer to the table.
    ///
    segment_pointer allocate_table(size_type n)
    {
        segment_allocator seg_alloc(data_.ref_to_alloc());
        return SFL_DTL::allocate(seg_alloc, n);
    }

    /// Deallocates table at `p`.
    /// Does not deallocates segments, it only deallocates memory used by table.
    ///
    void deallocate_table(segment_pointer p, size_type n) noexcept
    {
        segment_allocator seg_alloc(data_.ref_to_alloc());
        SFL_DTL::deallocate(seg_alloc, p, n);
    }

    /// Allocates a segment and returns pointer to it.
    /// Does not construct elements, it only allocates memory for segment.
    ///
    pointer allocate_segment()
    {
        return SFL_DTL::allocate(data_.ref_to_alloc(), N);
    }

    /// Deallocates segments at `p`.
    /// Does not destroy elements, it only deallocates memory used by segment.
    ///
    void deallocate_segment(pointer p) noexcept
    {
        SFL_DTL::deallocate(data_.ref_to_alloc(), p, N);
    }

    /// Allocates segments in table in range [first, last).
    /// Does not construct elements, it only allocates memory for segments.
    ///
    void construct_segments(segment_pointer first, segment_pointer last)
    {
        segment_pointer curr = first;

        SFL_TRY
        {
            while (curr != last)
            {
                *curr = allocate_segment();
                ++curr;
            }
        }
        SFL_CATCH (...)
        {
            destroy_segments(first, curr);
            SFL_RETHROW;
        }
    }

    /// Destroys segments in table in range [first, last).
    /// Does not destroy elements, it only deallocates memory used by segments.
    ///
    void destroy_segments(segment_pointer first, segment_pointer last) noexcept
    {
        while (first != last)
        {
            deallocate_segment(*first);
            ++first;
        }
    }

    static constexpr size_type min_table_capacity() noexcept
    {
        return 8;
    }

    static constexpr double table_grow_factor() noexcept
    {
        return 1.5;
    }

    /// Allocates storage large enough for given number of elements.
    /// Does not construct elements, it only allocates memory.
    ///
    void construct_storage(size_type num_elements)
    {
        if (num_elements > max_size())
        {
            SFL_DTL::throw_length_error("sfl::segmented_vector::construct_storage");
        }

        const size_type num_segments = num_elements / N + 1;

        const size_type table_capacity = std::max
        (
            min_table_capacity(),
            num_segments
        );

        data_.seg_first_ = allocate_table(table_capacity);
        data_.seg_last_  = data_.seg_first_ + num_segments;
        data_.seg_end_   = data_.seg_first_ + table_capacity;

        SFL_TRY
        {
            construct_segments(data_.seg_first_, data_.seg_last_);

            data_.first_.seg_  = data_.seg_first_;
            data_.first_.elem_ = *data_.seg_first_;

            data_.last_ = data_.first_;

            data_.end_.seg_  = data_.seg_last_ - 1;
            data_.end_.elem_ = *(data_.seg_last_ - 1) + (N - 1);
        }
        SFL_CATCH (...)
        {
            deallocate_table(data_.seg_first_, table_capacity);
            SFL_RETHROW;
        }
    }

    /// Deallocates storage.
    /// Does not destroy elements, it only deallocates memory.
    ///
    void destroy_storage() noexcept
    {
        destroy_segments(data_.seg_first_, data_.seg_last_);
        deallocate_table(data_.seg_first_, data_.seg_end_ - data_.seg_first_);
    }

    /// Increases storage capacity for given number of elements.
    /// Does not construct elements, it only allocates additional memory.
    ///
    void grow_storage(size_type num_additional_elements)
    {
        if (max_size() - capacity() < num_additional_elements)
        {
            SFL_DTL::throw_length_error("sfl::segmented_vector::grow_storage");
        }

        const size_type num_additional_segments =
            num_additional_elements / N + 1;

        const size_type available_table_capacity =
            data_.seg_end_ - data_.seg_last_;

        // Grow table if neccessary.
        if (num_additional_segments > available_table_capacity)
        {
            const size_type table_capacity = data_.seg_end_ - data_.seg_first_;

            const size_type table_size = data_.seg_last_ - data_.seg_first_;

            const size_type new_table_capacity = std::max<size_type>
            (
                size_type(double(table_capacity) * table_grow_factor()),
                table_size + num_additional_segments
            );

            const size_type n = data_.last_.seg_ - data_.first_.seg_;
            const size_type m = data_.end_.seg_ - data_.first_.seg_;

            // Allocate new table. No effects if allocation fails.
            segment_pointer new_seg_first = allocate_table(new_table_capacity);
            segment_pointer new_seg_last  = new_seg_first;
            segment_pointer new_seg_end   = new_seg_first + new_table_capacity;

            // Copy pointers (noexcept).
            new_seg_last = std::copy
            (
                data_.seg_first_,
                data_.seg_last_,
                new_seg_first
            );

            // Deallocate old table (noexcept).
            deallocate_table(data_.seg_first_, table_capacity);

            // Update pointers (noexcept).
            data_.seg_first_ = new_seg_first;
            data_.seg_last_  = new_seg_last;
            data_.seg_end_   = new_seg_end;

            // Update iterators (noexcept).
            data_.first_.seg_ = new_seg_first;
            data_.last_.seg_ = new_seg_first + n;
            data_.end_.seg_ = new_seg_first + m;
        }

        auto new_seg_last = data_.seg_last_ + num_additional_segments;

        // No effects in allocation fails.
        construct_segments(data_.seg_last_, new_seg_last);

        data_.seg_last_ = new_seg_last;

        data_.end_.seg_  = data_.seg_last_ - 1;
        data_.end_.elem_ = *(data_.seg_last_ - 1) + (N - 1);
    }

    /// Removes unused capacity.
    ///
    void shrink_storage()
    {
        // Destroy empty segments.
        {
            auto new_seg_last = data_.last_.seg_ + 1;

            destroy_segments(new_seg_last, data_.seg_last_);

            data_.seg_last_ = new_seg_last;

            data_.end_.seg_  = data_.seg_last_ - 1;
            data_.end_.elem_ = *(data_.seg_last_ - 1) + (N - 1);
        }

        // Shrink table.
        {
            const size_type table_capacity = data_.seg_end_ - data_.seg_first_;

            const size_type table_size = data_.seg_last_ - data_.seg_first_;

            const size_type new_table_capacity = std::max
            (
                min_table_capacity(),
                table_size
            );

            const size_type n = data_.last_.seg_ - data_.first_.seg_;
            const size_type m = data_.end_.seg_ - data_.first_.seg_;

            // Allocate new table. No effects if allocation fails.
            segment_pointer new_seg_first = allocate_table(new_table_capacity);
            segment_pointer new_seg_last  = new_seg_first;
            segment_pointer new_seg_end   = new_seg_first + new_table_capacity;

            // Copy pointers (noexcept).
            new_seg_last = std::copy
            (
                data_.seg_first_,
                data_.seg_last_,
                new_seg_first
            );

            // Deallocate old table (noexcept).
            deallocate_table(data_.seg_first_, table_capacity);

            // Update pointers (noexcept).
            data_.seg_first_ = new_seg_first;
            data_.seg_last_  = new_seg_last;
            data_.seg_end_   = new_seg_end;

            // Update iterators (noexcept).
            data_.first_.seg_ = new_seg_first;
            data_.last_.seg_ = new_seg_first + n;
            data_.end_.seg_ = new_seg_first + m;
        }
    }

    void initialize_empty()
    {
        construct_storage(0);
    }

    void initialize_default_n(size_type n)
    {
        construct_storage(n);

        SFL_TRY
        {
            data_.last_ = SFL_DTL::uninitialized_default_construct_n
            (
                data_.ref_to_alloc(),
                data_.first_,
                n
            );
        }
        SFL_CATCH (...)
        {
            destroy_storage();
            SFL_RETHROW;
        }
    }

    void initialize_fill_n(size_type n, const T& value)
    {
        construct_storage(n);

        SFL_TRY
        {
            data_.last_ = SFL_DTL::uninitialized_fill_n
            (
                data_.ref_to_alloc(),
                data_.first_,
                n,
                value
            );
        }
        SFL_CATCH (...)
        {
            destroy_storage();
            SFL_RETHROW;
        }
    }

    template <typename InputIt>
    void initialize_range(InputIt first, InputIt last, std::input_iterator_tag)
    {
        construct_storage(0);

        SFL_TRY
        {
            while (first != last)
            {
                emplace_back(*first);
                ++first;
            }
        }
        SFL_CATCH (...)
        {
            clear();
            destroy_storage();
            SFL_RETHROW;
        }
    }

    template <typename ForwardIt>
    void initialize_range(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
    {
        construct_storage(std::distance(first, last));

        SFL_TRY
        {
            data_.last_ = SFL_DTL::uninitialized_copy
            (
                data_.ref_to_alloc(),
                first,
                last,
                data_.first_
            );
        }
        SFL_CATCH (...)
        {
            destroy_storage();
            SFL_RETHROW;
        }
    }

    void initialize_copy(const segmented_vector& other)
    {
        construct_storage(other.size());

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
            destroy_storage();
            SFL_RETHROW;
        }
    }

    void initialize_move(segmented_vector& other)
    {
        if (data_.ref_to_alloc() == other.data_.ref_to_alloc())
        {
            construct_storage(0);
            using std::swap;
            swap(data_, other.data_);
        }
        else
        {
            construct_storage(other.size());

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
                destroy_storage();
                SFL_RETHROW;
            }
        }
    }

    void assign_fill_n(size_type n, const T& value)
    {
        const size_type c = capacity();

        if (n > c)
        {
            grow_storage(n - c);
        }

        const size_type s = size();

        if (n <= s)
        {
            iterator new_last = std::fill_n
            (
                data_.first_,
                n,
                value
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
            std::fill_n
            (
                data_.first_,
                s,
                value
            );

            data_.last_ = SFL_DTL::uninitialized_fill_n
            (
                data_.ref_to_alloc(),
                data_.last_,
                n - s,
                value
            );
        }
    }

    template <typename InputIt>
    void assign_range(InputIt first, InputIt last, std::input_iterator_tag)
    {
        iterator curr = data_.first_;

        while (first != last && curr != data_.last_)
        {
            *curr = *first;
            ++curr;
            ++first;
        }

        if (first != last)
        {
            do
            {
                emplace_back(*first);
                ++first;
            }
            while (first != last);
        }
        else if (curr < data_.last_)
        {
            SFL_DTL::destroy(data_.ref_to_alloc(), curr, data_.last_);
            data_.last_ = curr;
        }
    }

    template <typename ForwardIt>
    void assign_range(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
    {
        const size_type n = std::distance(first, last);

        const size_type c = capacity();

        if (n > c)
        {
            grow_storage(n - c);
        }

        const size_type s = size();

        if (n <= s)
        {
            iterator new_last = std::copy
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

    void assign_copy(const segmented_vector& other)
    {
        if (this != &other)
        {
            if (allocator_traits::propagate_on_container_copy_assignment::value)
            {
                if (data_.ref_to_alloc() != other.data_.ref_to_alloc())
                {
                    // Create temporary vector using other allocator.
                    // There are no effects if allocation fails.
                    segmented_vector temp(other.data_.ref_to_alloc());

                    // Clear and destroy current storage (noexcept).
                    clear();
                    destroy_storage();

                    // Set pointers to null (noexcept).
                    data_.seg_first_ = nullptr;
                    data_.seg_last_  = nullptr;
                    data_.seg_end_   = nullptr;

                    // Swap storage of this and temporary vector (noexcept).
                    using std::swap;
                    swap(data_, temp.data_);

                    // Temporary vector has no allocated storage (pointers
                    // are set to null) so destructor of temporary vector
                    // has nothing to do.
                }

                // Propagate allocator (noexcept).
                data_.ref_to_alloc() = other.data_.ref_to_alloc();
            }

            assign_range
            (
                other.data_.first_,
                other.data_.last_,
                std::random_access_iterator_tag()
            );
        }
    }

    void assign_move(segmented_vector& other)
    {
        using std::swap;

        if (data_.ref_to_alloc() == other.data_.ref_to_alloc())
        {
            // Create temporary container using allocator of "this".
            // There are no effects if allocation fails.
            // NOTE: We could also use allocator of "other". There are no
            // difference since both allocators compare equal.
            segmented_vector temp(data_.ref_to_alloc());

            // Clear storage of "this" (noexcept).
            clear();

            // Destroy storage of "this" (noexcept).
            // NOTE: This does not set pointers to null.
            destroy_storage();

            // Set pointers of "this" to null pointers (noexcept).
            data_.seg_first_ = nullptr;
            data_.seg_last_  = nullptr;
            data_.seg_end_   = nullptr;

            // Current state:
            //  - "this" has no allocated storage (pointers are null).

            // Swap storage of "this" and "other" (noexcept)
            swap(data_, other.data_);

            // After swap:
            //  - "this" owns storage previously owned by "other".
            //  - "other" has no allocated storage (pointers are null).

            // Swap storage of "other" and "temp" (noexcept)
            swap(other.data_, temp.data_);

            // After swap:
            //  - "other" owns storage previously owned by "temp".
            //  - "temp" has no allocated storage (pointers are null).
            //    This is OK in this case. Destructor of "temp" has
            //    nothing to do.

            if (allocator_traits::propagate_on_container_move_assignment::value)
            {
                // Propagate allocator (noexcept).
                data_.ref_to_alloc() = std::move(other.data_.ref_to_alloc());
            }
        }
        else if (allocator_traits::propagate_on_container_move_assignment::value)
        {
            // Create temporary container using allocator of "other".
            // There are no effects if allocation fails.
            segmented_vector temp(other.data_.ref_to_alloc());

            // Clear storage of "this" (noexcept).
            clear();

            // Destroy storage of "this" (noexcept).
            // NOTE: This does not set pointers to null.
            destroy_storage();

            // Set pointers of "this" to null pointers (noexcept).
            data_.seg_first_ = nullptr;
            data_.seg_last_  = nullptr;
            data_.seg_end_   = nullptr;

            // Current state:
            //  - "this" has no allocated storage (pointers are null).

            // Swap storage of "this" and "temp" (noexcept)
            swap(data_, temp.data_);

            // After swap:
            //  - "this" owns storage previously owned by "temp".
            //    That storage was allocated by allocator of "temp"
            //    (i.e. copy of allocator of "other").
            //    "this" cannot deallocate that storage because allocators
            //    of "this" and "other" does not compare equal.
            //  - "temp" has no allocated storage (pointers are null).
            //    This is OK in this case. Destructor of "temp" has
            //    nothing to do.

            // Propagate allocator (noexcept).
            data_.ref_to_alloc() = std::move(other.data_.ref_to_alloc());

            // After propagation:
            //  - "this" owns storage previously owned by "temp", but now
            //    "this" can deallocate that storage.

            // Move elements one-by-one from "other" to "this" (can throw)
            assign_range
            (
                std::make_move_iterator(other.data_.first_),
                std::make_move_iterator(other.data_.last_),
                std::random_access_iterator_tag()
            );
        }
        else
        {
            // Move elements one-by-one from "other" to "this" (can throw)
            assign_range
            (
                std::make_move_iterator(other.data_.first_),
                std::make_move_iterator(other.data_.last_),
                std::random_access_iterator_tag()
            );
        }
    }

    iterator insert_fill_n(const_iterator pos, size_type n, const T& value)
    {
        iterator p(pos.seg_, pos.elem_);

        if (n == 0)
        {
            return p;
        }

        const size_type available = data_.end_ - data_.last_;

        if (n > available)
        {
            const size_type offset = pos - cbegin();

            grow_storage(n - available);

            p = nth(offset);
        }

        // The order of operations is critical. First we will construct
        // temporary value because `value` can be a reference to element
        // in this container and after that we will move elements and
        // insert new element.

        value_type tmp(value);

        const size_type num_elems_after = data_.last_ - p;

        if (num_elems_after > n)
        {
            iterator old_last = data_.last_;

            data_.last_ = SFL_DTL::uninitialized_move
            (
                data_.ref_to_alloc(),
                data_.last_ - n,
                data_.last_,
                data_.last_
            );

            std::move_backward
            (
                p,
                old_last - n,
                old_last
            );

            std::fill_n
            (
                p,
                n,
                tmp
            );
        }
        else
        {
            iterator old_last = data_.last_;

            data_.last_ = SFL_DTL::uninitialized_fill_n
            (
                data_.ref_to_alloc(),
                data_.last_,
                n - num_elems_after,
                tmp
            );

            data_.last_ = SFL_DTL::uninitialized_move
            (
                data_.ref_to_alloc(),
                p,
                old_last,
                data_.last_
            );

            std::fill
            (
                p,
                old_last,
                tmp
            );
        }

        return p;
    }

    template <typename InputIt>
    iterator insert_range(const_iterator pos, InputIt first, InputIt last,
                          std::input_iterator_tag)
    {
        const size_type offset = pos - cbegin();

        while (first != last)
        {
            pos = insert(pos, *first);
            ++pos;
            ++first;
        }

        return nth(offset);
    }

    template <typename ForwardIt>
    iterator insert_range(const_iterator pos, ForwardIt first, ForwardIt last,
                          std::forward_iterator_tag)
    {
        iterator p(pos.seg_, pos.elem_);

        if (first == last)
        {
            return p;
        }

        const size_type n = std::distance(first, last);

        const size_type available = data_.end_ - data_.last_;

        if (n > available)
        {
            const size_type offset = pos - cbegin();

            grow_storage(n - available);

            p = nth(offset);
        }

        const size_type num_elems_after = data_.last_ - p;

        if (num_elems_after > n)
        {
            iterator old_last = data_.last_;

            data_.last_ = SFL_DTL::uninitialized_move
            (
                data_.ref_to_alloc(),
                data_.last_ - n,
                data_.last_,
                data_.last_
            );

            std::move_backward
            (
                p,
                old_last - n,
                old_last
            );

            std::copy
            (
                first,
                last,
                p
            );
        }
        else
        {
            iterator old_last = data_.last_;

            ForwardIt mid = std::next(first, num_elems_after);

            data_.last_ = SFL_DTL::uninitialized_copy
            (
                data_.ref_to_alloc(),
                mid,
                last,
                data_.last_
            );

            data_.last_ = SFL_DTL::uninitialized_move
            (
                data_.ref_to_alloc(),
                p,
                old_last,
                data_.last_
            );

            std::copy
            (
                first,
                mid,
                p
            );
        }

        return p;
    }
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator==
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator!=
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return !(x == y);
}

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator<
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator>
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return y < x;
}

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator<=
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return !(y < x);
}

template <typename T, std::size_t N, typename A>
SFL_NODISCARD
bool operator>=
(
    const segmented_vector<T, N, A>& x,
    const segmented_vector<T, N, A>& y
)
{
    return !(x < y);
}

template <typename T, std::size_t N, typename A>
void swap
(
    segmented_vector<T, N, A>& x,
    segmented_vector<T, N, A>& y
)
{
    x.swap(y);
}

template <typename T, std::size_t N, typename A, typename U>
typename segmented_vector<T, N, A>::size_type
    erase(segmented_vector<T, N, A>& c, const U& value)
{
    auto it = std::remove(c.begin(), c.end(), value);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
}

template <typename T, std::size_t N, typename A, typename Predicate>
typename segmented_vector<T, N, A>::size_type
    erase_if(segmented_vector<T, N, A>& c, Predicate pred)
{
    auto it = std::remove_if(c.begin(), c.end(), pred);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
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

#endif // SFL_SEGMENTED_VECTOR_HPP

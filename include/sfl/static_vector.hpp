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

#ifndef SFL_STATIC_VECTOR_HPP_INCLUDED
#define SFL_STATIC_VECTOR_HPP_INCLUDED

#include "private.hpp"

#include <algorithm>        // copy, move, swap, swap_ranges
#include <cstddef>          // size_t
#include <initializer_list> // initializer_list
#include <iterator>         // distance, next, reverse_iterator
#include <limits>           // numeric_limits
#include <memory>           // allocator, allocator_traits, pointer_traits
#include <type_traits>      // is_same, is_nothrow_xxxxx
#include <utility>          // forward, move, pair

namespace sfl
{

template <typename T, std::size_t N>
class static_vector
{
    static_assert(N > 0, "N must be greater than zero.");

public:

    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:

    struct data
    {
        union
        {
            unsigned char dummy_;
            value_type first_[N];
        };

        size_type size_;

        data() noexcept : size_(0)
        {}

        data(size_type size) noexcept : size_(size)
        {}

        ~data() noexcept
        {}
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_vector() noexcept
        : data_(0)
    {}

    static_vector(size_type n)
        : data_(n)
    {
        SFL_ASSERT(n <= capacity());
        sfl::dtl::uninitialized_default_construct_n(data_.first_, n);
    }

    static_vector(size_type n, const T& value)
        : data_(n)
    {
        SFL_ASSERT(n <= capacity());
        sfl::dtl::uninitialized_fill_n(data_.first_, n, value);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_exactly_input_iterator<InputIt>::value>* = nullptr>
    static_vector(InputIt first, InputIt last)
        : data_(0)
    {
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
            sfl::dtl::destroy_n(data_.first_, data_.size_);
            SFL_RETHROW;
        }
    }

    template <typename ForwardIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_forward_iterator<ForwardIt>::value>* = nullptr>
    static_vector(ForwardIt first, ForwardIt last)
        : data_(std::distance(first, last))
    {
        SFL_ASSERT(size_type(std::distance(first, last)) <= capacity());
        sfl::dtl::uninitialized_copy(first, last, data_.first_);
    }

    static_vector(std::initializer_list<T> ilist)
        : static_vector(ilist.begin(), ilist.end())
    {}

    static_vector(const static_vector& other)
        : data_(other.data_.size_)
    {
        sfl::dtl::uninitialized_copy_n(other.data_.first_, other.data_.size_, this->data_.first_);
    }

    static_vector(static_vector&& other)
        : data_(other.data_.size_)
    {
        sfl::dtl::uninitialized_move_n(other.data_.first_, other.data_.size_, this->data_.first_);
    }

    ~static_vector() noexcept
    {
        sfl::dtl::destroy_n(data_.first_, data_.size_);
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    void assign(size_type n, const T& value)
    {
        SFL_ASSERT(n <= capacity());

        if (n <= data_.size_)
        {
            sfl::dtl::destroy
            (
                sfl::dtl::fill_n(data_.first_, n, value),
                data_.first_ + data_.size_
            );
        }
        else
        {
            sfl::dtl::uninitialized_fill
            (
                sfl::dtl::fill_n(data_.first_, data_.size_, value),
                data_.first_ + n,
                value
            );
        }

        data_.size_ = n;
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_exactly_input_iterator<InputIt>::value>* = nullptr>
    void assign(InputIt first, InputIt last)
    {
        pointer ptr = data_.first_;
        pointer end = data_.first_ + data_.size_;

        while (first != last && ptr != end)
        {
            *ptr = *first;
            ++ptr;
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
        else if (ptr < end)
        {
            sfl::dtl::destroy(ptr, end);
            data_.size_ = std::distance(data_.first_, ptr);
        }
    }

    template <typename ForwardIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_forward_iterator<ForwardIt>::value>* = nullptr>
    void assign(ForwardIt first, ForwardIt last)
    {
        SFL_ASSERT(size_type(std::distance(first, last)) <= capacity());

        const size_type n = std::distance(first, last);

        if (n <= data_.size_)
        {
            sfl::dtl::destroy
            (
                sfl::dtl::copy(first, last, data_.first_),
                data_.first_ + data_.size_
            );
        }
        else
        {
            const auto mid = std::next(first, data_.size_);
            sfl::dtl::uninitialized_copy
            (
                mid,
                last,
                sfl::dtl::copy(first, mid, data_.first_)
            );
        }

        data_.size_ = n;
    }

    void assign(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
    }

    static_vector& operator=(const static_vector& other)
    {
        if (this != &other)
        {
            assign(other.begin(), other.end());
        }
        return *this;
    }

    static_vector& operator=(static_vector&& other)
    {
        assign
        (
            std::make_move_iterator(other.begin()),
            std::make_move_iterator(other.end())
        );
        return *this;
    }

    static_vector& operator=(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
        return *this;
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
        return data_.first_ + data_.size_;
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return data_.first_ + data_.size_;
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return data_.first_ + data_.size_;
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
        return data_.size_ == 0;
    }

    SFL_NODISCARD
    bool full() const noexcept
    {
        return data_.size_ == N;
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return data_.size_;
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return N;
    }

    SFL_NODISCARD
    size_type capacity() const noexcept
    {
        return N;
    }

    SFL_NODISCARD
    size_type available() const noexcept
    {
        return N - data_.size_;
    }

    //
    // ---- ELEMENT ACCESS ----------------------------------------------------
    //

    SFL_NODISCARD
    reference at(size_type pos)
    {
        if (pos >= size())
        {
            sfl::dtl::throw_out_of_range("sfl::static_vector::at");
        }

        return *(data_.first_ + pos);
    }

    SFL_NODISCARD
    const_reference at(size_type pos) const
    {
        if (pos >= size())
        {
            sfl::dtl::throw_out_of_range("sfl::static_vector::at");
        }

        return *(data_.first_ + pos);
    }

    SFL_NODISCARD
    reference operator[](size_type pos) noexcept
    {
        SFL_ASSERT(pos < size());
        return *(data_.first_ + pos);
    }

    SFL_NODISCARD
    const_reference operator[](size_type pos) const noexcept
    {
        SFL_ASSERT(pos < size());
        return *(data_.first_ + pos);
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
        return *(data_.first_ + data_.size_ - 1);
    }

    SFL_NODISCARD
    const_reference back() const noexcept
    {
        SFL_ASSERT(!empty());
        return *(data_.first_ + data_.size_ - 1);
    }

    SFL_NODISCARD
    T* data() noexcept
    {
        return data_.first_;
    }

    SFL_NODISCARD
    const T* data() const noexcept
    {
        return data_.first_;
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear() noexcept
    {
        sfl::dtl::destroy_n(data_.first_, data_.size_);
        data_.size_ = 0;
    }

    template <typename... Args>
    iterator emplace(const_pointer pos, Args&&... args)
    {
        SFL_ASSERT(!full());
        SFL_ASSERT(cbegin() <= pos && pos <= cend());

        const pointer p1 = data_.first_ + std::distance(cbegin(), pos);

        if (p1 == end())
        {
            sfl::dtl::construct_at(p1, std::forward<Args>(args)...);

            ++data_.size_;
        }
        else
        {
            const pointer p3 = data_.first_ + data_.size_;
            const pointer p2 = p3 - 1;

            // The order of operations is critical. First we will construct
            // temporary value because arguments `args...` can contain
            // reference to element in this container and after that
            // we will move elements and insert new element.

            value_type tmp(std::forward<Args>(args)...);

            sfl::dtl::construct_at(p3, std::move(*p2));

            ++data_.size_;

            sfl::dtl::move_backward(p1, p2, p3);

            *p1 = std::move(tmp);
        }

        return p1;
    }

    iterator insert(const_iterator pos, const T& value)
    {
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value)
    {
        return emplace(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type n, const T& value)
    {
        SFL_ASSERT(n <= available());
        SFL_ASSERT(cbegin() <= pos && pos <= cend());

        const difference_type offset = std::distance(cbegin(), pos);

        if (n != 0)
        {
            // `value` can be a reference to an element in this container.
            // First we will create temporary value and after that we can
            // safely move elements.

            value_type tmp(value);

            if (n > data_.size_ - offset)
            {
                // |<----------size----------->|
                // |                           |
                // |<-----offset----->|<--n1-->|<---------n2--------->|
                // |                  |        |                      |
                // [.........data..............]                      |
                //                    [...........to insert...........]
                //                    |                               |
                //                    |<--------------n-------------->|

                const size_type n1 = data_.size_ - offset;
                const size_type n2 = n - n1;

                sfl::dtl::uninitialized_fill_n
                (
                    data_.first_ + data_.size_,
                    n2,
                    tmp
                );

                data_.size_ += n2;

                sfl::dtl::uninitialized_move_n
                (
                    data_.first_ + offset,
                    n1,
                    data_.first_ + data_.size_
                );

                data_.size_ += n1;

                sfl::dtl::fill_n
                (
                    data_.first_ + offset,
                    n1,
                    tmp
                );
            }
            else
            {
                // |<----------------------size--------------------->|
                // |                                                 |
                // |<--offset-->|<--------n1-------->|<----n2=n----->|
                // |            |                    |               |
                // [.......................data......................]
                //              [...to insert...]
                //              |               |
                //              |<------n------>|

                const size_type n1 = data_.size_ - offset - n;
                const size_type n2 = n;

                sfl::dtl::uninitialized_move_n
                (
                    data_.first_ + data_.size_ - n2,
                    n2,
                    data_.first_ + data_.size_
                );

                data_.size_ += n2;

                sfl::dtl::move_backward
                (
                    data_.first_ + offset,
                    data_.first_ + offset + n1,
                    data_.first_ + offset + n1 + n2
                );

                sfl::dtl::fill_n
                (
                    data_.first_ + offset,
                    n,
                    tmp
                );
            }
        }

        return begin() + offset;
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_exactly_input_iterator<InputIt>::value>* = nullptr>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        const difference_type offset = std::distance(cbegin(), pos);

        while (first != last)
        {
            pos = emplace(pos, *first);
            ++pos;
            ++first;
        }

        return begin() + offset;
    }

    template <typename ForwardIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_forward_iterator<ForwardIt>::value>* = nullptr>
    iterator insert(const_iterator pos, ForwardIt first, ForwardIt last)
    {
        SFL_ASSERT(size_type(std::distance(first, last)) <= available());
        SFL_ASSERT(cbegin() <= pos && pos <= cend());

        const difference_type offset = std::distance(cbegin(), pos);

        if (first != last)
        {
            const size_type n = std::distance(first, last);

            if (n != 0)
            {
                if (n > data_.size_ - offset)
                {
                    // |<----------size----------->|
                    // |                           |
                    // |<-----offset----->|<--n1-->|<---------n2--------->|
                    // |                  |        |                      |
                    // [.........data..............]                      |
                    //                    [...........to insert...........]
                    //                    |                               |
                    //                    |<--------------n-------------->|

                    const size_type n1 = data_.size_ - offset;
                    const size_type n2 = n - n1;

                    sfl::dtl::uninitialized_copy_n
                    (
                        first + n1,
                        n2,
                        data_.first_ + data_.size_
                    );

                    data_.size_ += n2;

                    sfl::dtl::uninitialized_move_n
                    (
                        data_.first_ + offset,
                        n1,
                        data_.first_ + data_.size_
                    );

                    data_.size_ += n1;

                    sfl::dtl::copy_n
                    (
                        first,
                        n1,
                        data_.first_ + offset
                    );
                }
                else
                {
                    // |<----------------------size--------------------->|
                    // |                                                 |
                    // |<--offset-->|<--------n1-------->|<----n2=n----->|
                    // |            |                    |               |
                    // [.......................data......................]
                    //              [...to insert...]
                    //              |               |
                    //              |<------n------>|

                    const size_type n1 = data_.size_ - offset - n;
                    const size_type n2 = n;

                    sfl::dtl::uninitialized_move_n
                    (
                        data_.first_ + data_.size_ - n2,
                        n2,
                        data_.first_ + data_.size_
                    );

                    data_.size_ += n2;

                    sfl::dtl::move_backward
                    (
                        data_.first_ + offset,
                        data_.first_ + offset + n1,
                        data_.first_ + offset + n1 + n2
                    );

                    sfl::dtl::copy
                    (
                        first,
                        last,
                        data_.first_ + offset
                    );
                }
            }
        }

        return begin() + offset;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template <typename... Args>
    reference emplace_back(Args&&... args)
    {
        SFL_ASSERT(!full());

        const pointer p = data_.first_ + data_.size_;

        sfl::dtl::construct_at(p, std::forward<Args>(args)...);

        ++data_.size_;

        return *p;
    }

    void push_back(const T& value)
    {
        emplace_back(value);
    }

    void push_back(T&& value)
    {
        emplace_back(std::move(value));
    }

    void pop_back()
    {
        SFL_ASSERT(!empty());
        --data_.size_;
        sfl::dtl::destroy_at(data_.first_ + data_.size_);
    }

    iterator erase(const_iterator pos)
    {
        SFL_ASSERT(cbegin() <= pos && pos < cend());

        const pointer p1 = data_.first_ + std::distance(cbegin(), pos);
        const pointer p2 = p1 + 1;

        sfl::dtl::move(p2, data_.first_ + data_.size_, p1);

        --data_.size_;

        sfl::dtl::destroy_at(data_.first_ + data_.size_);

        return p1;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        SFL_ASSERT(cbegin() <= first && first <= last && last <= cend());

        if (first == last)
        {
            return begin() + std::distance(cbegin(), first);
        }

        const difference_type n = std::distance(first, last);

        const pointer p1 = data_.first_ + std::distance(cbegin(), first);
        const pointer p2 = p1 + n;

        sfl::dtl::move(p2, data_.first_ + data_.size_, p1);

        data_.size_ -= n;

        sfl::dtl::destroy_n(data_.first_ + data_.size_, n);

        return p1;
    }

    void resize(size_type n)
    {
        SFL_ASSERT(n <= capacity());

        if (n <= data_.size_)
        {
            sfl::dtl::destroy
            (
                data_.first_ + n,
                data_.first_ + data_.size_
            );
        }
        else
        {
            sfl::dtl::uninitialized_default_construct
            (
                data_.first_ + data_.size_,
                data_.first_ + n
            );
        }

        data_.size_ = n;
    }

    void resize(size_type n, const T& value)
    {
        SFL_ASSERT(n <= capacity());

        if (n <= data_.size_)
        {
            sfl::dtl::destroy
            (
                data_.first_ + n,
                data_.first_ + data_.size_
            );
        }
        else
        {
            sfl::dtl::uninitialized_fill
            (
                data_.first_ + data_.size_,
                data_.first_ + n,
                value
            );
        }

        data_.size_ = n;
    }

    void swap(static_vector& other)
    {
        if (this == &other)
        {
            return;
        }

        if (this->data_.size_ <= other.data_.size_)
        {
            std::swap_ranges
            (
                this->data_.first_,
                this->data_.first_ + this->data_.size_,
                other.data_.first_
            );

            sfl::dtl::uninitialized_move_n
            (
                other.data_.first_ + this->data_.size_,
                other.data_.size_ - this->data_.size_,
                this->data_.first_ + this->data_.size_
            );

            sfl::dtl::destroy
            (
                other.data_.first_ + this->data_.size_,
                other.data_.first_ + other.data_.size_
            );
        }
        else
        {
            std::swap_ranges
            (
                this->data_.first_,
                this->data_.first_ + other.data_.size_,
                other.data_.first_
            );

            sfl::dtl::uninitialized_move_n
            (
                this->data_.first_ + other.data_.size_,
                this->data_.size_ - other.data_.size_,
                other.data_.first_ + other.data_.size_
            );

            sfl::dtl::destroy
            (
                this->data_.first_ + other.data_.size_,
                this->data_.first_ + this->data_.size_
            );
        }

        std::swap(this->data_.size_, other.data_.size_);
    }
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator==
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator!=
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return !(x == y);
}

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator<
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator>
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return y < x;
}

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator<=
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return !(y < x);
}

template <typename T, std::size_t N>
SFL_NODISCARD
bool operator>=
(
    const static_vector<T, N>& x,
    const static_vector<T, N>& y
)
{
    return !(x < y);
}

template <typename T, std::size_t N>
void swap
(
    static_vector<T, N>& x,
    static_vector<T, N>& y
)
{
    x.swap(y);
}

template <typename T, std::size_t N, typename U>
typename static_vector<T, N>::size_type
    erase(static_vector<T, N>& c, const U& value)
{
    auto it = std::remove(c.begin(), c.end(), value);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
}

template <typename T, std::size_t N, typename Predicate>
typename static_vector<T, N>::size_type
    erase_if(static_vector<T, N>& c, Predicate pred)
{
    auto it = std::remove_if(c.begin(), c.end(), pred);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
}

} // namespace sfl

#endif // SFL_STATIC_VECTOR_HPP_INCLUDED

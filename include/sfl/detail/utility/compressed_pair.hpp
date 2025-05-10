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

#ifndef SFL_DETAIL_COMPRESSED_PAIR_HPP_INCLUDED
#define SFL_DETAIL_COMPRESSED_PAIR_HPP_INCLUDED

#include <type_traits>  // is_empty
#include <utility>      // forward, move, swap

namespace sfl
{

namespace dtl
{

struct compressed_pair_default_init_t {};

template <typename T, int Index, bool = std::is_empty<T>::value>
class compressed_pair_element
{
private:

    T value_;

public:

    compressed_pair_element(sfl::dtl::compressed_pair_default_init_t)
    {}

    template <typename U>
    compressed_pair_element(U&& arg)
        : value_(std::forward<U>(arg))
    {}

    T& get()
    {
        return value_;
    }

    const T& get() const
    {
        return value_;
    }
};

template <typename T, int Index>
class compressed_pair_element<T, Index, true>
    : private T
{
public:

    compressed_pair_element(sfl::dtl::compressed_pair_default_init_t)
    {}

    template <typename U>
    compressed_pair_element(U&& arg)
        : T(std::forward<U>(arg))
    {}

    T& get()
    {
        return *this;
    }

    const T& get() const
    {
        return *this;
    }
};

template <typename T1, typename T2>
class compressed_pair
    : private sfl::dtl::compressed_pair_element<T1, 0>
    , private sfl::dtl::compressed_pair_element<T2, 1>
{
private:

    using base1 = sfl::dtl::compressed_pair_element<T1, 0>;
    using base2 = sfl::dtl::compressed_pair_element<T2, 1>;

public:

    using first_type = T1;
    using second_type = T2;

public:

    template <typename U1, typename U2>
    compressed_pair(U1&& first, U2&& second)
        : base1(std::forward<U1>(first))
        , base2(std::forward<U2>(second))
    {}

    first_type& first()
    {
        return static_cast<base1*>(this)->get();
    }

    const first_type& first() const
    {
        return static_cast<const base1*>(this)->get();
    }

    second_type& second()
    {
        return static_cast<base2*>(this)->get();
    }

    const second_type& second() const
    {
        return static_cast<const base2*>(this)->get();
    }

    void swap(compressed_pair& other)
    {
        using std::swap;
        swap(first(), other.first());
        swap(second(), other.second());
    }
};

template <typename T1, typename T2>
void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
    x.swap(y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_COMPRESSED_PAIR_HPP_INCLUDED

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

#ifndef SFL_DETAIL_FILL_HPP_INCLUDED
#define SFL_DETAIL_FILL_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_segmented_iterator.hpp>
#include <sfl/detail/type_traits/segmented_iterator_traits.hpp>

#include <algorithm> // fill

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_FILL_HPP_INCLUDED

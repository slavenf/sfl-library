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

#ifndef SFL_DETAIL_MOVE_HPP_INCLUDED
#define SFL_DETAIL_MOVE_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_random_access_iterator.hpp>
#include <sfl/detail/type_traits/is_segmented_iterator.hpp>
#include <sfl/detail/type_traits/segmented_iterator_traits.hpp>

#include <algorithm> // move, min
#include <iterator>  // iterator_traits, distance

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_MOVE_HPP_INCLUDED

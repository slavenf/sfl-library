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

#ifndef SFL_DETAIL_UNINITIALIZED_FILL_A_HPP_INCLUDED
#define SFL_DETAIL_UNINITIALIZED_FILL_A_HPP_INCLUDED

#include <sfl/detail/memory/construct_at_a.hpp>
#include <sfl/detail/memory/destroy_a.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_segmented_iterator.hpp>
#include <sfl/detail/type_traits/segmented_iterator_traits.hpp>
#include <sfl/detail/cpp.hpp>

#include <memory> // addressof

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_UNINITIALIZED_FILL_A_HPP_INCLUDED

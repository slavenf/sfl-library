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

#ifndef SFL_DETAIL_UNINITIALIZED_FILL_N_A_HPP_INCLUDED
#define SFL_DETAIL_UNINITIALIZED_FILL_N_A_HPP_INCLUDED

#include <sfl/detail/memory/construct_at_a.hpp>
#include <sfl/detail/memory/destroy_a.hpp>
#include <sfl/detail/memory/destroy_n_a.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_segmented_iterator.hpp>
#include <sfl/detail/type_traits/segmented_iterator_traits.hpp>
#include <sfl/detail/cpp.hpp>

#include <algorithm> // min
#include <iterator>  // iterator_traits, distance
#include <memory>    // addressof

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_UNINITIALIZED_FILL_N_A_HPP_INCLUDED

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

#ifndef SFL_DETAIL_UNINITIALIZED_MEMORY_ALGORITHMS_HPP_INCLUDED
#define SFL_DETAIL_UNINITIALIZED_MEMORY_ALGORITHMS_HPP_INCLUDED

#include <sfl/detail/memory/construct_at.hpp>
#include <sfl/detail/memory/construct_at_a.hpp>
#include <sfl/detail/memory/default_construct_at.hpp>
#include <sfl/detail/memory/destroy_a.hpp>
#include <sfl/detail/memory/destroy_at.hpp>
#include <sfl/detail/memory/destroy_at_a.hpp>
#include <sfl/detail/memory/destroy_n_a.hpp>
#include <sfl/detail/memory/value_construct_at.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_random_access_iterator.hpp>
#include <sfl/detail/type_traits/is_segmented_iterator.hpp>
#include <sfl/detail/type_traits/segmented_iterator_traits.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/to_address.hpp>

#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_UNINITIALIZED_MEMORY_ALGORITHMS_HPP_INCLUDED

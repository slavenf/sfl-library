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

#ifndef SFL_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP_INCLUDED
#define SFL_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP_INCLUDED

#include <sfl/detail/memory/destroy.hpp>
#include <sfl/detail/memory/value_construct_at.hpp>
#include <sfl/detail/cpp.hpp>

#include <memory> // addressof

namespace sfl
{

namespace dtl
{

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

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP_INCLUDED

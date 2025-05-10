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

#ifndef SFL_DETAIL_BIT_LOG2_HPP_INCLUDED
#define SFL_DETAIL_BIT_LOG2_HPP_INCLUDED

#include <sfl/detail/bit/bit_width.hpp>
#include <sfl/detail/type_traits/is_unsigned_integer.hpp>

#include <type_traits>  // enable_if

namespace sfl
{

namespace dtl
{

template <typename T,
          typename std::enable_if<sfl::dtl::is_unsigned_integer<T>::value>::type* = nullptr>
constexpr int bit_log2(T x)
{
    return sfl::dtl::bit_width(x) - 1;
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_BIT_LOG2_HPP_INCLUDED

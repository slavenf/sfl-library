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

#ifndef SFL_DETAIL_CEIL_HPP_INCLUDED
#define SFL_DETAIL_CEIL_HPP_INCLUDED

#include <sfl/detail/cpp.hpp>

#include <cmath> // ceil
#include <type_traits> // enable_if, is_floating_point

namespace sfl
{

namespace dtl
{

template <typename T,
          typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
SFL_CONSTEXPR_20
T ceil(T num)
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    if (std::is_constant_evaluated())
    {
        return (static_cast<T>(static_cast<long long>(num)) == num)
            ? static_cast<T>(static_cast<long long>(num))
            : static_cast<T>(static_cast<long long>(num) + ((num > 0) ? 1 : 0));
    }
    else
    #endif
    {
        return std::ceil(num);
    }
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_CEIL_HPP_INCLUDED

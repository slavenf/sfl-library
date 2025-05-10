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

#ifndef SFL_DETAIL_FLOATING_POINT_TO_SIZE_T_HPP_INCLUDED
#define SFL_DETAIL_FLOATING_POINT_TO_SIZE_T_HPP_INCLUDED

#include <cstddef> // size_t
#include <limits>  // numeric_limits

namespace sfl
{

namespace dtl
{

constexpr std::size_t floating_point_to_size_t(float value)
{
    return value >= static_cast<float>(std::numeric_limits<std::size_t>::max())
        ? std::numeric_limits<std::size_t>::max()
        : static_cast<std::size_t>(value);
}

constexpr std::size_t floating_point_to_size_t(double value)
{
    return value >= static_cast<double>(std::numeric_limits<std::size_t>::max())
        ? std::numeric_limits<std::size_t>::max()
        : static_cast<std::size_t>(value);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_FLOATING_POINT_TO_SIZE_T_HPP_INCLUDED

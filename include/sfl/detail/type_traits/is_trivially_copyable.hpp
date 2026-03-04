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

#ifndef SFL_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED
#define SFL_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

#include <type_traits> // is_trivially_copyable, integral_constant

namespace sfl
{

namespace dtl
{

template <typename T>
struct is_trivially_copyable
    #if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ < 5)) || (defined(__clang__) && (__clang_major__ < 4))
    : std::integral_constant<bool, __has_trivial_copy(T)>
    #else
    : std::is_trivially_copyable<T>
    #endif
{};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

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

#ifndef SFL_DETAIL_IS_NOTHROW_SWAPPABLE_HPP_INCLUDED
#define SFL_DETAIL_IS_NOTHROW_SWAPPABLE_HPP_INCLUDED

#include <type_traits> // true_type, false_type
#include <utility>     // declval

namespace sfl
{

namespace dtl
{

namespace is_nothrow_swappable_aux
{

using std::swap;

template <typename T, bool B = noexcept(swap(std::declval<T&>(), std::declval<T&>()))>
static std::integral_constant<bool, B> test(int);

template <typename T>
static std::false_type test(...);

} // namespace is_nothrow_swappable_aux

template <typename T>
struct is_nothrow_swappable_impl
{
    using type = decltype(sfl::dtl::is_nothrow_swappable_aux::test<T>(0));
};

template <typename T>
struct is_nothrow_swappable : sfl::dtl::is_nothrow_swappable_impl<T>::type {};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_IS_NOTHROW_SWAPPABLE_HPP_INCLUDED

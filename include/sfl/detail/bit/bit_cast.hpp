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

#ifndef SFL_DETAIL_BIT_CAST_HPP_INCLUDED
#define SFL_DETAIL_BIT_CAST_HPP_INCLUDED

#include <sfl/detail/type_traits/is_trivially_copyable.hpp>
#include <sfl/detail/cpp.hpp>

#include <cstring> // memcpy

#if SFL_CPP_VERSION >= SFL_CPP_20
#include <bit> // bit_cast
#endif

namespace sfl
{

namespace dtl
{

template <typename To, typename From>
To bit_cast_impl_11(const From& src) noexcept
{
    static_assert(sizeof(To) == sizeof(From), "To and From must have the same size");
    static_assert(sfl::dtl::is_trivially_copyable<From>::value, "From must be trivially copyable");
    static_assert(sfl::dtl::is_trivially_copyable<To>::value, "To must be trivially copyable");

    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}

#if SFL_CPP_VERSION >= SFL_CPP_20

template <typename To, typename From>
constexpr To bit_cast_impl_20(const From& from) noexcept
{
    return std::bit_cast<To>(from);
}

#endif // SFL_CPP_VERSION >= SFL_CPP_20

template <typename To, typename From>
SFL_CONSTEXPR_20
To bit_cast(const From& from) noexcept
{
    #if SFL_CPP_VERSION >= SFL_CPP_20
    return sfl::dtl::bit_cast_impl_20<To>(from);
    #else
    return sfl::dtl::bit_cast_impl_11<To>(from);
    #endif
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_BIT_CAST_HPP_INCLUDED

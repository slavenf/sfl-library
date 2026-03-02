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

#ifndef SFL_HASH_HPP_INCLUDED
#define SFL_HASH_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/cpp.hpp>

#include <cstddef> // size_t
#include <cstdint> // uint32_t, uint64_t
#include <functional> // hash
#include <limits> // numeric_limits
#include <type_traits> // is_enum, is_integral, is_floating_point

#if SFL_CPP_VERSION >= SFL_CPP_20
#include <bit> // bit_cast
#endif

namespace sfl
{

namespace dtl
{

template <typename T, typename = void>
struct hash_impl : std::hash<T>
{
    using std::hash<T>::hash;
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_enum<T>::value>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        return static_cast<std::size_t>(value);
    }
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_integral<T>::value>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        return static_cast<std::size_t>(value);
    }
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_floating_point<T>::value && sizeof(T) == 4 && sizeof(std::size_t) == 4>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        // Canonicalize zeros
        if (value == static_cast<T>(0))
        {
            value = static_cast<T>(0);
        }

        // Canonicalize NaN
        if (value != value)
        {
            value = std::numeric_limits<T>::quiet_NaN();
        }

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return std::bit_cast<std::uint32_t>(value);
        }
        else
        #endif
        {
            union
            {
                T t;
                std::uint32_t a;
            } u;
            u.t = value;
            return u.a;
        }
    }
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_floating_point<T>::value && sizeof(T) == 4 && sizeof(std::size_t) == 8>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        // Canonicalize zeros
        if (value == static_cast<T>(0))
        {
            value = static_cast<T>(0);
        }

        // Canonicalize NaN
        if (value != value)
        {
            value = std::numeric_limits<T>::quiet_NaN();
        }

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return std::bit_cast<std::uint32_t>(value);
        }
        else
        #endif
        {
            union
            {
                T t;
                std::uint32_t a;
            } u;
            u.t = value;
            return u.a;
        }
    }
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_floating_point<T>::value && sizeof(T) == 8 && sizeof(std::size_t) == 4>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        // Canonicalize zeros
        if (value == static_cast<T>(0))
        {
            value = static_cast<T>(0);
        }

        // Canonicalize NaN
        if (value != value)
        {
            value = std::numeric_limits<T>::quiet_NaN();
        }

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            std::uint64_t bits = std::bit_cast<std::uint64_t>(value);
            std::size_t h1 = static_cast<std::size_t>(bits);
            std::size_t h2 = static_cast<std::size_t>(bits >> 32);
            return h1 ^ (h2 + 0x9e3779b9u + (h1 << 6) + (h1 >> 2));
        }
        else
        #endif
        {
            union
            {
                T t;
                std::uint64_t a;
            } u;
            u.t = value;
            std::size_t h1 = static_cast<std::size_t>(u.a);
            std::size_t h2 = static_cast<std::size_t>(u.a >> 32);
            return h1 ^ (h2 + 0x9e3779b9u + (h1 << 6) + (h1 >> 2));
        }
    }
};

template <typename T>
struct hash_impl<T, sfl::dtl::enable_if_t<std::is_floating_point<T>::value && sizeof(T) == 8 && sizeof(std::size_t) == 8>>
{
    SFL_CONSTEXPR_20
    std::size_t operator()(T value) const noexcept
    {
        // Canonicalize zeros
        if (value == static_cast<T>(0))
        {
            value = static_cast<T>(0);
        }

        // Canonicalize NaN
        if (value != value)
        {
            value = std::numeric_limits<T>::quiet_NaN();
        }

        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return std::bit_cast<std::uint64_t>(value);
        }
        else
        #endif
        {
            union
            {
                T t;
                std::uint64_t a;
            } u;
            u.t = value;
            return u.a;
        }
    }
};

} // namespace dtl

template <typename T>
struct hash : sfl::dtl::hash_impl<T>
{
    using sfl::dtl::hash_impl<T>::hash_impl;
};

} // namespace sfl

#endif // SFL_HASH_HPP_INCLUDED

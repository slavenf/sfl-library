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

#include <sfl/detail/cpp.hpp>

#include <cstddef> // size_t
#include <functional> // hash

#if SFL_CPP_VERSION >= SFL_CPP_20
#include <bit> // bit_cast
#include <type_traits> // is_constant_evaluated
#endif

namespace sfl
{

template <typename T>
struct hash : std::hash<T>
{
    using std::hash<T>::hash;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// HASH FOR INTEGRAL TYPES
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(T)            \
    template <>                                         \
    struct hash<T>                                      \
    {                                                   \
        SFL_CONSTEXPR_20                                \
        std::size_t operator()(T value) const noexcept  \
        {                                               \
            return static_cast<std::size_t>(value);     \
        }                                               \
    };

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(bool)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(char)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(signed char)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(unsigned char)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(wchar_t)

#if SFL_CPP_VERSION >= SFL_CPP_20
SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(char8_t)
#endif

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(char16_t)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(char32_t)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(short)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(unsigned short)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(int)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(unsigned int)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(long)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(unsigned long)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(long long)

SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE(unsigned long long)

#undef SFL_DEFINE_HASH_FOR_INTEGRAL_TYPE

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// HASH FOR FLOATING TYPES
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#if SFL_CPP_VERSION >= SFL_CPP_20

#define SFL_DEFINE_HASH_FOR_FLOATING_TYPE(T)                        \
    template <>                                                     \
    struct hash<T> : std::hash<T>                                   \
    {                                                               \
        constexpr std::size_t operator()(T value) const noexcept    \
        {                                                           \
            if (std::is_constant_evaluated())                       \
            {                                                       \
                if (value == static_cast<T>(0))                     \
                {                                                   \
                    return 0;                                       \
                }                                                   \
                                                                    \
                struct bytes_t                                      \
                {                                                   \
                    unsigned char data[sizeof(T)];                  \
                };                                                  \
                                                                    \
                auto bytes = std::bit_cast<bytes_t>(value);         \
                                                                    \
                std::size_t hash = 0;                               \
                                                                    \
                for (unsigned char byte : bytes.data)               \
                {                                                   \
                    hash ^= static_cast<std::size_t>(byte)          \
                            + 0x9e3779b9ul                          \
                            + (hash << 6)                           \
                            + (hash >> 2);                          \
                }                                                   \
                                                                    \
                return hash;                                        \
            }                                                       \
            else                                                    \
            {                                                       \
                return std::hash<T>::operator()(value);             \
            }                                                       \
        }                                                           \
    };

SFL_DEFINE_HASH_FOR_FLOATING_TYPE(float)

SFL_DEFINE_HASH_FOR_FLOATING_TYPE(double)

SFL_DEFINE_HASH_FOR_FLOATING_TYPE(long double)

#undef SFL_DEFINE_HASH_FOR_FLOATING_TYPE

#endif // SFL_CPP_VERSION >= SFL_CPP_20

} // namespace sfl

#endif // SFL_HASH_HPP_INCLUDED

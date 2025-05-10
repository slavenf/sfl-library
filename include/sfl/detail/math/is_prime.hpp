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

#ifndef SFL_DETAIL_IS_PRIME_HPP_INCLUDED
#define SFL_DETAIL_IS_PRIME_HPP_INCLUDED

#include <cstddef> // size_t
#include <limits>  // numeric_limits

namespace sfl
{

namespace dtl
{

namespace is_prime_impl
{

// Source: https://stackoverflow.com/a/18306693/18289298

constexpr std::size_t mid(std::size_t low, std::size_t high)
{
    return (low + high) / 2;
}

// precondition: low*low <= n, high*high > n.
constexpr std::size_t ceilsqrt(std::size_t n, std::size_t low, std::size_t high)
{
    return low + 1 >= high
        ? high
        : (mid(low, high) * mid(low, high) == n)
            ? mid(low, high)
            : (mid(low, high) * mid(low, high) < n)
                ? ceilsqrt(n, mid(low, high), high)
                : ceilsqrt(n, low, mid(low, high));
}

// returns ceiling(sqrt(n))
constexpr std::size_t ceilsqrt(std::size_t n)
{
    return n < 3
        ? n
        : ceilsqrt(n, 1, std::size_t(1) << (std::numeric_limits<std::size_t>::digits / 2));
}

// returns true if n is divisible by an odd integer in
// [2 * low + 1, 2 * high + 1).
constexpr bool find_factor(std::size_t n, std::size_t low, std::size_t high)
{
    return low + 1 >= high
        ? (n % (2 * low + 1)) == 0
        : (find_factor(n, low, mid(low, high)) || find_factor(n, mid(low, high), high));
}

constexpr bool calculate(std::size_t n)
{
    return n > 1
        && (n == 2
            || (n % 2 == 1
                && (n == 3
                    || !find_factor(n, 1, (ceilsqrt(n) + 1) / 2))));
}

} // namespace is_prime_impl

constexpr bool is_prime(std::size_t n)
{
    return sfl::dtl::is_prime_impl::calculate(n);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_IS_PRIME_HPP_INCLUDED

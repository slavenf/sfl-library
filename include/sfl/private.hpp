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

#ifndef SFL_PRIVATE_HPP_INCLUDED
#define SFL_PRIVATE_HPP_INCLUDED

#include <sfl/detail/cpp.hpp>
#include <sfl/detail/ignore_unused.hpp>
#include <sfl/detail/pointer_traits.hpp>
#include <sfl/detail/type_traits.hpp>

#include <algorithm>    // move, copy, etc.
#include <cassert>      // assert
#include <cstddef>      // size_t
#include <cstdlib>      // abort
#include <iterator>     // iterator_traits, xxxxx_iterator_tag
#include <memory>       // addressof, allocator_traits, pointer_traits
#include <stdexcept>    // length_error, out_of_range
#include <type_traits>  // enable_if, is_convertible, is_function, true_type...
#include <utility>      // forward, move, move_if_noexcept

namespace sfl
{

namespace dtl
{

} // namespace dtl

} // namespace sfl

#endif // SFL_PRIVATE_HPP_INCLUDED

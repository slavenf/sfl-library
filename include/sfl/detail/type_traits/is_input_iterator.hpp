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

#ifndef SFL_DETAIL_IS_INPUT_ITERATOR_HPP_INCLUDED
#define SFL_DETAIL_IS_INPUT_ITERATOR_HPP_INCLUDED

#include <sfl/detail/type_traits/enable_if_t.hpp>

#include <iterator>    // iterator_traits, input_iterator_tag
#include <type_traits> // true_type, false_type, is_convertible

namespace sfl
{

namespace dtl
{

template <typename Iterator, typename = void>
struct is_input_iterator : std::false_type {};

template <typename Iterator>
struct is_input_iterator
<
    Iterator,
    sfl::dtl::enable_if_t
    <
        std::is_convertible
        <
            typename std::iterator_traits<Iterator>::iterator_category,
            std::input_iterator_tag
        >::value
    >
> : std::true_type {};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_IS_INPUT_ITERATOR_HPP_INCLUDED

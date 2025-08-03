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

#ifndef SFL_DETAIL_SEGMENTED_ITERATOR_TRAITS_HPP_INCLUDED
#define SFL_DETAIL_SEGMENTED_ITERATOR_TRAITS_HPP_INCLUDED

#include <type_traits> // false_type

namespace sfl
{

namespace dtl
{

//
// This struct provides information about segmented iterators.
//
// The architecture about segmented iterator traits is based on this article:
// "Segmented Iterators and Hierarchical Algorithms", Matthew H. Austern.
//
template <typename T>
struct segmented_iterator_traits
{
    using is_segmented_iterator = std::false_type;

    //
    // Specialized struct must define the following types and functions:
    //
    // using iterator         = xxxxx; (it is usually `T`)
    // using segment_iterator = xxxxx;
    // using local_iterator   = xxxxx;
    //
    // static segment_iterator segment(iterator);
    // static local_iterator   local(iterator);
    //
    // static local_iterator begin(segment_iterator);
    // static local_iterator end(segment_iterator);
    //
    // static iterator compose(segment_iterator, local_iterator);
    //
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_SEGMENTED_ITERATOR_TRAITS_HPP_INCLUDED

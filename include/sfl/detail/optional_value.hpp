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

#ifndef SFL_DETAIL_OPTIONAL_VALUE_HPP_INCLUDED
#define SFL_DETAIL_OPTIONAL_VALUE_HPP_INCLUDED

#include <sfl/detail/cpp.hpp>

#include <memory> // addressof

namespace sfl
{

namespace dtl
{

template <typename T>
union optional_value
{
private:

    T value_;

public:

    optional_value() noexcept
    {}

    optional_value(const optional_value& other) = delete;

    optional_value(optional_value&& other) = delete;

    optional_value& operator=(const optional_value& other) = delete;

    optional_value& operator=(optional_value&& other) = delete;

    ~optional_value() noexcept
    {}

    SFL_NODISCARD
    T* get() noexcept
    {
        return std::addressof(value_);
    }

    SFL_NODISCARD
    const T* get() const noexcept
    {
        return std::addressof(value_);
    }
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_OPTIONAL_VALUE_HPP_INCLUDED

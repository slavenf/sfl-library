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

#ifndef SFL_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP_INCLUDED
#define SFL_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP_INCLUDED

#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/ignore_unused.hpp>

#include <cstddef>      // size_t, ptrdiff_t
#include <type_traits>  // true_type, false_type

namespace sfl
{

namespace dtl
{

template <typename T, std::size_t N>
class static_storage_allocator
{
public:

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap            = std::false_type;
    using is_always_equal                        = std::false_type;
    using is_partially_propagable                = std::true_type;

    template <typename U>
    struct rebind
    {
        using other = static_storage_allocator<U, N>;
    };

private:

    union
    {
        T internal_storage_[N];
    };

    #ifndef NDEBUG
    bool internal_storage_allocated_ = false;
    #endif

public:

    static_storage_allocator() noexcept
    {}

    static_storage_allocator(const static_storage_allocator& /*other*/) noexcept
    {}

    static_storage_allocator(static_storage_allocator&& /*other*/) noexcept
    {}

    template <typename T2, std::size_t N2>
    static_storage_allocator(const static_storage_allocator<T2, N2>& /*other*/) noexcept
    {}

    template <typename T2, std::size_t N2>
    static_storage_allocator(static_storage_allocator<T2, N2>&& /*other*/) noexcept
    {}

    ~static_storage_allocator()
    {}

    static_storage_allocator& operator=(const static_storage_allocator& /*other*/) noexcept
    {
        return *this;
    }

    static_storage_allocator& operator=(static_storage_allocator&& /*other*/) noexcept
    {
        return *this;
    }

    template <typename T2, std::size_t N2>
    static_storage_allocator& operator=(const static_storage_allocator<T2, N2>& /*other*/) noexcept
    {
        return *this;
    }

    template <typename T2, std::size_t N2>
    static_storage_allocator& operator=(static_storage_allocator<T2, N2>&& /*other*/) noexcept
    {
        return *this;
    }

    SFL_NODISCARD
    pointer allocate(size_type n)
    {
        sfl::dtl::ignore_unused(n);

        SFL_ASSERT(n <= N);

        #ifndef NDEBUG
        SFL_ASSERT(!internal_storage_allocated_);
        internal_storage_allocated_ = true;
        #endif

        return pointer(internal_storage_);
    }

    SFL_NODISCARD
    sfl::dtl::allocation_result<pointer, size_type> allocate_at_least(size_type n)
    {
        sfl::dtl::ignore_unused(n);

        SFL_ASSERT(n <= N);

        #ifndef NDEBUG
        SFL_ASSERT(!internal_storage_allocated_);
        internal_storage_allocated_ = true;
        #endif

        return {pointer(internal_storage_), size_type(N)};
    }

    void deallocate(pointer p, std::size_t n) noexcept
    {
        sfl::dtl::ignore_unused(p, n);

        SFL_ASSERT(p == pointer(internal_storage_));
        SFL_ASSERT(n <= N);

        #ifndef NDEBUG
        SFL_ASSERT(internal_storage_allocated_);
        internal_storage_allocated_ = false;
        #endif
    }

    SFL_NODISCARD
    static constexpr size_type max_size() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    bool is_storage_unpropagable(pointer p) const noexcept
    {
        sfl::dtl::ignore_unused(p);

        SFL_ASSERT(p == pointer(internal_storage_));

        #ifndef NDEBUG
        SFL_ASSERT(internal_storage_allocated_);
        #endif

        return true;
    }
};

template <typename T1, typename T2, std::size_t N>
SFL_NODISCARD
bool operator==
(
    const static_storage_allocator<T1, N>& x,
    const static_storage_allocator<T2, N>& y
) noexcept
{
    sfl::dtl::ignore_unused(x, y);
    return false;
}

template <typename T1, typename T2, std::size_t N>
SFL_NODISCARD
bool operator!=
(
    const static_storage_allocator<T1, N>& x,
    const static_storage_allocator<T2, N>& y
) noexcept
{
    return !(x == y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP_INCLUDED

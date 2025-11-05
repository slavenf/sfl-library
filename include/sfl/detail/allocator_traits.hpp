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

#ifndef SFL_DETAIL_ALLOCATOR_TRAITS_HPP_INCLUDED
#define SFL_DETAIL_ALLOCATOR_TRAITS_HPP_INCLUDED

#include <sfl/detail/type_traits/void_t.hpp>
#include <sfl/detail/utility/ignore_unused.hpp>
#include <sfl/detail/cpp.hpp>

#include <limits>       // numeric_limits
#include <memory>       // pointer_traits
#include <type_traits>  // true_type, false_type
#include <utility>      // declval

namespace sfl
{

namespace dtl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ALLOCATION RESULT
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifdef __cpp_lib_allocate_at_least

template <typename Pointer, typename SizeType>
using allocation_result = std::allocation_result<Pointer, SizeType>;

#else

template <typename Pointer, typename SizeType>
struct allocation_result
{
    Pointer ptr;
    SizeType count;
};

#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ALLOCATOR TRAITS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename Allocator>
class allocator_traits
{
private:

    template <typename Alloc>
    struct has_allocate_at_least
    {
    private:
        template <typename Alloc2>
        static std::true_type test(decltype(&Alloc2::allocate_at_least));

        template <typename Alloc2>
        static std::false_type test(...);

    public:
        using type = decltype(test<Alloc>(nullptr));
    };

public:

    using allocator_type = Allocator;

    using value_type = typename Allocator::value_type;

    ///////////////////////////////////////////////////////////////////////////
    #define SFL_NESTED_TYPE_OR_ALTERNATIVE(TNAME, ALTERNATIVE)              \
    private:                                                                \
        template <typename T> static typename T::TNAME test_##TNAME(T*);    \
        template <typename T> static ALTERNATIVE       test_##TNAME(...);   \
        using priv_##TNAME = decltype(test_##TNAME<Allocator>(nullptr));    \
    public:                                                                 \
    ///////////////////////////////////////////////////////////////////////////

    using pointer = typename std::allocator_traits<Allocator>::pointer;

    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    using void_pointer = typename std::allocator_traits<Allocator>::void_pointer;

    using const_void_pointer = typename std::allocator_traits<Allocator>::const_void_pointer;

    using difference_type = typename std::allocator_traits<Allocator>::difference_type;

    using size_type = typename std::allocator_traits<Allocator>::size_type;

    using propagate_on_container_copy_assignment = typename std::allocator_traits<Allocator>::propagate_on_container_copy_assignment;

    using propagate_on_container_move_assignment = typename std::allocator_traits<Allocator>::propagate_on_container_move_assignment;

    using propagate_on_container_swap = typename std::allocator_traits<Allocator>::propagate_on_container_swap;

    #if SFL_CPP_VERSION >= SFL_CPP_20
    using is_always_equal = typename std::allocator_traits<Allocator>::is_always_equal;
    #else
    SFL_NESTED_TYPE_OR_ALTERNATIVE(is_always_equal, typename std::is_empty<Allocator>::type)
    using is_always_equal = priv_is_always_equal;
    #endif

    SFL_NESTED_TYPE_OR_ALTERNATIVE(is_partially_propagable, std::false_type)
    using is_partially_propagable = priv_is_partially_propagable;

    ///////////////////////////////////////////////////////////////////////////
    #undef SFL_NESTED_TYPE_OR_ALTERNATIVE
    ///////////////////////////////////////////////////////////////////////////

    template <typename T>
    using rebind_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;

    template <typename T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

public:

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static pointer allocate(Allocator& a, size_type n)
    {
        return std::allocator_traits<Allocator>::allocate(a, n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static pointer allocate(Allocator& a, size_type n, const_void_pointer hint)
    {
        return std::allocator_traits<Allocator>::allocate(a, n, hint);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static sfl::dtl::allocation_result<pointer, size_type> allocate_at_least(Allocator& a, size_type n)
    {
        return priv_allocate_at_least(a, n, typename has_allocate_at_least<Allocator>::type());
    }

    SFL_CONSTEXPR_20
    static void deallocate(Allocator& a, pointer p, size_type n)
    {
        std::allocator_traits<Allocator>::deallocate(a, p, n);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static size_type max_size(const Allocator& a) noexcept
    {
        return std::allocator_traits<Allocator>::max_size(a);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static Allocator select_on_container_copy_construction(const Allocator& a)
    {
        return std::allocator_traits<Allocator>::select_on_container_copy_construction(a);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    static bool is_storage_unpropagable(const Allocator& a, pointer p) noexcept
    {
        return priv_is_storage_unpropagable(a, p, is_partially_propagable());
    }

private:

    SFL_CONSTEXPR_20
    static sfl::dtl::allocation_result<pointer, size_type> priv_allocate_at_least(Allocator& a, size_type n, std::true_type)
    {
        return a.allocate_at_least(n);
    }

    SFL_CONSTEXPR_20
    static sfl::dtl::allocation_result<pointer, size_type> priv_allocate_at_least(Allocator& a, size_type n, std::false_type)
    {
        return sfl::dtl::allocation_result<pointer, size_type>{a.allocate(n), n};
    }

    SFL_CONSTEXPR_20
    static bool priv_is_storage_unpropagable(const Allocator& a, pointer p, std::true_type) noexcept
    {
        return a.is_storage_unpropagable(p);
    }

    SFL_CONSTEXPR_20
    static bool priv_is_storage_unpropagable(const Allocator& a, pointer p, std::false_type) noexcept
    {
        sfl::dtl::ignore_unused(a, p);
        return false;
    }
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_ALLOCATOR_TRAITS_HPP_INCLUDED

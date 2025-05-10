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

#ifndef SFL_DETAIL_SMALL_STORAGE_ALLOCATOR_HPP_INCLUDED
#define SFL_DETAIL_SMALL_STORAGE_ALLOCATOR_HPP_INCLUDED

#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>

#include <cstddef>      // size_t, ptrdiff_t
#include <memory>       // pointer_traits
#include <utility>      // move
#include <type_traits>  // is_xxxxx, true_type, false_type

namespace sfl
{

namespace dtl
{

template <typename T, std::size_t N, typename BaseAllocator>
class small_storage_allocator : public BaseAllocator
{
    static_assert
    (
        std::is_same<typename BaseAllocator::value_type, T>::value,
        "BaseAllocator::value_type must be same as T."
    );

    template <typename, std::size_t, typename>
    friend class small_storage_allocator;

private:

    using base_allocator_type = BaseAllocator;

public:

    using value_type         = T;
    using pointer            = typename sfl::dtl::allocator_traits<base_allocator_type>::pointer;
    using const_pointer      = typename sfl::dtl::allocator_traits<base_allocator_type>::const_pointer;
    using void_pointer       = typename sfl::dtl::allocator_traits<base_allocator_type>::void_pointer;
    using const_void_pointer = typename sfl::dtl::allocator_traits<base_allocator_type>::const_void_pointer;
    using reference          = T&;
    using const_reference    = const T&;
    using size_type          = std::size_t;
    using difference_type    = std::ptrdiff_t;

    using propagate_on_container_copy_assignment = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_move_assignment;
    using propagate_on_container_swap            = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_swap;
    using is_always_equal                        = typename sfl::dtl::allocator_traits<base_allocator_type>::is_always_equal;
    using is_partially_propagable                = std::true_type;

    template <typename U>
    struct rebind
    {
        using other = small_storage_allocator
        <
            U,
            N,
            typename sfl::dtl::allocator_traits<base_allocator_type>::template rebind_alloc<U>
        >;
    };

private:

    SFL_NODISCARD
    base_allocator_type& base() noexcept
    {
        return *static_cast<base_allocator_type*>(this);
    }

    SFL_NODISCARD
    const base_allocator_type& base() const noexcept
    {
        return *static_cast<const base_allocator_type*>(this);
    }

private:

    union
    {
        T internal_storage_[N];
    };

    bool internal_storage_allocated_ = false;

public:

    small_storage_allocator() noexcept(std::is_nothrow_default_constructible<base_allocator_type>::value)
    {}

    small_storage_allocator(const small_storage_allocator& other) noexcept
        : base_allocator_type(other.base())
    {}

    small_storage_allocator(small_storage_allocator&& other) noexcept
        : base_allocator_type(std::move(other.base()))
    {}

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator(const small_storage_allocator<T2, N2, Allocator2>& other) noexcept
        : base_allocator_type(other.base())
    {}

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator(small_storage_allocator<T2, N2, Allocator2>&& other) noexcept
        : base_allocator_type(std::move(other.base()))
    {}

    explicit small_storage_allocator(const base_allocator_type& other) noexcept
        : base_allocator_type(other)
    {}

    explicit small_storage_allocator(base_allocator_type&& other) noexcept
        : base_allocator_type(std::move(other))
    {}

    ~small_storage_allocator()
    {}

    small_storage_allocator& operator=(const small_storage_allocator& other) noexcept
    {
        base_allocator_type::operator=(other.base());
        return *this;
    }

    small_storage_allocator& operator=(small_storage_allocator&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other.base()));
        return *this;
    }

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator& operator=(const small_storage_allocator<T2, N2, Allocator2>& other) noexcept
    {
        base_allocator_type::operator=(other.base());
        return *this;
    }

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator& operator=(small_storage_allocator<T2, N2, Allocator2>&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other.base()));
        return *this;
    }

    small_storage_allocator& operator=(const base_allocator_type& other) noexcept
    {
        base_allocator_type::operator=(other);
        return *this;
    }

    small_storage_allocator& operator=(base_allocator_type&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other));
        return *this;
    }

    SFL_NODISCARD
    pointer allocate(size_type n)
    {
        if (n <= N && !internal_storage_allocated_)
        {
            internal_storage_allocated_ = true;
            return std::pointer_traits<pointer>::pointer_to(*internal_storage_);
        }
        else
        {
            return sfl::dtl::allocator_traits<base_allocator_type>::allocate(base(), n);
        }
    }

    SFL_NODISCARD
    pointer allocate(size_type n, const void* hint)
    {
        if (n <= N && !internal_storage_allocated_)
        {
            internal_storage_allocated_ = true;
            return std::pointer_traits<pointer>::pointer_to(*internal_storage_);
        }
        else
        {
            return sfl::dtl::allocator_traits<base_allocator_type>::allocate(base(), n, hint);
        }
    }

    SFL_NODISCARD
    sfl::dtl::allocation_result<pointer, size_type> allocate_at_least(size_type n)
    {
        if (n <= N && !internal_storage_allocated_)
        {
            internal_storage_allocated_ = true;
            return {std::pointer_traits<pointer>::pointer_to(*internal_storage_), size_type(N)};
        }
        else
        {
            return sfl::dtl::allocator_traits<base_allocator_type>::allocate_at_least(base(), n);
        }
    }

    void deallocate(pointer p, std::size_t n) noexcept
    {
        if (sfl::dtl::to_address(p) == internal_storage_)
        {
            SFL_ASSERT(internal_storage_allocated_);
            internal_storage_allocated_ = false;
        }
        else
        {
            sfl::dtl::allocator_traits<base_allocator_type>::deallocate(base(), p, n);
        }
    }

    SFL_NODISCARD
    bool is_storage_unpropagable(pointer p) const noexcept
    {
        return sfl::dtl::to_address(p) == internal_storage_;
    }
};

template <typename T, typename BaseAllocator>
class small_storage_allocator<T, 0, BaseAllocator> : public BaseAllocator
{
    static_assert
    (
        std::is_same<typename BaseAllocator::value_type, T>::value,
        "BaseAllocator::value_type must be same as T."
    );

    template <typename, std::size_t, typename>
    friend class small_storage_allocator;

private:

    using base_allocator_type = BaseAllocator;

public:

    using value_type         = T;
    using pointer            = typename sfl::dtl::allocator_traits<base_allocator_type>::pointer;
    using const_pointer      = typename sfl::dtl::allocator_traits<base_allocator_type>::const_pointer;
    using void_pointer       = typename sfl::dtl::allocator_traits<base_allocator_type>::void_pointer;
    using const_void_pointer = typename sfl::dtl::allocator_traits<base_allocator_type>::const_void_pointer;
    using reference          = T&;
    using const_reference    = const T&;
    using size_type          = std::size_t;
    using difference_type    = std::ptrdiff_t;

    using propagate_on_container_copy_assignment = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_move_assignment;
    using propagate_on_container_swap            = typename sfl::dtl::allocator_traits<base_allocator_type>::propagate_on_container_swap;
    using is_always_equal                        = typename sfl::dtl::allocator_traits<base_allocator_type>::is_always_equal;
    using is_partially_propagable                = std::false_type;

    template <typename U>
    struct rebind
    {
        using other = small_storage_allocator
        <
            U,
            0,
            typename sfl::dtl::allocator_traits<base_allocator_type>::template rebind_alloc<U>
        >;
    };

private:

    SFL_NODISCARD
    base_allocator_type& base() noexcept
    {
        return *static_cast<base_allocator_type*>(this);
    }

    SFL_NODISCARD
    const base_allocator_type& base() const noexcept
    {
        return *static_cast<const base_allocator_type*>(this);
    }

public:

    small_storage_allocator() noexcept(std::is_nothrow_default_constructible<base_allocator_type>::value)
    {}

    small_storage_allocator(const small_storage_allocator& other) noexcept
        : base_allocator_type(other.base())
    {}

    small_storage_allocator(small_storage_allocator&& other) noexcept
        : base_allocator_type(std::move(other.base()))
    {}

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator(const small_storage_allocator<T2, N2, Allocator2>& other) noexcept
        : base_allocator_type(other.base())
    {}

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator(small_storage_allocator<T2, N2, Allocator2>&& other) noexcept
        : base_allocator_type(std::move(other.base()))
    {}

    explicit small_storage_allocator(const base_allocator_type& other) noexcept
        : base_allocator_type(other)
    {}

    explicit small_storage_allocator(base_allocator_type&& other) noexcept
        : base_allocator_type(std::move(other))
    {}

    ~small_storage_allocator()
    {}

    small_storage_allocator& operator=(const small_storage_allocator& other) noexcept
    {
        base_allocator_type::operator=(other.base());
        return *this;
    }

    small_storage_allocator& operator=(small_storage_allocator&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other.base()));
        return *this;
    }

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator& operator=(const small_storage_allocator<T2, N2, Allocator2>& other) noexcept
    {
        base_allocator_type::operator=(other.base());
        return *this;
    }

    template <typename T2, std::size_t N2, typename Allocator2>
    small_storage_allocator& operator=(small_storage_allocator<T2, N2, Allocator2>&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other.base()));
        return *this;
    }

    small_storage_allocator& operator=(const base_allocator_type& other) noexcept
    {
        base_allocator_type::operator=(other);
        return *this;
    }

    small_storage_allocator& operator=(base_allocator_type&& other) noexcept
    {
        base_allocator_type::operator=(std::move(other));
        return *this;
    }

    SFL_NODISCARD
    pointer allocate(size_type n)
    {
        return sfl::dtl::allocator_traits<base_allocator_type>::allocate(base(), n);
    }

    SFL_NODISCARD
    pointer allocate(size_type n, const void* hint)
    {
        return sfl::dtl::allocator_traits<base_allocator_type>::allocate(base(), n, hint);
    }

    SFL_NODISCARD
    sfl::dtl::allocation_result<pointer, size_type> allocate_at_least(size_type n)
    {
        return sfl::dtl::allocator_traits<base_allocator_type>::allocate_at_least(base(), n);
    }

    void deallocate(pointer p, std::size_t n) noexcept
    {
        sfl::dtl::allocator_traits<base_allocator_type>::deallocate(base(), p, n);
    }
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_SMALL_STORAGE_ALLOCATOR_HPP_INCLUDED

#ifndef SFL_TEST_ALLOCATOR_3_HPP
#define SFL_TEST_ALLOCATOR_3_HPP

#include <cstddef>
#include <type_traits>

namespace sfl
{

template<typename T>
class test_allocator_3
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

    template <typename U>
    struct rebind
    {
        using other = test_allocator_3<U>;
    };

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    test_allocator_3() noexcept
    {}

    test_allocator_3(const test_allocator_3&) noexcept
    {}

    template <typename U>
    test_allocator_3(const test_allocator_3<U>&) noexcept
    {}

    ~test_allocator_3() noexcept
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    test_allocator_3& operator=(const test_allocator_3&) noexcept
    {
        return *this;
    }

    //
    // ---- ALLOCATE AND DEALLOACTE -------------------------------------------
    //

    T* allocate(size_type n, const void* = nullptr)
    {
        if (n > max_size())
        {
            throw std::bad_alloc();
        }

        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_type)
    {
        ::operator delete(p);
    }

    //
    // ---- CONSTRUCT AND DESTROY ---------------------------------------------
    //

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) noexcept(
        std::is_nothrow_constructible<U, Args...>::value
    )
    {
        ::new ((void *)p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) noexcept(std::is_nothrow_destructible<U>::value)
    {
        p->~U();
    }

    //
    // ---- ADDRESS -----------------------------------------------------------
    //

    pointer address(reference x) const noexcept
    {
        return std::addressof(x);
    }

    const_pointer address(const_reference x) const noexcept
    {
        return std::addressof(x);
    }

    //
    // ---- MAX SIZE ----------------------------------------------------------
    //

    size_type max_size() const noexcept
    {
        return std::size_t(PTRDIFF_MAX) / sizeof(T);
    }

    //
    // ---- COMPARISONS -------------------------------------------------------
    //

    template <typename U>
    friend
    bool operator==(const test_allocator_3&, const test_allocator_3<U>&) noexcept
    {
        return true;
    }

    template <typename U>
    friend
    bool operator!=(const test_allocator_3&, const test_allocator_3<U>&) noexcept
    {
        return false;
    }
};

} // namespace sfl

#endif //SFL_TEST_ALLOCATOR_3_HPP

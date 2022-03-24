#ifndef SFL_TEST_ALLOCATOR_4
#define SFL_TEST_ALLOCATOR_4

#include <cstddef>
#include <memory>
#include <type_traits>

#include "fancy_ptr.hpp"

namespace sfl
{

template<typename T>
class test_allocator_4
{
public:

    using value_type      = T;
    using pointer         = fancy_ptr<T>;
    using const_pointer   = fancy_ptr<const T>;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap            = std::true_type;

    template <typename U>
    struct rebind
    {
        using other = test_allocator_4<U>;
    };

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    test_allocator_4() noexcept
    {}

    test_allocator_4(const test_allocator_4&) noexcept
    {}

    template <typename U>
    test_allocator_4(const test_allocator_4<U>&) noexcept
    {}

    ~test_allocator_4() noexcept
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    test_allocator_4& operator=(const test_allocator_4&) noexcept
    {
        return *this;
    }

    //
    // ---- ALLOCATE AND DEALLOACTE -------------------------------------------
    //

    pointer allocate(size_type n, const void* = nullptr)
    {
        if (n > max_size())
        {
            throw std::bad_alloc();
        }

        return std::pointer_traits<pointer>::pointer_to
        (
            *static_cast<T*>(::operator new(n * sizeof(T)))
        );
    }

    void deallocate(pointer p, size_type)
    {
        ::operator delete(std::addressof(*p));
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
    bool operator==(const test_allocator_4&, const test_allocator_4<U>&) noexcept
    {
        return true;
    }

    template <typename U>
    friend
    bool operator!=(const test_allocator_4&, const test_allocator_4<U>&) noexcept
    {
        return false;
    }
};

} // namespace sfl

#endif //SFL_TEST_ALLOCATOR_4

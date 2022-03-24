//
// g++ -Wall -Wextra -Wpedantic -std=c++11 -g -o test.out test_allocator_4.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>

#include "MyInt.hpp"
#include "test_allocator_4.hpp"

template <typename T>
T* to_address(T* p) noexcept
{
    static_assert(!std::is_function<T>::value, "not a function pointer");
    return p;
}

template <typename Pointer>
auto to_address(const Pointer& p) noexcept
-> typename std::pointer_traits<Pointer>::element_type*
{
    return p == nullptr ? nullptr : to_address(p.operator->());
}

int main()
{
    sfl::test_allocator_4<MyInt> a;

    const std::size_t n = 10;

    auto p = a.allocate(n);

    for (std::size_t i = 0; i < n; ++i)
    {
        a.construct(to_address(p + i), i);
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        assert(p[i] == i);
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        a.destroy(to_address(p + i));
    }

    a.deallocate(p, n);
}

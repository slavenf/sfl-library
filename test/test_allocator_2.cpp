//
// g++ -Wall -Wextra -Wpedantic -std=c++11 -g -o test.out test_allocator_2.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>

#include "MyInt.hpp"
#include "test_allocator_2.hpp"

int main()
{
    sfl::test_allocator_2<MyInt> a;

    const std::size_t n = 10;

    auto p = a.allocate(n);

    for (std::size_t i = 0; i < n; ++i)
    {
        a.construct(p + i, i);
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        assert(p[i] == i);
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        a.destroy(p + i);
    }

    a.deallocate(p, n);
}

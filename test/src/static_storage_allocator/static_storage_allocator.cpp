#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/static_storage_allocator.hpp"

#include "sfl/detail/memory/construct_at_a.hpp"
#include "sfl/detail/memory/destroy_at_a.hpp"

#include "check.hpp"

#include "xint.hpp"

template <typename T>
SFL_CONSTEXPR_20
bool test()
{
    constexpr int N = 10;

    using allocator_type = sfl::dtl::static_storage_allocator<T, N>;

    using pointer = typename std::allocator_traits<allocator_type>::pointer;

    for (int n = 1; n <= N; ++n)
    {
        allocator_type alloc;

        pointer p = alloc.allocate(n);

        for (int i = 0; i < n; ++i)
        {
            sfl::dtl::construct_at_a(alloc, p + i, i);
        }

        for (int i = 0; i < n; ++i)
        {
            CHECK(*(p + i) == int(i));
        }

        for (int i = 0; i < n; ++i)
        {
            sfl::dtl::destroy_at_a(alloc, p + i);
        }

        alloc.deallocate(p, n);
    }

    for (int n = 1; n <= N; ++n)
    {
        allocator_type alloc;

        auto res = alloc.allocate_at_least(n);

        CHECK(res.count == N);

        alloc.deallocate(res.ptr, n);
    }

    return true;
}

int main()
{
    test<sfl::test::xint>();
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test<int>());
#endif

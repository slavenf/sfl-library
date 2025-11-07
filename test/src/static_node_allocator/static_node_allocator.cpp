#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/static_node_allocator.hpp"

#include "sfl/detail/memory/allocate.hpp"
#include "sfl/detail/memory/construct_at_a.hpp"
#include "sfl/detail/memory/deallocate.hpp"
#include "sfl/detail/memory/destroy_at_a.hpp"

#include "check.hpp"

#include "xint.hpp"

SFL_CONSTEXPR_20
bool test()
{
    using sfl::test::xint;

    sfl::dtl::static_node_allocator<xint, 4> a;

    auto* p1 = sfl::dtl::allocate(a, 1);
    auto* p2 = sfl::dtl::allocate(a, 1);
    auto* p3 = sfl::dtl::allocate(a, 1);
    auto* p4 = sfl::dtl::allocate(a, 1);

    sfl::dtl::construct_at_a(a, p1, 10);
    sfl::dtl::construct_at_a(a, p2, 20);
    sfl::dtl::construct_at_a(a, p3, 30);
    sfl::dtl::construct_at_a(a, p4, 40);

    CHECK(*p1 == 10);
    CHECK(*p2 == 20);
    CHECK(*p3 == 30);
    CHECK(*p4 == 40);

    sfl::dtl::destroy_at_a(a, p1);
    sfl::dtl::destroy_at_a(a, p2);
    sfl::dtl::destroy_at_a(a, p3);
    sfl::dtl::destroy_at_a(a, p4);

    sfl::dtl::deallocate(a, p1, 1);
    sfl::dtl::deallocate(a, p2, 1);
    sfl::dtl::deallocate(a, p3, 1);
    sfl::dtl::deallocate(a, p4, 1);

    return true;
}

int main()
{
    test();
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test());
#endif

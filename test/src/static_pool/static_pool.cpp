#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/static_pool.hpp"

#include "sfl/detail/memory/construct_at.hpp"
#include "sfl/detail/memory/destroy_at.hpp"

#include "check.hpp"

#include "xint.hpp"

SFL_CONSTEXPR_20
bool test()
{
    using sfl::test::xint;

    sfl::dtl::static_pool<xint, 4> pool;

    // Make 10
    auto* p1 = pool.allocate();
    sfl::dtl::construct_at(p1, 10);
    CHECK(*p1 == 10);

    // Make 20
    auto* p2 = pool.allocate();
    sfl::dtl::construct_at(p2, 20);
    CHECK(*p2 == 20);

    // Make 30
    auto* p3 = pool.allocate();
    sfl::dtl::construct_at(p3, 30);
    CHECK(*p3 == 30);

    CHECK(p1 < p2);
    CHECK(p2 < p3);

    ///////////////////////////////////////////////////////////////////////

    // Dump 20
    sfl::dtl::destroy_at(p2);
    pool.deallocate(p2);

    // Make 21
    p2 = pool.allocate();
    sfl::dtl::construct_at(p2, 21);
    CHECK(*p2 == 21);

    // New element should be at the same address as old element.
    CHECK(p1 < p2);
    CHECK(p2 < p3);

    ///////////////////////////////////////////////////////////////////////

    // Make 40
    auto* p4 = pool.allocate();
    sfl::dtl::construct_at(p4, 40);
    CHECK(*p4 == 40);

    // New element is last.
    CHECK(p1 < p2);
    CHECK(p2 < p3);
    CHECK(p3 < p4);

    ///////////////////////////////////////////////////////////////////////

    // The following line aborts because pool is full.
    // auto* p5 = pool.allocate(); (void)p5;

    ///////////////////////////////////////////////////////////////////////

    // Dump 10
    sfl::dtl::destroy_at(p1);
    pool.deallocate(p1);

    // Make 11
    p1 = pool.allocate();
    sfl::dtl::construct_at(p1, 11);
    CHECK(*p1 == 11);

    // New element should be at the same address as old element.
    CHECK(p1 < p2);
    CHECK(p2 < p3);
    CHECK(p3 < p4);

    ///////////////////////////////////////////////////////////////////////

    // Deallocate elements if FIFO order!!!

    // Dump 11
    sfl::dtl::destroy_at(p1);
    pool.deallocate(p1);

    // Dump 21
    sfl::dtl::destroy_at(p2);
    pool.deallocate(p2);

    // Dump 30
    sfl::dtl::destroy_at(p3);
    pool.deallocate(p3);

    // Dump 40
    sfl::dtl::destroy_at(p4);
    pool.deallocate(p4);

    ///////////////////////////////////////////////////////////////////////

    // Make 10
    p1 = pool.allocate();
    sfl::dtl::construct_at(p1, 10);
    CHECK(*p1 == 10);

    // Make 20
    p2 = pool.allocate();
    sfl::dtl::construct_at(p2, 20);
    CHECK(*p2 == 20);

    // Make 30
    p3 = pool.allocate();
    sfl::dtl::construct_at(p3, 30);
    CHECK(*p3 == 30);

    // Make 40
    p4 = pool.allocate();
    sfl::dtl::construct_at(p4, 40);
    CHECK(*p4 == 40);

    // Pointer are now in reversed order because old elements were not deallocated if LIFO order.
    CHECK(p4 < p3);
    CHECK(p3 < p2);
    CHECK(p2 < p1);

    ///////////////////////////////////////////////////////////////////////

    CHECK(pool.contains(p1));
    CHECK(pool.contains(p2));
    CHECK(pool.contains(p3));
    CHECK(pool.contains(p4));

    xint* temp = new xint(12345);

    CHECK(!pool.contains(temp));

    delete temp;

    ///////////////////////////////////////////////////////////////////////

    // Deallocate elements. Order is irrelevant since this is end of test.

    // Dump 10
    sfl::dtl::destroy_at(p1);
    pool.deallocate(p1);

    // Dump 20
    sfl::dtl::destroy_at(p2);
    pool.deallocate(p2);

    // Dump 30
    sfl::dtl::destroy_at(p3);
    pool.deallocate(p3);

    // Dump 40
    sfl::dtl::destroy_at(p4);
    pool.deallocate(p4);

    return true;
}

int main()
{
    test();
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test());
#endif

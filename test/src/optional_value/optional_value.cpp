#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/memory/construct_at_a.hpp"
#include "sfl/detail/memory/destroy_at_a.hpp"
#include "sfl/detail/utility/optional_value.hpp"

#include "check.hpp"

#include <memory>

SFL_CONSTEXPR_20
bool test()
{
    std::allocator<int> alloc;

    sfl::dtl::optional_value<int> v;

    sfl::dtl::construct_at_a(alloc, v.ptr(), 12345);

    CHECK(v.ref() == 12345);

    sfl::dtl::destroy_at_a(alloc, v.ptr());

    return true;
}

int main()
{
    test();
}

#if SFL_CPP_VERSION >= SFL_CPP_20
static_assert(test());
#endif

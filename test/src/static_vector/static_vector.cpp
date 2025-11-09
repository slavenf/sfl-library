#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_vector.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"

#include <sstream>
#include <vector>

#define BEGIN_TEST(x) PRINT(x)
#define END_TEST()

void test_static_vector()
{
    #include "static_vector.inc"
}

int main()
{
    test_static_vector();
}

#if SFL_CPP_VERSION >= SFL_CPP_20

#undef  BEGIN_TEST
#undef  END_TEST

#define BEGIN_TEST(x) static_assert([](){
#define END_TEST()    return true;}());

#define TEST_CPP20_CONSTEXPR

#include "static_vector.inc"

#endif // SFL_CPP_VERSION >= SFL_CPP_20

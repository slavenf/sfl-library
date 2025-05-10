#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/math/is_pow2.hpp"
#include "sfl/detail/math/is_prime.hpp"

static_assert(sfl::dtl::is_pow2(0ull) == false, "");
static_assert(sfl::dtl::is_pow2(1ull) == true, "");
static_assert(sfl::dtl::is_pow2(2ull) == true, "");
static_assert(sfl::dtl::is_pow2(3ull) == false, "");
static_assert(sfl::dtl::is_pow2(4ull) == true, "");
static_assert(sfl::dtl::is_pow2(5ull) == false, "");
static_assert(sfl::dtl::is_pow2(6ull) == false, "");
static_assert(sfl::dtl::is_pow2(7ull) == false, "");
static_assert(sfl::dtl::is_pow2(8ull) == true, "");
static_assert(sfl::dtl::is_pow2(9ull) == false, "");
static_assert(sfl::dtl::is_pow2(10ull) == false, "");
static_assert(sfl::dtl::is_pow2(11ull) == false, "");
static_assert(sfl::dtl::is_pow2(12ull) == false, "");
static_assert(sfl::dtl::is_pow2(13ull) == false, "");
static_assert(sfl::dtl::is_pow2(14ull) == false, "");
static_assert(sfl::dtl::is_pow2(15ull) == false, "");
static_assert(sfl::dtl::is_pow2(16ull) == true, "");

static_assert(sfl::dtl::is_prime(0ull) == false, "");
static_assert(sfl::dtl::is_prime(1ull) == false, "");
static_assert(sfl::dtl::is_prime(2ull) == true, "");
static_assert(sfl::dtl::is_prime(3ull) == true, "");
static_assert(sfl::dtl::is_prime(4ull) == false, "");
static_assert(sfl::dtl::is_prime(5ull) == true, "");
static_assert(sfl::dtl::is_prime(6ull) == false, "");
static_assert(sfl::dtl::is_prime(7ull) == true, "");
static_assert(sfl::dtl::is_prime(8ull) == false, "");
static_assert(sfl::dtl::is_prime(9ull) == false, "");
static_assert(sfl::dtl::is_prime(10ull) == false, "");
static_assert(sfl::dtl::is_prime(11ull) == true, "");
static_assert(sfl::dtl::is_prime(12ull) == false, "");
static_assert(sfl::dtl::is_prime(13ull) == true, "");
static_assert(sfl::dtl::is_prime(14ull) == false, "");
static_assert(sfl::dtl::is_prime(15ull) == false, "");
static_assert(sfl::dtl::is_prime(16ull) == false, "");
static_assert(sfl::dtl::is_prime(17ull) == true, "");
static_assert(sfl::dtl::is_prime(18ull) == false, "");
static_assert(sfl::dtl::is_prime(19ull) == true, "");
static_assert(sfl::dtl::is_prime(20ull) == false, "");
static_assert(sfl::dtl::is_prime(21ull) == false, "");
static_assert(sfl::dtl::is_prime(22ull) == false, "");
static_assert(sfl::dtl::is_prime(23ull) == true, "");
static_assert(sfl::dtl::is_prime(100000007ull) == true, "");
static_assert(sfl::dtl::is_prime(4294967029ull) == true, "");
static_assert(sfl::dtl::is_prime(4294967295ull) == false, "");
static_assert(sfl::dtl::is_prime(4294967311ull) == true, "");

#if defined(__GNUC__) && !defined(__clang__) && (__GNUC__ >= 14)
static_assert(sfl::dtl::is_prime(1000000000039ull) == true, "");
#endif

int main()
{}

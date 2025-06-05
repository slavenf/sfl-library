#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/type_traits/conjunction.hpp"
#include "sfl/detail/type_traits/disjunction.hpp"
#include "sfl/detail/type_traits/is_nothrow_swappable.hpp"
#include "sfl/detail/type_traits/negation.hpp"

///////////////////////////////////////////////////////////////////////////////

static_assert(sfl::dtl::conjunction<std::true_type>::value == true, "");
static_assert(sfl::dtl::conjunction<std::false_type>::value == false, "");

static_assert(sfl::dtl::conjunction<std::true_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::conjunction<std::true_type, std::false_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::true_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::false_type>::value == false, "");

static_assert(sfl::dtl::conjunction<std::true_type, std::true_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::conjunction<std::true_type, std::true_type, std::false_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::true_type, std::false_type, std::true_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::true_type, std::false_type, std::false_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::true_type, std::true_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::true_type, std::false_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::false_type, std::true_type>::value == false, "");
static_assert(sfl::dtl::conjunction<std::false_type, std::false_type, std::false_type>::value == false, "");

///////////////////////////////////////////////////////////////////////////////

static_assert(sfl::dtl::disjunction<std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type>::value == false, "");

static_assert(sfl::dtl::disjunction<std::true_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::true_type, std::false_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::false_type>::value == false, "");

static_assert(sfl::dtl::disjunction<std::true_type, std::true_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::true_type, std::true_type, std::false_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::true_type, std::false_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::true_type, std::false_type, std::false_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::true_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::true_type, std::false_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::false_type, std::true_type>::value == true, "");
static_assert(sfl::dtl::disjunction<std::false_type, std::false_type, std::false_type>::value == false, "");

///////////////////////////////////////////////////////////////////////////////

static_assert(sfl::dtl::negation<std::true_type>::value == false, "");
static_assert(sfl::dtl::negation<std::false_type>::value == true, "");

///////////////////////////////////////////////////////////////////////////////

namespace test_is_nothrow_swappable
{

struct S0
{};

struct S1
{};

void swap(S1&, S1&) noexcept(false);

struct S2
{};

void swap(S2&, S2&) noexcept(true);

struct S3
{
    S3() = delete;
    S3(int);
    S3(const S3&);
    S3(S3&&);
    S3& operator=(const S3&);
    S3& operator=(S3&&);
};

struct S4
{
    S4() = delete;
    S4(int) noexcept(false);
    S4(const S4&) noexcept(false);
    S4(S4&&) noexcept(false);
    S4& operator=(const S4&) noexcept(false);
    S4& operator=(S4&&) noexcept(false);
};

struct S5
{
    S5() = delete;
    S5(int) noexcept(true);
    S5(const S5&) noexcept(true);
    S5(S5&&) noexcept(true);
    S5& operator=(const S5&) noexcept(true);
    S5& operator=(S5&&) noexcept(true);
};

static_assert(sfl::dtl::is_nothrow_swappable<S0>::value == true, "");
static_assert(sfl::dtl::is_nothrow_swappable<S1>::value == false, "");
static_assert(sfl::dtl::is_nothrow_swappable<S2>::value == true, "");
static_assert(sfl::dtl::is_nothrow_swappable<S3>::value == false, "");
static_assert(sfl::dtl::is_nothrow_swappable<S4>::value == false, "");
static_assert(sfl::dtl::is_nothrow_swappable<S5>::value == true, "");

} // namespace test_is_nothrow_swappable

///////////////////////////////////////////////////////////////////////////////

int main()
{}

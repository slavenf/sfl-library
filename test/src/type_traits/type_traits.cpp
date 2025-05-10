#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/type_traits/conjunction.hpp"
#include "sfl/detail/type_traits/disjunction.hpp"
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

int main()
{}

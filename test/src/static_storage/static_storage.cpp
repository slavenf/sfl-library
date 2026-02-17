#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/static_storage.hpp"

#include "check.hpp"

#include <iterator>
#include <memory>
#include <type_traits>

using static_storage = sfl::dtl::static_storage<int, 8>;

using pointer = typename static_storage::pointer;

using const_pointer = typename static_storage::const_pointer;

#if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ < 5)) || (defined(__clang__) && (__clang_major__ < 4))

static_assert(__has_trivial_copy(pointer), "");

static_assert(__has_trivial_copy(const_pointer), "");

#else

static_assert(std::is_trivially_copyable<pointer>::value, "");

static_assert(std::is_trivially_copyable<const_pointer>::value, "");

#endif

static_assert(std::is_same<typename std::pointer_traits<pointer>::element_type, int>::value, "");

static_assert(std::is_same<typename std::pointer_traits<const_pointer>::element_type, const int>::value, "");

static_assert(std::is_same<typename std::iterator_traits<pointer>::value_type, int>::value, "");

static_assert(std::is_same<typename std::iterator_traits<const_pointer>::value_type, int>::value, "");

static_assert(std::is_same<typename std::iterator_traits<pointer>::pointer, int*>::value, "");

static_assert(std::is_same<typename std::iterator_traits<const_pointer>::pointer, const int*>::value, "");

static_assert(std::is_same<typename std::iterator_traits<pointer>::reference, int&>::value, "");

static_assert(std::is_same<typename std::iterator_traits<const_pointer>::reference, const int&>::value, "");

int main()
{
    using value_type = typename static_storage::value_type;

    value_type val = 12345;
    const value_type cval = 12345;

    // Default construct
    pointer p1 = pointer();
    const_pointer cp1 = const_pointer();

    // Construct from pointer to value_type
    pointer p2(&val);
    const_pointer cp2(&val);

    // Construct from pointer to const value_type
    // pointer p3(&cval); // ---> NOT ALLOWED
    const_pointer cp3(&cval);

    // Copy constructor
    pointer p4(p2);
    const_pointer cp4(cp2);

    // Converting constructor (from pointer to const_pointer)
    const_pointer cp5(p1);

    // Converting constructor (from const_pointer to pointer)
    // pointer p5(cp1); // ---> NOT ALLOWED

    // Copy assignment operator
    p2 = p1;
    cp2 = cp1;

    // Converting copy assignment operator (from pointer to const_pointer)
    cp1 = p1;

    // Converting copy assignment operator (from const_pointer to pointer)
    // p1 = cp1; // ---> NOT ALLOWED

    // Comparisons
    CHECK(pointer(&val) == pointer(&val));
    CHECK(pointer(&val) == const_pointer(&val));
    CHECK(const_pointer(&val) == pointer(&val));
    CHECK(const_pointer(&val) == const_pointer(&val));
    CHECK(pointer(&val) != const_pointer(&cval));
    CHECK(const_pointer(&cval) != pointer(&val));
    CHECK(const_pointer(&val) != const_pointer(&cval));

    // Unused variables
    (void)p4;
    (void)cp3;
    (void)cp4;
    (void)cp5;
}

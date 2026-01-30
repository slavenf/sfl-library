#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/static_storage.hpp"

#include <type_traits>

using pointer = sfl::dtl::static_storage_pointer<int>;

using const_pointer = sfl::dtl::static_storage_pointer<const int>;

static_assert(std::is_trivially_copyable<pointer>::value, "");

static_assert(std::is_trivially_copyable<const_pointer>::value, "");

static_assert(std::is_same<typename pointer::element_type, int>::value, "");

static_assert(std::is_same<typename const_pointer::element_type, const int>::value, "");

static_assert(std::is_same<typename pointer::value_type, int>::value, "");

static_assert(std::is_same<typename const_pointer::value_type, int>::value, "");

static_assert(std::is_same<typename pointer::pointer, int*>::value, "");

static_assert(std::is_same<typename const_pointer::pointer, const int*>::value, "");

static_assert(std::is_same<typename pointer::reference, int&>::value, "");

static_assert(std::is_same<typename const_pointer::reference, const int&>::value, "");

int main()
{
    sfl::dtl::static_storage_bucket<int> bucket;

    // Default constructor
    pointer p1;
    const_pointer cp1;

    // Construct from pointer
    pointer p2(&bucket);
    const_pointer cp2(&bucket);

    // Copy constructor
    pointer p3(p2);
    const_pointer cp3(cp2);

    // Copy assignment operator
    p2 = p1;
    cp2 = cp1;

    // Converting constructor (from pointer to const_pointer)
    const_pointer cp4(p1);

    // Converting copy assignment operator (from pointer to const_pointer)
    cp1 = p1;

    // Converting constructor (from const_pointer to pointer) - NOT ALLOWED
    // pointer p4(cp1);

    // Copy assignment operator (from const_pointer to pointer) - NOT ALLOWED
    // p1 = cp1;
}

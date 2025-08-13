#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/segmented_iterator.hpp"

#include <type_traits>

using iterator = sfl::dtl::segmented_iterator<int**, int*, 4, false>;

using const_iterator = sfl::dtl::segmented_iterator<int**, int*, 4, true>;

static_assert(std::is_same<typename iterator::pointer, int*>::value, "");

static_assert(std::is_same<typename const_iterator::pointer, const int*>::value, "");

static_assert(std::is_same<typename iterator::reference, int&>::value, "");

static_assert(std::is_same<typename const_iterator::reference, const int&>::value, "");

int main()
{
    int a = 42;
    int* pa = &a;

    // Construct from pointer
    iterator it1(&pa, &a);
    (void)it1;

    // Default constructor
    iterator it2;
    (void)it2;

    // Copy constructor
    iterator it3(it1);
    (void)it3;

    // Copy assignment operator
    it2 = it1;

    // Construct from pointer
    const_iterator cit1(&pa, &a);
    (void)cit1;

    // Default constructor
    const_iterator cit2;
    (void)cit2;

    // Copy constructor
    const_iterator cit3(cit1);
    (void)cit3;

    // Converting constructor (from iterator to const_iterator)
    const_iterator cit4(it1);
    (void)cit4;

    // Copy assignment operator
    cit2 = cit1;

    // Copy assignment operator (from iterator to const_iterator)
    cit2 = it1;
}

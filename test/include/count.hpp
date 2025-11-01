#ifndef SFL_TEST_COUNT_HPP
#define SFL_TEST_COUNT_HPP

#include <sfl/detail/cpp.hpp>

#include <cstddef> // size_t

#define COUNT(container, value) sfl::test::count(container, value)

namespace sfl
{

namespace test
{

template <typename Container, typename T>
SFL_CONSTEXPR_20
std::size_t count(const Container& container, const T& value)
{
    std::size_t n = 0;

    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (*it == value)
        {
            ++n;
        }
    }

    return n;
}

} // namespace test

} // namespace sfl

#endif // SFL_TEST_COUNT_HPP

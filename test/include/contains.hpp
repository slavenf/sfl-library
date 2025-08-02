#ifndef SFL_TEST_CONTAINS_HPP
#define SFL_TEST_CONTAINS_HPP

#define CONTAINS(container, value) sfl::test::contains(container, value)

namespace sfl
{

namespace test
{

template <typename Container, typename T>
bool contains(const Container& container, const T& value)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (*it == value)
        {
            return true;
        }
    }

    return false;
}

} // namespace test

} // namespace sfl

#endif // SFL_TEST_CONTAINS_HPP

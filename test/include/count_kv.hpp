#ifndef SFL_TEST_COUNT_KV_HPP
#define SFL_TEST_COUNT_KV_HPP

#include <cstddef> // size_t

#define COUNT_KV(container, key, value) sfl::test::count_kv(container, key, value)

namespace sfl
{

namespace test
{

template <typename Container, typename Key, typename T>
std::size_t count_kv(const Container& container, const Key& key, const T& value)
{
    std::size_t n = 0;

    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (it->first == key && it->second == value)
        {
            ++n;
        }
    }

    return n;
}

} // namespace test

} // namespace sfl

#endif // SFL_TEST_COUNT_KV_HPP

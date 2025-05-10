#ifndef SFL_TEST_HASH_HPP
#define SFL_TEST_HASH_HPP

#include <cstddef>

namespace sfl
{

namespace test
{

template <typename Key>
struct hash
{
    std::size_t operator()(const Key& key)
    {
        return static_cast<std::size_t>(key);
    }
};

} // namespace test

} // namespace sfl

#endif // SFL_TEST_HASH_HPP

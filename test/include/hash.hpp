#ifndef SFL_TEST_HASH_HPP
#define SFL_TEST_HASH_HPP

#include <sfl/detail/cpp.hpp>

#include <cstddef>

namespace sfl
{

namespace test
{

template <typename Key>
struct hash
{
    SFL_CONSTEXPR_20
    std::size_t operator()(const Key& key) const
    {
        return static_cast<std::size_t>(key);
    }
};

} // namespace test

} // namespace sfl

#endif // SFL_TEST_HASH_HPP

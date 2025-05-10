# sfl::small_unordered_map

## Summary

Defined in header `sfl/small_unordered_map.hpp`:

```
namespace sfl
{
    template < typename Key,
               typename T,
               std::size_t StaticCapacity,
               std::size_t StaticBucketCount = StaticCapacity == 0 ? 0 : sfl::dtl::bit_ceil(StaticCapacity),
               typename Hash = std::hash<Key>,
               typename KeyEqual = std::equal_to<Key>,
               typename Allocator = std::allocator<std::pair<const Key, T>> >
    class small_unordered_map;
}
```

TODO...

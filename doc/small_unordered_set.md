# sfl::small_unordered_set

## Summary

Defined in header `sfl/small_unordered_set.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t StaticCapacity,
               std::size_t StaticBucketCount = StaticCapacity == 0 ? 0 : sfl::dtl::bit_ceil(StaticCapacity),
               typename Hash = std::hash<Key>,
               typename KeyEqual = std::equal_to<Key>,
               typename Allocator = std::allocator<Key> >
    class small_unordered_set;
}
```

TODO...

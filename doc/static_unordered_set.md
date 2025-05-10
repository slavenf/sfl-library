# sfl::static_unordered_set

## Summary

Defined in header `sfl/static_unordered_set.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t StaticCapacity,
               std::size_t StaticBucketCount = sfl::dtl::bit_ceil(StaticCapacity),
               typename Hash = std::hash<Key>,
               typename KeyEqual = std::equal_to<Key> >
    class static_unordered_set;
}
```

TODO...

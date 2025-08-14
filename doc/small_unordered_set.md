# sfl::small_unordered_set

<details>

<summary>Table of Contents</summary>

* [Summary](#summary)
* [Template Parameters](#template-parameters)
* [Public Member Types](#public-member-types)
* [Public Data Members](#public-data-members)
  * [static\_capacity](#static_capacity)
  * [static\_bucket\_count](#static_bucket_count)
* [Public Member Functions](#public-member-functions)
  * [(constructor)](#constructor)
  * [(destructor)](#destructor)
  * [operator=](#operator)
  * [get\_allocator](#get_allocator)
  * [hash\_function](#hash_function)
  * [key\_eq](#key_eq)
  * [begin, cbegin](#begin-cbegin)
  * [end, cend](#end-cend)
  * [empty](#empty)
  * [size](#size)
  * [max\_size](#max_size)
  * [clear](#clear)
  * [emplace](#emplace)
  * [emplace\_hint](#emplace_hint)
  * [insert](#insert)
  * [insert\_range](#insert_range)
  * [erase](#erase)
  * [swap](#swap)
  * [equal\_range](#equal_range)
  * [find](#find)
  * [count](#count)
  * [contains](#contains)
  * [begin, cbegin (bucket interface)](#begin-cbegin-bucket-interface)
  * [end, cend (bucket interface)](#end-cend-bucket-interface)
  * [bucket\_count](#bucket_count)
  * [max\_bucket\_count](#max_bucket_count)
  * [bucket\_size](#bucket_size)
  * [bucket](#bucket)
  * [load\_factor](#load_factor)
  * [max\_load\_factor](#max_load_factor)
  * [rehash](#rehash)
  * [reserve](#reserve)
* [Non-member Functions](#non-member-functions)
  * [operator==](#operator-1)
  * [operator!=](#operator-2)
  * [swap](#swap-1)
  * [erase\_if](#erase_if)

</details>

## Summary

Defined in header `sfl/small_unordered_set.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t StaticCapacity,
               std::size_t StaticBucketCount = /* see description below */,
               typename Hash = std::hash<Key>,
               typename KeyEqual = std::equal_to<Key>,
               typename Allocator = std::allocator<Key> >
    class small_unordered_set;
}
```

`sfl::small_unordered_set` is an associative container similar to [`std::unordered_set`](https://en.cppreference.com/w/cpp/container/unordered_set), but it internally holds a small amount of statically allocated memory to avoid dynamic memory management when the number of stored elements is small. Dynamic memory management is used when the number of elements exceeds `StaticCapacity`, or when the number of buckets exceeds `StaticBucketCount`. This design provides a compact and cache-friendly representation optimized for small sizes.

The underlying storage is implemented as a **hash table** with separate chaining.

The complexity of search, insert, and erase operations is O(1) on average.

References and pointers to elements are stable: insert and erase operations do not invalidate them unless the referenced element is erased.

Iterators to elements are forward iterators, and they meet the requirements of [*LegacyForwardIterator*](https://en.cppreference.com/w/cpp/named_req/ForwardIterator).

`sfl::small_unordered_set` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer), and [*UnorderedAssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer).

<br><br>



## Template Parameters

1.  ```
    typename Key
    ```

    Key type.

2.  ```
    std::size_t StaticCapacity
    ```

    Size of the internal statically allocated array used for elements.

    This parameters can be zero.

3.  ```
    std::size_t StaticBucketCount
    ```

    Size of the internal statically allocated array used for buckets.

    Default value of this parameter is `StaticCapacity` rounded up to the nearest power of two.

    This parameters can be zero.

4.  ```
    typename Hash
    ```

    Hash function for keys.

5.  ```
    typename KeyEqual
    ```

    Comparison function for keys.

6.  ```
    typename Allocator
    ```

    Allocator used for memory allocation/deallocation and construction/destruction of elements.

    This type must meet the requirements of [*Allocator*](https://en.cppreference.com/w/cpp/named_req/Allocator).

    The program is ill-formed if `Allocator::value_type` is not the same as `Key`.

<br><br>



## Public Member Types

| Member Type               | Definition |
| :------------------------ | :--------- |
| `allocator_type`          | `Allocator` |
| `key_type`                | `Key` |
| `value_type`              | `Key` |
| `size_type`               | Unsigned integer type |
| `difference_type`         | Signed integer type |
| `hasher`                  | `Hash` |
| `key_equal`               | `KeyEqual` |
| `reference`               | `value_type&` |
| `const_reference`         | `const value_type&` |
| `pointer`                 | Pointer to `value_type` |
| `const_pointer`           | Pointer to `const value_type` |
| `iterator`                | [*LegacyForwardIterator*](https://en.cppreference.com/w/cpp/named_req/ForwardIterator) to `const value_type` |
| `const_iterator`          | [*LegacyForwardIterator*](https://en.cppreference.com/w/cpp/named_req/ForwardIterator) to `const value_type` |
| `local_iterator`          | [*LegacyForwardIterator*](https://en.cppreference.com/w/cpp/named_req/ForwardIterator) to `const value_type`. This iterator can be used to iterate through a single bucket but not across buckets. |
| `const_local_iterator`    | [*LegacyForwardIterator*](https://en.cppreference.com/w/cpp/named_req/ForwardIterator) to `const value_type`. This iterator can be used to iterate through a single bucket but not across buckets |

<br><br>



## Public Data Members

### static_capacity

1.  ```
    static constexpr size_type static_capacity = StaticCapacity;
    ```

<br><br>



### static_bucket_count

1.  ```
    static constexpr size_type static_bucket_count = StaticBucketCount;
    ```

<br><br>



## Public Member Functions

### (constructor)

1.  ```
    small_unordered_set();
    ```
2.  ```
    explicit
    small_unordered_set(const Allocator& alloc);
    ```
3.  ```
    explicit
    small_unordered_set(size_type bucket_count);
    ```
4.  ```
    small_unordered_set(size_type bucket_count, const Allocator& alloc);
    ```
5.  ```
    small_unordered_set(size_type bucket_count, const Hash& hash);
    ```
6.  ```
    small_unordered_set(size_type bucket_count, const Hash& hash, const Allocator& alloc);
    ```
7.  ```
    small_unordered_set(size_type bucket_count, const Hash& hash, const KeyEqual& equal);
    ```
8.  ```
    small_unordered_set(size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs an empty container.

    Parameter `bucket_count` specifies minimal number of buckets to use on initialization. If it is not specified, an unspecified default value is used.

    **Complexity:**
    Constant.

    <br><br>



9.  ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last);
    ```
10. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count);
    ```
11. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Allocator& alloc);
    ```
12. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash);
    ```
13. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const Allocator& alloc);
    ```
14. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const KeyEqual& equal);
    ```
15. ```
    template <typename InputIt>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the range `[first, last)`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    Parameter `bucket_count` specifies minimal number of buckets to use on initialization. If it is not specified, an unspecified default value is used.

    **Note:**
    These overloads participate in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

    <br><br>



16. ```
    small_unordered_set(std::initializer_list<value_type> ilist);
    ```
17. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count);
    ```
18. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Allocator& alloc);
    ```
19. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash);
    ```
20. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const Allocator& alloc);
    ```
21. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const KeyEqual& equal);
    ```
22. ```
    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the initializer list `ilist`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    Parameter `bucket_count` specifies minimal number of buckets to use on initialization. If it is not specified, an unspecified default value is used.

    <br><br>



23. ```
    small_unordered_set(const small_unordered_set& other);
    ```
24. ```
    small_unordered_set(const small_unordered_set& other, const Allocator& alloc);
    ```

    **Effects:**
    Copy constructor.
    Constructs the container with the copy of the contents of `other`.

    <br><br>



25. ```
    small_unordered_set(small_unordered_set&& other);
    ```
26. ```
    small_unordered_set(small_unordered_set&& other, const Allocator& alloc);
    ```

    **Effects:**
    Move constructor.
    Constructs the container with the contents of `other` using move semantics.

    `other` is not guaranteed to be empty after the move.

    `other` is in a valid but unspecified state after the move.

    <br><br>



27. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range);
    ```
28. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count);
    ```
29. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Allocator& alloc);
    ```
30. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash);
    ```
31. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const Allocator& alloc);
    ```
32. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal);
    ```
33. ```
    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of `range`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    Parameter `bucket_count` specifies minimal number of buckets to use on initialization. If it is not specified, an unspecified default value is used.

    **Note:**
    These overloads are available in C++11. If compiled with C++20 or later, proper C++20 range concepts are used.

    <br><br>



### (destructor)

1.  ```
    ~small_unordered_set();
    ```

    **Effects:**
    Destructs the container. The destructors of the elements are called and the used storage is deallocated.

    **Complexity:**
    Linear in `size()`.

    <br><br>



### operator=

1.  ```
    small_unordered_set& operator=(const small_unordered_set& other);
    ```

    **Effects:**
    Copy assignment operator.
    Replaces the contents with a copy of the contents of `other`.

    **Returns:**
    `*this()`.

    <br><br>



2.  ```
    small_unordered_set& operator=(small_unordered_set&& other);
    ```

    **Effects:**
    Move assignment operator.
    Replaces the contents with those of `other` using move semantics.

    `other` is not guaranteed to be empty after the move.

    `other` is in a valid but unspecified state after the move.

    **Returns:**
    `*this()`.

    <br><br>



3.  ```
    small_unordered_set& operator=(std::initializer_list<value_type> ilist);
    ```

    **Effects:**
    Replaces the contents with those identified by initializer list `ilist`.

    **Returns:**
    `*this()`.

    <br><br>



### get_allocator

1.  ```
    allocator_type get_allocator() const noexcept;
    ```

    **Effects:**
    Returns the allocator associated with the container.

    **Complexity:**
    Constant.

    <br><br>



### hash_function

1.  ```
    hasher hash_function() const;
    ```

    **Effects:**
    Returns the function object that hashes the keys.

    **Complexity:**
    Constant.

    <br><br>



### key_eq

1.  ```
    key_equal key_eq() const;
    ```

    **Effects:**
    Returns a function object that compares keys for equality.

    **Complexity:**
    Constant.

    <br><br>



### begin, cbegin

1.  ```
    iterator begin() noexcept;
    ```
2.  ```
    const_iterator begin() const noexcept;
    ```
3.  ```
    const_iterator cbegin() const noexcept;
    ```

    **Effects:**
    Returns an iterator to the first element of the container.
    If the container is empty, the returned iterator will be equal to `end()`.

    **Complexity:**
    Constant.

    <br><br>



### end, cend

1.  ```
    iterator end() noexcept;
    ```
2.  ```
    const_iterator end() const noexcept;
    ```
3.  ```
    const_iterator cend() const noexcept;
    ```

    **Effects:**
    Returns an iterator to the element following the last element of the container.
    This element acts as a placeholder; attempting to access it results in undefined behavior.

    **Complexity:**
    Constant.

    <br><br>



### empty

1.  ```
    bool empty() const noexcept;
    ```

    **Effects:**
    Returns `true` if the container has no elements, i.e. whether `begin() == end()`.

    **Complexity:**
    Constant.

    <br><br>



### size

1.  ```
    size_type size() const noexcept;
    ```

    **Effects:**
    Returns the number of elements in the container, i.e. `std::distance(begin(), end())`.

    **Complexity:**
    Constant.

    <br><br>



### max_size

1.  ```
    size_type max_size() const noexcept;
    ```

    **Effects:**
    Returns the maximum number of elements the container is able to hold, i.e. `std::distance(begin(), end())` for the largest container.

    **Complexity:**
    Constant.

    <br><br>



### clear

1.  ```
    void clear() noexcept;
    ```

    **Effects:**
    Erases all elements from the container.
    After this call, `size()` returns zero.

    **Complexity:**
    Linear in `size()`.

    <br><br>



### emplace

1.  ```
    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);
    ```

    **Effects:**
    Inserts new element into the container if the container doesn't already contain an element with an equivalent key.

    New element is constructed as `value_type(std::forward<Args>(args)...)`.

    The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

    **Returns:**
    The iterator component points to the inserted element or to the already existing element. The `bool` component is `true` if insertion happened and `false` if it did not.

    <br><br>



### emplace_hint

1.  ```
    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args);
    ```

    **Effects:**
    Inserts new element into the container if the container doesn't already contain an element with an equivalent key.

    New element is constructed as `value_type(std::forward<Args>(args)...)`.

    The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



### insert

1.  ```
    std::pair<iterator, bool> insert(const value_type& value);
    ```

    **Effects:**
    Inserts copy of `value` if the container doesn't already contain an element with an equivalent key.

    **Returns:**
    The iterator component points to the inserted element or to the already existing element. The `bool` component is `true` if insertion happened and `false` if it did not.

    <br><br>



2.  ```
    std::pair<iterator, bool> insert(value_type&& value);
    ```

    **Effects:**
    Inserts `value` using move semantics if the container doesn't already contain an element with an equivalent key.

    **Returns:**
    The iterator component points to the inserted element or to the already existing element. The `bool` component is `true` if insertion happened and `false` if it did not.

    <br><br>



3.  ```
    template <typename K>
    std::pair<iterator, bool> insert(K&& x);
    ```

    **Effects:**
    Inserts new element if the container doesn't already contain an element with a key equivalent to `x`.

    New element is constructed as `value_type(std::forward<K>(x))`.

    **Note:**
    This overload participates in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.

    **Returns:**
    The iterator component points to the inserted element or to the already existing element. The `bool` component is `true` if insertion happened and `false` if it did not.

    <br><br>



4.  ```
    iterator insert(const_iterator hint, const value_type& value);
    ```

    **Effects:**
    Inserts copy of `value` if the container doesn't already contain an element with an equivalent key.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



5.  ```
    iterator insert(const_iterator hint, value_type&& value);
    ```

    **Effects:**
    Inserts `value` using move semantics if the container doesn't already contain an element with an equivalent key.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



6.  ```
    template <typename K>
    iterator insert(const_iterator hint, K&& x);
    ```

    **Effects:**
    Inserts new element if the container doesn't already contain an element with a key equivalent to `x`.

    New element is constructed as `value_type(std::forward<K>(x))`.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Note:**
    This overload participates in overload resolution only if all following conditions are satisfied:
    1. Both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.
    2. `std::is_convertible_v<K&&, iterator>` is `false`.
    3. `std::is_convertible_v<K&&, const_iterator>` is `false`.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



7.  ```
    template <typename InputIt>
    void insert(InputIt first, InputIt last);
    ```

    **Effects:**
    Inserts elements from range `[first, last)` if the container doesn't already contain an element with an equivalent key.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    The call to this function is equivalent to:
    ```
    while (first != last)
    {
        insert(*first);
        ++first;
    }
    ```

    **Note:**
    This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

    <br><br>



8.  ```
    void insert(std::initializer_list<value_type> ilist);
    ```

    **Effects:**
    Inserts elements from initializer list `ilist` if the container doesn't already contain an element with an equivalent key.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    The call to this function is equivalent to `insert(ilist.begin(), ilist.end())`.

    <br><br>



### insert_range

1.  ```
    template <typename Range>
    void insert_range(Range&& range);
    ```

    **Effects:**
    Inserts elements from `range` if the container doesn't already contain an element with an equivalent key.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    **Note:**
    This function is available in C++11. If compiled with C++20 or later, proper C++20 range concepts are used.

    <br><br>



### erase

1.  ```
    iterator erase(iterator pos);
    ```
2.  ```
    iterator erase(const_iterator pos);
    ```

    **Effects:**
    Removes the element at `pos`.

    **Returns:**
    Iterator following the last removed element.

    <br><br>



3.  ```
    iterator erase(const_iterator first, const_iterator last);
    ```

    **Effects:**
    Removes the elements in the range `[first, last)`.

    **Returns:**
    Iterator following the last removed element.

    <br><br>



4.  ```
    size_type erase(const Key& key);
    ```
5.  ```
    template <typename K>
    size_type erase(K&& x);
    ```

    **Effects:**
    Removes the element (if one exists) with the key equivalent to `key` or `x`.

    **Note:**
    Overload (5) participates in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.

    **Returns:**
    Number of elements removed (0 or 1).

    <br><br>



### swap

1.  ```
    void swap(small_unordered_set& other);
    ```

    **Effects:**
    Exchanges the contents of the container with those of `other`.

    <br><br>



### equal_range

1.  ```
    std::pair<iterator, iterator> equal_range(const Key& key);
    ```
2.  ```
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
    ```
3.  ```
    template <typename K>
    std::pair<iterator, iterator> equal_range(const K& x);
    ```
4.  ```
    template <typename K>
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const;
    ```

    **Effects:**
    Returns a range containing all elements with key that compares equivalent to `key` or `x`.
    *   The first iterator in pair points to the first element of range. It is equal to `end()` if no such element is found.
    *   The second iterator in pair points to the one-past-last element of range. It is equal to `end()` is no such element is found.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows these functions to be called without constructing an instance of `Key`.

    **Complexity:**
    Average case linear in number of elements with key that compares equivalent to `key` or `x`. Worst case linear in `size()`.

    <br><br>



### find

1.  ```
    iterator find(const Key& key);
    ```
2.  ```
    const_iterator find(const Key& key) const;
    ```
3.  ```
    template <typename K>
    iterator find(const K& x);
    ```
4.  ```
    template <typename K>
    const_iterator find(const K& x) const;
    ```

    **Effects:**
    Returns an iterator pointing to the element with key equivalent to `key` or `x`. Returns `end()` if no such element is found.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows these functions to be called without constructing an instance of `Key`.

    **Complexity:**
    Constant on average. Worst case linear in `size()`.

    <br><br>



### count

1.  ```
    size_type count(const Key& key) const;
    ```
2.  ```
    template <typename K>
    size_type count(const K& x) const;
    ```

    **Effects:**
    Returns the number of elements with key equivalent to `key` or `x`, which is either 1 or 0 since this container does not allow duplicates.

    **Note:**
    Overload (2) participates in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.

    **Complexity:**
    Constant on average. Worst case linear in `size()`.

    <br><br>



### contains

1.  ```
    bool contains(const Key& key) const;
    ```
2.  ```
    template <typename K>
    bool contains(const K& x) const;
    ```

    **Effects:**
    Returns `true` if the container contains an element with key equivalent to `key` or `x`, otherwise returns `false`.

    **Note:**
    Overload (2) participates in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.

    **Complexity:**
    Constant on average. Worst case linear in `size()`.

    <br><br>



### begin, cbegin (bucket interface)

1.  ```
    local_iterator begin(size_type n) noexcept;
    ```
2.  ```
    const_local_iterator begin(size_type n) const noexcept;
    ```
3.  ```
    const_local_iterator cbegin(size_type n) const noexcept;
    ```

    **Effects:**
    Returns an iterator to the first element of the bucket with index `n`.

    **Complexity:**
    Constant.

    <br><br>



### end, cend (bucket interface)

1.  ```
    local_iterator end(size_type n) noexcept;
    ```
2.  ```
    const_local_iterator end(size_type n) const noexcept;
    ```
3.  ```
    const_local_iterator cend(size_type n) const noexcept;
    ```

    **Effects:**
    Returns an iterator to the element following the last element of the bucket with index `n`.
    This element acts as a placeholder; attempting to access it results in undefined behavior.

    **Complexity:**
    Constant.

    <br><br>



### bucket_count

1.  ```
    size_type bucket_count() const;
    ```

    **Effects:**
    Returns the number of buckets in the container.

    **Complexity:**
    Constant.

    <br><br>



### max_bucket_count

1.  ```
    size_type max_bucket_count() const;
    ```

    **Effects:**
    Returns the maximum number of buckets the container is able to hold due to system or library implementation limitations.

    **Complexity:**
    Constant.

    <br><br>



### bucket_size

1.  ```
    size_type bucket_size(size_type n) const;
    ```

    **Effects:**
    Returns the number of elements in the bucket with index `n`.

    **Complexity:**
    Linear in the size of the bucket `n`.

    <br><br>



### bucket

1.  ```
    size_type bucket(const Key& key) const;
    ```
2.  ```
    template <typename K>
    size_type bucket(const K& x) const;
    ```

    **Effects:**
    Returns the index of the bucket for key equivalent to `key` or `x`.

    **Note:**
    Overload (2) participates in overload resolution only if both `Hash::is_transparent` and `KeyEqual::is_transparent` exist and are valid types. This allows the function to be called without constructing an instance of `Key`.

    **Complexity:**
    Constant.

    <br><br>



### load_factor

1.  ```
    float load_factor() const;
    ```

    **Effects:**
    Returns the average number of elements per bucket, that is, `size()` divided by `bucket_count()`.

    **Complexity:**
    Constant.

    <br><br>



### max_load_factor

1.  ```
    float max_load_factor() const;
    ```

    **Effects:**
    Returns current maximum load factor.

    **Complexity:**
    Constant.

    <br><br>


2.  ```
    void max_load_factor(float mlf);
    ```

    **Effects:**
    Sets the maximum load factor to `mlf`.

    **Complexity:**
    Constant.

    <br><br>



### rehash

1.  ```
    void rehash(size_type count);
    ```

    **Effects:**
    Changes the number of buckets to a value `n` that is not less than `count` and satisfies `n >= size() / max_load_factor()`, then rehashes the container, i.e. puts the elements into appropriate buckets considering that total number of buckets has changed.

    <br><br>



### reserve

1.  ```
    void reserve(size_type count);
    ```

    **Effects:**
    Sets the number of buckets to the number needed to accommodate at least `count` elements without exceeding maximum load factor and rehashes the container, i.e. puts the elements into appropriate buckets considering that total number of buckets has changed. Effectively calls `rehash(std::ceil(count / max_load_factor()))`.

    <br><br>



## Non-member Functions

### operator==

1.  ```
    template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
    bool operator==
    (
        const small_unordered_set<K, N, M, H, E, A>& x,
        const small_unordered_set<K, N, M, H, E, A>& y
    );
    ```

    **Effects:**
    Compares the contents of two containers.

    **Returns:**
    Returns `true` if the contents of the `x` and `y` are equal, `false` otherwise.

    <br><br>



### operator!=

1.  ```
    template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
    bool operator!=
    (
        const small_unordered_set<K, N, M, H, E, A>& x,
        const small_unordered_set<K, N, M, H, E, A>& y
    );
    ```

    **Effects:**
    Compares the contents of two containers.

    **Returns:**
    Returns `true` if the contents of the `x` and `y` are not equal, `false` otherwise.

    <br><br>



### swap

1.  ```
    template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
    void swap
    (
        small_unordered_set<K, N, M, H, E, A>& x,
        small_unordered_set<K, N, M, H, E, A>& y
    );
    ```

    **Effects:**
    Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

    <br><br>



### erase_if

1.  ```
    template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A, typename Predicate>
    typename small_unordered_set<K, N, M, H, E, A>::size_type
        erase_if(small_unordered_set<K, N, M, H, E, A>& c, Predicate pred);
    ```

    **Effects:**
    Erases all elements that satisfy the predicate `pred` from the container.

    `pred` is unary predicate which returns `true` if the element should be removed.

    **Returns:**
    The number of erased elements.

    <br><br>



End of document.

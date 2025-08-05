# sfl::small_unordered_linear_set

<details>

<summary>Table of Contents</summary>

* [Summary](#summary)
* [Template Parameters](#template-parameters)
* [Public Member Types](#public-member-types)
* [Public Data Members](#public-data-members)
  * [static\_capacity](#static_capacity)
* [Public Member Functions](#public-member-functions)
  * [(constructor)](#constructor)
  * [(destructor)](#destructor)
  * [operator=](#operator)
  * [get\_allocator](#get_allocator)
  * [key\_eq](#key_eq)
  * [begin, cbegin](#begin-cbegin)
  * [end, cend](#end-cend)
  * [nth](#nth)
  * [index\_of](#index_of)
  * [empty](#empty)
  * [size](#size)
  * [max\_size](#max_size)
  * [capacity](#capacity)
  * [available](#available)
  * [reserve](#reserve)
  * [shrink\_to\_fit](#shrink_to_fit)
  * [clear](#clear)
  * [emplace](#emplace)
  * [emplace\_hint](#emplace_hint)
  * [insert](#insert)
  * [insert\_range](#insert_range)
  * [erase](#erase)
  * [swap](#swap)
  * [find](#find)
  * [count](#count)
  * [contains](#contains)
  * [data](#data)
* [Non-member Functions](#non-member-functions)
  * [operator==](#operator-1)
  * [operator!=](#operator-2)
  * [swap](#swap-1)
  * [erase\_if](#erase_if)

</details>



## Summary

Defined in header `sfl/small_unordered_linear_set.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t N,
               typename KeyEqual = std::equal_to<Key>,
               typename Allocator = std::allocator<Key> >
    class small_unordered_linear_set;
}
```

`sfl::small_unordered_linear_set` is an unordered associative container that contains an unsorted collection of unique keys. Underlying storage is implemented as an unsorted [`small_vector`](small_vector.md), which internally holds a statically allocated array of size `N` and stores elements in this array until their number exceeds `N`, which avoids dynamic memory allocation and deallocation. Dynamic memory management is used when the number of elements exceeds `N`. This design provides a compact and cache-friendly representation optimized for small sizes.

Complexity of search, insert and remove operations is O(N).

Elements of this container are always stored contiguously in the memory.

Iterators to elements are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::small_unordered_linear_set` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer) and [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer). The requirements of [*UnorderedAssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer) are partionally met (this container doesn't use [*Hash*](https://en.cppreference.com/w/cpp/named_req/Hash)).

<br><br>



## Template Parameters

1.  ```
    typename Key
    ```

    Key type.

2.  ```
    std::size_t N
    ```

    Size of the internal statically allocated array, i.e. the maximal number of elements that can fit into this array.

    This parameter can be zero.

3.  ```
    typename KeyEqual
    ```

    Function for comparing keys.

4.  ```
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
| `key_equal`               | `KeyEqual` |
| `reference`               | `value_type&` |
| `const_reference`         | `const value_type&` |
| `pointer`                 | Pointer to `value_type` |
| `const_pointer`           | Pointer to `const value_type` |
| `iterator`                | [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) and [*LegacyContiguousIterator*](https://en.cppreference.com/w/cpp/named_req/ContiguousIterator) to `const value_type` |
| `const_iterator`          | [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) and [*LegacyContiguousIterator*](https://en.cppreference.com/w/cpp/named_req/ContiguousIterator) to `const value_type` |

<br><br>



## Public Data Members

### static_capacity

```
static constexpr size_type static_capacity = N;
```

<br><br>



## Public Member Functions

### (constructor)

1.  ```
    small_unordered_linear_set() noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    );
    ```
2.  ```
    explicit small_unordered_linear_set(const KeyEqual& equal) noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    );
    ```
3.  ```
    explicit small_unordered_linear_set(const Allocator& alloc) noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    );
    ```
4.  ```
    explicit small_unordered_linear_set(const KeyEqual& equal, const Allocator& alloc) noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    );
    ```

    **Effects:**
    Constructs an empty container.

    <br><br>



5.  ```
    template <typename InputIt>
    small_unordered_linear_set(InputIt first, InputIt last);
    ```
6.  ```
    template <typename InputIt>
    small_unordered_linear_set(InputIt first, InputIt last, const KeyEqual& equal);
    ```
7.  ```
    template <typename InputIt>
    small_unordered_linear_set(InputIt first, InputIt last, const Allocator& alloc);
    ```
8.  ```
    template <typename InputIt>
    small_unordered_linear_set(InputIt first, InputIt last, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the range `[first, last)`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    **Note:**
    This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

    <br><br>



9.  ```
    small_unordered_linear_set(std::initializer_list<value_type> ilist);
    ```
10. ```
    small_unordered_linear_set(std::initializer_list<value_type> ilist, const KeyEqual& equal);
    ```
11. ```
    small_unordered_linear_set(std::initializer_list<value_type> ilist, const Allocator& alloc);
    ```
12. ```
    small_unordered_linear_set(std::initializer_list<value_type> ilist, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the initializer list `ilist`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    <br><br>



13. ```
    small_unordered_linear_set(const small_unordered_linear_set& other);
    ```
14. ```
    small_unordered_linear_set(const small_unordered_linear_set& other, const Allocator& alloc);
    ```

    **Effects:**
    Copy constructor.
    Constructs the container with the copy of the contents of `other`.

    **Complexity:**
    Linear in `other.size()`.

    <br><br>



15. ```
    small_unordered_linear_set(small_unordered_linear_set&& other);
    ```
16. ```
    small_unordered_linear_set(small_unordered_linear_set&& other, const Allocator& alloc);
    ```

    **Effects:**
    Move constructor.
    Constructs the container with the contents of `other` using move semantics.

    `other` is not guaranteed to be empty after the move.

    `other` is in a valid but unspecified state after the move.

    **Complexity:**
    Constant in the best case. Linear in `N` in the worst case.

    <br><br>



17. ```
    template <typename Range>
    small_unordered_linear_set(sfl::from_range_t, Range&& range);
    ```
18. ```
    template <typename Range>
    small_unordered_linear_set(sfl::from_range_t, Range&& range, const KeyEqual& equal);
    ```
19. ```
    template <typename Range>
    small_unordered_linear_set(sfl::from_range_t, Range&& range, const Allocator& alloc);
    ```
20. ```
    template <typename Range>
    small_unordered_linear_set(sfl::from_range_t, Range&& range, const KeyEqual& equal, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of `range`.

    If multiple elements in the range have keys that compare equivalent, then the first element is inserted.

    **Note:**
    It is available in C++11. In C++20 are used proper C++20 range concepts.

    <br><br>



### (destructor)

1.  ```
    ~small_unordered_linear_set();
    ```

    **Effects:**
    Destructs the container. The destructors of the elements are called and the used storage is deallocated.

    **Complexity:**
    Linear in `size()`.

    <br><br>



### operator=

1.  ```
    small_unordered_linear_set& operator=(const small_unordered_linear_set& other);
    ```

    **Effects:**
    Copy assignment operator.
    Replaces the contents with a copy of the contents of `other`.

    **Returns:**
    `*this()`.

    **Complexity:**
    Linear in `this->size()` plus linear in `other.size()`.

    <br><br>



2.  ```
    small_unordered_linear_set& operator=(small_unordered_linear_set&& other);
    ```

    **Effects:**
    Move assignment operator.
    Replaces the contents with those of `other` using move semantics.

    `other` is not guaranteed to be empty after the move.

    `other` is in a valid but unspecified state after the move.

    **Returns:**
    `*this()`.

    **Complexity:**

    * The best case: Linear in `this->size()` plus constant.
    * The worst case: Linear in `this->size()` plus linear in `other.size()`.

    <br><br>



3.  ```
    small_unordered_linear_set& operator=(std::initializer_list<Key> ilist);
    ```

    **Effects:**
    Replaces the contents with those identified by initializer list `ilist`.

    **Returns:**
    `*this()`.

    **Complexity:**
    Linear in `this->size()` plus linear in `ilist.size()`.

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



### key_eq

1.  ```
    key_equal key_eq() const;
    ```

    **Effects:**
    Returns the function object that compares keys for equality, which is a copy of this container's constructor argument `equal`.

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



### nth

1.  ```
    iterator nth(size_type pos) noexcept;
    ```
2.  ```
    const_iterator nth(size_type pos) const noexcept;
    ```

    **Preconditions:**
    `pos <= size()`

    **Effects:**
    Returns an iterator to the element at position `pos`.

    If `pos == size()`, the returned iterator is equal to `end()`.

    **Complexity:**
    Constant.

    <br><br>



### index_of

1.  ```
    size_type index_of(const_iterator pos) const noexcept;
    ```

    **Preconditions:**
    `cbegin() <= pos && pos <= cend()`

    **Effects:**
    Returns position of the element pointed by iterator `pos`, i.e. `std::distance(begin(), pos)`.

    If `pos == end()`, the returned value is equal to `size()`.

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



### capacity

1.  ```
    size_type capacity() const noexcept;
    ```

    **Effects:**
    Returns the number of elements that the container has currently allocated space for.

    **Complexity:**
    Constant.

    <br><br>



### available

1.  ```
    size_type available() const noexcept;
    ```

    **Effects:**
    Returns the number of elements that can be inserted into the container without requiring allocation of additional memory.

    **Complexity:**
    Constant.

    <br><br>



### reserve

1.  ```
    void reserve(size_type new_cap);
    ```

    **Effects:**
    Tries to increase capacity by allocating additional memory.

    If `new_cap > capacity()`, the function allocates memory for new storage of capacity equal to the value of `new_cap`, moves elements from old storage to new storage, and deallocates memory used by old storage. Otherwise, the function does nothing.

    This function does not change size of the container.

    If the capacity is changed, all iterators and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.

    **Complexity:**
    Linear.

    **Exceptions:**

    * `Allocator::allocate` may throw.
    * `T`'s move or copy constructor may throw.

    If an exception is thrown:

    * If type `T` has available `noexcept` move constructor:
        * This function has no effects (strong exception guarantee).
    * Else if type `T` has available copy constructor:
        * This function has no effects (strong exception guarantee).
    * Else if type `T` has available throwing move constructor:
        * Container is changed but in valid state (basic exception guarantee).

    <br><br>



### shrink_to_fit

1.  ```
    void shrink_to_fit();
    ```

    **Effects:**
    Tries to reduce memory usage by freeing unused memory.

    1.  If `size() > N && size() < capacity()`, the function allocates memory for new storage of capacity equal to the value of `size()`, moves elements from old storage to new storage, and deallocates memory used by old storage.

    2.  If `size() <= N && N < capacity()`, the function sets new storage to be internal statically allocated array of capacity `N`, moves elements from old storage to new storage, and deallocates memory used by old storage.

    3.  Otherwise the function does nothing.

    This function does not change size of the container.

    If the capacity is changed, all iterators and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.

    **Complexity:**
    Linear.

    **Exceptions:**

    * `Allocator::allocate` may throw.
    * `T`'s move or copy constructor may throw.

    If an exception is thrown:

    * If type `T` has available `noexcept` move constructor:
        * This function has no effects (strong exception guarantee).
    * Else if type `T` has available copy constructor:
        * This function has no effects (strong exception guarantee).
    * Else if type `T` has available throwing move constructor:
        * Container is changed but in valid state (basic exception guarantee).

    <br><br>



### clear

1.  ```
    void clear() noexcept;
    ```

    **Effects:**
    Erases all elements from the container.
    After this call, `size()` returns zero and `capacity()` remains unchanged.

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

    **Preconditions:**
    `cbegin() <= hint && hint <= cend()`

    **Effects:**
    Inserts new element into the container if the container doesn't already contain an element with an equivalent key.

    New element is constructed as `value_type(std::forward<Args>(args)...)`.

    The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    Iterator `hint` is ignored due to container's underlying storage implementation. This overload exists just to have this container compatible with standard C++ containers as much as possible.

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

    **Note:** This overload participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Returns:**
    The iterator component points to the inserted element or to the already existing element. The `bool` component is `true` if insertion happened and `false` if it did not.

    <br><br>



4.  ```
    iterator insert(const_iterator hint, const value_type& value);
    ```

    **Preconditions:**
    `cbegin() <= hint && hint <= cend()`

    **Effects:**
    Inserts copy of `value` if the container doesn't already contain an element with an equivalent key.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    Iterator `hint` is ignored due to container's underlying storage implementation. This overload exists just to have this container compatible with standard C++ containers as much as possible.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



5.  ```
    iterator insert(const_iterator hint, value_type&& value);
    ```

    **Preconditions:**
    `cbegin() <= hint && hint <= cend()`

    **Effects:**
    Inserts `value` using move semantics if the container doesn't already contain an element with an equivalent key.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    Iterator `hint` is ignored due to container's underlying storage implementation. This overload exists just to have this container compatible with standard C++ containers as much as possible.

    **Returns:**
    Iterator to the inserted element or to the already existing element.

    <br><br>



6.  ```
    template <typename K>
    iterator insert(const_iterator hint, K&& x);
    ```

    **Preconditions:**
    `cbegin() <= hint && hint <= cend()`

    **Effects:**
    Inserts new element if the container doesn't already contain an element with a key equivalent to `x`.

    New element is constructed as `value_type(std::forward<K>(x))`.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    Iterator `hint` is ignored due to container's underlying storage implementation. This overload exists just to have this container compatible with standard C++ containers as much as possible.

    **Note:** This overload participates in overload resolution only if all following conditions are satisfied:
    1. `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.
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
    It is available in C++11. In C++20 are used proper C++20 range concepts.

    <br><br>



### erase

1.  ```
    iterator erase(iterator pos);
    ```
2.  ```
    iterator erase(const_iterator pos);
    ```

    **Preconditions:**
    `cbegin() <= pos && pos < cend()`

    **Effects:**
    Removes the element at `pos`.

    **Returns:**
    Iterator following the last removed element.

    <br><br>



3.  ```
    iterator erase(const_iterator first, const_iterator last);
    ```

    **Preconditions:**
    `cbegin() <= first && first <= last && last <= cend()`

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
    Overload (5) participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Returns:**
    Number of elements removed (0 or 1).

    <br><br>



### swap

1.  ```
    void swap(small_unordered_linear_set& other);
    ```

    **Preconditions:**
    `std::allocator_traits<allocator_type>::propagate_on_container_swap::value || get_allocator() == other.get_allocator()`

    **Effects:**
    Exchanges the contents of the container with those of `other`.

    **Complexity:**
    Constant in the best case. Linear in `this->size()` plus linear in `other.size()` in the worst case.

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
    Overloads (3) and (4) participate in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling these functions without constructing an instance of `Key`.

    **Complexity:**
    Constant in the best case. Linear in `size()` in the worst case.

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
    Overload (2) participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Complexity:**
    Constant in the best case. Linear in `size()` in the worst case.

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
    Overload (2) participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Complexity:**
    Constant in the best case. Linear in `size()` in the worst case.

    <br><br>



### data

1.  ```
    value_type* data() noexcept;
    ```
2.  ```
    const value_type* data() const noexcept;
    ```

    **Effects:**
    Returns pointer to the underlying array serving as element storage. The pointer is such that range `[data(), data() + size())` is always a valid range, even if the container is empty. `data()` is not dereferenceable if the container is empty.

    **Complexity:**
    Constant.

    <br><br>



## Non-member Functions

### operator==

1.  ```
    template <typename K, std::size_t N, typename E, typename A>
    bool operator==
    (
        const small_unordered_linear_set<K, N, E, A>& x,
        const small_unordered_linear_set<K, N, E, A>& y
    );
    ```

    **Effects:**
    Checks if the contents of `x` and `y` are equal.

    The contents of `x` and `y` are equal if the following conditions hold:
    * `x.size() == y.size()`
    * For each element in `x` there is equal element in `y`.

    The comparison is performed by `std::is_permutation`.
    This comparison ignores the container's `KeyEqual` function.

    **Returns:**
    `true` if the contents of the `x` and `y` are equal, `false` otherwise.

    <br><br>



### operator!=

1.  ```
    template <typename K, std::size_t N, typename E, typename A>
    bool operator!=
    (
        const small_unordered_linear_set<K, N, E, A>& x,
        const small_unordered_linear_set<K, N, E, A>& y
    );
    ```

    **Effects:**
    Checks if the contents of `x` and `y` are equal.

    For details see `operator==`.

    **Returns:**
    `true` if the contents of the `x` and `y` are not equal, `false` otherwise.

    <br><br>



### swap

1.  ```
    template <typename K, std::size_t N, typename E, typename A>
    void swap
    (
        small_unordered_linear_set<K, N, E, A>& x,
        small_unordered_linear_set<K, N, E, A>& y
    );
    ```

    **Effects:**
    Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

    <br><br>



### erase_if

1.  ```
    template <typename K, std::size_t N, typename E, typename A, typename Predicate>
    typename small_unordered_linear_set<K, N, E, A>::size_type
        erase_if(small_unordered_linear_set<K, N, E, A>& c, Predicate pred);
    ```

    **Effects:**
    Erases all elements that satisfy the predicate `pred` from the container.

    `pred` is unary predicate which returns `true` if the element should be removed.

    **Returns:**
    The number of erased elements.

    **Complexity:**
    Linear.

    <br><br>



End of document.

# sfl::static_unordered_flat_multimap

<details>

<summary>Table of Contents</summary>

* [Summary](#summary)
* [Template Parameters](#template-parameters)
* [Public Member Types](#public-member-types)
* [Public Data Members](#public-data-members)
* [Public Member Functions](#public-member-functions)
  * [(constructor)](#constructor)
  * [(destructor)](#destructor)
  * [operator=](#operator)
  * [key\_eq](#key_eq)
  * [value\_eq](#value_eq)
  * [begin, cbegin](#begin-cbegin)
  * [end, cend](#end-cend)
  * [nth](#nth)
  * [index\_of](#index_of)
  * [empty](#empty)
  * [full](#full)
  * [size](#size)
  * [max\_size](#max_size)
  * [capacity](#capacity)
  * [available](#available)
  * [clear](#clear)
  * [emplace](#emplace)
  * [emplace\_hint](#emplace_hint)
  * [insert](#insert)
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

Defined in header `sfl/static_unordered_flat_multimap.hpp`:

```
namespace sfl
{
    template < typename Key,
               typename T,
               std::size_t N,
               typename KeyEqual = std::equal_to<Key> >
    class static_unordered_flat_multimap;
}
```

`sfl::static_unordered_flat_multimap` is an associative container similar to [`std::unordered_multimap`](https://en.cppreference.com/w/cpp/container/unordered_multimap), but the capacity is **fixed** and the underlying storage is implemented as an **unsorted vector**.

`sfl::static_unordered_flat_multimap` internally holds statically allocated array of size `N` and stores elements into this array, which avoids dynamic memory allocation and deallocation. This container **never** uses dynamic memory management.

The number of elements in static flat unordered multimap **cannot** be greater than `N`. Attempting to insert more than `N` elements into this container results in **undefined behavior**.

The complexity of insertion or removal of elements is O(1). The complexity of search is O(N).

The elements of `sfl::static_unordered_flat_multimap` are always stored contiguously in the memory.

Iterators to elements of `sfl::static_unordered_flat_multimap` are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::static_unordered_flat_multimap` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container) and [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer). The requirements of [*UnorderedAssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer) are partionally met.

This container is convenient for bare-metal embedded software development.

<br><br>



## Template Parameters

1.  ```
    typename Key
    ```

    Key type.

2.  ```
    typename T
    ```

    Value type.

3.  ```
    std::size_t N
    ```

    Size of the internal statically allocated array, i.e. the maximal number of elements that this container can contain.

4.  ```
    typename KeyEqual
    ```

    Function for comparing keys.

<br><br>



## Public Member Types

```
using key_type         = Key;
using mapped_type      = T;
using value_type       = std::pair<Key, T>;
using size_type        = std::size_t;
using difference_type  = std::ptrdiff_t;
using key_equal        = KeyEqual;
using reference        = value_type&;
using const_reference  = const value_type&;
using pointer          = value_type*;
using const_pointer    = const value_type*;
using iterator         = pointer;
using const_iterator   = const_pointer;

class value_equal
{
public:
    bool operator()(const value_type& x, const value_type& y) const;
};
```

<br><br>



## Public Data Members

```
static constexpr size_type static_capacity = N;
```

<br><br>



## Public Member Functions

### (constructor)

```
static_unordered_flat_multimap() noexcept(std::is_nothrow_default_constructible<KeyEqual>::value)
```
```
explicit static_unordered_flat_multimap(const KeyEqual& equal) noexcept(std::is_nothrow_copy_constructible<KeyEqual>::value)
```

**Effects:**
Constructs an empty container.

<br><br>



```
template <typename InputIt>
static_unordered_flat_multimap(InputIt first, InputIt last);
```
```
template <typename InputIt>
static_unordered_flat_multimap(InputIt first, InputIt last, const KeyEqual& equal);
```

**Preconditions:**
`std::distance(first, last) <= capacity()`

**Effects:**
Constructs an empty container and inserts elements from the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Complexity:**
Linear in `std::distance(first, last)`.

<br><br>



```
static_unordered_flat_multimap(std::initializer_list<value_type> ilist);
```
```
static_unordered_flat_multimap(std::initializer_list<value_type> ilist, const KeyEqual& equal);
```

**Preconditions:**
`ilist.size() <= capacity()`

**Effects:**
Constructs an empty container and inserts elements from the initializer list `ilist`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Complexity:**
Linear in `ilist.size()`.

<br><br>



```
static_unordered_flat_multimap(const static_unordered_flat_multimap& other);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in size.

<br><br>



```
static_unordered_flat_multimap(static_unordered_flat_multimap&& other);
```

**Effects:**
Move constructor.
Constructs the container with the contents of `other` using move semantics.

`other` is not guaranteed to be empty after the move.

`other` is in a valid but unspecified state after the move.

**Complexity:**
Linear in size.

<br><br>



### (destructor)

```
~static_unordered_flat_multimap();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in size.

<br><br>



### operator=

```
static_unordered_flat_multimap& operator=(const static_unordered_flat_multimap& other);
```

**Effects:**
Copy assignment operator.
Replaces the contents with a copy of the contents of `other`.

**Returns:**
`*this()`.

**Complexity:**
Linear in size.

<br><br>



```
static_unordered_flat_multimap& operator=(static_unordered_flat_multimap&& other);
```

**Effects:**
Move assignment operator.
Replaces the contents with those of `other` using move semantics.

`other` is not guaranteed to be empty after the move.

`other` is in a valid but unspecified state after the move.

**Returns:**
`*this()`.

**Complexity:**
Linear in size.

<br><br>



```
static_unordered_flat_multimap& operator=(std::initializer_list<value_type> ilist);
```

**Preconditions:**
`ilist.size() <= capacity()`

**Effects:**
Replaces the contents with those identified by initializer list `ilist`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
`*this()`.

**Complexity:**
Linear in size.

<br><br>



### key_eq

```
key_equal key_eq() const;
```

**Effects:**
Returns the function object that compares keys for equality, which is a copy of this container's constructor argument `equal`.

**Complexity:**
Constant.

<br><br>



### value_eq

```
value_equal value_eq() const;
```

**Effects:**
Returns a function object that compares objects of type `value_type`.

**Complexity:**
Constant.

<br><br>



### begin, cbegin

```
iterator begin() noexcept;
```
```
const_iterator begin() const noexcept;
```
```
const_iterator cbegin() const noexcept;
```

**Effects:**
Returns an iterator to the first element of the container.

If the container is empty, the returned iterator will be equal to `end()`.

**Complexity:**
Constant.

<br><br>



### end, cend

```
iterator end() noexcept;
```
```
const_iterator end() const noexcept;
```
```
const_iterator cend() const noexcept;
```

**Effects:**
Returns an iterator to the element following the last element of the container.

This element acts as a placeholder; attempting to access it results in undefined behavior.

**Complexity:**
Constant.

<br><br>



### nth

```
iterator nth(size_type pos) noexcept;
```
```
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

```
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

```
bool empty() const noexcept;
```

**Effects:**
Returns `true` if the container has no elements, i.e. whether `begin() == end()`.

**Complexity:**
Constant.

<br><br>



### full

```
bool full() const noexcept;
```

**Effects:**
Returns `true` if the container is full, i.e. whether `size() == capacity()`.

**Complexity:**
Constant.

<br><br>



### size

```
size_type size() const noexcept;
```

**Effects:**
Returns the number of elements in the container, i.e. `std::distance(begin(), end())`.

**Complexity:**
Constant.

<br><br>



### max_size

```
static constexpr size_type max_size() const noexcept;
```

**Effects:**
Returns the maximum number of elements the container is able to hold, i.e. returns `N`.

**Complexity:**
Constant.

<br><br>



### capacity

```
static constexpr size_type capacity() const noexcept;
```

**Effects:**
Returns the maximum number of elements the container is able to hold, i.e. returns `N`.

**Complexity:**
Constant.

<br><br>



### available

```
size_type available() const noexcept;
```

**Effects:**
Returns the number of elements that can be inserted into the container, i.e. returns `capacity() - size()`.

**Complexity:**
Constant.

<br><br>



### clear

```
void clear() noexcept;
```

**Effects:**
Erases all elements from the container.
After this call, `size()` returns zero and `capacity()` remains unchanged.

**Complexity:**
Linear in `size()`.

<br><br>



### emplace

```
template <typename... Args>
iterator emplace(Args&&... args);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



### emplace_hint

```
template <typename... Args>
iterator emplace_hint(const_iterator hint, Args&&... args);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



### insert

```
iterator insert(const value_type& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts copy of `value`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(value_type&& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts `value` using move semantics.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
template <typename P>
iterator insert(P&& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<P>(value))`.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator hint, const value_type& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts copy of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator hint, value_type&& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts `value` using move semantics.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
template <typename P>
iterator insert(const_iterator hint, P&& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<P>(value))`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element.

<br><br>



```
template <typename InputIt>
void insert(InputIt first, InputIt last);
```

**Preconditions:**
`std::distance(first, last) <= available()`

**Effects:**
Inserts elements from range `[first, last)`.

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

**Note:**
The behavior is undefined if preconditions are not satisfied.

<br><br>



```
void insert(std::initializer_list<value_type> ilist);
```

**Preconditions:**
`ilist.size() <= available()`

**Effects:**
Inserts elements from initializer list `ilist`.

The call to this function is equivalent to:
```
insert(ilist.begin(), ilist.end());
```

**Note:**
The behavior is undefined if preconditions are not satisfied.

<br><br>



### erase

```
iterator erase(iterator pos);
```
```
iterator erase(const_iterator pos);
```

**Preconditions:**
`cbegin() <= pos && pos < cend()`

**Effects:**
Removes the element at `pos`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator following the last removed element.

<br><br>



```
iterator erase(const_iterator first, const_iterator last);
```

**Preconditions:**
`cbegin() <= first && first <= last && last <= cend()`

**Effects:**
Removes the elements in the range `[first, last)`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator following the last removed element.

<br><br>



```
size_type erase(const Key& key);
```

**Effects:**
Removes all elements with the key equivalent to `key`.

**Returns:**
Number of elements removed.

<br><br>



```
template <typename K>
size_type erase(K&& x);
```

**Effects:**
Removes all elements with key that compares equivalent to the value `x`.

**Note:**
This overload participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Returns:**
Number of elements removed.

<br><br>



### swap

```
void swap(static_unordered_flat_multimap& other);
```

**Effects:**
Exchanges the contents of the container with those of `other`.

**Complexity:**
Linear in size.

<br><br>



### find

```
iterator find(const Key& key);
```
```
const_iterator find(const Key& key) const;
```

**Effects:**
Returns an iterator to an element with key equivalent to `key`, or `end()` if such an element is not found. If there are several elements with key in the container, any of them may be returned.

**Complexity:**
Constant in the best case. Linear in `size()` in the worst case.

<br><br>



```
template <typename K>
iterator find(const K& x);
```
```
template <typename K>
const_iterator find(const K& x) const;
```

**Effects:**
Returns an iterator to an element with key that compares equivalent to `x`, or `end()` if such an element is not found. If there are several elements with key in the container, any of them may be returned.

**Note:**
This overload participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Constant in the best case. Linear in `size()` in the worst case.

<br><br>



### count

```
size_type count(const Key& key) const;
```

**Effects:**
Returns the number of elements with key equivalent to `key`.

**Complexity:**
Linear in `size()`.

<br><br>



```
template <typename K>
size_type count(const K& x) const;
```

**Effects:**
Returns the number of elements with key that compares equivalent to the value `x`.

**Note:**
This overload participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Linear in `size()`.

<br><br>



### contains

```
bool contains(const Key& key) const;
```

**Effects:**
Returns `true` if the container contains an element with key equivalent to `key`, otherwise returns `false`.

**Complexity:**
Constant in the best case. Linear in `size()` in the worst case.

<br><br>



```
template <typename K>
bool contains(const K& x) const;
```

**Effects:**
Returns `true` if the container contains an element with the key that compares equivalent to `x`, otherwise returns `false`.

**Note:**
This overload participates in overload resolution only if `KeyEqual::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Constant in the best case. Linear in `size()` in the worst case.

<br><br>



### data

```
value_type* data() noexcept;
```
```
const value_type* data() const noexcept;
```

**Effects:**
Returns pointer to the underlying array serving as element storage. The pointer is such that range `[data(), data() + size())` is always a valid range, even if the container is empty. `data()` is not dereferenceable if the container is empty.

**Complexity:**
Constant.

<br><br>



## Non-member Functions

### operator==

```
template <typename K, typename T, std::size_t N, typename E>
bool operator==
(
    const static_unordered_flat_multimap<K, T, N, E>& x,
    const static_unordered_flat_multimap<K, T, N, E>& y
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

```
template <typename K, typename T, std::size_t N, typename E>
bool operator!=
(
    const static_unordered_flat_multimap<K, T, N, E>& x,
    const static_unordered_flat_multimap<K, T, N, E>& y
);
```

**Effects:**
Checks if the contents of `x` and `y` are equal.

For details see `operator==`.

**Returns:**
`true` if the contents of the `x` and `y` are not equal, `false` otherwise.

<br><br>



### swap

```
template <typename K, typename T, std::size_t N, typename E>
void swap
(
    static_unordered_flat_multimap<K, T, N, E>& x,
    static_unordered_flat_multimap<K, T, N, E>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase_if

```
template <typename K, typename T, std::size_t N, typename E, typename Predicate>
typename static_unordered_flat_multimap<K, T, N, E>::size_type
    erase_if(static_unordered_flat_multimap<K, T, N, E>& c, Predicate pred);
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

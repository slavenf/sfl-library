# sfl::static_flat_multiset

## Summary

Defined in header `sfl/static_flat_multiset.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t N,
               typename Compare = std::less<Key> >
    class static_flat_multiset;
}
```

`sfl::static_flat_multiset` is an associative container similar to [`std::multiset`](https://en.cppreference.com/w/cpp/container/multiset), but the capacity is **fixed** and the underlying storage is implemented as a **sorted vector**.

`sfl::static_flat_multiset` internally holds statically allocated array of size `N` and stores elements into this array, which avoids dynamic memory allocation and deallocation. This container **never** uses dynamic memory management.

The number of elements in static flat multiset **cannot** be greater than `N`. Attempting to insert more than `N` elements into this container results in **undefined behavior**.

The complexity of insertion or removal of elements is O(N). The complexity of search is O(log N).

The elements of `sfl::static_flat_multiset` are always stored contiguously in the memory.

Iterators to elements of `sfl::static_flat_multiset` are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::static_flat_multiset` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*ReversibleContainer*](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer) and [*AssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer).

This container is convenient for bare-metal embedded software development.

<br><br>



## Template Parameters

1.  ```
    typename Key
    ```

    Key type.

2.  ```
    std::size_t N
    ```

    Size of the internal statically allocated array, i.e. the maximal number of elements that this container can contain.

3.  ```
    typename Compare
    ```

    Ordering function for keys.

<br><br>



## Public Member Types

```
using key_type               = Key;
using value_type             = Key;
using size_type              = std::size_t;
using difference_type        = std::ptrdiff_t;
using key_compare            = Compare;
using value_compare          = Compare;
using reference              = value_type&;
using const_reference        = const value_type&;
using pointer                = value_type*;
using const_pointer          = const value_type*;
using iterator               = const_pointer;
using const_iterator         = const_pointer;
using reverse_iterator       = std::reverse_iterator<iterator>;
using const_reverse_iterator = std::reverse_iterator<const_iterator>;
```

<br><br>



## Public Member Functions

### (constructor)

```
static_flat_multiset() noexcept(std::is_nothrow_default_constructible<Compare>::value)
```
```
explicit static_flat_multiset(const Compare& comp) noexcept(std::is_nothrow_copy_constructible<Compare>::value)
```

**Effects:**
Constructs an empty container.

**Complexity:**
Constant.

<br><br>



```
template <typename InputIt>
static_flat_multiset(InputIt first, InputIt last);
```
```
template <typename InputIt>
static_flat_multiset(InputIt first, InputIt last, const Compare& comp);
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
static_flat_multiset(std::initializer_list<value_type> ilist);
```
```
static_flat_multiset(std::initializer_list<value_type> ilist, const Compare& comp);
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
static_flat_multiset(const static_flat_multiset& other);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in `other.size()`.

<br><br>



```
static_flat_multiset(static_flat_multiset&& other);
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
~static_flat_multiset();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in size.

<br><br>



### operator=

```
static_flat_multiset& operator=(const static_flat_multiset& other);
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
static_flat_multiset& operator=(static_flat_multiset&& other);
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
static_flat_multiset& operator=(std::initializer_list<Key> ilist);
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



### key_comp

```
key_compare key_comp() const;
```

**Effects:**
Returns the function object that compares the keys, which is a copy of this container's constructor argument `comp`.

**Complexity:**
Constant.

<br><br>



### value_comp

```
value_compare value_comp() const;
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



### rbegin, crbegin

```
reverse_iterator rbegin() noexcept;
```
```
const_reverse_iterator rbegin() const noexcept;
```
```
const_reverse_iterator crbegin() const noexcept;
```

**Effects:**
Returns a reverse iterator to the first element of the reversed container.
It corresponds to the last element of the non-reversed container.
If the container is empty, the returned iterator is equal to `rend()`.

**Complexity:**
Constant.

<br><br>



### rend, crend

```
reverse_iterator rend() noexcept;
```
```
const_reverse_iterator rend() const noexcept;
```
```
const_reverse_iterator crend() const noexcept;
```

**Effects:**
Returns a reverse iterator to the element following the last element of the reversed container.
It corresponds to the element preceding the first element of the non-reversed container.
This element acts as a placeholder, attempting to access it results in undefined behavior.

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
size_type max_size() const noexcept;
```

**Effects:**
Returns the maximum number of elements the container is able to hold, i.e. returns `N`.

**Complexity:**
Constant.

<br><br>



### capacity

```
size_type capacity() const noexcept;
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
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Returns:**
Number of elements removed.

<br><br>



### swap

```
void swap(static_flat_multiset& other);
```

**Effects:**
Exchanges the contents of the container with those of `other`.

**Complexity:**
Linear in size.

<br><br>



### lower_bound

```
iterator lower_bound(const Key& key);
```
```
const_iterator lower_bound(const Key& key) const;
```

**Effects:**
Returns an iterator pointing to the first element with key that is not less than `key`, or `end()` if such an element is not found.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
iterator lower_bound(const K& x);
```
```
template <typename K>
const_iterator lower_bound(const K& x) const;
```

**Effects:**
Returns an iterator pointing to the first element with key that compares not less to the value `x`, or `end()` if such an element is not found.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



### upper_bound

```
iterator upper_bound(const Key& key);
```
```
const_iterator upper_bound(const Key& key) const;
```

**Effects:**
Returns an iterator pointing to the first element with key that is greater than `key`, or `end()` if such an element is not found.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
iterator upper_bound(const K& x);
```
```
template <typename K>
const_iterator upper_bound(const K& x) const;
```

**Effects:**
Returns an iterator pointing to the first element with key that compares greater to the value `x`, or `end()` if such an element is not found.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



### equal_range

```
std::pair<iterator, iterator> equal_range(const Key& key);
```
```
std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
```

**Effects:**
Returns a range containing all elements with the key that is equal to `key`:
* The first iterator in pair points to the first element that is not less than `key`, or `end()` if such an element does not exist.
* The second iterator in pair points to the first element that is greater that `key`, or `end()` is such an element does not exist.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
std::pair<iterator, iterator> equal_range(const K& x);
```
```
template <typename K>
std::pair<const_iterator, const_iterator> equal_range(const K& x) const;
```

**Effects:**
Returns a range containing all elements with the key that compares equal to the value `x`:
* The first iterator in pair points to the first element that compares not less to the value `x`, or `end()` if such an element does not exist.
* The second iterator in pair points to the first element that compares greater to the value `x`, or `end()` is such an element does not exist.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

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
Logarithmic in `size()`.

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
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



### count

```
size_type count(const Key& key) const;
```

**Effects:**
Returns the number of elements with key equivalent to `key`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
size_type count(const K& x) const;
```

**Effects:**
Returns the number of elements with key that compares equivalent to the value `x`.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



### contains

```
bool contains(const Key& key) const;
```

**Effects:**
Returns `true` if the container contains an element with key equivalent to `key`, otherwise returns `false`.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
bool contains(const K& x) const;
```

**Effects:**
Returns `true` if the container contains an element with the key that compares equivalent to `x`, otherwise returns `false`.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Complexity:**
Logarithmic in `size()`.

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
template <typename K, std::size_t N, typename C>
bool operator==
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Checks if the contents of `x` and `y` are equal.

The contents of `x` and `y` are equal if the following conditions hold:
* `x.size() == y.size()`
* Each element in `x` compares equal with the element in `y` at the same position.

The comparison is performed by `std::equal`.
This comparison ignores the container's ordering `Compare`.

**Returns:**
Returns `true` if the contents of the `x` and `y` are equal, `false` otherwise.

<br><br>



### operator!=

```
template <typename K, std::size_t N, typename C>
bool operator!=
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Checks if the contents of `x` and `y` are equal.

For details see `operator==`.

**Returns:**
Returns `true` if the contents of the `x` and `y` are not equal, `false` otherwise.

<br><br>



### operator<

```
template <typename K, std::size_t N, typename C>
bool operator<
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.
This comparison ignores the container's ordering `Compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically less than the contents of `y`, `false` otherwise.

<br><br>



### operator>

```
template <typename K, std::size_t N, typename C>
bool operator>
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Compares the contents of lhs and rhs lexicographically.

The comparison is performed by a function `std::lexicographical_compare`.
This comparison ignores the container's ordering `Compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically greater than the contents of `y`, `false` otherwise.

<br><br>



### operator<=

```
template <typename K, std::size_t N, typename C>
bool operator<=
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.
This comparison ignores the container's ordering `Compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically less than or equal to the contents of `y`, `false` otherwise.

<br><br>



### operator>=

```
template <typename K, std::size_t N, typename C>
bool operator>=
(
    const static_flat_multiset<K, N, C>& x,
    const static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.
This comparison ignores the container's ordering `Compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically greater than or equal to the contents of `y`, `false` otherwise.

<br><br>



### swap

```
template <typename K, std::size_t N, typename C>
void swap
(
    static_flat_multiset<K, N, C>& x,
    static_flat_multiset<K, N, C>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase_if

```
template <typename K, std::size_t N, typename C, typename Predicate>
typename static_flat_multiset<K, N, C>::size_type
    erase_if(static_flat_multiset<K, N, C>& c, Predicate pred);
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

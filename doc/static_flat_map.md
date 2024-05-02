# sfl::static_flat_map

## Summary

Defined in header `sfl/static_flat_map.hpp`:

```
namespace sfl
{
    template < typename Key,
               typename T,
               std::size_t N,
               typename Compare = std::less<Key> >
    class static_flat_map;
}
```

`sfl::static_flat_map` is an associative container similar to [`std::map`](https://en.cppreference.com/w/cpp/container/map), but the capacity is **fixed** and the underlying storage is implemented as a **sorted vector**.

`sfl::static_flat_map` internally holds statically allocated array of size `N` and stores elements into this array, which avoids dynamic memory allocation and deallocation. This container **never** uses dynamic memory management.

The number of elements in static flat map **cannot** be greater than `N`. Attempting to insert more than `N` elements into this container results in **undefined behavior**.

The complexity of insertion or removal of elements is O(N). The complexity of search is O(log N).

The elements of `sfl::static_flat_map` are always stored contiguously in the memory.

Iterators to elements of `sfl::static_flat_map` are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::static_flat_map` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*ReversibleContainer*](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer) and [*AssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer).

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
    typename Compare
    ```

    Ordering function for keys.

<br><br>



## Public Member Types

```
using key_type               = Key;
using mapped_type            = T;
using value_type             = std::pair<Key, T>;
using size_type              = std::size_t;
using difference_type        = std::ptrdiff_t;
using key_compare            = Compare;
using reference              = value_type&;
using const_reference        = const value_type&;
using pointer                = value_type*;
using const_pointer          = const value_type*;
using iterator               = pointer;
using const_iterator         = const_pointer;
using reverse_iterator       = std::reverse_iterator<iterator>;
using const_reverse_iterator = std::reverse_iterator<const_iterator>;

class value_compare
{
public:
    bool operator()(const value_type& x, const value_type& y) const;
};
```

<br><br>



## Public Member Functions

### (constructor)

```
static_flat_map() noexcept(std::is_nothrow_default_constructible<Compare>::value);
```
```
explicit static_flat_map(const Compare& comp) noexcept(std::is_nothrow_copy_constructible<Compare>::value);
```

**Effects:**
Constructs an empty container.

**Complexity:**
Constant.

<br><br>



```
template <typename InputIt>
static_flat_map(InputIt first, InputIt last);
```
```
template <typename InputIt>
static_flat_map(InputIt first, InputIt last, const Compare& comp);
```

**Preconditions:**
`std::distance(first, last) <= capacity()`

**Effects:**
Constructs an empty container and inserts elements from the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [`LegacyInputIterator`](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Complexity:**
Linear in `std::distance(first, last)`.

<br><br>



```
static_flat_map(std::initializer_list<value_type> ilist);
```
```
static_flat_map(std::initializer_list<value_type> ilist, const Compare& comp);
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
static_flat_map(const static_flat_map& other);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in size.

<br><br>



```
static_flat_map(static_flat_map&& other);
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
~static_flat_map();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in size.

<br><br>



### operator=

```
static_flat_map& operator=(const static_flat_map& other);
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
static_flat_map& operator=(static_flat_map&& other);
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
static_flat_map& operator=(std::initializer_list<value_type> ilist);
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
std::pair<iterator, bool> emplace(Args&&... args);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

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
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



### insert

```
std::pair<iterator, bool> insert(const value_type& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts copy of `value` only if the container does not already contain an element with an key equivalent to the key of `value`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
std::pair<iterator, bool> insert(value_type&& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts `value` using move semantics only if the container does not already contain an element with an key equivalent to the key of `value`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
template <typename P>
std::pair<iterator, bool> insert(P&& value);
```

**Preconditions:**
`!full()`

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<P>(value))`.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
iterator insert(const_iterator hint, const value_type& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts copy of `value` only if the container does not already contain an element with an key equivalent to the key of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



```
iterator insert(const_iterator hint, value_type&& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts `value` using move semantics only if the container does not already contain an element with an key equivalent to the key of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



```
template <typename P>
iterator insert(const_iterator hint, P&& value);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<P>(value))`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element or to the already existing element.

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
This overload participates in overload resolution only if `InputIt` satisfies requirements of [`LegacyInputIterator`](https://en.cppreference.com/w/cpp/named_req/InputIterator).

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



### insert_or_assign

```
template <typename M>
std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj);
```
```
template <typename M>
std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj);
```

**Preconditions:**
`!full()`

**Effects:**
If a key equivalent to `key` already exists in the container, assigns `std::forward<M>(obj)` to the mapped type corresponding to the key `key`. If the key does not exist, inserts the new element.

* If the first overload is used, the new element is constructed as
  ```
  value_type( std::piecewise_construct,
              std::forward_as_tuple(key),
              std::forward_as_tuple(std::forward<M>(obj)) )
  ```
* If the second overload is used, the new element is constructed as
  ```
  value_type( std::piecewise_construct,
              std::forward_as_tuple(std::move(key)),
              std::forward_as_tuple(std::forward<M>(obj)) )
  ```

**Note:**
This overload participates in overload resolution only if `std::is_assignable_v<mapped_type&, M&&>` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
A pair of iterator and `bool`:
* The iterator component points at the element that was inserted or updated.
* The `bool` component is `true` if the insertion took place and `false` if the assignment took place.

<br><br>



```
template <typename M>
iterator insert_or_assign(const_iterator hint, const Key& key, M&& obj);
```
```
template <typename M>
iterator insert_or_assign(const_iterator hint, Key&& key, M&& obj);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Same as `insert_or_assign` overloads that do not take `hint`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
This overload participates in overload resolution only if `std::is_assignable_v<mapped_type&, M&&>` is `true`.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the element that was inserted or updated.

<br><br>



### try_emplace

```
template <typename... Args>
std::pair<iterator, bool> try_emplace(const Key& key, Args&&... args);
```
```
template <typename... Args>
std::pair<iterator, bool> try_emplace(Key&& key, Args&&... args);
```

**Preconditions:**
`!full()`

**Effects:**
If a key equivalent to `key` already exists in the container, does nothing. Otherwise, behaves like `emplace`.

* If the first overload is used, the new element is constructed as
  ```
  value_type( std::piecewise_construct,
              std::forward_as_tuple(key),
              std::forward_as_tuple(std::forward<Args>(args)...) )
  ```
* If the second overload is used, the new element is constructed as
  ```
  value_type( std::piecewise_construct,
              std::forward_as_tuple(std::move(key)),
              std::forward_as_tuple(std::forward<Args>(args)...) )
  ```

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
A pair of iterator and `bool`:
* The iterator component points at the inserted element or to the already existing element.
* The `bool` component is `true` if insertion happened and `false` if it did not.

<br><br>



```
template <typename... Args>
iterator try_emplace(const_iterator hint, const Key& key, Args&&... args);
```
```
template <typename... Args>
iterator try_emplace(const_iterator hint, Key&& key, Args&&... args);
```

**Preconditions:**
1. `!full()`
2. `cbegin() <= hint && hint <= cend()`

**Effects:**
Same as `try_emplace` overloads that do not take `hint`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
The behavior is undefined if preconditions are not satisfied.

**Returns:**
Iterator to the inserted element or to the already existing element.

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
Removes the element (if one exists) with the key equivalent to `key`.

**Returns:**
Number of elements removed (0 or 1).

<br><br>



```
template <typename K>
size_type erase(K&& x);
```

**Effects:**
Removes the element (if one exists) with key that compares equivalent to the value `x`.

**Note:**
This overload participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

**Returns:**
Number of elements removed (0 or 1).

<br><br>



### swap

```
void swap(static_flat_map& other);
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
Returns an iterator to an element with key equivalent to `key`, or `end()` if such an element is not found.

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
Returns an iterator to an element with key that compares equivalent to `x`, or `end()` if such an element is not found.

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
Returns the number of elements with key equivalent to `key`, which is either 1 or 0 since this container does not allow duplicates.

**Complexity:**
Logarithmic in `size()`.

<br><br>



```
template <typename K>
size_type count(const K& x) const;
```

**Effects:**
Returns the number of elements with key that compares equivalent to `x`, which is either 1 or 0 since this container does not allow duplicates.

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



### at

```
T& at(const Key& key);
```
```
const T& at(const Key& key) const;
```

**Effects:**
Returns a reference to the mapped value of the element with key equivalent to `key`. If no such element exists, an exception of type `std::out_of_range` is thrown.

**Complexity:**
Logarithmic in `size()`.

**Exceptions:**
`std::out_of_range` if the container does not have an element with the specified key.

<br><br>



### operator[]

```
T& operator[](const Key& key);
```
```
T& operator[](Key&& key);
```

**Preconditions:**
`!full()`

**Effects:**
Returns a reference to the value that is mapped to a key equivalent to `key`, performing an insertion if such key does not already exist.

* The first overload is equivalent to:
  ```
  return try_emplace(key).first->second;
  ```
* The second overload is equivalent to:
  ```
  return try_emplace(std::move(key)).first->second;
  ```

**Note:**
The behavior is undefined if preconditions are not satisfied.

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
template <typename K, typename T, std::size_t N, typename C>
bool operator==
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
bool operator!=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
bool operator<
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
bool operator>
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
bool operator<=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
bool operator>=
(
    const static_flat_map<K, T, N, C>& x,
    const static_flat_map<K, T, N, C>& y
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
template <typename K, typename T, std::size_t N, typename C>
void swap
(
    static_flat_map<K, T, N, C>& x,
    static_flat_map<K, T, N, C>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase_if

```
template <typename K, typename T, std::size_t N, typename C, typename Predicate>
typename static_flat_map<K, T, N, C>::size_type
    erase_if(static_flat_map<K, T, N, C>& c, Predicate pred)
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

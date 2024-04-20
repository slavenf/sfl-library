# sfl::small_unordered_flat_multiset

* [Summary](#summary)
* [Template Parameters](#template-parameters)
* [Public Member Types](#public-member-types)
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
  * [erase](#erase)
  * [swap](#swap)
  * [find](#find)
  * [count](#count)
  * [contains](#contains)
  * [data](#data)
* [Non-member Functions](#non-member-functions)
  * [operator==](#operator-1)
  * [operator !=](#operator-)
  * [swap](#swap-1)
  * [erase\_if](#erase_if)

## Summary

Defined in header `sfl/small_unordered_flat_multiset.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t N,
               typename KeyEqual = std::equal_to<Key>,
               typename Allocator = std::allocator<Key> >
    class small_unordered_flat_multiset;
}
```

`sfl::small_unordered_flat_multiset` is an associative container similar to [`std::unordered_multiset`](https://en.cppreference.com/w/cpp/container/unordered_multiset) with the underlying storage implemented as an unsorted vector.

`sfl::small_unordered_flat_multiset` internally holds statically allocated array of size `N` and stores elements into this array until the number of elements is not greater than `N`, which avoids dynamic memory allocation and deallocation. The dynamic memory management is used when the number of elements has to be greater than `N`.

The complexity of insertion or removal of elements is O(1). The complexity of search is O(N).

The elements of `sfl::small_unordered_flat_multiset` are always stored contiguously in the memory.

Iterators to elements of `sfl::small_unordered_flat_multiset` are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::small_unordered_flat_multiset` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer) and [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer). The requirements of [*UnorderedAssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer) are partionally met.

<br><br>



## Template Parameters

1.  ```
    typename Key
    ```

    Key type.

2.  ```
    std::size_t N
    ```

    Size of the internal statically allocated array.
    This parameter can be zero.

3.  ```
    typename KeyEqual
    ```

    Function for comparing keys.

4.  ```
    typename Allocator
    ```

    Allocator used for memory allocation/deallocation and construction/destruction of elements.

    This type must meet the requirements of [`Allocator`](https://en.cppreference.com/w/cpp/named_req/Allocator).

    The program is ill-formed if `Allocator::value_type` is not the same as `Key`.

<br><br>



## Public Member Types

```
using allocator_type   = Allocator;
using allocator_traits = std::allocator_traits<allocator_type>;
using key_type         = Key;
using value_type       = Key;
using size_type        = typename allocator_traits::size_type;
using difference_type  = typename allocator_traits::difference_type;
using key_equal        = KeyEqual;
using reference        = value_type&;
using const_reference  = const value_type&;
using pointer          = typename allocator_traits::pointer;
using const_pointer    = typename allocator_traits::const_pointer;
using iterator         = const_pointer;
using const_iterator   = const_pointer;
```

<br><br>



## Public Member Functions

### (constructor)

```
small_unordered_flat_multiset()
    noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    );
```
```
explicit small_unordered_flat_multiset(const KeyEqual& equal)
    noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    );
```
```
explicit small_unordered_flat_multiset(const Allocator& alloc)
    noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyEqual>::value
    );
```
```
explicit small_unordered_flat_multiset(const KeyEqual& equal, const Allocator& alloc)
    noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyEqual>::value
    );
```

**Effects:**
Constructs an empty container.

<br><br>



```
template <typename InputIt>
small_unordered_flat_multiset(InputIt first, InputIt last);
```
```
template <typename InputIt>
small_unordered_flat_multiset(InputIt first, InputIt last, const KeyEqual& equal);
```
```
template <typename InputIt>
small_unordered_flat_multiset(InputIt first, InputIt last, const Allocator& alloc);
```
```
template <typename InputIt>
small_unordered_flat_multiset(InputIt first, InputIt last, const KeyEqual& equal, const Allocator& alloc);
```

**Effects:**
Constructs an empty container and inserts elements from the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [`LegacyInputIterator`](https://en.cppreference.com/w/cpp/named_req/InputIterator).

<br><br>



```
small_unordered_flat_multiset(std::initializer_list<value_type> ilist);
```
```
small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const KeyEqual& equal);
```
```
small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const Allocator& alloc);
```
```
small_unordered_flat_multiset(std::initializer_list<value_type> ilist, const KeyEqual& equal, const Allocator& alloc);
```

**Effects:**
Constructs an empty container and inserts elements from the initializer list `ilist`.

<br><br>



```
small_unordered_flat_multiset(const small_unordered_flat_multiset& other);
```
```
small_unordered_flat_multiset(const small_unordered_flat_multiset& other, const Allocator& alloc);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in `other.size()`.

<br><br>



```
small_unordered_flat_multiset(small_unordered_flat_multiset&& other);
```
```
small_unordered_flat_multiset(small_unordered_flat_multiset&& other, const Allocator& alloc);
```

**Effects:**
Move constructor.
Constructs the container with the contents of `other` using move semantics.

`other` is not guaranteed to be empty after the move.

`other` is in a valid but unspecified state after the move.

**Complexity:**
Constant in the best case. Linear in `N` in the worst case.

<br><br>



### (destructor)

```
~small_unordered_flat_multiset();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in `size()`.

<br><br>



### operator=

```
small_unordered_flat_multiset& operator=(const small_unordered_flat_multiset& other);
```

**Effects:**
Copy assignment operator.
Replaces the contents with a copy of the contents of `other`.

**Returns:**
`*this()`.

**Complexity:**
Linear in `this->size()` plus linear in `other.size()`.

<br><br>



```
small_unordered_flat_multiset& operator=(small_unordered_flat_multiset&& other);
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



```
small_unordered_flat_multiset& operator=(std::initializer_list<Key> ilist);
```

**Effects:**
Replaces the contents with those identified by initializer list `ilist`.

**Returns:**
`*this()`.

**Complexity:**
Linear in `this->size()` plus linear in `ilist.size()`.

<br><br>



### get_allocator

```
allocator_type get_allocator() const noexcept;
```

**Effects:**
Returns the allocator associated with the container.

**Complexity:**
Constant.

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
Returns the maximum number of elements the container is able to hold, i.e. `std::distance(begin(), end())` for the largest container.

**Complexity:**
Constant.

<br><br>



### capacity

```
size_type capacity() const noexcept;
```

**Effects:**
Returns the number of elements that the container has currently allocated space for.

**Complexity:**
Constant.

<br><br>



### available

```
size_type available() const noexcept;
```

**Effects:**
Returns the number of elements that can be inserted into the container without requiring allocation of additional memory.

**Complexity:**
Constant.

<br><br>



### reserve

```
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

```
void shrink_to_fit();
```

**Effects:**
Tries to reduce memory usage by freeing unused memory.

1. If `size() > N && size() < capacity()`, the function allocates memory for new storage of capacity equal to the value of `size()`, moves elements from old storage to new storage, and deallocates memory used by old storage.
2. If `size() <= N && N < capacity()`, the function sets new storage to be internal statically allocated array of capacity `N`, moves elements from old storage to new storage, and deallocates memory used by old storage.
3. Otherwise the function does nothing.

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

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

**Returns:**
Iterator to the inserted element.

<br><br>



### emplace_hint

```
template <typename... Args>
iterator emplace_hint(const_iterator hint, Args&&... args);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element.

<br><br>



### insert

```
iterator insert(const value_type& value);
```

**Effects:**
Inserts copy of `value`.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(value_type&& value);
```

**Effects:**
Inserts `value` using move semantics.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator hint, const value_type& value);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts copy of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator hint, value_type&& value);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts `value` using move semantics.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element.

<br><br>



```
template <typename InputIt>
void insert(InputIt first, InputIt last);
```

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

<br><br>



```
void insert(std::initializer_list<value_type> ilist);
```

**Effects:**
Inserts elements from initializer list `ilist`.

The call to this function is equivalent to:
```
insert(ilist.begin(), ilist.end());
```

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
void swap(small_unordered_flat_multiset& other);
```

**Preconditions:**
`allocator_traits::propagate_on_container_swap::value || get_allocator() == other.get_allocator()`

**Effects:**
Exchanges the contents of the container with those of `other`.

**Complexity:**
Constant in the best case. Linear in `this->size()` plus linear in `other.size()` in the worst case.

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
template <typename K, std::size_t N, typename E, typename A>
bool operator==
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
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



### operator !=

```
template <typename K, std::size_t N, typename E, typename A>
bool operator!=
(
    const small_unordered_flat_multiset<K, N, E, A>& x,
    const small_unordered_flat_multiset<K, N, E, A>& y
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
template <typename K, std::size_t N, typename E, typename A>
void swap
(
    small_unordered_flat_multiset<K, N, E, A>& x,
    small_unordered_flat_multiset<K, N, E, A>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase_if

```
template <typename K, std::size_t N, typename E, typename A, typename Predicate>
typename small_unordered_flat_multiset<K, N, E, A>::size_type
    erase_if(small_unordered_flat_multiset<K, N, E, A>& c, Predicate pred);
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

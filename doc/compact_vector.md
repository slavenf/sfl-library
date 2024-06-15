# sfl::compact_vector

<details>

<summary>Table of Contents</summary>

* [Summary](#summary)
* [Template Parameters](#template-parameters)
* [Public Member Types](#public-member-types)
* [Public Member Functions](#public-member-functions)
  * [(constructor)](#constructor)
  * [(destructor)](#destructor)
  * [assign](#assign)
  * [operator=](#operator)
  * [get\_allocator](#get_allocator)
  * [begin, cbegin](#begin-cbegin)
  * [end, cend](#end-cend)
  * [rbegin, crbegin](#rbegin-crbegin)
  * [rend, crend](#rend-crend)
  * [nth](#nth)
  * [index\_of](#index_of)
  * [empty](#empty)
  * [size](#size)
  * [max\_size](#max_size)
  * [capacity](#capacity)
  * [available](#available)
  * [at](#at)
  * [operator\[\]](#operator-1)
  * [front](#front)
  * [back](#back)
  * [data](#data)
  * [clear](#clear)
  * [emplace](#emplace)
  * [insert](#insert)
  * [emplace\_back](#emplace_back)
  * [push\_back](#push_back)
  * [pop\_back](#pop_back)
  * [erase](#erase)
  * [resize](#resize)
  * [swap](#swap)
* [Non-member Functions](#non-member-functions)
  * [operator==](#operator-2)
  * [operator!=](#operator-3)
  * [operator\<](#operator-4)
  * [operator\>](#operator-5)
  * [operator\<=](#operator-6)
  * [operator\>=](#operator-7)
  * [swap](#swap-1)
  * [erase](#erase-1)
  * [erase\_if](#erase_if)

</details>



## Summary

Defined in header `sfl/compact_vector.hpp`:

```
namespace sfl
{
    template < typename T,
               typename Allocator = std::allocator<T> >
    class compact_vector;
}
```

`sfl::compact_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) that always has `capacity()` equal to `size()`. Compact vector reallocates storage every time when element is inserted or removed in order to keep capacity and size equal. That means insertions and removals are very inefficient.

This container is inspired by [OpenFOAM's](https://openfoam.org/) container [`List`](https://github.com/OpenFOAM/OpenFOAM-dev/blob/master/src/OpenFOAM/containers/Lists/List/List.H).

`sfl::compact_vector` is **not** specialized for `bool`.

`sfl::compact_vector` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer), [*ReversibleContainer*](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer) and [*SequenceContainer*](https://en.cppreference.com/w/cpp/named_req/SequenceContainer).

<br><br>



## Template Parameters

1.  ```
    typename T
    ```

    The type of the elements.

2.  ```
    typename Allocator
    ```

    Allocator used for memory allocation/deallocation and construction/destruction of elements.

    This type must meet the requirements of [*Allocator*](https://en.cppreference.com/w/cpp/named_req/Allocator).

    The program is ill-formed if `Allocator::value_type` is not the same as `T`.

<br><br>



## Public Member Types

| Member Type               | Definition |
| ------------------------- | ---------- |
| `allocator_type`          | `Allocator` |
| `allocator_traits`        | `std::allocator_traits<Allocator>` |
| `value_type`              | `T` |
| `size_type`               | `typename allocator_traits::size_type` |
| `difference_type`         | `typename allocator_traits::difference_type` |
| `reference`               | `T&` |
| `const_reference`         | `const T&` |
| `pointer`                 | `typename allocator_traits::pointer` |
| `const_pointer`           | `typename allocator_traits::const_pointer` |
| `iterator`                | [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) and [*LegacyContiguousIterator*](https://en.cppreference.com/w/cpp/named_req/ContiguousIterator) to `value_type` |
| `const_iterator`          | [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) and [*LegacyContiguousIterator*](https://en.cppreference.com/w/cpp/named_req/ContiguousIterator) to `const value_type` |
| `reverse_iterator`        | `std::reverse_iterator<iterator>` |
| `const_reverse_iterator`  | `std::reverse_iterator<const_iterator>` |

<br><br>



## Public Member Functions

### (constructor)

```
compact_vector()
    noexcept(std::is_nothrow_default_constructible<Allocator>::value);
```
```
explicit compact_vector(const Allocator& alloc)
    noexcept(std::is_nothrow_copy_constructible<Allocator>::value);
```

**Effects:**
Constructs an empty container.

**Complexity:**
Constant.

<br><br>



```
explicit compact_vector(size_type n);
```
```
explicit compact_vector(size_type n, const Allocator& alloc);
```

**Effects:**
Constructs the container with `n` default-constructed elements.

**Complexity:**
Linear in `n`.

<br><br>



```
compact_vector(size_type n, const T& value);
```
```
compact_vector(size_type n, const T& value, const Allocator& alloc);
```

**Effects:**
Constructs the container with `n` copies of elements with value `value`.

**Complexity:**
Linear in `n`.

<br><br>



```
template <typename InputIt>
compact_vector(InputIt first, InputIt last);
```
```
template <typename InputIt>
compact_vector(InputIt first, InputIt last, const Allocator& alloc);
```

**Effects:**
Constructs the container with the contents of the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Complexity:**
Linear in `std::distance(first, last)`.

<br><br>



```
compact_vector(std::initializer_list<T> ilist);
```
```
compact_vector(std::initializer_list<T> ilist, const Allocator& alloc);
```

**Effects:**
Constructs the container with the contents of the initializer list `ilist`.

**Complexity:**
Linear in `ilist.size()`.

<br><br>



```
compact_vector(const compact_vector& other);
```
```
compact_vector(const compact_vector& other, const Allocator& alloc);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in `other.size()`.

<br><br>



```
compact_vector(compact_vector&& other);
```
```
compact_vector(compact_vector&& other, const Allocator& alloc);
```

**Effects:**
Move constructor.
Constructs the container with the contents of `other` using move semantics.

* First overload:
    * `other` is guaranteed to be empty after the move.
* Second overload:
    * `other` is not guaranteed to be empty after the move.
    * `other` is in a valid but unspecified state after the move.

**Complexity:**
Constant in the best case. Linear in `other.size()` in the worst case.

<br><br>



### (destructor)

```
~compact_vector();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in `size()`.

<br><br>



### assign

```
void assign(size_type n, const T& value);
```

**Effects:**
Replaces the contents of the container with `n` copies of value `value`.

<br><br>



```
template <typename InputIt>
void assign(InputIt first, InputIt last);
```

**Effects:**
Replaces the contents of the container with the contents of the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Note:**
The behavior is undefined if either `first` or `last` is an iterator into `*this`.

<br><br>



```
void assign(std::initializer_list<T> ilist);
```

**Effects:**
Replaces the contents of the container with the contents of the initializer list `ilist`.

<br><br>



### operator=

```
compact_vector& operator=(const compact_vector& other);
```

**Effects:**
Copy assignment operator.
Replaces the contents with a copy of the contents of `other`.

**Returns:**
`*this()`.

<br><br>



```
compact_vector& operator=(compact_vector&& other);
```

**Effects:**
Move assignment operator.
Replaces the contents with those of `other` using move semantics.

`other` is not guaranteed to be empty after the move.

`other` is in a valid but unspecified state after the move.

**Returns:**
`*this()`.

<br><br>



```
compact_vector& operator=(std::initializer_list<T> ilist);
```

**Effects:**
Replaces the contents with those identified by initializer list `ilist`.

**Returns:**
`*this()`.

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

**Note:**
The call to this function is equivalent to `return size();`.
The equality `capacity() == size()` is always `true` for this container.

**Complexity:**
Constant.

<br><br>



### available

```
size_type available() const noexcept;
```

**Effects:**
Returns the number of elements that can be inserted into the container without requiring allocation of additional memory. It always returns zero.

**Complexity:**
Constant.

<br><br>



### at

```
reference at(size_type pos);
```
```
const_reference at(size_type pos) const;
```

**Effects:**
Returns a reference to the element at specified location `pos`, with bounds checking.

**Complexity:**
Constant.

**Exceptions:**
`std::out_of_range` if `pos >= size()`.

<br><br>



### operator[]

```
reference operator[](size_type pos) noexcept;
```
```
const_reference operator[](size_type pos) const noexcept;
```

**Preconditions:**
`pos < size()`

**Effects:**
Returns a reference to the element at specified location pos. No bounds checking is performed.

**Note:**
This operator never inserts a new element into the container.

**Complexity:**
Constant.

<br><br>



### front

```
reference front() noexcept;
```
```
const_reference front() const noexcept;
```

**Preconditions:**
`!empty()`

**Effects:**
Returns a reference to the first element in the container.

**Complexity:**
Constant.

<br><br>



### back

```
reference back() noexcept;
```
```
const_reference back() const noexcept;
```

**Preconditions:**
`!empty()`

**Effects:**
Returns a reference to the last element in the container.

**Complexity:**
Constant.

<br><br>



### data

```
T* data() noexcept;
```
```
const T* data() const noexcept;
```

**Effects:**
Returns pointer to the underlying array serving as element storage. The pointer is such that range `[data(), data() + size())` is always a valid range, even if the container is empty. `data()` is not dereferenceable if the container is empty.

**Complexity:**
Constant.

<br><br>



### clear

```
void clear() noexcept;
```

**Effects:**
Erases all elements from the container.
After this call, both `size()` and `capacity()` return zero.
Remember that equality `capacity() == size()` is always `true` for this container.

**Complexity:**
Linear in `size()`.

<br><br>



### emplace

```
template <typename... Args>
iterator emplace(const_iterator pos, Args&&... args);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts a new element into the container at position `pos`.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

`args...` may directly or indirectly refer to a value in the container.

**Returns:**
Iterator to the inserted element.

<br><br>



### insert

```
iterator insert(const_iterator pos, const T& value);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts copy of `value` at position `pos`.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator pos, T&& value);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts `value` using move semantics at position `pos`.

**Returns:**
Iterator to the inserted element.

<br><br>



```
iterator insert(const_iterator pos, size_type n, const T& value);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts `n` copies of `value` before position `pos`.

**Returns:**
Iterator to the first element inserted, or `pos` if `n == 0`.

<br><br>



```
template <typename InputIt>
iterator insert(const_iterator pos, InputIt first, InputIt last);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts elements from the range `[first, last)` before position `pos`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Note:**
The behavior is undefined if either `first` or `last` is an iterator into `*this`.

**Returns:**
Iterator to the first element inserted, or `pos` if `first == last`.

<br><br>



```
iterator insert(const_iterator pos, std::initializer_list<T> ilist);
```

**Preconditions:**
`cbegin() <= pos && pos <= cend()`

**Effects:**
Inserts elements from initializer list `ilist` before position `pos`.

**Returns:**
Iterator to the first element inserted, or `pos` if `ilist` is empty.

<br><br>



### emplace_back

```
template <typename... Args>
reference emplace_back(Args&&... args);
```

**Effects:**
Inserts a new element at the end of container.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

**Returns:**
Reference to the inserted element.

<br><br>



### push_back

```
void push_back(const T& value);
```

**Effects:**
Inserts copy of `value` at the end of container.

<br><br>



```
void push_back(T&& value);
```

**Effects:**
Inserts `value` using move semantics at the end of container.

<br><br>



### pop_back

```
void pop_back();
```

**Preconditions:**
`!empty()`

**Effects:**
Removes the last element of the container.

<br><br>



### erase

```
iterator erase(const_iterator pos);
```

**Preconditions:**
`cbegin() <= pos && pos < cend()`

**Effects:**
Removes the element at `pos`.

**Returns:**
Iterator following the last removed element.

If `pos` refers to the last element, then the `end()` iterator is returned.

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

If `last == end()` prior to removal, then the updated `end()` iterator is returned.

If `[first, last)` is an empty range, then `last` is returned.

<br><br>



### resize

```
void resize(size_type n);
```

**Effects:**
Resizes the container to contain `n` elements.

1. If the `size() > n`, the last `size() - n` elements are removed.
2. If the `size() < n`, additional default-constructed elements are inserted at the end of container.

<br><br>



```
void resize(size_type n, const T& value);
```

**Effects:**
Resizes the container to contain `n` elements.

1. If the `size() > n`, the last `size() - n` elements are removed.
2. If the `size() < n`, additional copies of `value` are inserted at the end of container.

<br><br>



### swap

```
void swap(compact_vector& other);
```

**Preconditions:**
`allocator_traits::propagate_on_container_swap::value || get_allocator() == other.get_allocator()`

**Effects:**
Exchanges the contents of the container with those of `other`.

**Complexity:**
Constant.

<br><br>



## Non-member Functions

### operator==

```
template <typename T, typename A>
bool operator==
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Checks if the contents of `x` and `y` are equal.

The contents of `x` and `y` are equal if the following conditions hold:
* `x.size() == y.size()`
* Each element in `x` compares equal with the element in `y` at the same position.

**Returns:**
`true` if the contents of the `x` and `y` are equal, `false` otherwise.

**Complexity:**
Constant if `x` and `y` are of different size, otherwise linear in the size of the container.

<br><br>



### operator!=

```
template <typename T, typename A>
bool operator!=
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Checks if the contents of `x` and `y` are equal.

For details see `operator==`.

**Returns:**
`true` if the contents of the `x` and `y` are not equal, `false` otherwise.

**Complexity:**
Constant if `x` and `y` are of different size, otherwise linear in the size of the container.

<br><br>



### operator<

```
template <typename T, typename A>
bool operator<
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically less than the contents of `y`, `false` otherwise.

**Complexity:**
Linear in the size of the container.

<br><br>



### operator>

```
template <typename T, typename A>
bool operator>
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically greater than the contents of `y`, `false` otherwise.

**Complexity:**
Linear in the size of the container.

<br><br>



### operator<=

```
template <typename T, typename A>
bool operator<=
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically less than or equal to the contents of `y`, `false` otherwise.

**Complexity:**
Linear in the size of the container.

<br><br>



### operator>=

```
template <typename T, typename A>
bool operator>=
(
    const compact_vector<T, A>& x,
    const compact_vector<T, A>& y
);
```

**Effects:**
Compares the contents of `x` and `y` lexicographically.
The comparison is performed by a function `std::lexicographical_compare`.

**Returns:**
`true` if the contents of the `x` are lexicographically greater than or equal to the contents of `y`, `false` otherwise.

**Complexity:**
Linear in the size of the container.

<br><br>



### swap

```
template <typename T, typename A>
void swap
(
    compact_vector<T, A>& x,
    compact_vector<T, A>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase

```
template <typename T, typename A, typename U>
typename compact_vector<T, A>::size_type
    erase(compact_vector<T, A>& c, const U& value);
```

**Effects:**
Erases all elements that compare equal to `value` from the container.

**Returns:**
The number of erased elements.

**Complexity:**
Linear.

<br><br>



### erase_if

```
template <typename T, typename A, typename Predicate>
typename compact_vector<T, A>::size_type
    erase_if(compact_vector<T, A>& c, Predicate pred);
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

# sfl::small_flat_map

## Summary

Defined in header `sfl/small_flat_map.hpp`:

```
namespace sfl
{
    template < typename Key,
               typename T,
               std::size_t N,
               typename Compare = std::less<Key>,
               typename Allocator = std::allocator<std::pair<Key, T>> >
    class small_flat_map;
}
```

`sfl::small_flat_map` is an associative container similar to [`std::map`](https://en.cppreference.com/w/cpp/container/map), but the underlying storage is implemented as a **sorted vector**.

`sfl::small_flat_map` internally holds statically allocated array of size `N` and stores elements into this array until the number of elements is not greater than `N`, which avoids dynamic memory allocation and deallocation. The dynamic memory management is used when the number of elements has to be greater than `N`.

The complexity of insertion or removal of elements is O(N). The complexity of search is O(log N).

The elements of `sfl::small_flat_map` are always stored contiguously in the memory.

Iterators to elements of `sfl::small_flat_map` are random access iterators and they meet the requirements of [*LegacyRandomAccessIterator*](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator).

`sfl::small_flat_map` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer), [*ReversibleContainer*](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), [*ContiguousContainer*](https://en.cppreference.com/w/cpp/named_req/ContiguousContainer) and [*AssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer).

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

    Size of the internal statically allocated array.
    This parameter can be zero.

4.  ```
    typename Compare
    ```

    Ordering function for keys.

5.  ```
    typename Allocator
    ```

    Allocator used for memory allocation/deallocation and construction/destruction of elements.

    This type must meet the requirements of [*Allocator*](https://en.cppreference.com/w/cpp/named_req/Allocator).

    The program is ill-formed if `Allocator::value_type` is not the same as `std::pair<Key, T>`.

<br><br>



## Public Member Types

```
using allocator_type         = Allocator;
using allocator_traits       = std::allocator_traits<allocator_type>;
using key_type               = Key;
using mapped_type            = T;
using value_type             = std::pair<Key, T>;
using size_type              = typename allocator_traits::size_type;
using difference_type        = typename allocator_traits::difference_type;
using key_compare            = Compare;
using reference              = value_type&;
using const_reference        = const value_type&;
using pointer                = typename allocator_traits::pointer;
using const_pointer          = typename allocator_traits::const_pointer;
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
small_flat_map()
    noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    );
```
```
explicit small_flat_map(const Compare& comp)
    noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    );
```
```
explicit small_flat_map(const Allocator& alloc)
    noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    );
```
```
explicit small_flat_map(const Compare& comp, const Allocator& alloc)
    noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    );
```

**Effects:**
Constructs an empty container.

**Complexity:**
Constant.

<br><br>



```
template <typename InputIt>
small_flat_map(InputIt first, InputIt last);
```
```
template <typename InputIt>
small_flat_map(InputIt first, InputIt last, const Compare& comp);
```
```
template <typename InputIt>
small_flat_map(InputIt first, InputIt last, const Allocator& alloc);
```
```
template <typename InputIt>
small_flat_map(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc);
```

**Effects:**
Constructs an empty container and inserts elements from the range `[first, last)`.

**Note:**
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

**Complexity:**
Linear in `std::distance(first, last)`.

<br><br>



```
small_flat_map(std::initializer_list<value_type> ilist);
```
```
small_flat_map(std::initializer_list<value_type> ilist, const Compare& comp);
```
```
small_flat_map(std::initializer_list<value_type> ilist, const Allocator& alloc);
```
```
small_flat_map(std::initializer_list<value_type> ilist, const Compare& comp, const Allocator& alloc);
```

**Effects:**
Constructs an empty container and inserts elements from the initializer list `ilist`.

**Complexity:**
Linear in `ilist.size()`.

<br><br>



```
small_flat_map(const small_flat_map& other);
```
```
small_flat_map(const small_flat_map& other, const Allocator& alloc);
```

**Effects:**
Copy constructor.
Constructs the container with the copy of the contents of `other`.

**Complexity:**
Linear in `other.size()`.

<br><br>



```
small_flat_map(small_flat_map&& other);
```
```
small_flat_map(small_flat_map&& other, const Allocator& alloc);
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
~small_flat_map();
```

**Effects:**
Destructs the container. The destructors of the elements are called and the used storage is deallocated.

**Complexity:**
Linear in `size()`.

<br><br>



### operator=

```
small_flat_map& operator=(const small_flat_map& other);
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
small_flat_map& operator=(small_flat_map&& other);
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
small_flat_map& operator=(std::initializer_list<value_type> ilist);
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
std::pair<iterator, bool> emplace(Args&&... args);
```

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



### emplace_hint

```
template <typename... Args>
iterator emplace_hint(const_iterator hint, Args&&... args);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<Args>(args)...)`.

The element may be constructed even if there already is an element with the key in the container, in which case the newly constructed element will be destroyed immediately.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



### insert

```
std::pair<iterator, bool> insert(const value_type& value);
```

**Effects:**
Inserts copy of `value` only if the container does not already contain an element with an key equivalent to the key of `value`.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
std::pair<iterator, bool> insert(value_type&& value);
```

**Effects:**
Inserts `value` using move semantics only if the container does not already contain an element with an key equivalent to the key of `value`.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
template <typename P>
std::pair<iterator, bool> insert(P&& value);
```

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<P>(value))`.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Returns:**
Pair consisting of an iterator to the inserted element, or the already-existing element if no insertion happened, and a `bool` denoting whether the insertion took place (`true` if insertion happened, `false` if it did not).

<br><br>



```
iterator insert(const_iterator hint, const value_type& value);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts copy of `value` only if the container does not already contain an element with an key equivalent to the key of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



```
iterator insert(const_iterator hint, value_type&& value);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts `value` using move semantics only if the container does not already contain an element with an key equivalent to the key of `value`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Returns:**
Iterator to the inserted element or to the already existing element.

<br><br>



```
template <typename P>
iterator insert(const_iterator hint, P&& value);
```

**Preconditions:**
`cbegin() <= hint && hint <= cend()`

**Effects:**
Inserts a new element into the container only if the container does not already contain an element with an equivalent key.

New element is constructed as `value_type(std::forward<P>(value))`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
This overload participates in overload resolution only if `std::is_constructible<value_type, P&&>::value` is `true`.

**Returns:**
Iterator to the inserted element or to the already existing element.

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
This overload participates in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

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



### insert_or_assign

```
template <typename M>
std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj);
```
```
template <typename M>
std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj);
```

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
`cbegin() <= hint && hint <= cend()`

**Effects:**
Same as `insert_or_assign` overloads that do not take `hint`.

Iterator `hint` is used as a suggestion where to start to search insert position.

**Note:**
This overload participates in overload resolution only if `std::is_assignable_v<mapped_type&, M&&>` is `true`.

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
`cbegin() <= hint && hint <= cend()`

**Effects:**
Same as `try_emplace` overloads that do not take `hint`.

Iterator `hint` is used as a suggestion where to start to search insert position.

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
void swap(small_flat_map& other);
```

**Preconditions:**
`allocator_traits::propagate_on_container_swap::value || get_allocator() == other.get_allocator()`

**Effects:**
Exchanges the contents of the container with those of `other`.

**Complexity:**
Constant in the best case. Linear in `this->size()` plus linear in `other.size()` in the worst case.

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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator==
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator!=
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator<
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator>
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator<=
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
bool operator>=
(
    const small_flat_map<K, T, N, C, A>& x,
    const small_flat_map<K, T, N, C, A>& y
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
template <typename K, typename T, std::size_t N, typename C, typename A>
void swap
(
    small_flat_map<K, T, N, C, A>& x,
    small_flat_map<K, T, N, C, A>& y
);
```

**Effects:**
Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

<br><br>



### erase_if

```
template <typename K, typename T, std::size_t N, typename C, typename A, typename Predicate>
typename small_flat_map<K, T, N, C, A>::size_type
    erase_if(small_flat_map<K, T, N, C, A>& c, Predicate pred)
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

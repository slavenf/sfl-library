# sfl::small_multiset

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
  * [key\_comp](#key_comp)
  * [value\_comp](#value_comp)
  * [begin, cbegin](#begin-cbegin)
  * [end, cend](#end-cend)
  * [rbegin, crbegin](#rbegin-crbegin)
  * [rend, crend](#rend-crend)
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
  * [lower\_bound](#lower_bound)
  * [upper\_bound](#upper_bound)
  * [equal\_range](#equal_range)
  * [find](#find)
  * [count](#count)
  * [contains](#contains)
* [Non-member Functions](#non-member-functions)
  * [operator==](#operator-1)
  * [operator!=](#operator-2)
  * [operator\<](#operator-3)
  * [operator\>](#operator-4)
  * [operator\<=](#operator-5)
  * [operator\>=](#operator-6)
  * [swap](#swap-1)
  * [erase\_if](#erase_if)

</details>



## Summary

Defined in header `sfl/small_multiset.hpp`:

```
namespace sfl
{
    template < typename Key,
               std::size_t N,
               typename Compare = std::less<Key>,
               typename Allocator = std::allocator<Key> >
    class small_multiset;
}
```

`sfl::small_multiset` is an associative container similar to [`std::multiset`](https://en.cppreference.com/w/cpp/container/multiset), but it internally holds a small amount of statically allocated memory to avoid dynamic memory management when the number of stored elements is small. Dynamic memory management is used when the number of elements exceeds `N`. This design provides a compact and cache-friendly representation optimized for small sizes.

The underlying storage is implemented as **red-black tree**.

The complexity of search, insert, and remove operations is O(log N).

References and pointers to elements are stable: insert and erase operations do not invalidate them unless the referenced element is erased.

Iterators to elements are bidirectional iterators, and they meet the requirements of [*LegacyBidirectionalIterator*](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator).

`sfl::small_multiset` meets the requirements of [*Container*](https://en.cppreference.com/w/cpp/named_req/Container), [*AllocatorAwareContainer*](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer), [*ReversibleContainer*](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), and [*AssociativeContainer*](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer).

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
    typename Compare
    ```

    Ordering function for keys.

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
| `key_compare`             | `Compare` |
| `value_compare`           | `Compare` |
| `reference`               | `value_type&` |
| `const_reference`         | `const value_type&` |
| `pointer`                 | Pointer to `value_type` |
| `const_pointer`           | Pointer to `const value_type` |
| `iterator`                | [*LegacyBidirectionalIterator*](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator) to `const value_type` |
| `const_iterator`          | [*LegacyBidirectionalIterator*](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator) to `const value_type` |
| `reverse_iterator`        | Reverse [*LegacyBidirectionalIterator*](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator) to `const value_type` |
| `const_reverse_iterator`  | Reverse [*LegacyBidirectionalIterator*](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator) to `const value_type` |

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
    small_multiset() noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    );
    ```
2.  ```
    explicit small_multiset(const Compare& comp) noexcept(
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    );
    ```
3.  ```
    explicit small_multiset(const Allocator& alloc) noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<Compare>::value
    );
    ```
4.  ```
    explicit small_multiset(const Compare& comp, const Allocator& alloc) noexcept(
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<Compare>::value
    );
    ```

    **Effects:**
    Constructs an empty container.

    **Complexity:**
    Constant.

    <br><br>



5.  ```
    template <typename InputIt>
    small_multiset(InputIt first, InputIt last);
    ```
6.  ```
    template <typename InputIt>
    small_multiset(InputIt first, InputIt last, const Compare& comp);
    ```
7.  ```
    template <typename InputIt>
    small_multiset(InputIt first, InputIt last, const Allocator& alloc);
    ```
8.  ```
    template <typename InputIt>
    small_multiset(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the range `[first, last)`.

    **Note:**
    These overloads participate in overload resolution only if `InputIt` satisfies requirements of [*LegacyInputIterator*](https://en.cppreference.com/w/cpp/named_req/InputIterator).

    <br><br>



9.  ```
    small_multiset(std::initializer_list<value_type> ilist);
    ```
10. ```
    small_multiset(std::initializer_list<value_type> ilist, const Compare& comp);
    ```
11. ```
    small_multiset(std::initializer_list<value_type> ilist, const Allocator& alloc);
    ```
12. ```
    small_multiset(std::initializer_list<value_type> ilist, const Compare& comp, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of the initializer list `ilist`.

    <br><br>



13. ```
    small_multiset(const small_multiset& other);
    ```
14. ```
    small_multiset(const small_multiset& other, const Allocator& alloc);
    ```

    **Effects:**
    Copy constructor.
    Constructs the container with the copy of the contents of `other`.

    <br><br>



15. ```
    small_multiset(small_multiset&& other);
    ```
16. ```
    small_multiset(small_multiset&& other, const Allocator& alloc);
    ```

    **Effects:**
    Move constructor.
    Constructs the container with the contents of `other` using move semantics.

    `other` is not guaranteed to be empty after the move.

    `other` is in a valid but unspecified state after the move.

    <br><br>



17. ```
    template <typename Range>
    small_multiset(sfl::from_range_t, Range&& range);
    ```
18. ```
    template <typename Range>
    small_multiset(sfl::from_range_t, Range&& range, const Compare& comp);
    ```
19. ```
    template <typename Range>
    small_multiset(sfl::from_range_t, Range&& range, const Allocator& alloc);
    ```
20. ```
    template <typename Range>
    small_multiset(sfl::from_range_t, Range&& range, const Compare& comp, const Allocator& alloc);
    ```

    **Effects:**
    Constructs the container with the contents of `range`.

    **Note:**
    It is available in C++11. In C++20 are used proper C++20 range concepts.

    <br><br>



### (destructor)

1.  ```
    ~small_multiset();
    ```

    **Effects:**
    Destructs the container. The destructors of the elements are called and the used storage is deallocated.

    **Complexity:**
    Linear in `size()`.

    <br><br>



### operator=

1.  ```
    small_multiset& operator=(const small_multiset& other);
    ```

    **Effects:**
    Copy assignment operator.
    Replaces the contents with a copy of the contents of `other`.

    **Returns:**
    `*this()`.

    <br><br>



2.  ```
    small_multiset& operator=(small_multiset&& other);
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
    small_multiset& operator=(std::initializer_list<Key> ilist);
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



### key_comp

1.  ```
    key_compare key_comp() const;
    ```

    **Effects:**
    Returns the function object that compares the keys, which is a copy of this container's constructor argument `comp`.

    **Complexity:**
    Constant.

    <br><br>



### value_comp

1.  ```
    value_compare value_comp() const;
    ```

    **Effects:**
    Returns a function object that compares objects of type `value_type`.

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



### rbegin, crbegin

1.  ```
    reverse_iterator rbegin() noexcept;
    ```
2.  ```
    const_reverse_iterator rbegin() const noexcept;
    ```
3.  ```
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

1.  ```
    reverse_iterator rend() noexcept;
    ```
2.  ```
    const_reverse_iterator rend() const noexcept;
    ```
3.  ```
    const_reverse_iterator crend() const noexcept;
    ```

    **Effects:**
    Returns a reverse iterator to the element following the last element of the reversed container.
    It corresponds to the element preceding the first element of the non-reversed container.
    This element acts as a placeholder, attempting to access it results in undefined behavior.

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
    After this call, `size()` returns zero and `capacity()` remains unchanged.

    **Complexity:**
    Linear in `size()`.

    <br><br>



### emplace

1.  ```
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

1.  ```
    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args);
    ```

    **Effects:**
    Inserts a new element into the container.

    New element is constructed as `value_type(std::forward<Args>(args)...)`.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element.

    <br><br>



### insert

1.  ```
    iterator insert(const value_type& value);
    ```

    **Effects:**
    Inserts copy of `value`.

    **Returns:**
    Iterator to the inserted element.

    <br><br>


2.  ```
    iterator insert(value_type&& value);
    ```

    **Effects:**
    Inserts `value` using move semantics.

    **Returns:**
    Iterator to the inserted element.

    <br><br>



3.  ```
    iterator insert(const_iterator hint, const value_type& value);
    ```

    **Effects:**
    Inserts copy of `value`.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element.

    <br><br>



4.  ```
    iterator insert(const_iterator hint, value_type&& value);
    ```

    **Effects:**
    Inserts `value` using move semantics.

    Iterator `hint` is used as a suggestion where to start to search insert position.

    **Returns:**
    Iterator to the inserted element.

    <br><br>



5.  ```
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



6.  ```
    void insert(std::initializer_list<value_type> ilist);
    ```

    **Effects:**
    Inserts elements from initializer list `ilist`.

    The call to this function is equivalent to `insert(ilist.begin(), ilist.end())`.

    <br><br>



### insert_range

1.  ```
    template <typename Range>
    void insert_range(Range&& range);
    ```

    **Effects:**
    Inserts elements from `range`.

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
    Removes all elements with the key equivalent to `key` or `x`.

    **Note:**
    Overload (5) participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Returns:**
    Number of elements removed.

    <br><br>



### swap

1.  ```
    void swap(small_multiset& other);
    ```

    **Effects:**
    Exchanges the contents of the container with those of `other`.

    <br><br>



### lower_bound

1.  ```
    iterator lower_bound(const Key& key);
    ```
2.  ```
    const_iterator lower_bound(const Key& key) const;
    ```
3.  ```
    template <typename K>
    iterator lower_bound(const K& x);
    ```
4.  ```
    template <typename K>
    const_iterator lower_bound(const K& x) const;
    ```

    **Effects:**
    Returns an iterator pointing to the first element with key that compares **not less than** `key` or `x`. Returns `end()` if no such element is found.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling these functions without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()`.

    <br><br>



### upper_bound

1.  ```
    iterator upper_bound(const Key& key);
    ```
2.  ```
    const_iterator upper_bound(const Key& key) const;
    ```
3.  ```
    template <typename K>
    iterator upper_bound(const K& x);
    ```
4.  ```
    template <typename K>
    const_iterator upper_bound(const K& x) const;
    ```

    **Effects:**
    Returns an iterator pointing to the first element with key that compares **greater than** `key` or `x`. Returns `end()` if no such element is found.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling these functions without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()`.

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
    *   The first iterator in pair points to the first element that compares **not less than** `key` or `x`. It is equal to `end()` if no such element is found.
    *   The second iterator in pair points to the first element that compares **greater than** `key` or `x`. It is equal to `end()` is no such element is found.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling these functions without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()`.

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
    If there are several elements with key in the container, any of them may be returned.

    **Note:**
    Overloads (3) and (4) participate in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling these functions without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()`.

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
    Returns the number of elements with key equivalent to `key` or `x`.

    **Note:**
    Overload (2) participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()` plus linear in the number of the elements found.

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
    Overload (2) participates in overload resolution only if `Compare::is_transparent` exists and is a valid type. It allows calling this function without constructing an instance of `Key`.

    **Complexity:**
    Logarithmic in `size()`.

    <br><br>



## Non-member Functions

### operator==

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator==
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
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

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator!=
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
    );
    ```

    **Effects:**
    Checks if the contents of `x` and `y` are equal.

    For details see `operator==`.

    **Returns:**
    Returns `true` if the contents of the `x` and `y` are not equal, `false` otherwise.

    <br><br>



### operator<

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator<
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
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

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator>
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
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

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator<=
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
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

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    bool operator>=
    (
        const small_multiset<K, N, C, A>& x,
        const small_multiset<K, N, C, A>& y
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

1.  ```
    template <typename K, std::size_t N, typename C, typename A>
    void swap
    (
        small_multiset<K, N, C, A>& x,
        small_multiset<K, N, C, A>& y
    );
    ```

    **Effects:**
    Swaps the contents of `x` and `y`. Calls `x.swap(y)`.

    <br><br>



### erase_if

1.  ```
    template <typename K, std::size_t N, typename C, typename A, typename Predicate>
    typename small_multiset<K, N, C, A>::size_type
        erase_if(small_multiset<K, N, C, A>& c, Predicate pred);
    ```

    **Effects:**
    Erases all elements that satisfy the predicate `pred` from the container.

    `pred` is unary predicate which returns `true` if the element should be removed.

    **Returns:**
    The number of erased elements.

    <br><br>



End of document.

# New

* Iterators are now distinct types for all containers.
  Iterators are no more aliases for `pointer` and `const_pointer`.

  Now it is possible to overload functions for different iterators, for example:

      void test(const T*);
      void test(sfl::compact_vector<T>::const_iterator);
      void test(sfl::small_vector<T, 10>::const_iterator);
      void test(sfl::small_vector<T, 20>::const_iterator);
      void test(sfl::small_flat_set<T, 10>::const_iterator);
      void test(sfl::small_flat_set<T, 20>::const_iterator);
      void test(sfl::static_unordered_flat_set<T, 10>::const_iterator);
      void test(sfl::static_unordered_flat_set<T, 20>::const_iterator);

  The above example cannot be compiled with older versions of this library
  because iterators are just aliases to pointers and all overloads are
  equivalent to the overload for `const T*`.

* Static flat map: Added heterogeneous `at`.
* Static unordered flat map: Added heterogeneous `at`.


# 1.6.0 (2024-06-04)

* Segmented vector and devector: Added public data member `segment_capacity`.
* All small and static containers: Added public data member `static_capacity`.
* All static containers: Public member functions `max_size` and `capacity` are `constexpr` now.



# 1.5.0 (2024-05-08)

* New containers:
  - `static_flat_map`.
  - `static_flat_set`.
  - `static_flat_multimap`.
  - `static_flat_multiset`.
  - `static_unordered_flat_map`.
  - `static_unordered_flat_set`.
  - `static_unordered_flat_multimap`.
  - `static_unordered_flat_multiset`.
* All small containers: Using anonymous union for internal storage. The effect
  is the same as before, but the code is more readable and it is consistent with
  static containers.
* Small flat map: Refactored `insert_exactly_at`.
* Small flat map: Fixed memory leak in `insert_exactly_at` if exception is thrown.
* Small flat map: Refactored `erase`.
* Small flat set: Refactored `insert_exactly_at`.
* Small flat set: Fixed memory leak in `insert_exactly_at` if exception is thrown.
* Small flat set: Refactored `erase`.
* Small flat multimap: Refactored `insert_exactly_at`.
* Small flat multimap: Fixed memory leak in `insert_exactly_at` if exception is thrown.
* Small flat multimap: Refactored `erase`.
* Small flat multiset: Refactored `insert_exactly_at`.
* Small flat multiset: Fixed memory leak in `insert_exactly_at` if exception is thrown.
* Small flat multiset: Refactored `erase`.
* Small unordered flat map: Removed `insert_unordered` and added `emplace_back`
* Small unordered flat set: Removed `insert_unordered` and added `emplace_back`
* Small unordered flat multimap: Removed `insert_unordered` and added `emplace_back`
* Small unordered flat multiset: Removed `insert_unordered` and added `emplace_back`
* Static vector: Refactored copy constructor.
* Static vector: Refactored move constructor.
* Static vector: Refactored copy assignment operator.
* Static vector: Refactored move assignment operator.
* Static vector: Refactored `emplace`.



# 1.4.0 (2024-04-14)

* New container `static_vector`.
* Compact vector: Improved tests for `assign`.
* Compact vector: Improved tests for `resize`.
* Segmented devector: Refactored member function `emplace`.
* Segmented devector: Refactored private member function `insert_fill_n`.
* Segmented devector: Refactored private member function `insert_range`.
* Segmented devector: Improved tests for `assign`.
* Segmented devector: Improved tests for `resize`.
* Segmented devector: Improved tests for `resize_front`.
* Segmented devector: Improved tests for `resize_back`.
* Segmented vector: Refactored member function `resize`.
* Segmented vector: Refactored private member function `insert_fill_n`.
* Segmented vector: Refactored private member function `insert_range`.
* Segmented vector: Improved tests for `assign`.
* Segmented vector: Improved tests for `emplace_back`.
* Segmented vector: Improved tests for `emplace`.
* Small vector: Refactored member function `emplace`.
* Small vector: Refactored member function `erase`.
* Small vector: Refactored private member function `assign_fill_n`.
* Small vector: Refactored private member function `assign_range`.
* Small vector: Refactored private member function `insert_fill_n`.
* Small vector: Refactored private member function `insert_range`.
* Small vector: Improved tests for `assign`.
* Small vector: Improved tests for `resize`.



# 1.3.1 (2024-03-20)

* Bug fix: If iterator is segmented iterator but not random access iterator then
  compiler must select the most basic algorithm (that is not specialized for
  segmented iterators).



# 1.3.0 (2024-03-16)

* New container `segmented_devector` (segmented double-ended vector).
* All containers: Added member function `available`.
* All containers: Moved common private functions into new header `private.hpp`.
* Implemented custom hierarchical algorithms `copy`, `move`, `fill`, etc. in
  header `private.hpp` that are aware of segmented iterators.
* All containers: Use algorithms from header `private.hpp` whenever possible.
* Segmented vector: Significantly improved performances by using algorithms
  from header `private.hpp`.
* Segmented vector: Reworked member function `emplace`.
* Segmented vector: Reworked member function `emplace_back`.
* Segmented vector: Reworked member function `resize`.
* Segmented vector: Reworked private member function `grow_storage`.
* Segmented vector: Reworked private member function `shrink_storage`.
* Segmented vector: Reworked private member function `assign_fill_n`.
* Segmented vector: Reworked private member function `assign_range`.
* Segmented vector: Reworked private member function `insert_fill_n`.
* Segmented vector: Reworked private member function `insert_range`.
* Segmented vector: Various small improvements (added comments, added `const`
  qualifiers, renamed function and variables, use `std::addressof` and other
  minor changes that make code more readable).
* Segmented vector: Added missing tests for `reserve` and `shrink_to_fit`.
* Segmented vector: Improved tests for `resize`.
* Small vector: Renamed variables and exchanged first and second case in
  member function `resize` for better readability.
* All containers: Use `sfl::dtl::enable_if_t` instead of `std::enable_if`
  for better readability.
* All containers: Use SFINAE instead of iterator tag dispatching to select the
  most appropriate private member functions `initialize_range`, `assign_range`,
  `insert_range` and similar.



# 1.2.4 (2024-02-13)

* Refactoring insert functions in small maps and sets. Removed duplicated code.
  Added private member function for checking `hint` iterator.
* Removed private nested class `temporary_value` from all containers.
  That class was actually was unnecessary. Just use `value_type` instead of.
* Reworked move assignment operator of `segmented_vector`. Old move assignment
  operator had unusual behavior: in some situations it behaved like `swap`.
* Reworked and improved all tests.
* Added GNU makefiles for test for GCC/Clang and Visual C++ compilers.
* Reworked scripts for testing on Arch Linux and CentOS 7.
* Added script for testing on Windows.
* Reworked and improved `erase(iterator)` and `erase(iterator, iterator)`
  member functions.
* Added GitHub actions for automated testing.
* Added CMake support. Thanks to @ZehMatt and @johannes-wolf.



# 1.2.3 (2023-08-14)

* Refactoring - inheritance. Containers no longer inherit directly from
  `Allocator`, `Compare` or `KeyEqual`. This solves some rare and obscure
  problems and errors (for example, `Allocator` with `virtual` member
  function that has the same name as container's member function).
  Every container from now has private member class `data` that contains
  pointers and inherits directly from `Allocator`, `Compare` or `KeyEqual`.
  Empty base optimization is also used in this case.



# 1.2.2 (2023-08-07)

* New test script. Added test scripts for CentOS 7 and Arch Linux to test all
  possible combinations of compiler flags.
* Converted detailed documentation from AsciiDoc to Markdown format. Markdown
  is simpler and easier to read and maintain.
* Updated README file.
* Converted CHANGELOG file to Markdown format.



# 1.2.1 (2023-02-23)

* Reorganized tests.
* Updated README file.



# 1.2.0 (2022-06-29)

* New container `segmented_vector`.
* Move constructors and move assignment operators no longer implicitly call
  `other.clear()`. This behavior applies to ALL containers.
  In other words, `other` is not guaranteed to be empty after the move.
  `other` is in a valid but unspecified state after the move.
* Bug fix: `small_vector` constructor taking only size is no longer `explicit`.
* Improved common functions and macros (`constexpr`, `noexcept`, all calls to
  functions in `SFL_DTL` namespace are fully qualified).
* Improved allocators for tests.



# 1.1.0 (2022-05-11)

* Added option to avoid exception handling. If `SFL_NO_EXCEPTIONS` is defined,
  the library avoids using try/catch/throw statements. In case of error
  `std::abort` is called.
* Internal changes: Removed macro `SFL_UNUSED`. Added function `ignore_unused`.
  Added macro `SFL_CONSTEXPR_14`.



# 1.0.1 (2022-03-24)

* Fixed compile error regarding function `to_pointer` when C++20 is used.
  Call to `to_address` must be fully qualified, i.e. `SFL_DTL::to_address`.
  If call is not fully qualified then compiler somehow cannot decide between
  `std::to_address` and `SFL_DTL::to_address`.
* Improved tests. Testing with different allocators. Several allocators are
  designed specially for tests. One of allocators uses fancy pointers.



# 1.0.0 (2022-03-17)

* Fancy pointers revisited. Using pointer traits `to_address` and `to_pointer`.
* Started semantic versioning (see https://semver.org).
* Added file VERSION.txt.



# 2022-03-13-1

* `static_assert` must have message in C++11.



# 2022-03-13

* Added pointer trait `to_address`. Added support for fancy pointers.
* Updating tests.
* Added file CHANGELOG.txt.



# 2022-02-24

* Fixed `swap` member functions. Old member functions could create memory leaks
  in case of exceptions.

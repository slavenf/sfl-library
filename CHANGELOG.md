# Next Release

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
  member functions of `segmented_vector`, `small_vector` and `small_flat_XXX`.



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

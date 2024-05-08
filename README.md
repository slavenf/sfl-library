# sfl library

This is header-only C++11 library that offers several new or less-known containers:

  * [`small_vector`](doc/small_vector.md)
    * A sequence container similar to `std::vector` that internally holds small amount of statically allocated memory to avoid dynamic memory management if the number of stored elements is small.
  * [`small_flat_set`](doc/small_flat_set.md)
  * [`small_flat_map`](doc/small_flat_map.md)
  * [`small_flat_multiset`](doc/small_flat_multiset.md)
  * [`small_flat_multimap`](doc/small_flat_multimap.md)
  * [`small_unordered_flat_set`](doc/small_unordered_flat_set.md)
  * [`small_unordered_flat_map`](doc/small_unordered_flat_map.md)
  * [`small_unordered_flat_multiset`](doc/small_unordered_flat_multiset.md)
  * [`small_unordered_flat_multimap`](doc/small_unordered_flat_multimap.md)
    * An associative containers that internally hold small amount of statically allocated memory to avoid dynamic memory management if the number of stored elements is small.
  * [`static_vector`](doc/static_vector.md)
    * A sequence container similar to `std::vector` with fixed capacity. Storage is statically allocated. Dynamic memory management is never used. Convenient for bare-metal embedded software development.
  * [`static_flat_set`](doc/static_flat_set.md)
  * [`static_flat_map`](doc/static_flat_map.md)
  * [`static_flat_multiset`](doc/static_flat_multiset.md)
  * [`static_flat_multimap`](doc/static_flat_multimap.md)
  * [`static_unordered_flat_set`](doc/static_unordered_flat_set.md)
  * [`static_unordered_flat_map`](doc/static_unordered_flat_map.md)
  * [`static_unordered_flat_multiset`](doc/static_unordered_flat_multiset.md)
  * [`static_unordered_flat_multimap`](doc/static_unordered_flat_multimap.md)
    * An associative containers with fixed capacity. Storage is statically allocated. Dynamic memory management is never used. Convenient for bare-metal embedded software development.
  * [`compact_vector`](doc/compact_vector.md)
    * A sequence container similar to `std::vector` that always has `capacity()` equal to `size()`.
  * [`segmented_vector`](doc/segmented_vector.md)
    * A sequence container similar to `std::vector` with segmented storage that allows fast insertion and deletion at its end.
  * [`segmented_devector`](doc/segmented_devector.md)
    * A sequence container similar to `std::deque` with segmented storage that allows fast insertion and deletion at both its beginning and its end.



# Requirements

This library requires C++11 compiler or newer.

If available, the library uses the features of the newer C++ standards.

Tested compilers:
* GCC 4.8.5 on CentOS 7 (C++11)
* Clang 3.4.2 on CentOS 7 (C++11)
* GCC 13.2.1 on Arch Linux (C++11, 14, 17, 20, 23)
* Clang 17.0.6 on Arch Linux (C++11, 14, 17, 20, 23)
* MSVC 19.38 (C++14, 17, 20, latest)



# Installation and usage

## Method 1: Manual copy-paste

Copy subdirectory `sfl` from directory `include` into your project directory and `#include` what you need.

## Method 2: CMake integration

This library can be integrated into CMake project using CMake module [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html).

**Step 1:** Add the following lines into your `CMakeLists.txt`:

```
include(FetchContent)

FetchContent_Declare(
    sfl
    GIT_REPOSITORY https://github.com/slavenf/sfl-library)

FetchContent_MakeAvailable(sfl)
```

**Step 2:** Add this library as a dependency to your executable or library:

```
target_link_libraries(your_target_name PRIVATE sfl)
```

**Step 3:** `#include` what you need.



# Exceptions

This library by default throw exceptions in case of error.

If macro `SFL_NO_EXCEPTIONS` is defined then library avoids using exceptions and calls `std::abort` in case of error.

This library does not automatically detect whether the compiler is invoked with appropriate flag or not, like `-fno-exceptions` in GCC and Clang.



# Debugging

This library extensively uses macro `assert` from header `<cassert>`.

The definition of the macro `assert` depends on another macro, `NDEBUG`, which is not defined by the standard library.

If macro `NDEBUG` is defined then `assert` does nothing.

If macro `NDEBUG` is not defined then `assert` performs check. If check fails, `assert` outputs implementation-specific diagnostic information on the standard error output and calls `std::abort`.



# Detailed documentation

The detailed documentation is located in directory `doc`. The detailed documentation is handwritten in Markdown format, it is not automatically generated with tools like Doxygen, so there may be some errors or mistakes. If you find one, please report it.



# Tests

Test programs and scripts are located in directory `test`.

Tested compilers are listed in section [Requirements](#requirements).

Each test program is checked with Valgrind tool.



# License

Licensed under zlib license. The license text is in file [`LICENSE.txt`](LICENSE.txt).

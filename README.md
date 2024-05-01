# sfl library

This is header-only C++11 library that offers several new containers:

  * [`small_vector`](doc/small_vector.md)
  * [`small_flat_set`](doc/small_flat_set.md)
  * [`small_flat_map`](doc/small_flat_map.md)
  * [`small_flat_multiset`](doc/small_flat_multiset.md)
  * [`small_flat_multimap`](doc/small_flat_multimap.md)
  * [`small_unordered_flat_set`](doc/small_unordered_flat_set.md)
  * [`small_unordered_flat_map`](doc/small_unordered_flat_map.md)
  * [`small_unordered_flat_multiset`](doc/small_unordered_flat_multiset.md)
  * [`small_unordered_flat_multimap`](doc/small_unordered_flat_multimap.md)
  * [`static_vector`](doc/static_vector.md)
  * [`compact_vector`](doc/compact_vector.md)
  * [`segmented_vector`](doc/segmented_vector.md)
  * [`segmented_devector`](doc/segmented_devector.md)

All containers are defined in namespace `sfl`.

## About small vector

`sfl::small_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) that internally holds statically allocated array of size `N` and stores elements into this array until the number of elements is not greater than `N`, which avoids dynamic memory allocation and deallocation. The dynamic memory management is used when the number of elements has to be greater than `N`. Size `N` is is specified at the compile time as a template parameter.

## About small flat maps and sets

Small flat maps and sets from namespace `sfl` are associative containers similar to standard maps and sets, but with the storage model identical to the storage model of `sfl::small_vector`, i.e. all of them internally hold statically allocated array of size `N` and store elements into this array until the number of elements is not greater than `N`. Elements of these containers are **always** stored contiguously into the memory.

## About static vector

`sfl::static_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) that internally holds statically allocated array of size `N` and stores elements into this array, which avoids dynamic memory allocation and deallocation. This container **never** uses dynamic memory management and the number of elements **cannot** be greater than `N`. Size `N` is specified at the compile time as a template parameter.

## About compact vector

`sfl::compact_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) that always has `capacity()` equal to `size()`. Compact vector reallocates storage every time when element is inserted or removed in order to keep capacity and size equal. That means insertions and removals are very inefficient.

This container is inspired by [OpenFOAM's](https://openfoam.org/) container [`List`](https://github.com/OpenFOAM/OpenFOAM-dev/blob/master/src/OpenFOAM/containers/Lists/List/List.H).

## About segmented vector

`sfl::segmented_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) that allows fast insertion at its end. The storage of segmented vector consists of a sequence of individually allocated arrays of size `N` which are referred to as *segments*. Size `N` is specified at the compile time as a template parameter.

## About segmented double-ended vector

`sfl::segmented_devector` is a sequence container similar to [`std::deque`](https://en.cppreference.com/w/cpp/container/deque) that allows fast insertion and deletion at both its beginning and its end. The storage of segmented double-ended vector consists of a sequence of individually allocated arrays of size `N` which are referred to as *segments*. Size `N` is specified at the compile time as a template parameter.



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

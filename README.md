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
  * [`compact_vector`](doc/compact_vector.md)
  * [`segmented_vector`](doc/segmented_vector.md)

All containers are defined in namespace `sfl`.



## About small vector

`sfl::small_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector), but with the different storage model.

`sfl::small_vector` holds statically allocated array of size `N` in the object itself. The container stores elements into this array until number of elements is not greater than `N`, which avoids dynamic memory allocation and deallocation. The dynamic memory management is used when the number of elements has to be greater than `N`.

Size `N` is specified at the compile time as a template parameter.



## About small flat maps and sets

Small flat maps and sets from namespace `sfl` are associative containers similar to standard maps and sets, but with the different storage model.

The storage model of small flat maps and sets is identical to the storage model of `sfl::small_vector`, that is, each of them holds statically allocated array of size `N` in the object itself. Elements are stored into this array until the number of elements is not greater than `N`, which avoids dynamic memory allocation and deallocation. The dynamic memory management is used when the number of elements has to be greater than `N`.

Size `N` is specified at the compile time as a template parameter.



## About compact vector

`sfl::compact_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector), but with the key difference that `capacity()` and `size()` are always equal.

`sfl::compact_vector` reallocates storage every time when element is inserted or removed in order to keep `capacity()` and `size()` equal. That means insertions and removals are very inefficient.

This container is inspired by [OpenFOAM's](https://openfoam.org/) container [`List`](https://github.com/OpenFOAM/OpenFOAM-dev/blob/master/src/OpenFOAM/containers/Lists/List/List.H).



## About segmented vector

`sfl::segmented_vector` is a sequence container similar to [`std::vector`](https://en.cppreference.com/w/cpp/container/vector), but with the different storage model.

The storage of `sfl::segmented_vector` consists of a sequence of individually allocated arrays of size `N` which are called *segments*. Size `N` is specified at the compile time as a template parameter.

Elements of `sfl::segmented_vector` are not stored contiguously in the memory, but they are stored contiguously within a segment.

This container is inspired by `std::deque`, but the behavior and API is different than `std::deque`. Segmented vector has the same set of public member functions as `std::vector`, except the `data()` member function, which does not exist.



# Requirements

This library requires C++11 compiler or newer.

If available, the library uses the features of the newer C++ standards.

Tested compilers:
* GCC 4.8.5 on CentOS 7 (C++11)
* Clang 3.4.2 on CentOS 7 (C++11)
* GCC 13.2.1 on Arch Linux (C++11, 14, 17, 20, 23)
* Clang 15.0.7 on Arch Linux (C++11, 14, 17, 20)



# Installation and usage

Copy the contents of directory `include/sfl` into your project and `#include` what you need.

The header files in `include/sfl` are not mutually dependent. That means you can copy into your project directory only what you need. For example, if you need only `sfl::small_vector` then copy only `small_vector.hpp` into your project directory.



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

The detailed documentation is located in directory `doc`.

The detailed documentation is handwritten in Markdown format, it is not automatically generated with tools like Doxygen, so there may be some errors or mistakes. If you find one, please report it.



# Tests

Test programs and scripts are located in directory `test`.

Tested compilers are listed in section [Requirements](#requirements).

Each test program is checked with Valgrind tool.



# License

Licensed under zlib license. The license text is in file [`LICENSE.txt`](LICENSE.txt).

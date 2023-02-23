# sfl library

This is header-only C++11 library that offers several new containers:

  * [`small_vector`](doc/small_vector.asciidoc)
  * [`small_flat_set`](doc/small_flat_set.asciidoc)
  * [`small_flat_map`](doc/small_flat_map.asciidoc)
  * [`small_flat_multiset`](doc/small_flat_multiset.asciidoc)
  * [`small_flat_multimap`](doc/small_flat_multimap.asciidoc)
  * [`small_unordered_flat_set`](doc/small_unordered_flat_set.asciidoc)
  * [`small_unordered_flat_map`](doc/small_unordered_flat_map.asciidoc)
  * [`small_unordered_flat_multiset`](doc/small_unordered_flat_multiset.asciidoc)
  * [`small_unordered_flat_multimap`](doc/small_unordered_flat_multimap.asciidoc)
  * [`compact_vector`](doc/compact_vector.asciidoc)
  * [`segmented_vector`](doc/segmented_vector.asciidoc)

All containers are defined in namespace `sfl`.

## About small vector

`sfl::small_vector` is a sequence container similar to `std::vector`,
but with a different storage model.

`sfl::small_vector` holds statically allocated array of size `N` in
the object itself.
The container stores elements into this array until number of elements is not
greater than `N`, which avoids dynamic memory allocation and deallocation.
The dynamic memory management is used when the number of elements has to be
greater than `N`.

The size `N` is specified at the compile time as a template parameter.
In case when `N` is equal to zero the container does not hold any statically
allocated array and uses only dynamic memory management.
In case when `N` is equal to zero `sfl::small_vector` behaves just like
`std::vector`.

Unlike standard vector, `sfl::small_vector` is not specialized for `bool`.

## About small maps and sets

Small maps and sets from namespace `sfl` are associative containers similar to
standard maps and sets from namespace `std`, but with a different storage model.

The storage model of small maps and sets from namespace `sfl` is identical
to the storage model of `sfl::small_vector`.
Small maps and sets from namespace `sfl` hold statically allocated array of
size `N` in the object itself, just like `sfl::small_vector`.
Elements are stored into this array until number of elements is not
greater than `N`, which avoids dynamic memory allocation and deallocation.
The dynamic memory management is used when the number of elements has to be
greater than `N`.

The size `N` is specified at the compile time as a template parameter.
In case when `N` is equal to zero the container does not hold any statically
allocated array and uses only dynamic memory management.

Small maps and sets from namespace `sfl` always store elements contiguously
in the memory, even when dynamic memory management is used.
Iterators to the elements are random access iterators.

## About compact vector

`sfl::compact_vector` is a sequence container similar to `std::vector`.
The key difference is that `capacity()` and `size()` of `sfl::compact_vector`
are always equal.
This container reallocates storage every time when element is inserted or
removed in order to keep `capacity()` and `size()` equal.
That means insertion and removal are very inefficient.

In general it is not recommended to use `sfl::compact_vector` instead of
`std::vector` because of its inefficient memory management, but there are
some situations when `sfl::compact_vector` is better choice than `std::vector`.
For example, consider using `std::vector<sfl::compact_vector<T>>` instead
of `std::vector<std::vector<T>>` when there is huge number of subvectors.
If `std::vector` is used as subvector then there is a high probability that
there will be unused capacity because `std::vector` does not guarantee that
`capacity()` and `size()` are equal.
`std::vector` does not guarantee that `capacity()` and `size()` are equal
even though `shrink_to_fit()` is invoked.
On the other hand, using `sfl::compact_vector` as subvector guarantees that
there are no unused capacity.

## About segmented vector

`sfl::segmented_vector` is a sequence container similar to `std::vector` but
with the different storage model.

The storage of `sfl::segmented_vector` consists of a sequence of individually
allocated arrays of size `N` which are called *segments*.
The size `N` is specified at the compile time as a template parameter.

Elements of `sfl::segmented_vector` are not stored contiguously in the memory,
but they are stored contiguously within a segment.

The storage model of `sfl::segmented_vector` is similar to storage models of
most implementations of `std::deque` but the behavior and API of
`sfl::segmented_vector` is not compatible with `std::deque`.
`sfl::segmented_vector` has the same set of member functions as `std::vector`,
except the `data()` member function, which does not exist.

## Detailed documentation

The detailed documentation is located in `doc` directory.
It is written in asciidoc format and then converted to html file format.
Generated html files are located in `doc/html` directory.
I recommend reading documentation from html files because html files are
rendered much better than asciidoc files.
Unfortunately, github can render only asciidoc files.
To view html files, first download them onto your computer and then open
using your favorite web browser.

## Requirements

The only requirement is C++11 compiler or newer.

Tested with GCC 4.8.5 on CentOS 7.

Tested with Clang 3.4.2 on CentOS 7.

## Installation and usage

Copy `include/sfl` directory into your project and `#include` what you need.

The header files in `include/sfl` are not mutually dependent.
That means you can copy into your project directory only what you need.
For example, if you need `sfl::small_vector` container then copy only
`small_vector.hpp` into your project directory.

## Exceptions

This library by default throw exceptions in case of error.

If macro `SFL_NO_EXCEPTIONS` is defined then library avoids using exceptions
and calls `std::abort` in case of error.

This library does not automatically detect whether the compiler is invoked
with appropriate flag, like `-fno-exceptions` in GCC and Clang.

## Debugging

This library uses macro `assert` from header `<cassert>`.

The definition of the macro `assert` depends on another macro, `NDEBUG`,
which is not defined by the standard library.

If macro `NDEBUG` is defined then `assert` does nothing.

If macro `NDEBUG` is not defined then `assert` performs check.
If check fails, `assert` outputs implementation-specific diagnostic
information on the standard error output and calls `std::abort`.

## Tests

Directory `test` contains test programs.
Script `test_all.sh` builds and runs all test programs.
Each test program is checked with `valgrind` tool.

## License

Licensed under zlib license.
The license text is in [`LICENSE.txt`](LICENSE.txt) file.

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

All containers are defined in namespace `sfl`.

## About _small_ vector

`sfl::small_vector` is a sequence container similar to `std::vector`.

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

## About other _small_ containers

`sfl::small_flat_XXX` are sorted associative containers similar
to `std::XXX` sorted associative containers.

`sfl::small_unordered_flat_XXX` are unordered associative containers similar
to `std::unordered_XXX` unordered associative containers.

The storage model of `sfl::small_flat_XXX` and `sfl::small_unordered_flat_XXX`
is identical to the storage model of `sfl::small_vector`.
That means that (1) all of them store elements contiguously in the memory,
(2) iterators to the elements are random access iterators and
(3) all of them hold statically allocated array of size `N` in the object itself.

# Requirements

The only requirement is C++11 compiler or newer.

Tested with GCC 4.8.5 on CentOS 7.

# Installation and usage

This is header-only library.
Just add `include/sfl` directory to your project and `#include` what you need.

You can copy `include/sfl` directory with its contents into your project
directory.

The header files in `include/sfl` are not mutually dependent.
That means you can copy into your project directory only what you need.
For example, if you need `sfl::small_vector` container then copy only
`small_vector.hpp` into your project directory.

# Detailed documentation

The detailed documentation is located in `doc` directory.
It is written in asciidoc format and then converted to html file format.
Generated html files are located in `doc/html` directory.
I recommend reading documentation from html files because html files are
rendered much better than asciidoc files.
Unfortunately, github can render only asciidoc files.
To view html files, first download them onto your computer and then open
using your favorite web browser.

# Tests

Directory `test` contains test programs for each container.
I didn't write unit tests because this was easier for me.
Test programs are checked with `valgrind` tool.

# License

Licensed under zlib license.
The license text is in [`LICENSE.txt`](LICENSE.txt) file.

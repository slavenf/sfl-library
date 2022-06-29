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

Click on the container name to see detailed documentation.
For more information about documentation please scroll down to the
section [Detailed documentation](#detailed-documentation).

## About small vector

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

## About other small containers

`sfl::small_flat_XXX` are sorted associative containers similar
to `std::XXX` sorted associative containers.

`sfl::small_unordered_flat_XXX` are unordered associative containers similar
to `std::unordered_XXX` unordered associative containers.

The storage model of `sfl::small_flat_XXX` and `sfl::small_unordered_flat_XXX`
is identical to the storage model of `sfl::small_vector`.
That means that (1) all of them store elements contiguously in the memory,
(2) iterators to the elements are random access iterators and
(3) all of them hold statically allocated array of size `N` in the object itself.

## About compact vector

`sfl::compact_vector` is a sequence container similar to `std::vector`.
The main difference is that `sfl::compact_vector` always has `capacity()`
equal to `size()`.
This container reallocates storage every time an element is inserted or
removed such that capacity becomes equal to the size.
That means insertion and removal are very inefficient.

In general it is not recommended to use `sfl::compact_vector` instead of
`std::vector` because of its inefficient memory management but there are some
situations where `sfl::compact_vector` is an excellent choice.
For example consider the following code snippet:

```C++
const std::size_t N = 1000000; // Very big number.

std::vector<std::vector<int>> vv(N); // Vector of vectors.

for (std::size_t i = 0; i < N; ++i)
{
    const std::size_t M = get_random_M();

    for (std::size_t j = 0; j < M; ++j)
    {
        vv[i].push_back(get_random_int());
    }

    // In general vv[i].capacity() can be greater than vv[i].size(), that is,
    // we have unused capacity.
    //
    // Using vv[i].shrink_to_fit() does not guarantee that
    // vv[i].capacity() will become equal to vv[i].size().
    //
    // vv[i].assign(InputIterator, InputIterator) also does not guarantee
    // that vv[i].capacity() will be equal to vv[i].size().
}

// Now use vector vv but never change its contents.
```

The example above is pretty stupid but it clearly ilustrates the point.
Because we used `std::vector` there is a high probability that we will have
unused capacity.
The example below does not have problems with unused capacity:

```C++
const std::size_t N = 1000000; // Very big number.

std::vector<sfl::compact_vector<int>> vv(N); // Vector of COMPACT vectors!!!

for (std::size_t i = 0; i < N; ++i)
{
    const std::size_t M = get_random_M();

    std::vector<int> temp;

    for (std::size_t j = 0; j < M; ++j)
    {
        temp.push_back(get_random_int());
    }

    vv[i].assign(temp.begin(), temp.end());

    // vv[i].capacity() is equal to vv[i].size(). This is guaranteed.
    // We do not have unused capacity.
}

// Now use vector vv but never change its contents.
```

## About segmented vector

`sfl::segmented_vector` is a sequence container similar to `std::vector` but
with the different storage model.
The storage of `sfl::segmented_vector` consists of a sequence of individually
allocated arrays of size `N` which are called *segments*.
The size `N` is specified at the compile time as a template parameter.
Elements of `sfl::segmented_vector` are not stored contiguously in the memory,
but they are stored contiguously within a segment.
This is very similar to the storage model of `std::deque`.
Unlike `std::deque`, `sfl::segmented_vector` allows fast insertion only at
its end.
`sfl::segmented_vector` does not have interface compatible with `std::deque`.
Interface of `sfl::segmented_vector` is compatible with `std::vector`, except
the `data()` member function, which does not exist.

# Requirements

The only requirement is C++11 compiler or newer.

Tested with GCC 4.8.5 on CentOS 7.

Tested with Clang 3.4.2 on CentOS 7.

# Installation and usage

This is header-only library.
Just add `include/sfl` directory to your project and `#include` what you need.

You can copy `include/sfl` directory with its contents into your project
directory.

The header files in `include/sfl` are not mutually dependent.
That means you can copy into your project directory only what you need.
For example, if you need `sfl::small_vector` container then copy only
`small_vector.hpp` into your project directory.

# Exceptions

This library by default uses `try`, `catch` and `throw` statements for
error handling.

If macro `SFL_NO_EXCEPTIONS` is defined then library avoids using `try`, `catch`
and `throw` statements, and in case of error library calls `std::abort`.

The library does not automatically detect whether the compiler is invoked
with appropriate flag, like `-fno-exceptions` in GCC and Clang.

# Detailed documentation {#detailed-documentation}

The detailed documentation is located in `doc` directory.
It is written in asciidoc format and then converted to html file format.
Generated html files are located in `doc/html` directory.
I recommend reading documentation from html files because html files are
rendered much better than asciidoc files.
Unfortunately, github can render only asciidoc files.
To view html files, first download them onto your computer and then open
using your favorite web browser.

# Tests

Directory `test` contains test programs and allocators used for testing.
There is a Bash script `run-all-tests.sh` that build and run all test programs.
Each test programs is checked with `valgrind` tool.

# License

Licensed under zlib license.
The license text is in [`LICENSE.txt`](LICENSE.txt) file.

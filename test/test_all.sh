#!/bin/bash

CXX=""

CXX+="g++ -std=c++20 "
#CXX+="clang++ -gdwarf-4 -std=c++20 "

CXX+="-g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include "

#CXX+="-fno-exceptions -DSFL_NO_EXCEPTIONS "

ALLOCATORS=()
ALLOCATORS+=("std::allocator")
ALLOCATORS+=("sfl::test::stateless_fancy_alloc")
ALLOCATORS+=("sfl::test::stateless_alloc")
ALLOCATORS+=("sfl::test::stateless_alloc_no_prop")
ALLOCATORS+=("sfl::test::statefull_alloc")

TEST_SMALL_FLAT_MAP=1
TEST_SMALL_FLAT_MULTIMAP=1
TEST_SMALL_FLAT_SET=1
TEST_SMALL_FLAT_MULTISET=1
TEST_SMALL_UNORDERED_FLAT_MAP=1
TEST_SMALL_UNORDERED_FLAT_MULTIMAP=1
TEST_SMALL_UNORDERED_FLAT_SET=1
TEST_SMALL_UNORDERED_FLAT_MULTISET=1
TEST_SMALL_VECTOR=1
TEST_COMPACT_VECTOR=1
TEST_SEGMENTED_VECTOR=1

build_and_valgrind()
{
    # First argument is build command.
    BUILD_COMMAND=$1

    # Print build command.
    echo $BUILD_COMMAND

    # Execute build command.
    $BUILD_COMMAND

    if [ $? -ne 0 ] ; then
        echo ""
        echo "ERROR: Build failed."
        echo "Build command: $BUILD_COMMAND"
        echo "THE END."
        exit 1
    fi

    valgrind --leak-check=full ./a.out

    if [ $? -ne 0 ] ; then
        echo ""
        echo "ERROR: Valgrind check failed."
        echo "Build command: $BUILD_COMMAND"
        echo "THE END."
        exit 1
    fi
}

if [ $TEST_SMALL_FLAT_MAP -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_flat_map.cpp"
    done
fi

if [ $TEST_SMALL_FLAT_MULTIMAP -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_flat_multimap.cpp"
    done
fi

if [ $TEST_SMALL_FLAT_SET -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_flat_set.cpp"
    done
fi

if [ $TEST_SMALL_FLAT_MULTISET -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_flat_multiset.cpp"
    done
fi

if [ $TEST_SMALL_UNORDERED_FLAT_MAP -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_unordered_flat_map.cpp"
    done
fi

if [ $TEST_SMALL_UNORDERED_FLAT_MULTIMAP -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_unordered_flat_multimap.cpp"
    done
fi

if [ $TEST_SMALL_UNORDERED_FLAT_SET -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_unordered_flat_set.cpp"
    done
fi

if [ $TEST_SMALL_UNORDERED_FLAT_MULTISET -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_unordered_flat_multiset.cpp"
    done
fi

if [ $TEST_SMALL_VECTOR -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR small_vector.cpp"
    done
fi

if [ $TEST_COMPACT_VECTOR -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR compact_vector.cpp"
    done
fi

if [ $TEST_SEGMENTED_VECTOR -eq 1 ] ; then
    for ALLOCATOR in ${ALLOCATORS[*]}; do
        for N in 1 2 4 1024; do
            build_and_valgrind "$CXX -DTPARAM_ALLOCATOR=$ALLOCATOR -DTPARAM_N=$N segmented_vector.cpp"
        done
    done
fi

echo ""
echo "All tests finished successfully. The end."

#!/bin/bash

# C++ compiler.
CXX=${CXX:-"g++ -std=c++11"}

# C++ flags. These flags are mandatory. All warnings are errors.
CXXFLAGS="-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -g -O0 -I ../include"

# List of allocators.
ALLOCATORS=(
    std::allocator
    sfl::test::stateless_fancy_alloc
    sfl::test::stateless_alloc
    sfl::test::stateless_alloc_no_prop
    sfl::test::statefull_alloc
)

build_and_valgrind()
{
    # First argument is build command.
    BUILD_COMMAND=$1

    echo :::: Starting building...

    # Print build command.
    echo $BUILD_COMMAND

    # Execute build command.
    $BUILD_COMMAND

    if [ $? -ne 0 ] ; then
        echo :::: Build failed.
        echo :::: Build command: $BUILD_COMMAND
        echo :::: THE END.
        exit 1
    fi

    echo :::: Finished building.
    echo :::: Starting valgrind check...

    valgrind --leak-check=full ./a.out

    if [ $? -ne 0 ] ; then
        echo :::: Valgrind check failed.
        echo :::: Build command: $BUILD_COMMAND
        echo :::: THE END.
        exit 1
    fi

    echo :::: Finished valgrind check.
}

if [[ $1 == "all" || $1 == "compact_vector" ]] ; then
    echo :::: Starting checking compact_vector...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX compact_vector.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking compact_vector.
fi

if [[ $1 == "all" || $1 == "segmented_vector" ]] ; then
    echo :::: Starting checking segmented_vector...
    for allocator in ${ALLOCATORS[*]}; do
        for N in 1 2 4 1024; do
            build_and_valgrind "$CXX segmented_vector.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator -DTPARAM_N=$N"
        done
    done
    echo :::: Finished checking segmented_vector.
fi

if [[ $1 == "all" || $1 == "small_flat_map" ]] ; then
    echo :::: Starting checking small_flat_map...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_flat_map.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_flat_map.
fi

if [[ $1 == "all" || $1 == "small_flat_multimap" ]] ; then
    echo :::: Starting checking small_flat_multimap...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_flat_multimap.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_flat_multimap.
fi

if [[ $1 == "all" || $1 == "small_flat_multiset" ]] ; then
    echo :::: Starting checking small_flat_multiset...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_flat_multiset.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_flat_multiset.
fi

if [[ $1 == "all" || $1 == "small_flat_set" ]] ; then
    echo :::: Starting checking small_flat_set...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_flat_set.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_flat_set.
fi

if [[ $1 == "all" || $1 == "small_unordered_flat_map" ]] ; then
    echo :::: Starting checking small_unordered_flat_map...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_unordered_flat_map.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_unordered_flat_map.
fi

if [[ $1 == "all" || $1 == "small_unordered_flat_multimap" ]] ; then
    echo :::: Starting checking small_unordered_flat_multimap...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_unordered_flat_multimap.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_unordered_flat_multimap.
fi

if [[ $1 == "all" || $1 == "small_unordered_flat_multiset" ]] ; then
    echo :::: Starting checking small_unordered_flat_multiset...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_unordered_flat_multiset.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_unordered_flat_multiset.
fi

if [[ $1 == "all" || $1 == "small_unordered_flat_set" ]] ; then
    echo :::: Starting checking small_unordered_flat_set...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_unordered_flat_set.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_unordered_flat_set.
fi

if [[ $1 == "all" || $1 == "small_vector" ]] ; then
    echo :::: Starting checking small_vector...
    for allocator in ${ALLOCATORS[*]}; do
        build_and_valgrind "$CXX small_vector.cpp $CXXFLAGS -DTPARAM_ALLOCATOR=$allocator"
    done
    echo :::: Finished checking small_vector.
fi

echo :::: All tests finished successfully. THE END.

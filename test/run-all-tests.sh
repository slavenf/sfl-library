#!/bin/sh

# Compiler executable:
CXX=g++

# Compiler flags:
CXXFLAGS="-Wall -Wextra -Werror -Wfatal-errors -Wpedantic -std=c++11 -g"

# Name of the output executable file:
OUT_FILE="test.out"

# -----------------------------------------------------------------------------
# Testing test_allocator_XXX
# -----------------------------------------------------------------------------

# List of input files for testing:
INPUT_FILES=(
    "test_allocator_1.cpp"
    "test_allocator_2.cpp"
    "test_allocator_3.cpp"
    "test_allocator_4.cpp"
)

for IN_FILE in ${INPUT_FILES[@]}; do

    # Store build command in string:
    BUILD_COMMAND="$CXX $CXXFLAGS -I ../include -o $OUT_FILE $IN_FILE"

    # Execute build command:
    $BUILD_COMMAND

    if [ $? -ne 0 ]
    then
        echo ""
        echo "ERROR: Build failed."
        echo "> File: $IN_FILE"
        echo "> Build command: $BUILD_COMMAND"
        exit
    fi

    # Execute valgrind:
    valgrind --leak-check=full ./$OUT_FILE

    if [ $? -ne 0 ]
    then
        echo ""
        echo "ERROR: Test failed."
        echo "> File: $IN_FILE"
        echo "> Build command: $BUILD_COMMAND"
        exit
    fi

done

# -----------------------------------------------------------------------------
# Testing containers
# -----------------------------------------------------------------------------

# List of allocators:
ALLOCATORS=(
    "std::allocator"
    "sfl::test_allocator_1"
    "sfl::test_allocator_2"
    "sfl::test_allocator_3"
    "sfl::test_allocator_4"
)

# List of input files for testing:
INPUT_FILES=(
    "test_small_flat_map.cpp"
    "test_small_flat_multimap.cpp"
    "test_small_flat_set.cpp"
    "test_small_flat_multiset.cpp"
    "test_small_unordered_flat_map.cpp"
    "test_small_unordered_flat_multimap.cpp"
    "test_small_unordered_flat_set.cpp"
    "test_small_unordered_flat_multiset.cpp"
    "test_small_vector.cpp"
    "test_compact_vector.cpp"
)

for IN_FILE in ${INPUT_FILES[@]}; do

    for ALLOC in ${ALLOCATORS[@]}; do

        # Store build command in string:
        BUILD_COMMAND="$CXX $CXXFLAGS -D SFL_TEST_ALLOCATOR=$ALLOC -I ../include -o $OUT_FILE $IN_FILE"

        # Execute build command:
        $BUILD_COMMAND

        if [ $? -ne 0 ]
        then
            echo ""
            echo "ERROR: Build failed."
            echo "> File: $IN_FILE"
            echo "> Allocator: $ALLOC"
            echo "> Build command: $BUILD_COMMAND"
            exit
        fi

        # Execute valgrind:
        valgrind --leak-check=full ./$OUT_FILE

        if [ $? -ne 0 ]
        then
            echo ""
            echo "ERROR: Test failed."
            echo "> File: $IN_FILE"
            echo "> Allocator: $ALLOC"
            echo "> Build command: $BUILD_COMMAND"
            exit
        fi

    done

done

echo ""
echo "All tests finished successfully. The end."

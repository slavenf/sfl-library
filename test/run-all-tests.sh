#!/bin/sh

# Compiler executable:
CXX=g++

# Compiler flags:
CXXFLAGS="-Wall -Wextra -Werror -Wfatal-errors -Wpedantic -std=c++11 -g"

# Name of the output executable file:
OUT_FILE="test.out"

# List of allocators which will be used during testing:
TEST_ALLOCATORS=(
    "std::allocator"
    "sfl::stateless_alloc"
    "sfl::stateless_alloc_no_prop"
    "sfl::stateless_fancy_alloc"
    "sfl::statefull_alloc"
)

# -----------------------------------------------------------------------------
# Testing all small_XXX containers and compact_vector
# -----------------------------------------------------------------------------

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

    for ALLOC in ${TEST_ALLOCATORS[@]}; do

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

# -----------------------------------------------------------------------------
# Testing segmented_vector
# -----------------------------------------------------------------------------

IN_FILE="test_segmented_vector.cpp"

SEGMENT_SIZES=(1 2 4 100)

for SEG_SZ in ${SEGMENT_SIZES[@]}; do

    for ALLOC in ${TEST_ALLOCATORS[@]}; do

        # Store build command in string:
        BUILD_COMMAND="$CXX $CXXFLAGS -D SFL_TEST_ALLOCATOR=$ALLOC -I ../include -o $OUT_FILE $IN_FILE -D TP_N=$SEG_SZ"

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

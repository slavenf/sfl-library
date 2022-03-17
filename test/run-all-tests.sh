#!/bin/sh

test()
{
    g++ -Wall -Wextra -Werror -Wpedantic -std=c++11 -g -I ../include -o test.out "test_${1}.cpp"

    if [ $? -ne 0 ]
    then
        echo ""
        echo "ERROR: ${1}: Build failed."
        exit
    fi

    valgrind --leak-check=full ./test.out

    if [ $? -ne 0 ]
    then
        echo ""
        echo "ERROR: ${1}: Test failed."
        exit
    fi
}

test small_flat_map
test small_flat_multimap
test small_flat_set
test small_flat_multiset
test small_unordered_flat_map
test small_unordered_flat_multimap
test small_unordered_flat_set
test small_unordered_flat_multiset
test small_vector
test compact_vector

echo ""
echo "All test finished successfully."

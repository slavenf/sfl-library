#!/bin/bash

run()
{
    # Print command
    echo :::: Starting test \[$1\]

    # Execute command
    eval $1

    if [ $? -ne 0 ] ; then
        echo :::: ERROR. Test failed \[$1\]
        exit 1
    fi

    echo :::: Finished test \[$1\]
}

run "make CXX=\"g++     -std=c++11\" -j"
run "make CXX=\"g++     -std=c++14\" -j"
run "make CXX=\"g++     -std=c++17\" -j"
run "make CXX=\"g++     -std=c++20\" -j"
run "make CXX=\"g++     -std=c++23\" -j"
run "make CXX=\"clang++ -std=c++11\" -j"
run "make CXX=\"clang++ -std=c++14\" -j"
run "make CXX=\"clang++ -std=c++17\" -j"
run "make CXX=\"clang++ -std=c++20\" -j"

echo :::: Finished all tests.
echo :::: THE END.

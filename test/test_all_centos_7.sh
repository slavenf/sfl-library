#!/bin/bash

run()
{
    # Print command
    echo :::: Starting test \[$1\]

    # Execute command
    eval $1

    if [ $? -ne 0 ] ; then
        echo :::: ERROR. Test failed \[$1\]
        echo :::: ALL STOP.
        exit 1
    fi

    echo :::: Finished test \[$1\]
}

run "make CXX=\"g++     -std=c++11\" SILENT=1 -j"
run "make CXX=\"clang++ -std=c++11\" SILENT=1 -j"

run "make CXX=\"g++     -std=c++11 -fno-exceptions -DSFL_NO_EXCEPTIONS\" SILENT=1 -j"
run "make CXX=\"clang++ -std=c++11 -fno-exceptions -DSFL_NO_EXCEPTIONS\" SILENT=1 -j"

echo :::: Finished all tests.
echo :::: THE END.

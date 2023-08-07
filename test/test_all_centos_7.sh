#!/bin/bash

set -e

CXX="g++ -std=c++11" ./test.sh all
CXX="clang++ -std=c++11" ./test.sh all
CXX="g++ -std=c++11 -fno-exceptions -DSFL_NO_EXCEPTIONS" ./test.sh all
CXX="clang++ -std=c++11 -fno-exceptions -DSFL_NO_EXCEPTIONS" ./test.sh all

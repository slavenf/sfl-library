#!/bin/bash

set -e

CXX="g++ -std=c++11" ./test.sh all
CXX="g++ -std=c++14" ./test.sh all
CXX="g++ -std=c++17" ./test.sh all
CXX="g++ -std=c++20" ./test.sh all
CXX="g++ -std=c++23" ./test.sh all

CXX="clang++ -std=c++11" ./test.sh all
CXX="clang++ -std=c++14" ./test.sh all
CXX="clang++ -std=c++17" ./test.sh all
CXX="clang++ -std=c++20" ./test.sh all

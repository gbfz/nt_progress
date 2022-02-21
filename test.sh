#!/bin/bash

echo "Compiling..."
g++ -pthread Calculator.cpp test.cpp -lgtest -lgtest_main -o calctest && ./calctest 2> /dev/null

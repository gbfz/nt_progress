#!/bin/bash

echo "Compiling..."
g++ -pthread src/Calculator.cpp src/test.cpp -lgtest -lgtest_main -o calctest && ./calctest 2> /dev/null

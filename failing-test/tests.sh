#!/bin/bash

set -e

echo "Compiling tests"
g++ -std=c++11 -g -Wall resize-big-image.cpp `pkg-config vips-cpp --cflags --libs` -Wno-c++11-extensions -o bench-resize

echo "Running tests"
./bench-resize samples/twin-peaks.jpeg

echo "Test Completed"

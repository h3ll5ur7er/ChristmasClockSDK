#! /bin/bash -c

set -e

cmake -B build .
cmake --build build

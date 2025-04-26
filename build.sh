#!/bin/bash

set -e

mkdir -p build
cd build
cmake ../

# Forward all arguments to make
make "$@"

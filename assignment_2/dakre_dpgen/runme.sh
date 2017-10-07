#!/bin/bash

echo "Setting up build environment for high level synthesis"
mkdir build
cd build
cmake ..
make

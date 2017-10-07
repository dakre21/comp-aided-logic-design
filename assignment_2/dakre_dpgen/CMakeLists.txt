cmake_minimum_required (VERSION 2.6)
project (dpgen)

# Version number
set (dpgen_VERSION_MAJOR 1)
set (dpgen_VERSION_MINOR 0)

# Configure header files
#configure_file (
#    "src/dpgen.h"
#    "build/dpgen.h"
#)

include_directories(src)

# Create the exe
add_executable(dpgen src/dpgen.cpp)

cmake_minimum_required (VERSION 2.6)
project (dpgen)

# Version number
set (dpgen_VERSION_MAJOR 1)
set (dpgen_VERSION_MINOR 0)

# Set compiler to cpp11
set (CMAKE_CXX_STANDARD 11)

# Add subdirectories
add_subdirectory(src)

# Create the exe
add_executable(dpgen $<TARGET_OBJECTS:SRC>)

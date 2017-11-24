cmake_minimum_required (VERSION 2.6)
project (hlsyn)

# Version number
set (dpgen_VERSION_MAJOR 1)
set (dpgen_VERSION_MINOR 0)

# Set compiler to cpp11
set (CMAKE_CXX_STANDARD 11)

# Add subdirectories
add_subdirectory(src)

# Create the exe
add_executable(hlsyn $<TARGET_OBJECTS:SRC>)
set(EXECUTABLE_OUTPUT_PATH src)

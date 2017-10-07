# Include directories
include_directories(./)

# Set sources
set (
    MAIN_SOURCES
    "dpgen.cpp"
)

set (
    HLS_SOURCES
    "HLSEngine.cpp"
)

# Add sources
add_library(SRC OBJECT ${MAIN_SOURCES} ${HLS_SOURCES})

# CMake
cmake_minimum_required(VERSION 3.21.3)

# プロジェクト情報
project(Parquet
    VERSION 0.1
    DESCRIPTION "Compiler Creation Support Library in C"
    LANGUAGES C
)

# in-source ビルドガード
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

add_subdirectory(lib)
add_subdirectory(examples EXCLUDE_FROM_ALL)

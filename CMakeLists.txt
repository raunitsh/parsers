cmake_minimum_required(VERSION 3.14)
project(parsers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# 1. Declare cpp-utils dependency
FetchContent_Declare(
    cpputils
    GIT_REPOSITORY https://github.com/raunitsh/cpputils.git
    GIT_TAG        main # or a specific release/commit
)

# 2. Declare memorymanager dependency
FetchContent_Declare(
    memorymanager
    GIT_REPOSITORY https://github.com/raunitsh/memorymanager.git
    GIT_TAG        main # or a specific release/commit
)

# Populate and make both targets available
FetchContent_MakeAvailable(cpputils memorymanager)

# 3. Your executable / library target
add_executable(parsers
    # List your source files here, e.g.:
    main.cpp
)

# 4. Link dependencies
# cpputils automatically provides its includes and C++17 compile features
target_link_libraries(parsers PRIVATE
    cpputils::cpputils
    memorymanager::memorymanager
)
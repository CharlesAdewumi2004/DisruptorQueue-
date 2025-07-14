# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.18)
project(disruptor_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only disruptor_queue library
add_library(disruptor_queue INTERFACE)
target_include_directories(disruptor_queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Fetch Catch2
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Unit tests
enable_testing()

add_executable(unit_tests
        Test/test_disruptor_queue.cpp
)


target_link_libraries(unit_tests
        PRIVATE Catch2::Catch2WithMain
)

# ---------------------------------------------------------
# Catch2 automatic test registration
include(CTest)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(unit_tests)

include(CTest)
include(Catch)


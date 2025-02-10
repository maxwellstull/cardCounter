cmake_minimum_required(VERSION 3.10)
project(Blackjack)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)

add_executable(blackjack main.cpp)
add_executable(tests tests/test_card.cpp tests/test_suit.cpp)
add_test(NAME TestyMcTest COMMAND tests)

target_link_libraries(blackjack PRIVATE Card)
target_link_libraries(tests PRIVATE gtest gtest_main Card)

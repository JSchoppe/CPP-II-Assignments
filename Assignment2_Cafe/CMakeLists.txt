cmake_minimum_required(VERSION 2.8)

project(Cafe2)

include(../gtest.cmake)

find_package(Threads)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -pthread")

file(GLOB ALL_PRODUCT_CPP source/*.cpp source/command/*.cpp)
file(GLOB ALL_TESTS_CPP tests/*.cpp source/*.cpp source/command/*.cpp)
list(REMOVE_ITEM ALL_TESTS_CPP ${PROJECT_SOURCE_DIR}/source/main.cpp)

add_executable(cafe ${ALL_PRODUCT_CPP})

add_executable(tests ${ALL_TESTS_CPP})
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT} gtest)
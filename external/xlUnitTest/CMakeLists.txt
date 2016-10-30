cmake_minimum_required(VERSION 2.4)
project(xlUnitTest CXX)

file(GLOB SRC_LIST "*.h")
add_custom_target(xlUnitTest SOURCES ${SRC_LIST})

file(GLOB_RECURSE SRC_LIST "Test/*.h" Test/*.cpp)
add_executable(Test ${SRC_LIST})
add_dependencies(Test xlUnitTest)
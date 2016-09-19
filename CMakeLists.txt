cmake_minimum_required(VERSION 2.4)
project(stdex)
if(${CMAKE_COMPILER_IS_GNUCXX})
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wfatal-errors")
endif()

file(GLOB SRC_LIST *.h)
add_custom_target(stdex SOURCES ${SRC_LIST})

file(GLOB SRC_LIST "unittest/*.cpp")
add_executable(unittest ${SRC_LIST})
add_dependencies(unittest stdex)

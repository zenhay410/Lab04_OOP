cmake_minimum_required(VERSION 3.10)
project(geometry_oop_lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wshadow")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(geometry_lib INTERFACE)
target_include_directories(geometry_lib INTERFACE include)

add_executable(geometry_app main.cpp)
target_link_libraries(geometry_app geometry_lib)

add_executable(geometry_tests test/tests.cpp)
target_link_libraries(geometry_tests geometry_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(geometry_tests)
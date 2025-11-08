cmake_minimum_required(VERSION 3.10)
project(shapes)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)
add_executable(tests test/tests.cpp)

target_link_libraries(tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
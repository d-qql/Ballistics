cmake_minimum_required(VERSION 3.17)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# CTest is a testing tool that can be used to test your project.
enable_testing()

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)

add_executable(all_tests ${TEST_SOURCES})
conan_target_link_libraries(all_tests)
target_link_libraries(all_tests Ballistics)
add_test(NAME all_tests COMMAND all_tests)

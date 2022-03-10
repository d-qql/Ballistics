cmake_minimum_required(VERSION 3.21)
project(Ballistics)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#add_executable(Ballistics main.cpp src/ballistics/gravity/EarthPotential.cpp src/ballistics/gravity/EarthPotential.hpp)
#target_link_libraries(Ballistics ${CONAN_LIBS})

add_subdirectory(src)

if (WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

# Типовой Cmake для тестов
# Ничего переименовывать не надо.
# Полагается на переменную окружения при линковки библиотеки для тестов.

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# CTest is a testing tool that can be used to test your project.
enable_testing()

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)

message("CONAN_LIBS: ${CONAN_LIBS}")

foreach(TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${MODULE_NAME} CONAN_PKG::gtest )
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()

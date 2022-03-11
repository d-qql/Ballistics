option(USE_STATIC_LIBRARY "Опция, указывающая, что надо использовать библиотеку собранную на прошлом шаге" OFF)
option(USE_STATIC_LIBRARY "Имя target сборки статической библиотеки и как следствие самой библиотеки" "Имя библиотеки должно быть задано!!!")

cmake_minimum_required(VERSION 3.17)
project(${MODULE_NAME})

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

message("CONAN_LIBS: ${CONAN_LIBS}")

file(GLOB_RECURSE ${MODULE_NAME}_SOURCES *.h *.cpp *.hpp)
list(FILTER Integrator_SOURCES EXCLUDE REGEX "*/main.cpp")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
if (WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
endif (WIN32)

set(LIBRARY_FOLDER $ENV{CI_PROJECT_DIR}/own_libs/$ENV{TARGET_PLATFORM})
set(LIBRARY_PATH ${LIBRARY_FOLDER}/lib${MODULE_NAME}.a)

if (USE_STATIC_LIBRARY)
    message("USE_STATIC_LIBRARY")
    # Очень важно не продолбать слово GLOBAL. Иначе imported target не будет видна в других папках, в том числе и тестах.
    add_library(${MODULE_NAME} STATIC IMPORTED GLOBAL)

    # указываем где собранная библиотека находится
    set_property(TARGET ${MODULE_NAME} PROPERTY
            IMPORTED_LOCATION ${LIBRARY_PATH})

    # Вроде данное свойство может потребоваться при использовании в качестве IMPORTED dll
    #set_property(TARGET ${MODULE_NAME} PROPERTY
    #             IMPORTED_IMPLIB ${LIBRARY_PATH})

    # указываем, что из других пакетов надо только заголовки тянуть. Исполняемый код уже слинкован в статическую библиотеку
    set(OTHER_MODULE_LINK_TYPE INTERFACE)
    install(FILES ${LIBRARY_PATH} DESTINATION lib)
else ()
    message("COMPILE_STATIC_LIBRARY")
    add_library(${MODULE_NAME} ${${MODULE_NAME}_SOURCES})
    set(OTHER_MODULE_LINK_TYPE PUBLIC)
    install(TARGETS ${MODULE_NAME} DESTINATION ${LIBRARY_FOLDER})
endif ()


target_include_directories(${MODULE_NAME} ${OTHER_MODULE_LINK_TYPE} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MODULE_NAME} ${OTHER_MODULE_LINK_TYPE}
        CONAN_PKG::sofa
        CONAN_PKG::geographiclib
        CONAN_PKG::eigen
        )

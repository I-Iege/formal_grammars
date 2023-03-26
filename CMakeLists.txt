
cmake_minimum_required(VERSION 3.22)

project (wind1)

#no option for latest and this will force 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32)
    #set ( CMAKE_CXX_FLAGS " /EHsc /MD /Zc:__cplusplus /permissive-")
    #hide cmake targets in visual studio /std:c++latest /experimental:module
    #set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (WIN32)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

enable_testing()

add_subdirectory(backend)
add_subdirectory(ui)
add_subdirectory(unittests)



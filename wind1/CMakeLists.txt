
cmake_minimum_required(VERSION 3.22)

project (wind1)

#no option for latest and this will force 20
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set ( CMAKE_CXX_FLAGS "/std:c++latest /experimental:module /EHsc /MD")
    #hide cmake targets in visual studio
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (WIN32)

if (UNIX)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
endif(UNIX)


find_package(Qt6 REQUIRED COMPONENTS Core)

enable_testing()


add_subdirectory(googletest)

add_subdirectory(main)
if(WIN32)
    set_target_properties(gmock gmock_main gtest gtest_main PROPERTIES FOLDER Gtest)
endif(WIN32)




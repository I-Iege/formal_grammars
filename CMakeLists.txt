
cmake_minimum_required(VERSION 3.5)

project (wind1)

#no option for latest and this will force 20
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_PREFIX_PATH C:/Qt/6.3.1/mingw_64)

if (WIN32)
    #set ( CMAKE_CXX_FLAGS " /EHsc /MD /Zc:__cplusplus /permissive-")
    #hide cmake targets in visual studio /std:c++latest /experimental:module
    #set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (WIN32)


find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
enable_testing()


add_subdirectory(googletest)
add_subdirectory(wind1)

if(WIN32)
    set_target_properties(gmock gmock_main gtest gtest_main PROPERTIES FOLDER Gtest)
endif(WIN32)




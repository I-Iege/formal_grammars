
set(TARGET ui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


file(GLOB SRC
     "*.cpp"
     "*.ui"
     "*.h"
)


qt_add_executable(${TARGET} MANUAL_FINALIZATION ${SRC})

target_include_directories(${TARGET} PUBLIC .)

target_link_libraries(${TARGET} PUBLIC backend Qt6::Core Qt6::Widgets)

set_target_properties(${TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION 6.5
    MACOSX_BUNDLE_SHORT_VERSION_STRING 6.5
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_target(${TARGET})

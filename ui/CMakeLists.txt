
set(TARGET ui)

qt_standard_project_setup()


file(GLOB SRC
     "*.cpp"
     "*.ui"
     "*.h"
)


qt_add_executable(${TARGET} MANUAL_FINALIZATION ${SRC})

target_include_directories(${TARGET} PUBLIC .)

target_link_libraries(${TARGET} PUBLIC 
    backend 
    Qt6::Core 
    Qt6::Widgets 
)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)

target_link_libraries(${TARGET} PUBLIC 
    Qt6::QWindowsIntegrationPlugin
    Shcore.lib
    D3d9.lib
)

qt_import_plugins(${TARGET}
   INCLUDE Qt6::QWindowsIntegrationPlugin Qt6::QMinimalIntegrationPlugin
)

else()

target_link_libraries(${TARGET} PUBLIC 
    Qt6::QXcbIntegrationPlugin Qt6::XcbQpaPrivate
)

qt_import_plugins(${TARGET}
   INCLUDE Qt6::QXcbIntegrationPlugin
)
endif()

set_target_properties(${TARGET} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

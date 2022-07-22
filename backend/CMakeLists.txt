
set(TARGET backend)


file(GLOB SRC "*.cpp" )


add_library(${TARGET} STATIC ${SRC})

target_include_directories(${TARGET} PUBLIC .)
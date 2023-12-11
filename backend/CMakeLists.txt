
set(TARGET backend)


file(GLOB SRC "*.cpp" )
file(GLOB IXX "*.ixx" )
file(GLOB HEADERS "*.h" )


add_library(${TARGET} STATIC ${SRC} ${IXX} ${HEADERS})

target_include_directories(${TARGET} PUBLIC .)

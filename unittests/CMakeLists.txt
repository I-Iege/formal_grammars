set(TARGET unittest)

file(GLOB TARGET_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(${TARGET}
    ${TARGET_SRC}
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/wind1)
target_link_libraries(${TARGET} PRIVATE gtest_main backend)


add_test(NAME ${TARGET} COMMAND ${TARGET})

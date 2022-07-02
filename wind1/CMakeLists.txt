
set(TARGET wind1)


file(GLOB SRC
     "*.cpp"
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET} PUBLIC .)
project(Gol CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_compile_options(-std=c++2a)

include_directories(gollib)

add_subdirectory(main)
add_subdirectory(gollib)

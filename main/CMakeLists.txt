project(Gol CXX)

set(MAIN_SOURCES main.cpp)

include_directories(../gollib)

add_executable(Main ${MAIN_SOURCES})

target_link_libraries(Main gollib)
find_package(Threads)
target_link_libraries(Main Threads::Threads)
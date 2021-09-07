project(Gol CXX)

set(GOLLIB_SOURCES board.cpp GOLRules.cpp GOLRules.h gollib.h)

add_library(gollib STATIC ${GOLLIB_SOURCES})
find_package(Threads)
target_link_libraries(gollib Threads::Threads)
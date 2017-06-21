cmake_minimum_required(VERSION 3.6)
project(ART)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Program.cpp include/Program.h src/ART1.cpp include/ART1.h include/ART.h src/boosters.cpp include/boosters.h)
add_executable(ART ${SOURCE_FILES})
target_link_libraries(ART boost_filesystem boost_system)
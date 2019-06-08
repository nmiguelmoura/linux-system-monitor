cmake_minimum_required(VERSION 3.13)
project(system_monitor)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_INCLUDE_PATH "/usr/include")

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )

add_executable(system_monitor main.cpp utils.cpp processParser.cpp sys_info.cpp process.cpp processContainer.cpp)

target_link_libraries( system_monitor ${CURSES_LIBRARIES} )
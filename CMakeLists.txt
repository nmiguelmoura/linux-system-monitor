cmake_minimum_required(VERSION 3.13)
project(system_monitor)

set(CMAKE_CXX_STANDARD 17)

add_executable(system_monitor main.cpp utils.cpp process_parser.cpp sys_info.cpp process.cpp)
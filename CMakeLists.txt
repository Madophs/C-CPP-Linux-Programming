cmake_minimum_required(VERSION 3.10)

project(LinuxProgramming)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

# Very useful for youcompleteme plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(threads)
add_subdirectory(lpi_common)

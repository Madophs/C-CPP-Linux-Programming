cmake_minimum_required(VERSION 3.10)

project(LinuxProgramming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(threads)
#add_executable(hi threads/chronometer/chronometer.cpp)
#target_link_libraries(hi PUBLIC pthread)


#target_include_directories(LinuxProgramming PUBLIC
    #"${PROJECT_BINARY_DIR}"
    #"${PROJECT_SOURCE_DIR}/threads"
    #)

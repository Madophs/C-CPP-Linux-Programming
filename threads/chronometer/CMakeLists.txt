set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(chronometer chronometer.cpp)

target_link_libraries(chronometer PUBLIC pthread)


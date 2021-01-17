set(CMAKE_CXX_STANDARD 14 PRIVATE)
set(CMAKE_CXX_STANDARD_REQUIRED True PRIVATE)

add_executable(chronometer chronometer.cpp)

target_link_libraries(chronometer PUBLIC pthread)


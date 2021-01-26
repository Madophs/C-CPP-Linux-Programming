set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR}/lpi_common PRIVATE)
link_directories(${CMAKE_SOURCE_DIR}/lpi_common PRIVATE)

add_executable(env env.c)

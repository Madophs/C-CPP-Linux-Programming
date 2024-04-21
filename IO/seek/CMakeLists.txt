set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR}/lpi_common PRIVATE)
link_directories(${CMAKE_SOURCE_DIR}/lpi_common)

add_executable(seek_io seek_io.c)

target_link_libraries(seek_io PRIVATE lpicommon)

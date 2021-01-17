set(CMAKE_C_STANDARD 11 PRIVATE)
set(CMAKE_C_STANDARD_REQUIRED 11 PRIVATE)

add_library(liblpicommon error_functions.c get_num.c)

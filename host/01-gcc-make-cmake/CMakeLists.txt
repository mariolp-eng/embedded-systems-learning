cmake_minimum_required(VERSION 3.16)

project(ring_buffer LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror)

add_library(ring_buffer src/ring_buffer.c)					# Crea la biblioteca
target_include_directories(ring_buffer PUBLIC include)		# Añade el prefijo include a la ruta

add_executable(ring_buffer_demo src/main.c)					# Crea los ejecutables
add_executable(test_ring_buffer tests/test_ring_buffer.c)

target_link_libraries(ring_buffer_demo PRIVATE ring_buffer)	# Enlaza los ejecutables con la biblioteca
target_link_libraries(test_ring_buffer PRIVATE ring_buffer)


enable_testing()
add_test(NAME prueba COMMAND test_ring_buffer)
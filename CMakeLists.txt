cmake_minimum_required(VERSION 3.10)
project(gacha_term C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic)

file(GLOB_RECURSE SOURCES "src/*.c" "src/rendering/*.c")
list(FILTER SOURCES EXCLUDE REGEX ".*/shaders/.*\\.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE dl m -rdynamic)

add_library(plasma SHARED src/shaders/plasma.c)
target_include_directories(plasma PRIVATE src)
set_target_properties(plasma PROPERTIES PREFIX "")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS plasma DESTINATION bin)

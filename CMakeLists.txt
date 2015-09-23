cmake_minimum_required(VERSION 3.3)
project(AVL C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall")

find_package(PkgConfig REQUIRED)
pkg_check_modules(CJSON REQUIRED cjson)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS} ${CJSON_INCLUDE_DIRS})
link_directories(${GTK3_LIBRAYR_DIRS} {CJSON_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER} ${CSJON_CFLAGS_OTHER})

set(SOURCE_FILES main.c avl.c set.c sns.c gui.c)
add_executable(AVL ${SOURCE_FILES})

target_link_libraries(AVL ${GTK3_LIBRARIES} ${CJSON_LIBRARIES})

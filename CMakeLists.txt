cmake_minimum_required(VERSION 3.7)
project(elaborato_ING_SW)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -Wextra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

message(${CMAKE_MODULE_PATH})

find_package(PkgConfig)
find_package(SQLite3 REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${SQLITE3_INCLUDE_DIRS})

add_definitions(${GTKMM_CFLAGS} ${GTKMM_CFLAGS_OTHER})

set(SRC_DIR code/src)
set(HDR_DIR code/hdr)
set(MAIN_DIR code/mains)

include_directories(${CMAKE_SOURCE_DIR}/inc)

file(GLOB_RECURSE SRC "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${HDR_DIR}/*.hpp")
set(MAIN_CLI ${MAIN_DIR}/main_cli.cpp)
set(MAIN ${MAIN_DIR}/main.cpp)
set(MAIN_WINDOW ${MAIN_DIR}/main_window.cpp)

add_executable(elaborato ${MAIN} ${SRC} ${HDR})
add_executable(elaborato_cli ${MAIN_CLI} ${SRC} ${HDR})
add_executable(window ${MAIN_WINDOW} ${SRC} ${HDR})

target_link_libraries(elaborato ${GTKMM_LDFLAGS})
target_link_libraries(elaborato ${SQLITE3_LIBRARIES})
target_link_libraries(elaborato_cli ${SQLITE3_LIBRARIES})
target_link_libraries(elaborato_cli ${GTKMM_LDFLAGS})
target_link_libraries(window ${GTKMM_LDFLAGS})
target_link_libraries(window ${SQLITE3_LIBRARIES})


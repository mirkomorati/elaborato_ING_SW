cmake_minimum_required(VERSION 3.7)
project(elaborato_ING_SW)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}:${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(PkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_definitions(${GTKMM_CFLAGS} ${GTKMM_CFLAGS_OTHER})

set(SRC_DIR code/src)
set(HDR_DIR code/hdr)

include_directories(${CMAKE_SOURCE_DIR}/inc)

file(GLOB_RECURSE SRC "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${HDR_DIR}/*.hpp")

add_executable(elaborato ${SRC} ${HDR})
add_executable(elaborato_cli ${SRC_DIR}/main.cpp ${SRC_DIR}/Configuration.cpp
        ${HDR_DIR}/Configuration.hpp)

target_link_libraries(elaborato ${GTKMM_LDFLAGS})



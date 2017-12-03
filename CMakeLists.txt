cmake_minimum_required(VERSION 3.7)
project(elaborato_ING_SW)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -Wextra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

# debug mode 
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DDEBUG)
endif (${CMAKE_BUILD_TYPE} MATCHES Debug)

find_package(PkgConfig REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(FMT REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${SQLITE3_INCLUDE_DIRS})

add_definitions(${GTKMM_CFLAGS} ${GTKMM_CFLAGS_OTHER})

include_directories(${CMAKE_SOURCE_DIR}/inc)

file(GLOB_RECURSE SRC "code/*.cpp")
file(GLOB_RECURSE HDR "code/*.hpp")

set(MAIN code/main.cpp)
set(GLADE_FILES ${CMAKE_SOURCE_DIR}/glade/mainWindow.glade ${CMAKE_SOURCE_DIR}/glade/style.css ${CMAKE_SOURCE_DIR}/glade/logoverona.png)
set(CONF_FILE ${CMAKE_SOURCE_DIR}/tmp/config.json)

if (APPLE)
    # icon files to copy in the bundle
    set(OSX_ICON_FILES ${CMAKE_SOURCE_DIR}/glade/med-h.icns)
    file(GLOB_RECURSE OSX_ICON_SET "glade/icons.iconset/*.png")

    # set where in the bundle to put the icns files
    set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties(${OSX_ICON_SET} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/icon.iconset)
    set_source_files_properties(${CONF_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    # set where to put in the bundle the glade file
    set_source_files_properties(${GLADE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/glade)

    # setting up the defined variable GLADE_FILE_NAME
    add_definitions(-DGLADE_FILE_NAME="../Resources/glade/mainWindow.glade"
            -DGLADE_CSS_FILE="../Resources/glade/style.css" -DCONFIG_FILE="../Resources/config.json")

    add_executable(med-h MACOSX_BUNDLE ${MAIN} ${SRC} ${HDR} ${OSX_ICON_FILES} ${OSX_ICON_SET} ${GLADE_FILES} ${CONF_FILE})

    # configure CMake to use a custom Info.plist
    set_target_properties(med-h PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/tmp/med-h-Info.plist)

endif (APPLE)

target_link_libraries(med-h ${GTKMM_LDFLAGS})
target_link_libraries(med-h ${SQLITE3_LIBRARIES})
target_link_libraries(med-h fmt)



cmake_minimum_required(VERSION 3.15)
project(gtk3-getting-started)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_subdirectory(example0)
add_subdirectory(example1)
add_subdirectory(example2)
add_subdirectory(example3)
add_subdirectory(example4)

include(GSettings.cmake)

add_subdirectory(application1)
add_subdirectory(application2)
add_subdirectory(application3)
add_subdirectory(application4)
add_subdirectory(application5)
add_subdirectory(application6)
add_subdirectory(application7)
add_subdirectory(application8)
add_subdirectory(application9)
add_subdirectory(application10)

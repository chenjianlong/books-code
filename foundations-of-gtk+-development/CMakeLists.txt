cmake_minimum_required(VERSION 3.15)
project(foundations-of-gtk)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_subdirectory(ch02)
add_subdirectory(ch03)
add_subdirectory(exercise)

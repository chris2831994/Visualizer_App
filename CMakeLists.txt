cmake_minimum_required(VERSION 3.9)
project(gtkmm_mvc_test)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)
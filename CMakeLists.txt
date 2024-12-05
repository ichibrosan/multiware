##########################################################################
## daphne.goodall.com:/home/doug/CLionProjects/multiware/CMakeLists.txt ##
## copyright (c) Douglas Wade Goodall. All Rights Reserved.             ##
##########################################################################
## The purpose of this make file is to build the multiware framework    ##
## library and the multiware framework client program resulting in a    ##
## "multiware" executable and a "libmfw.a" static library and header.   ##
##########################################################################

cmake_minimum_required(VERSION 3.25.1)
project(multiware)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX clang++)

############################################
# 2024/12/03 03:15 dwg -
# While I am setting for the use of std 23,
#   "import std;" is not working with
#   cmake 3.25.1 and clang 14.0.6
# This is in conflict with
#   Beginning C++23 (7e) page 5
# I will still have to use explicit includes
############################################

add_library(mfw STATIC mfw.h mfw.cpp)
add_executable(multiware main.cpp)

target_link_libraries(multiware mfw)


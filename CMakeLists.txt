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
set(CMAKE_CXX_FLAGS_RELEASE "-fpermissive")
set(CMAKE_CXX_FLAGS_DEBUG   "-fpermissive")
############################################
# 2024/12/03 03:15 dwg -
# While I am setting for the use of std 23,
#   "import std;" is not working with
#   cmake 3.25.1 and clang 14.0.6
# This is in conflict with
#   Beginning C++23 (7e) page 5
# I will still have to use explicit includes
############################################

find_library(CGICC_LIB cgicc REQUIRED)


add_library(mfw STATIC
        mfw.cpp         mfw.h
        shared.cpp      shared.h
        html.cpp        html.h
        metainfo.cpp    metainfo.h
        termbind.cpp    termbind.h
        global.cpp
        global.h
        local.cpp
        local.h
        location.cpp
        location.h
        environment.cpp environment.h
        ascii.h
        forkproc.cpp
        forkproc.h
)

add_executable(multiware main.cpp
        std.h
)
target_link_libraries(multiware mfw)

add_executable(look look.cpp)
target_link_libraries(look mfw)

add_executable(mwcgi.cgi mwcgi.cpp
        mwcgi.cpp
        mwcgi.h
        cgishared.cpp
        cgishared.h
        cgihtml.cpp
        cgihtml.h
)
#target_link_libraries(mwcgi.cgi ${CGICC_LIB})

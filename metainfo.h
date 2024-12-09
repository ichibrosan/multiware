// daphne.goodall.com:/home/doug/CLionProjects/multiware/metainfo.h
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.

/**
 * The purpose of the metainfo class is to encapsulate functions and data
 * that regard the Standard Preprocessor Macros present in this compilation.
 */

#ifndef MULTIWARE_METAINFO_H
#define MULTIWARE_METAINFO_H

#include "mfw.h"

/******************************************************************
 * Prefined macros (Standard Preprocessor Macros)
 * See Beginning C++23 (7e) Ivor Horton & Peter Van Weert, page 871
 *****************************************************************/
class metainfo {
    std::string m_date;
    std::string m_time;
    int         m_line;
    std::string m_file;
    std::string m_func;
    std::string m_prettyfunc;
    long        m_cplusplus;
public:
    metainfo();
    void show();
};


#endif //MULTIWARE_METAINFO_H

// daphne.goodall.com:/home/doug/Projects/multiware/metainfo.cpp
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.

#include "mfw.h"

metainfo::metainfo()
{
    m_date = __DATE__;
    m_time = __TIME__;
    m_line = __LINE__;
    m_file = __FILE__;
    m_func = __FUNCTION__;
    m_prettyfunc = __PRETTY_FUNCTION__;
    m_cplusplus  = __cplusplus;
}

void metainfo::show()
{
    std::cout << "__DATE__           is " << m_date << std::endl;
    std::cout << "__TIME__           is " << m_time << std::endl;
    std::cout << "__LINE__           is " << m_line << std::endl;
    std::cout << "__FILE__           is " << m_file << std::endl;
    std::cout << "__FUNCTION__       is " << m_func << std::endl;
    std::cout << "__PRETTYFUNCTION__ is " << m_prettyfunc << std::endl;
    std::cout << "__cplusplus        is ";
    switch(m_cplusplus) {
        case 199711l: std::cout << "non-modern c++" << std::endl; break;
        case 201103l: std::cout << "C++11"          << std::endl; break;
        case 201402l: std::cout << "C++14"          << std::endl; break;
        case 201703l: std::cout << "C++17"          << std::endl; break;
        case 202002l: std::cout << "C++20"          << std::endl; break;
        case 202302l: std::cout << "C++23"          << std::endl; break;
        default:      std::cout << "C++Unknown("    <<
                        m_cplusplus << ")" << std::endl; break;
    }
}
//
// Created by doug on 12/11/24.
//

#include "mfw.h"

extern global * pG;

location::location()
{
    m_ssLogname = pG->pEnv->m_ssLogname;
//    std::cout << __FUNCTION__ << " says m_ssLogname is " << m_ssLogname
//              << std::endl;
}
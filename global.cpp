///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/global.cpp 2024/12/03 dwg - //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"
#include "global.h"

global::global()
{
    /**
     * termbind comes first so if CLEAR_SCREEN_ON_TERMBIND_CTOR is defined
     * the screen will be cleared and the cursor homed before all else.
     */
    pTerm      = new termbind();

    /**
     * environment CTOR fetches LOGNAME from the environment
     */
    pEnv       = new environment();

    pHtml      = new html((char *)"global.html");
    pShared    = new shared();

    pShared->m_pShMem->bIntegers = false;
    pShared->m_pShMem->bBoldEven = false;
    pShared->m_pShMem->bBoldOdd  = false;
    pShared->m_pShMem->bKeypad   = false;
    pShared->m_pShMem->forkproc.bRunning = true;

    //pLoc       = new location();

#ifdef FORKPROC_ENABLED
    pFork       = new forkproc();
#endif // FORKPROC_ENABLED

}

global::~global()
{

#ifdef FORKPROC_ENABLED
    delete pFork;
#endif // FORKPROC_ENABLED

    delete pShared;
    delete pHtml;
    delete pTerm;
    delete pEnv;
}

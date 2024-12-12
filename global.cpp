///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/global.cpp 2024/12/03 dwg - //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"
#include "global.h"

global::global()
{
    pEnv       = new environment();
    pTerm      = new termbind();
    pHtml      = new html((char *)"global.html");
    pShared    = new shared();
    //pLoc       = new location();
}

global::~global()
{
    delete pShared;
    delete pHtml;
    delete pTerm;
    delete pEnv;
}

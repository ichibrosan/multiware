//
// Created by doug on 12/11/24.
//

#include "mfw.h"

environment::environment()
{

   // m_processPid = getpid();

    char *pszLogname = getenv("LOGNAME");
    //printf("pszLogname -> %s\n",pszLogname);
    m_ssLogname = pszLogname;
}

//
// Created by doug on 12/11/24.
//

#ifndef MULTIWARE_GLOBAL_H
#define MULTIWARE_GLOBAL_H

#include "mfw.h"

class global {
public:
    global();
    ~global();
    environment * pEnv;
    html        * pHtml;
    shared      * pShared;
    termbind    * pTerm;
    location    * pLoc;

#ifdef FORKPROC_ENABLED
    forkproc    * pFork;
#endif // FORKPROC_ENABLED

};


#endif //MULTIWARE_GLOBAL_H

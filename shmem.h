//
// Created by doug on 12/19/24.
//

#ifndef MULTIWARE_SHMEM_H
#define MULTIWARE_SHMEM_H

#include <stdio.h>
#include "forkproc.h"
#include "vpa.h"

/**
 * If you change the MFW_SHMEM_T schema, you need to reboot to assure
 * that you don't use a stale shared memory segment that is mis-aligned.
 */
struct  MFW_SHMEM_T {
    int     iSignature;
    int     iVpaPort;
    char    szIdent[256];

    // SHM DEMO DATA
    bool    bBooleans[256];
    int     iIntegers[256];
    double  dDoubles[256];

    bool    bBoldEven;
    bool    bBoldOdd;

    char    szKeypadData[BUFSIZ];
    char    szPin[BUFSIZ];

    // forkproc data
    struct FORKPROC_DATA_T {
        forkproc_control_t control;     // See forkproc.h
        bool bRunning;
    } forkproc;

    vpa * pVPA;

} * m_pShMem;

#endif //MULTIWARE_SHMEM_H

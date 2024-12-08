///////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/CLionProjects/multiware/shared.cpp   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"
#include "shared.h"

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/**
 * ------ Shared Memory Segments --------
 * key        shmid      owner      perms      bytes      nattch     status
 * 0x00005164 37         doug       660        3592       0
 */

/***********************************************************************
 * Constructor for Shared Memory Class
 *      creates (if necessary) and attaches to MFW Shared Memory Segment
 ***********************************************************************/
shared::shared()
{
    printf("shard ctor\n");
    MFW
    key_t key = 0x5164;
    size_t size=sizeof(MFW_SHMEM_T);
    int shmflg = OBJ_PERMS;

    char szBuffer[BUFSIZ];
    sprintf(szBuffer,
            "shmget(key=0x%x,size=%ld,shmflg=0x%x);",
            key,size,shmflg);
    pMFW->log(szBuffer);
    m_smsi  = shmget(key,size,shmflg);
    if(-1 == m_smsi) {
        //decode_shmget_errno(errno);
        if(ENOENT == errno) {
            pMFW->log("Creating shared memory segment");
            shmflg = IPC_CREAT | OBJ_PERMS;
            sprintf(szBuffer,
                    "shmget(key=0x%x,size=%ld,shmflg=0x%x);",
                    key,size,shmflg);
            pMFW->log(szBuffer);
            m_smsi  = shmget(key,size,shmflg);
            if(-1==m_smsi) {
                decode_shmget_errno(errno);
            }
        }
    }
    shmflg = 0;
    sprintf(szBuffer,
            "shmat(smsi=0x%x,shmaddr=%p,shmflg=0x%x);",
            key,nullptr,shmflg);
    pMFW->log(szBuffer);
    m_pShMem  = (MFW_SHMEM_T *)shmat(m_smsi,nullptr,shmflg);
    if( (void *)-1 == m_pShMem) {
        printf("Error calling shmat\n");
        decode_shmat_errno(errno);
    }
    else
    {
        printf("Shared segment attached\n");
    }
}

/**
 *   struct  MFW_SHMEM_T {
 *      int     iSignature;
 *      char    szIdent[256];
 *      bool    bBooleans[256];
 *      int     iIntegers[256];
 *      double  dDoubles[256];
 *   } * m_pShMem;
 */

/***************************************
 * Dump shared memory region to log file
 **************************************/
void shared::dump_to_log()
{
    MFW
    pMFW->print("iSignature",m_pShMem->iSignature);
    pMFW->log("m_pShMem->bBooleans:");
    char szBuffer[BUFSIZ];
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d:  ",row*16);
        for(int col=0;col<16;col++) {
            if(m_pShMem->bBooleans[(row*16)+col]) {
                strcat(szBuffer,"true   ");
            } else
            {
                strcat(szBuffer,"false  ");
            }
        }
        pMFW->log(szBuffer);
    }

    pMFW->log("m_pShMem->iIntegers:");
    char szTemp[BUFSIZ];
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d: ",row*16);
        for(int col=0;col<16;col++) {
            sprintf(szTemp,"%6d ",
                    m_pShMem->iIntegers[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        pMFW->log(szBuffer);
    }

    pMFW->log("m_pShMem->dDoubles:");
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d: ",row*16);
        for(int col=0;col<16;col++) {
            m_pShMem->dDoubles[(row*16)+col] = 3.14;
            sprintf(szTemp,"%6g ",
                    m_pShMem->dDoubles[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        pMFW->log(szBuffer);
    }


}


/************************************************************
 * Decode errno coming from shmget
 * @param shm_errno
 ************************************************************/
void shared::decode_shmget_errno(int shm_errno)
{
    switch(shm_errno) {
        case EACCES:
            printf("errno was EACCESS\n");    break;
        case EEXIST:
            printf("errno was EEXIST\n");     break;
        case EINVAL:
            printf("errno was EINVALO\n");    break;
        case ENFILE:
            printf("errno was ENFILE\n");     break;
        case ENOENT:
            printf("errno was ENOENT\n");     break;
        case ENOMEM:
            printf("errno was ENOMEM\n");     break;
        case ENOSPC:
            printf("errno was ENOSPC\n");     break;
        case EPERM:
            printf("EPERM\n");                break;
        default:
            printf("errno was %d\n",errno);   break;
    }

}

/***********************************************************
 * Decode errno coming from shmat
 * @param shm_errno
 ***********************************************************/
void shared::decode_shmat_errno(int shm_errno)
{
    switch(shm_errno) {
        case EACCES:
            printf("errno was EACCESS\n");    break;
        case EIDRM:
            printf("errno was EIDRM\n");      break;
        case EEXIST:
            printf("errno was EEXIST\n");     break;
        case EINVAL:
            printf("errno was EINVAL\n");    break;
        default:
            printf("errno was %d\n",errno);   break;
    }

}

/*******************************************
 * Get the Shared Memory Segment Identifier
 * @return
 *******************************************/
[[maybe_unused]] int shared::get_smsi() const
{
    return m_smsi;
}

/**************************
 * Shared memory destructor
 *************************/
shared::~shared()
{
    shmdt(m_pShMem);
}

//////////////////////
// eof - shared.cpp //
//////////////////////
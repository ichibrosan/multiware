///////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/CLionProjects/multiware/shared.cpp   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"
#include "shared.h"
extern global * pG;

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/**
 * ------ Shared Memory Segments --------
 * key        shmid      owner      perms      bytes      nattch     status
 * 0x00005164 37         doug       660        3592       0
 */

//+
// termbind * pTerm;

/***********************************************************************
 * Constructor for Shared Memory Class
 *      creates (if necessary) and attaches to MFW Shared Memory Segment
 ***********************************************************************/
shared::shared()
{
    MFW



    // Set key to hex version of my VPA port number (recognizable)
    key_t key = 0x5164;

    // Set size to the size of my shared data structure (member data)
    size_t size=sizeof(MFW_SHMEM_T);

    // Set shmFlg with read/write permissions, so I can access
    // the shared region once created. See shared.h
    int shmflg = OBJ_PERMS;

    // Log the parameters I am going to use to open the shared segment
    char szBuffer[BUFSIZ];
    sprintf(szBuffer,
            "shmget(key=0x%x,size=%ld,shmflg=0x%x);",
            key,size,shmflg);
    pMFW->log(szBuffer);

    m_smsi  = shmget(key,size,shmflg);
    // Test to see if we open the segment successfully
    if(-1 == m_smsi) {
        //decode_shmget_errno(errno);
        if(ENOENT == errno) {
            // ENOENT means no segment exists and create not specified
            pMFW->log("Creating shared memory segment");
            shmflg = IPC_CREAT | OBJ_PERMS;

            // Log the parameters I am using to create the segment
            sprintf(szBuffer,
                    "shmget(key=0x%x,size=%ld,shmflg=0x%x);",
                    key,size,shmflg);
            pMFW->log(szBuffer);

            // Create the memory segment and save the identifier
            m_smsi  = shmget(key,size,shmflg);

            if(-1==m_smsi) {
                decode_shmget_errno(errno);
                std::cout << "ERROR: unable to open shared segment"
                          << std::endl;
            }
        }
    }

    // Prepare to attach shared segment using shmat
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

    m_pShMem->iSignature = UNIVERSAL_ANSWER;
    // end of shared ctor
}



/**  Note: Defined in shared.h
 *
 *   struct  MFW_SHMEM_T {
 *      int     iSignature;
 *      char    szIdent[256];
 *      bool    bBooleans[256];
 *      int     iIntegers[256];
 *      double  dDoubles[256];
 *   } * m_pShMem;
 *
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
                strcat(szBuffer,"     true   ");
            } else
            {
                strcat(szBuffer,"     false  ");
            }
        }
        pMFW->log(szBuffer);
    }

    pMFW->log("m_pShMem->iIntegers:");
    char szTemp[BUFSIZ];
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d: ",row*16);
        for(int col=0;col<16;col++) {
            sprintf(szTemp,"%11d ",
                    m_pShMem->iIntegers[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        pMFW->log(szBuffer);
    }

    pMFW->log("m_pShMem->dDoubles:");
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d:    ",row*16);
        for(int col=0;col<16;col++) {
            //m_pShMem->dDoubles[(row*16)+col] = 3.14;
            sprintf(szTemp,"%8.6f    ",
                    m_pShMem->dDoubles[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        pMFW->log(szBuffer);
    }


}


/**********************************************************
 * Display the contents of the shared region on the console
 **********************************************************/
void shared::dump_to_screen()
{
    pG->pTerm->crtcntl(SGR,FG_WHITE);
    printf("daphe.goodall.com:/home/doug/CLionProjects/"
          "multiware/look.cpp  ");
    printf("Copyright (C) 2024 Douglas Wade Goodall. "
           "All Right s Reserved.\n\n");
//    printf("%c[38:5:91m",27);
    printf("pG->pShared->pShMem->iSignature is %d\n",
           pG->pShared->m_pShMem->iSignature);

    pG->pTerm->crtcntl(SGR,FG_RED);
    printf("pG->pShared->m_pShMem->bBooleans:\n");
    char szBuffer[BUFSIZ];
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d:  ",row*16);
        for(int col=0;col<16;col++) {
            if(pG->pShared->m_pShMem->bBooleans[(row*16)+col]) {
                strcat(szBuffer,"     true   ");
            } else
            {
                strcat(szBuffer,"     false  ");
            }
        }
        printf("%s\n",szBuffer);
    }

    pG->pTerm->crtcntl(SGR,FG_GREEN);
    printf("pG->pShared->m_pShMem->iIntegers:\n");
    char szTemp[BUFSIZ];
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d: ",row*16);
        for(int col=0;col<16;col++) {
            sprintf(szTemp,"%11d ",
                    pG->pShared->m_pShMem->iIntegers[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        printf("%s\n",szBuffer);
    }

    pG->pTerm->crtcntl(SGR,FG_BLUE);
    printf("pG->pShared->m_pShMem->dDoubles:\n");
    for(int row=0;row<16;row++) {
        sprintf(szBuffer,"%3d:    ",row*16);
        for(int col=0;col<16;col++) {
            //m_pShMem->dDoubles[(row*16)+col] = 3.14;
            sprintf(szTemp,"%8.6f    ",
                    pG->pShared->m_pShMem->dDoubles[(row*16)+col]);
            strcat(szBuffer,szTemp);
        }
        printf("%s\n",szBuffer);
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
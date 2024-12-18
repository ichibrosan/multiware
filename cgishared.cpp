///////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/CLionProjects/multiware/shared.cpp   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "std.h"
#include "cgishared.h"

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
cgishared::cgishared()
{
    // Set key to hex version of my VPA port number (recognizable)
    key_t key = 0x5164;

    // Set size to the size of my shared data structure (member data)
    size_t size=sizeof(MFW_SHMEM_T);

    // Set shmFlg with read/write permissions, so I can access
    // the shared region once created. See shared.h
    int shmflg = OBJ_PERMS;

    m_smsi  = shmget(key,size,shmflg);
    // Test to see if we open the segment successfully
    if(-1 == m_smsi) {
        //decode_shmget_errno(errno);
        if(ENOENT == errno) {
            // ENOENT means no segment exists and create not specified
            shmflg = IPC_CREAT | OBJ_PERMS;

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
    // Establish addressability to shared segment
    m_pShMem  = (MFW_SHMEM_T *)shmat(m_smsi,nullptr,shmflg);

    if( (void *)-1 == m_pShMem) {
        printf("Error calling shmat\n");
        decode_shmat_errno(errno);
    }

    m_pShMem->iSignature = UNIVERSAL_ANSWER;
    m_pShMem->forkproc.control = forkproc_control_t::ControlIdle;

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


/************************************************************
 * Decode errno coming from shmget
 * @param shm_errno
 ************************************************************/
void cgishared::decode_shmget_errno(int shm_errno)
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
void cgishared::decode_shmat_errno(int shm_errno)
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
[[maybe_unused]] int cgishared::get_smsi() const
{
    return m_smsi;
}

/**************************
 * Shared memory destructor
 *************************/
cgishared::~cgishared()
{
    shmdt(m_pShMem);
}

/////////////////////////
// eof - cgishared.cpp //
/////////////////////////
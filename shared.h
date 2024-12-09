/////////////////////////////////////////////////////////////////
// daphne.goodall.com/home/doug/CLionProjects/multiware/shared.h
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
/////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_SHARED_H
#define MULTIWARE_SHARED_H

// Used for shared segment signature
// See Douglas Adam, Hitchhiker's Guide et al.
#define UNIVERSAL_ANSWER 42

/************************************************************
 * A class to provide function and data for handling a shared
 * memory segment.
 ***********************************************************/
class shared {
    int m_smsi;     // shared memory segment identifier

    /**
     * If you change the MFW_SHMEM_T structure, you must reboot
     * Linux before running the program again. This gets rid of
     * the existing shared segment with old schema/length.
     */
    struct  MFW_SHMEM_T {
        int     iSignature;
        [[maybe_unused]] char    szIdent[256];
        bool    bBooleans[256];
        int     iIntegers[256];
        double  dDoubles[256];
    } * m_pShMem;

public:
    shared();

    [[maybe_unused]] [[nodiscard]] int get_smsi() const;
    static void decode_shmget_errno(int);
    static void decode_shmat_errno(int);
    void dump_to_log();
    ~shared();
};

#endif //MULTIWARE_SHARED_H

////////////////////
// eof - shared/h //
////////////////////

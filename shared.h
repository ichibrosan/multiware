/////////////////////////////////////////////////////////////////
// daphne.goodall.com/home/doug/CLionProjects/multiware/shared.h
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
/////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_SHARED_H
#define MULTIWARE_SHARED_H

// Used for shared segment signature
// See Douglas Adam, Hitchhiker's Guide et al.
#define UNIVERSAL_ANSWER 42

// See Beginning C++23 Page 97 for usage of enum class
enum class forkproc_control_t {
    ControlQuiescent,   // uninitialized state
    ControlIdle,
    ControlStep,
    ControlRun,
    ControlTerm
};

/************************************************************
 * A class to provide function and data for handling a shared
 * memory segment.
 ***********************************************************/
class shared {
    int m_smsi;     // shared memory segment identifier

public:
    shared();

    [[maybe_unused]] [[nodiscard]] int get_smsi() const;
    static void decode_shmget_errno(int);
    static void decode_shmat_errno(int);

#ifndef CGI
    void dump_to_log();
    void dump_to_screen();
#endif // DISABLE_SHARED_DUMPS

    ~shared();

    /**
      * If you change the MFW_SHMEM_T structure, you must reboot
      * Linux before running the program again. This gets rid of
      * the existing shared segment with old schema/length.
      */
    struct  MFW_SHMEM_T {
        int     iSignature;
        char    szIdent[256];

        // SHM DEMO DATA
        bool    bBooleans[256];
        int     iIntegers[256];
        double  dDoubles[256];

        // forkproc data
        struct FORKPROC_DATA_T {
            forkproc_control_t control;
            bool bRunning;
        } forkproc;



    } * m_pShMem;

};

#endif //MULTIWARE_SHARED_H

////////////////////
// eof - shared/h //
////////////////////

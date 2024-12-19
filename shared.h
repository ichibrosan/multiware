/////////////////////////////////////////////////////////////////
// daphne.goodall.com/home/doug/CLionProjects/multiware/shared.h
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
/////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_SHARED_H
#define MULTIWARE_SHARED_H

// Used for shared segment signature
// See Douglas Adam, Hitchhiker's Guide et al.
#define UNIVERSAL_ANSWER 42

//// See Beginning C++23 Page 97 for usage of enum class
//enum class forkproc_control_t {
//    ControlQuiescent,   // uninitialized state
//    ControlIdle,
//    ControlStep,
//    ControlRun,
//    ControlTerm
//};

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

#include "shmem.h"


};

#endif //MULTIWARE_SHARED_H

////////////////////
// eof - shared/h //
////////////////////

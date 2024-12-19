////////////////////////////////////////////////////////////////////
// daphne.goodall.com/home/doug/CLionProjects/multiware/cgishared.h
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CGISHARED_H
#define MULTIWARE_CGISHARED_H

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
class cgishared {
    int m_smsi;     // shared memory segment identifier

public:
    cgishared();
    [[maybe_unused]] [[nodiscard]] int get_smsi() const;
    static void decode_shmget_errno(int);
    static void decode_shmat_errno(int);
    ~cgishared();

#include "shmem.h"

};

#endif //MULTIWARE_CGISHARED_H

///////////////////////
// eof - cgishared.h //
///////////////////////

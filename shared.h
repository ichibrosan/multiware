//
// Created by doug on 12/8/24.
//

#ifndef MULTIWARE_SHARED_H
#define MULTIWARE_SHARED_H


class shared {
    int m_smsi;     // shared memory segment identifier
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

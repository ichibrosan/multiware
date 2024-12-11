//
// Created by doug on 12/9/24.
//

#include "mfw.h"
#include "look.h"

shared      * g_pShared = nullptr;
termbind    * g_pTerm   = nullptr;

int main() {
    MFW;

    // Instantiate Shared Segment support
    g_pShared = new shared();
    g_pTerm = new termbind();
    g_pTerm->crtclr();

    while (1) {
        g_pTerm->crtcntl(CUP,1, 1);


        g_pShared->dump_to_screen();

        sleep(1);
    }

    assert(g_pShared != nullptr);
    assert(g_pShared->m_pShMem != nullptr);
    g_pShared->m_pShMem->iSignature++;

    return 0;
}

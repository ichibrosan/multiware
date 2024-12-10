//
// Created by doug on 12/9/24.
//

#include "mfw.h"
#include "look.h"

shared      * pShared = nullptr;
termbind    * pTerm   = nullptr;

int main() {
    MFW;

    // Instantiate Shared Segment support
    pShared = new shared();
    pTerm = new termbind();
    pTerm->crtclr();

    while (1) {
        pTerm->crtlc(3, 1);


        pShared->dump_to_screen();

        sleep(1);
    }

    assert(pShared != nullptr);
    assert(pShared->m_pShMem != nullptr);
    pShared->m_pShMem->iSignature++;

    return 0;
}

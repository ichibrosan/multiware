//
// Created by doug on 12/9/24.
//

#include "mfw.h"
#include "look.h"

shared      * pShared = nullptr;


int main()
{
    MFW;

    // Instantiate Shared Segment support
    pShared = new shared();

    // Display the Shared Segment Signature s/b 42
    printf("Signature is %d\n",pShared->m_pShMem->iSignature);

    return 0;
}

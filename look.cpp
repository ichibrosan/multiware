//
// Created by doug on 12/9/24.
//

#include "mfw.h"
#include "look.h"

// Declare a global pointer to the instance
// of the Multiware Framework global class.
global * pG = nullptr;

int main() {
    pG = new global();
    while (1) {
        pG->pTerm->crtcntl(CUP,1,1);
        pG->pShared->dump_to_screen();
        sleep(1);
    }

    return 0;
}

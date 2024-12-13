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
    pG->pTerm->crtclr();

    int line; int column;
    pG->pTerm->crtcntl(CUP,line=1,column=1);

    printf("look Copyright %c 2024 Douglas Wade Goodall. "
           "All Rights Reserved."
           "\n",ASCII_COPR);

//    pid_t myPid = getpid();
//    printf("my pid is %d\n",myPid);

/**
 * Appears here for reference
 */
//    enum SGR_T {
//        SGR_RESET,
//        SGR_BOLD,
//        SGR_FAINT,
//        SGR_ITALIC,
//        SGR_UNDERLINE,
//        SGR_SLOW_BLINK,
//        SGR_RAPID_BLINK
//    };

//    pG->pTerm->crtcntl(SGR,SGR_BOLD);
//    pG->pTerm->crtcntl(SGR,SGR_ITALIC);
//    pG->pTerm->crtcntl(SGR,SGR_UNDERLINE);

    while (1) {
        pG->pTerm->crtcntl(CUP,line=3,column=1);
        //std::cout << pG->pEnv->m_ssLogname << std::endl;
        pG->pShared->dump_to_screen();
        sleep(1);
    }

    return 0;
}

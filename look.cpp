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

    pid_t myPid = getpid();
    printf("my pid is %d\n",myPid);

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
        pG->pTerm->crtcntl(CUP,1,1);
        std::cout << pG->pEnv->m_ssLogname << std::endl;
        pG->pShared->dump_to_screen();
        sleep(1);
    }

    return 0;
}

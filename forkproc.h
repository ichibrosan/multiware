//
// Created by doug on 12/16/24.
//

#ifndef MULTIWARE_FORKPROC_H
#define MULTIWARE_FORKPROC_H

#include "mfw.h"


class forkproc {
 public:
    forkproc();
    void idle();
    void step();
    void run();
    void term();
    ~forkproc();
};


#endif //MULTIWARE_FORKPROC_H

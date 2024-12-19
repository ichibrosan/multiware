//
// Created by doug on 12/16/24.
//

#ifndef MULTIWARE_FORKPROC_H
#define MULTIWARE_FORKPROC_H

//#include "mfw.h"

// See Beginning C++23 Page 97 for usage of enum class
enum class forkproc_control_t {
    ControlQuiescent,   // uninitialized state
    ControlIdle,
    ControlStep,
    ControlRun,
    ControlTerm
};


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

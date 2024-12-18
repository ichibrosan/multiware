//
// Created by doug on 12/16/24.
//

#include "mfw.h"
extern global * pG;

forkproc::forkproc()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    pG->pShared->m_pShMem->forkproc.control =
            forkproc_control_t::ControlIdle;
    while(1) {
        switch(pG->pShared->m_pShMem->forkproc.control) {
            case forkproc_control_t::ControlIdle:
                idle();
                break;
            case forkproc_control_t::ControlStep:
                step();
                break;
            case forkproc_control_t::ControlRun:
                run();
                break;
            case forkproc_control_t::ControlTerm:
                term();
                break;
        }

        sleep(1);
    }
}

void forkproc::idle()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


void forkproc::step()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    pG->pShared->m_pShMem->forkproc.control = forkproc_control_t::ControlIdle;
}

void forkproc::run()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void forkproc::term()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

forkproc::~forkproc()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
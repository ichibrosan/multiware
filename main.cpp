///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/main.cpp 2024/12/03 dwg -   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"


global * pG = nullptr;

/**
 * Demonstrate an overloaded function
 */
void demoPrint()
{
    // Instantiate an instance of the MultiWare Framework for this function
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EmptyDeclOrStmt"
    MFW;
#pragma clang diagnostic pop
    WHERE

    // Examples of Overloaded Function Calls to print logging function

    // Setup sample data of various types
    bool bBoolean = true;
    double dPi = 3.1415926535;
    int iInteger = 42;
    std::string stdstrHello = "Hello";

    // These print calls vary only in the type of the parameter
    pMFW->print("bBoolean",bBoolean);
    pMFW->print("dPi",dPi);
    pMFW->print("iInteger",iInteger);
    pMFW->print("stdstrHello",stdstrHello);

}

/*********************************************************************
 * Main Entry Point of MultiWare application
 * @param argc Number of formal parameters
 * @param argv Pointer to array of pointers to arguments
 * @return Returns in integer status code EXIT_SUCCESS or EXIT_FAILURE
 ********************************************************************/
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    pG = new global();

    // Instantiate an instance of the MultiWare Framework for this function
    MFW
    WHERE

#ifdef DISPLAY_METAINFO
    // See macro definition above
    pMFW->m_pMeta->show();
#endif // DISPLAY_METAINFO


#ifdef DUMP_SHARED_CONTENTS
    // Dump the current contents of the shared region.
    // See macro definition above
    pG->pShared->dump_to_log();
#endif // DUMP_SHARED_CONTENTS

    // Create a default web page at http://localhost/~doug
    // using the get_home member function of the mfw class.
    char szFQFS[FILENAME_MAX];
    sprintf(szFQFS,"%s/public_html/index.html",
            pMFW->get_home().c_str());
#ifdef DEBUG_MAIN
    // See macro definition above
    printf("szFQFS is %s\n",szFQFS);
#endif // DEBUG_MAIN


#ifdef DEBUG_MAIN
    // See macro definition above
    std::cout << "LOGNAME  is " << pMFW->get_logname() << std::endl;
    std::cout << "PWD      is " << pMFW->get_pwd()     << std::endl;
#endif // DEBUG_MAIN

#ifdef DEMO_OVERLOADED_FUNCTION
    // See macro definition above
    demoPrint();
#endif // DEMO_OVERLOADED_FUNCTION


#ifdef RANDOMIZE_SHARED_REGION
    std::cout << "Randomizing Shared Memory Segment" << std::endl;
    while(1) {
        if(pG->pShared->m_pShMem->forkproc.bRunning == true) {
            for (int i = 0; i < 256; i++) {
                int r = rand();
                if (r & 1) {
                    pG->pShared->m_pShMem->bBooleans[i] = true;
                } else {
                    pG->pShared->m_pShMem->bBooleans[i] = false;
                }
            }
            for (int i = 0; i < 256; i++) {
                pG->pShared->m_pShMem->iIntegers[i] = rand() & 255;
            }
            for (int i = 0; i < 256; i++) {
                pG->pShared->m_pShMem->dDoubles[i] = drand48();
            }
        }
        //pG->pShared->dump_to_log();
       sleep(1);
   }
#endif // RANDOMIZE_SHARED_REGION

    delete pG;

    return EXIT_SUCCESS;
}

////////////////////
// eof - main.cpp //
////////////////////



///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/main.cpp 2024/12/03 dwg -   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"

void tempfunc()
{

}

/*********************************************************************
 * Main Entry Point of MultiWare application
 * @param argc Number of formal parameters
 * @param argv Pointer to array of pointers to arguments
 * @return Returns in integer status code EXIT_SUCCESS or EXIT_FAILURE
 ********************************************************************/
int main(int argc,char **argv) {

    // Instantiate an instance of the MultiWare Framework for this function
    MFW;
    WHERE;

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

    return EXIT_SUCCESS;
}

////////////////////
// eof - main.cpp //
////////////////////



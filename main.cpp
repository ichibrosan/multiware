///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/main.cpp 2024/12/03 dwg -   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"

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


shared * g_pShared;

/*********************************************************************
 * Main Entry Point of MultiWare application
 * @param argc Number of formal parameters
 * @param argv Pointer to array of pointers to arguments
 * @return Returns in integer status code EXIT_SUCCESS or EXIT_FAILURE
 ********************************************************************/
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
     // Instantiate an instance of the MultiWare Framework for this function
    MFW
    WHERE
    g_pShared = new shared();
    g_pShared->dump_to_log();

    html *pHtml = new html((char *)"/home/doug/public_html/index.html");
    pHtml->open_head();
    pHtml->title((char *)"Hello Test");
    pHtml->close_head();
    pHtml->open_body();
    pHtml->print((char *)"      Hello World!!");
    pHtml->close_body();
    delete pHtml;

//    std::cout << "LOGNAME  is " << pMFW->get_logname() << std::endl;
//    std::cout << "PWD      is " << pMFW->get_pwd()     << std::endl;

    demoPrint();

    return EXIT_SUCCESS;
}

////////////////////
// eof - main.cpp //
////////////////////



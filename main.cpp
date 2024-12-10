///////////////////////////////////////////////////////////////////
// home/doug/CLionProjects/multiware/main.cpp 2024/12/03 dwg -   //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mfw.h"

/***************************************
 * Conditional Feature Support Macros
 ***************************************/
#define DEBUG_MAIN
// #define DEMO_OVERLOADED_FUNCTION
// #define DISPLAY_METAINFO
// #define DUMP_SHARED_CONTENTS
//#define RANDOMIZE_SHARED_REGION

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

/**
 * This global pointer to the instance of the shared class
 * assures we will have addressability to the shared data
 * from anywhere
 */
shared * g_pShared;
termbind * g_pTerm;

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

#ifdef DISPLAY_METAINFO
    // See macro definition above
    pMFW->m_pMeta->show();
#endif // DISPLAY_METAINFO

    // Instantiate the shared class and set the global pointer.
    g_pShared = new shared();

    g_pTerm = new termbind();
    g_pTerm->crtclr();

#ifdef DUMP_SHARED_CONTENTS
    // Dump the current contents of the shared region.
    // See macro definition above
    g_pShared->dump_to_log();
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
    html *pHtml = new html(szFQFS);
    pHtml->open_head();
    pHtml->title((char *)"Multiware Framework Console");
    pHtml->close_head();
    pHtml->open_body();
    pHtml->imgsrc((char *)"https://mainframe.goodall.com/images/services.png");
    pHtml->print((char *)"<p>");
    pHtml->ahref((char *)"http://localhost/~doug/file.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/File.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/edit.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Edit.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/view.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/View.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/navigate.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Navigate.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/code.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Code.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/refactor.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Refactor.png\">\n");
    pHtml->ahref((char *)"http://localhost/~doug/buiild.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Build.png\">\n");
    pHtml->ahref((char *)"https://localhost/~doug/run.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Run.png\">\n");
    pHtml->ahref((char *)"https://localhost/~doug/tools.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Tools.png\">\n");
    pHtml->ahref((char *)"https://localhost/~doug/window.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Window.png\">\n");
    pHtml->ahref((char *)"https://localhost/~doug/help.cgi",(char *)
                 "<img src=\"https://mainframe.goodall.com/images/Help.png\">\n");
    pHtml->close_body();
    delete pHtml;

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
   while(1) {
       for(int i=0;i<256;i++) {
           int r = rand();
           if(r & 1) {
               g_pShared->m_pShMem->bBooleans[i] = true;
           }
           else
           {
               g_pShared->m_pShMem->bBooleans[i] = false;
           }
       }
       for (int i = 0; i < 256; i++) {
           g_pShared->m_pShMem->iIntegers[i] = rand();
       }
       for(int i=0;i<256;i++) {
           g_pShared->m_pShMem->dDoubles[i] = drand48();
       }
       g_pShared->dump_to_log();
       sleep(5);
   }
#endif // RANDOMIZE_SHARED_REGION




    return EXIT_SUCCESS;
}

////////////////////
// eof - main.cpp //
////////////////////



///////////////////////////////////////////////////////////////////////
// /home/doug/CLionProjects/multiware/mfw.h 2024/12/03 dwg - created //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.     //
///////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_MFW_H
#define MULTIWARE_MFW_H

#include <string.h>
#include <time.h>

#define MFW_DELETE_LOGS_ON_MAIN_STARTUP
#define MFW_LOG_PARMS_ON_MFW_INSTANTIATION
#define MFW_LOG_ENTRY_TO_FUNCTION

/*****************************************************************
 * This macro is used on entry to a function to create a framework
 * instance within the function's scope. Subsequently, calls can
 * be made to member functions using the pointer.
 * i.e. pMFW->log("This is an example");
 *****************************************************************/
#define MFW mfw * pMFW = new mfw( \
    __FUNCTION__,__PRETTY_FUNCTION__,__FILE__,__LINE__);

/*****************************************************************
 * This macro is used somewhere in a MFW enabled function to log
 * the current execution location for debugging.
 *****************************************************************/
#define WHERE pMFW->where( \
    __FUNCTION__,__PRETTY_FUNCTION__,__FILE__,__LINE__);

/**************************************************
 * This is the MultiWare Framework Top Level Class
 *************************************************/
class mfw {
    std::string m_stdstrPrettyFunction; // __PRETTY_FUNCTION__
    std::string m_stdstrFunction;       // __FUNCTION__
    std::string m_stdstrFile;           // __FILE__
    int         m_iLine;                // __LINE__
    std::string m_stdstrLogFQFS;
    std::string m_stdstrHomeFQFS;       // getenv("HOME");
public:
    mfw(const char *,const char *,const char *,int);
    void where(const char *,const char *,const char *,int);
    // Member Data Getters
    std::string get_file();
    std::string get_home();

    std::string get_date_and_time();
    void log(const char *);
    ~mfw();
};


#endif //MULTIWARE_MFW_H

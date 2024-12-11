///////////////////////////////////////////////////////////////////////
// /home/doug/CLionProjects/multiware/mfw.h 2024/12/03 dwg - created //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.     //
///////////////////////////////////////////////////////////////////////
// 2024/12/08 05:46 dwg - added VPA TCP/UDP Assigned Numbers         //
///////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_MFW_H
#define MULTIWARE_MFW_H

// Emulate "import std;"
#include "std.h"
// Multiware FrameWork class headers
#include "shared.h"
#include "html.h"
#include "metainfo.h"
#include "termbind.h"
#include "global.h"



#define MFW_DELETE_LOGS_ON_MAIN_STARTUP
#define MFW_LOG_PARMS_ON_MFW_INSTANTIATION
#define MFW_LOG_ENTRY_TO_FUNCTION

//extern termbind * g_pTerm;

/*******************************************************************
 * From https://www.iana.org/assignments/service-names-port-numbers/
 *      service-names-port-numbers.xml
 *******************************************************************/
#define VPA_PORT      5164
#define VPA_DISC_PORT 5164

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
    std::string m_stdstrLogname;        // getenv("LOGNAME");
    std::string m_stdstrPwd;            // getenv("PWD");
public:
    mfw(const char *,const char *,const char *,int);
    // Member Data Getters
    static std::string get_date_and_time();
    [[maybe_unused]] std::string get_file();
    std::string get_home();

    [[maybe_unused]] std::string get_logname();
    [[maybe_unused]] std::string get_pwd();

    void log(const char *);

    [[maybe_unused]] void print(const std::string&,bool);
    void print(const std::string&,double);
    void print(const std::string&,int);
    void print(const std::string&,const std::string&);

    void where(const char *,
               [[maybe_unused]] const char *,
               const char *,
               [[maybe_unused]] int);
    ~mfw();

    shared   * m_pShared;
    metainfo * m_pMeta;
};


#endif //MULTIWARE_MFW_H

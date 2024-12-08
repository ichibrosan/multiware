//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/CLionProjects/multiware/mfw.cpp 2024/12/05
// copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
//////////////////////////////////////////////////////////////////////////////

#include "mfw.h"

/***********************************************************
 * This is the constructor for the multiware framework class
 * @param pszFunction
 * @param pszPrettyFunction
 * @param pszFile
 **********************************************************/
mfw::mfw(const char *pszFunction,
         const char *pszPrettyFunction,
         const char *pszFile,
         int        iLine) {

    // Save caller's parameters in class private member data
    m_stdstrFunction        = pszFunction;
    m_stdstrPrettyFunction  = pszPrettyFunction;
    m_stdstrFile            = pszFile;
    m_iLine                 = iLine;

    // Allocate C string buffer for fully qualified file specification
    char szFQFS[FILENAME_MAX];

    // Format filename string placing it in my Apache USERDIR
    sprintf(szFQFS,"%s/public_html/log/%s.log",
            get_home().c_str(),m_stdstrFunction.c_str());

    // Save copy of file specification in private member data for later
    m_stdstrLogFQFS = szFQFS;

#ifdef MFW_DELETE_LOGS_ON_MAIN_STARTUP
    // Allocate buffer for C string to hold "rm" command for "system" call
    char szLogFQAFN[BUFSIZ];

    // Set buffer to "%s/public_html/log/%s.log"
    strcpy(szLogFQAFN,szFQFS);

    // Trim off the %s.log on the end of the string
    szLogFQAFN[strlen(szLogFQAFN)-8] = 0;

    // Append the ambiguous file name to delete all logs
    strcat(szLogFQAFN,"*.log");

    // Allocate a C string buffer for the command we are building
    char szCommand[BUFSIZ];

    // Format the command for system call
    sprintf(szCommand,"rm -f %s",szLogFQAFN);

    // printf("command is %s\n",szCommand);

    // Execute command to remove all logs by calling "system"
    system(szCommand);
#endif // MFW_DELETE_LOGS_ON_MAIN_STARTUP

#ifdef MFW_LOG_PARMS_ON_MFW_INSTANTIATION
    // Allocate a  C string buffer used to construct a log entry
    char szLogData[BUFSIZ];

    log("**********************************************************"
      "********************************************************************");

    // Format the log entry using caller's parameters
    sprintf(szLogData,
            "MFW instance created by "
            "file=%s:%d function=%s prettyfunction=%s",
            m_stdstrFile.c_str(),
            m_iLine,
            m_stdstrFunction.c_str(),
            m_stdstrPrettyFunction.c_str());
    // Call "log" member function to write log entry
    log((const char *)szLogData);
#endif // MFW_LOG_PARMS_ON_MFW_INSTANTIATION


}

/**************************************
 * Log the current location and context
 * @param pszFunction
 * @param pszPrettyFunction
 * @param pszFile
 * @param iLine
 **************************************/
void mfw::where(const char *pszFunction,
                [[maybe_unused]] const char *pszPrettyFunction,
           const char *pszFile,
                [[maybe_unused]] int iLine)
{
#ifdef MFW_LOG_ENTRY_TO_FUNCTION
// Allocate a  C string buffer used to construct a log entry
char szLogData[BUFSIZ];

// Format the log entry using caller's parameters
sprintf(szLogData,
    "Running Function %s in file %s at Line %d ",
    pszFunction,pszFile,m_iLine);

// Call "log" member function to write log entry
log((const char *)szLogData);
#endif // MFW_LOG_ENTRY_TO_FUNCTION

}

/***********************************************************
 * Get the filename of the caller's source code
 * @return Return the caller source code FQFS as std::string
 **********************************************************/
[[maybe_unused]] std::string mfw::get_file()
{
    // Return the caller's __FILE__ data from private member data
    return m_stdstrFile;
}

/**************************************************************************
 * Get the fully qualified directory specification of the caller's home dir
 * @return
 *************************************************************************/
std::string mfw::get_home()
{
    // Save and return the contents of the "HOME" environment variable
    return m_stdstrHomeFQFS = getenv("HOME");
}

/**************************************************************************
 * Get the LOGNAME environment variable of the executing machine
 * @return
 *************************************************************************/
[[maybe_unused]] std::string mfw::get_logname()
{
    // Save and return the contents of the "LOGNAME" environment variable
    return m_stdstrLogname = getenv("LOGNAME");
}

/**************************************************************************
 * Get the PWD of the executing program
 * @return
 *************************************************************************/
[[maybe_unused]] std::string mfw::get_pwd()
{
    // Save and return the contents of the "PWD" environment variable
    return m_stdstrPwd = getenv("PWD");
}


/****************************************************************************
 * Log a message string in calling function's log file
 * @param pszData
 ***************************************************************************/
void mfw::log(const char * pszData)
{
    // Open the function's log file for appending
    FILE * fd = fopen(m_stdstrLogFQFS.c_str(),"a");

    // Assure file opened successfully and returned valid FILE * pointer
    assert(fd != nullptr);

    // Write the log entry into the function's log file
    fprintf(fd,"%s %s\n",get_date_and_time().c_str(),pszData);

    // Close the log file
    fclose(fd);
}

/****************************************************
 * Return date/time as "mm/dd/yy hh:mm:ss"
 * @return Returns standard string with date and time
 ****************************************************/
std::string mfw::get_date_and_time()
{
    // Allocate time_t structure and fill using standard time function
    time_t time = std::time(nullptr);

    // Allocate tm structure and fill using standard localtime function
    tm time_tm = *std::localtime(&time);

    // Allocate a C string buffer to use for log entry formatting
    char buffer[BUFSIZ];

    // Format the log entry using data from time_tm structure
    strftime(buffer,sizeof(buffer),"%x %X ",&time_tm);

    // Convert C string to std::string type and return to caller
    return buffer;
}

/**
 * Overloaded print function for bool
 * @param stdstrName
 * @param bValue
 */
[[maybe_unused]] void mfw::print(const std::string& stdstrName,bool bValue) {
    char szBuffer[BUFSIZ];
    if (bValue) {
        sprintf(szBuffer, "Boolean Variable %s is true",
                stdstrName.c_str());
    }
    else {
        sprintf(szBuffer, "Boolean Variable %s is false",
                stdstrName.c_str());
    }

    mfw::log((const char *)szBuffer);
}


/**
 * Overloaded print function for doubles
 * @param stdstrName
 * @param dValue
 */
void mfw::print(const std::string& stdstrName,double dValue)
{
    char szBuffer[BUFSIZ];
    sprintf(szBuffer,"Double Variable %s is %g",
            stdstrName.c_str(),dValue);
    mfw::log((const char *)szBuffer);
}


/**
 * Overloaded print function for integers
 * @param stdstrName
 * @param stdstrValue
 */
void mfw::print(const std::string& stdstrName,int iValue)
{
    char szBuffer[BUFSIZ];
    sprintf(szBuffer,"Integer Variable %s is %d",
            stdstrName.c_str(),iValue);
    mfw::log((const char *)szBuffer);
}

/**
 * Overloaded print function for std::strings
 * @param stdstrName
 * @param stdstrValue
 */
void mfw::print(const std::string& stdstrName,const std::string& stdstrValue)
{
    char szBuffer[BUFSIZ];
    sprintf(szBuffer,"std::string Variable %s is %s",
            stdstrName.c_str(),stdstrValue.c_str());
    log((const char *)szBuffer);
}


/********************************************************************
 * This is the destructor for the multiware framework class (unused)
 *******************************************************************/
mfw::~mfw() = default;

///////////////////
// eof - mfw.cpp //
///////////////////
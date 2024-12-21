/////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/CLionProjects/multiware/mwcgi.cpp //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include "std.h"
#include "cgishared.h"
#include "cgihtml.h"
#include "mwcgi.h"
#include "vpa.h"

//#define IMGROOT "http://127.0.0.1/~doug/"
//#define CGIROOT "http://127.0.0.1/~doug/"

//#define IMGROOT "https://mainframe.goodall.com/~doug/"
//#define CGIROOT "https://mainframe.goodall.com/~doug/"

#define IMGROOT "http://daphne.goodall.com/~doug/"
#define CGIROOT "http://daphne.goodall.com/~doug/"
#define CGI     "mwcgi.cgi"
#define FUNC    "?func="


/**********************************************************************
 * This enum provides function numbers that are passed in query strings
 * and used in the switch command during cgi execution.
 **********************************************************************/
enum {
    Reset,Step,Run,Stop,BoldEven,BoldOdd,BoldNone,
    One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Star,Zero,Pound,
    Keypad,Integers
};


/*****************************************************************
 * These pre-processor defines are used when concatenating strings
 * and dynamically generating the HTML 'A HREF' tags.
 *****************************************************************/
#define RESET    "0"
#define STEP     "1"
#define RUN      "2"
#define STOP     "3"
#define BOLDEVEN "4"
#define BOLDODD  "5"
#define BOLDNONE "6"
#define ONE      "7"
#define TWO      "8"
#define THREE    "9"
#define FOUR     "10"
#define FIVE     "11"
#define SIX      "12"
#define SEVEN    "13"
#define EIGHT    "14"
#define NINE     "15"
#define STAR     "16"
#define ZERO     "17"
#define POUND    "18"
#define KEYPAD   "19"
#define INTEGERS "20"


/******************************************************************
 * This is the constructor of the Multiware CGI class instantiated
 * by the main routine.
 ******************************************************************/
mwcgi::mwcgi()
{
    char szQueryString[BUFSIZ];
    char szFunctionNum[BUFSIZ];

    m_pShared = new cgishared();

//    if (UNIVERSAL_ANSWER == pShared->m_pShMem->iSignature) {
//        std::cout << "<p>established addressability to shared region"
//                  << std::endl;
//    }

    /*
     * Fetch the query string from the apache environment,
     * The existance of this environment variable is proof
     * that we are running as a CGI script. It would fail
     * if we were running from the command line.
     */
    char * psz = getenv("QUERY_STRING");
    if(nullptr != psz) {

        // convert to std::string and save in data member
        m_query_string = psz;

        // make sure the query string isn't empty before trying to copy
        if(0 < m_query_string.length()) {
            strcpy(szQueryString,psz);

            // query string offsets...
            // 0123456789
            // func=2
            //      ^
            // extract the character string determining the function number.
            strncpy(szFunctionNum,&szQueryString[5],
                    strlen(szQueryString));

            /*
             * convert the ascii string containing a number
             * into an integer in preparation for the switch command.
             */
            int iFunction = atoi(szFunctionNum);

            /*
             * Select the proper CGI functional routine and run it.
             */
            switch(iFunction) {
                case Reset:     reset();        break;
                case Step:      step();         break;
                case Run:       run();          break;
                case Stop:      stop();         break;
                case BoldEven:  bold_even();    break;
                case BoldOdd:   bold_odd();     break;
                case BoldNone:  bold_none();    break;
                case One:       one();          break;
                case Two:       two();          break;
                case Three:     three();        break;
                case Four:      four();         break;
                case Five:      five();         break;
                case Six:       six();          break;
                case Seven:     seven();        break;
                case Eight:     eight();        break;
                case Nine:      nine();         break;
                case Star:      star();         break;
                case Zero:      zero();         break;
                case Pound:     ppound();       break;
                case Keypad:    keypad();       break;
                case Integers:  integers();     break;
            }
        }
    }

    /*
     * Dynamically generate the HTML output of this CGI script.
     * The mandatory Content-type was output in the main first thing.
     */
    generate();

}

/******************************************
 * CGI func=0 handler
 ******************************************/
void mwcgi::reset()
{
    // Disable the keypad
    m_pShared->m_pShMem->bKeypad   = false;

    // Disable the Integers display
    m_pShared->m_pShMem->bIntegers = false;

    // Assure integers displayed are not bolded
    m_pShared->m_pShMem->bBoldEven = false;
    m_pShared->m_pShMem->bBoldOdd  = false;

    memset(m_pShared->m_pShMem->szKeypadData,0,BUFSIZ);
    memset(m_pShared->m_pShMem->szPin,0,BUFSIZ);

}


/***********************************************************
 * CGI func=1 handler
 * This handler doesn't have anything to do. Just by running
 * the screen gets refreshed.
 ***********************************************************/
void mwcgi::step()
{
}


/********************************************************
 * CGI func=2 handler
 * This handler sets the shared boolean indicating that
 * the program responsible for the integers vector should
 * continuously update the values in real-time.
 ********************************************************/
void mwcgi::run()
{
    m_pShared->m_pShMem->forkproc.bRunning = true;
}


/********************************************************
 * CGI func=3 handler
 * This handler resets the shared boolean indicating that
 * the program responsible for the integers vector should
 * stop updating the values in real-time.
 ********************************************************/
void mwcgi::stop()
{
    m_pShared->m_pShMem->forkproc.bRunning = false;
}


/*******************************************************
 * CGI func=4 handler
 * This handler sets the bolding booleans with the
 * even true and the odd false, causing the even numbers
 * to be bold.
 *******************************************************/
void mwcgi::bold_even()
{
    m_pShared->m_pShMem->bBoldEven = true;
    m_pShared->m_pShMem->bBoldOdd  = false;

}


/******************************************************
 * CGI func=5 handler
 * This handler sets the bolding booleans with the
 * even false and the odd true, causing the odd numbers
 * to be bold.
 ******************************************************/
void mwcgi::bold_odd()
{
    m_pShared->m_pShMem->bBoldEven = false;
    m_pShared->m_pShMem->bBoldOdd  = true;
}


/*******************************************************
 * CGI func=6 handler
 * This handler sets the bolding booleans with the
 * even false and the odd false, causing the odd numbers
 * to be bold.
 *******************************************************/
void mwcgi::bold_none()
{
    m_pShared->m_pShMem->bBoldEven = false;
    m_pShared->m_pShMem->bBoldOdd  = false;
}


/****************************************************
 * CGI func=19 handler
 * This handler toggles the bKeypad boolean causing
 * the keypad to appear and disappear each time it is
 * clicked on.
 ****************************************************/
void mwcgi::keypad()
{
    if(m_pShared->m_pShMem->bKeypad) {
        m_pShared->m_pShMem->bKeypad = false;
    } else {
        m_pShared->m_pShMem->bKeypad = true;
    }
}


/********************************************************
 * CGI func=7 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::one()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"1");
}


/********************************************************
 * CGI func=8 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::two()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"2");
}


/********************************************************
 * CGI func=9 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::three()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"3");

}


/********************************************************
 * CGI func=10 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::four()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"4");
}


/********************************************************
 * CGI func=11 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::five()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"5");
}


/********************************************************
 * CGI func=12 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::six()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"6");
}


/********************************************************
 * CGI func=13 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::seven()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"7");
}


/********************************************************
 * CGI func=14 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::eight()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"8");
}


/********************************************************
 * CGI func=15 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::nine()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"9");
}


/***********************************************************
 * CGI func=16 handler
 * This handler processes the * keypad entry that resets the
 * keypad buffers to the empty state.
 ***********************************************************/
void mwcgi::star()
{
    memset(m_pShared->m_pShMem->szKeypadData,0,BUFSIZ);
    memset(m_pShared->m_pShMem->szPin,0,BUFSIZ);

}


/********************************************************
 * CGI func=17 handler
 * This handler processes a keypad entry by appending the
 * appropriate  ascii digit onto the keypad data buffer.
 ********************************************************/
void mwcgi::zero()
{
    strcat(m_pShared->m_pShMem->szKeypadData,"0");
}


/********************************************************
 * CGI func=18 handler
 * This handler processes the # keypad entry that transfers
 * the current keypad bufffer to pin storage.
 ********************************************************/
void mwcgi::ppound()
{
    strcpy(m_pShared->m_pShMem->szPin,
           m_pShared->m_pShMem->szKeypadData);
    memset(m_pShared->m_pShMem->szKeypadData,0,BUFSIZ);
}


/**************************************************
 * CGI func=20 handler
 * This handler toggles the boolean controlling the
 * display of the integers vector.
 **************************************************/
void mwcgi::integers()
{
    if(m_pShared->m_pShMem->bIntegers) {
        m_pShared->m_pShMem->bIntegers = false;
    } else {
        m_pShared->m_pShMem->bIntegers = true;
    }

}


/********************************************************
 * This function dynamically generates an HTML web page,
 * the conmtents of which depend on the status of various
 * booleans.
 ********************************************************/
void mwcgi::generate()
{
    m_pHTML = new cgihtml();
    m_pHTML->open_head();
    m_pHTML->title(__FILE__);
    m_pHTML->close_head();
    m_pHTML->open_body();
    m_pHTML->imgsrc(IMGROOT "my-logo.png",250,150);

    m_pHTML->para();


    /*
     * Display the keypad if the boolean so allows
     */
    if(m_pShared->m_pShMem->bKeypad) {
        gen_keypad();
    }

    m_pHTML->para();

    /*
     * Display the integers vector if the controlling boolean so allows.
     */
    if(m_pShared->m_pShMem->bIntegers) {
        m_pHTML->open_table(3);
        // label the rows
        printf("<tr><th> + </th>");
        for (int col = 0; col < 16; col++) {
            printf("<th>%2X</th>", col);
        }
        printf("</tr>");
        for (int row = 0; row < 16; row++) {
            // label the row
            printf("<tr><th>%02X</th>", row * 16);
            // display each column of the current row
            for (int col = 0; col < 16; col++) {
                int byte = m_pShared->m_pShMem->iIntegers[(row * 16) + col];
                // odd values are bolded
                if (1 & byte) {
                    // low order bit was 1
                    if (m_pShared->m_pShMem->bBoldOdd) {
                        printf("<td><b>%02X</b></td>", byte);
                    } else {
                        printf("<td>%02X</td>", byte);
                    }
                } else {
                    // low order bit was 0
                    if (m_pShared->m_pShMem->bBoldEven) {
                        printf("<td><b>%02X</b></td>", byte);
                    } else {
                        printf("<td>%02X</td>", byte);

                    }
                }
            }
            printf("</tr>");
        }
    }

    m_pHTML->para();

    /**
     * Display the menu bar of command links depending on booleans
     */
    m_pHTML->print("<h3>");
    m_pHTML->ahref(CGIROOT CGI FUNC RESET,"Reset");
    if(m_pShared->m_pShMem->bIntegers) {
        m_pHTML->ahref(CGIROOT CGI FUNC STEP,"Step");
        m_pHTML->ahref(CGIROOT CGI FUNC RUN,"Run");
        m_pHTML->ahref(CGIROOT CGI FUNC STOP,"Stop");
        m_pHTML->ahref(CGIROOT CGI FUNC BOLDEVEN,"BoldEven");
        m_pHTML->ahref(CGIROOT CGI FUNC BOLDODD,"BoldOdd");
        m_pHTML->ahref(CGIROOT CGI FUNC BOLDNONE,"BoldNone");
    }
    m_pHTML->ahref(CGIROOT CGI FUNC KEYPAD,"Keypad");
    m_pHTML->ahref(CGIROOT CGI FUNC INTEGERS,"Integers");
    m_pHTML->print("</h3>");
    m_pHTML->para();

    m_pHTML->close_body();

}


/*************************************************************
 * Emit the required HTML to display the interactive keyboard.
 *************************************************************/
void mwcgi::gen_keypad()
{
    m_pHTML->print((char *)"<h3>");
    m_pHTML->open_table((2));
    printf("<tr><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC ONE,(char *)"1");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC TWO,(char *)"2");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC THREE,(char *)"3");
    printf("</tr><tr><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC FOUR,(char *)"4");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC FIVE,(char *)"5");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC SIX,(char *)"6");
    printf("</tr><tr><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC SEVEN,(char *)"7");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC EIGHT,(char *)"8");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC NINE,(char *)"9");
    printf("</tr><tr><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC STAR,(char *)"*");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC ZERO,(char *)"0");
    printf("</td><td>");
    m_pHTML->ahref(CGIROOT CGI FUNC POUND,(char *)"#");
    printf("</td></tr>");
    printf("<table><tr><td>%s</td></tr></table>",
          m_pShared->m_pShMem->szKeypadData);
    m_pHTML->close_table();
    m_pHTML->print("</h3>");

}


/**********************************
 ** CGI Script Main Entry Point  **
 ** @return Returns EXIT_SUCCESS **
 **********************************/
int main(int argc, char **argv) {
    std::cout << "Content-type: text/html\n\n";
    mwcgi *pCGI = new mwcgi();
    delete pCGI; // Avoid memory leaks
    return EXIT_SUCCESS;
}

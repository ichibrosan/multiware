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

enum {
    Reset,Step,Run,Stop,BoldEven,BoldOdd,BoldNone,
    One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Star,Zero,Pound
};

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

mwcgi::mwcgi()
{
    char szQueryString[BUFSIZ];
    char szFunctionNum[BUFSIZ];

    m_pShared = new cgishared();

//    if (UNIVERSAL_ANSWER == pShared->m_pShMem->iSignature) {
//        std::cout << "<p>established addressability to shared region"
//                  << std::endl;
//    }

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
            // extract the character string determining the function number
            strncpy(szFunctionNum,&szQueryString[5],3);
            int iFunction = atoi(szFunctionNum);
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
                case Pound:     ppound();        break;
            }
        }
    }
    generate();

}

 void mwcgi::reset()
 {
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    m_pHTML->para();
    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
 }

 void mwcgi::step()
 {
//     printf("<p>%s",__PRETTY_FUNCTION__ );
     m_pHTML->para();
     m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));

 }

 void mwcgi::run()
 {
//     printf("<p>%s",__PRETTY_FUNCTION__ );
     m_pHTML->para();
     m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
     m_pShared->m_pShMem->forkproc.bRunning = true;
 }

void mwcgi::stop()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
//    m_pHTML->para();
//    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
    m_pShared->m_pShMem->forkproc.bRunning = false;

}

void mwcgi::bold_even()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
//    m_pHTML->para();
//    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
    m_pShared->m_pShMem->bBoldEven = true;
    m_pShared->m_pShMem->bBoldOdd  = false;

}
void mwcgi::bold_odd()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
//    m_pHTML->para();
//    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
    m_pShared->m_pShMem->bBoldEven = false;
    m_pShared->m_pShMem->bBoldOdd  = true;

}
void mwcgi::bold_none()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
//    m_pHTML->para();
//    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
    m_pShared->m_pShMem->bBoldEven = false;
    m_pShared->m_pShMem->bBoldOdd  = false;

}

void mwcgi::one()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"1");
}

void mwcgi::two()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"2");
}

void mwcgi::three()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"3");

}

void mwcgi::four()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"4");

}

void mwcgi::five()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"5");

}

void mwcgi::six()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"6");

}

void mwcgi::seven()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"7");

}

void mwcgi::eight()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"8");

}

void mwcgi::nine()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"9");

}

void mwcgi::star()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    memset(m_pShared->m_pShMem->szKeypadData,0,BUFSIZ);
    memset(m_pShared->m_pShMem->szPin,0,BUFSIZ);

}

void mwcgi::zero()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcat(m_pShared->m_pShMem->szKeypadData,"0");

}

void mwcgi::ppound()
{
//    printf("<p>%s",__PRETTY_FUNCTION__ );
    strcpy(m_pShared->m_pShMem->szPin,
           m_pShared->m_pShMem->szKeypadData);

}

void mwcgi::clear_keypad()
{
    memset(m_pShared->m_pShMem->szPin,       0,BUFSIZ);
    memset(m_pShared->m_pShMem->szKeypadData,0,BUFSIZ);
}


void mwcgi::generate()
 {
     m_pHTML = new cgihtml();
     m_pHTML->open_head();
     m_pHTML->title((char *)__FILE__);
     m_pHTML->close_head();
     m_pHTML->open_body();
     m_pHTML->imgsrc((char *)IMGROOT "my-logo.png");

     m_pHTML->para();

//     printf("m_pShared->m_pShMem->szPin        is %s",
//            m_pShared->m_pShMem->szPin);
//     m_pHTML->para();
//     printf("m_pShared->m_pShMem->szKeypadData is %s",
//            m_pShared->m_pShMem->szKeypadData);

     gen_keypad();

     if(m_pShared->m_pShMem->bBoldEven) {
         printf("<p>bBoldEven is true");
     } else {
         printf("<p>bBoldEven is false");
     }

     if(m_pShared->m_pShMem->bBoldOdd) {
         printf(", bBoldOdd is true");
     } else {
         printf(", bBoldOdd is false");
     }

     if(m_pShared->m_pShMem->forkproc.bRunning) {
         printf(", bRunning is true");
     } else {
         printf(", bRunning is false");
     }


     m_pHTML->para();

     m_pHTML->open_table(3);

     // label the rows
     printf("<tr><th> + </th>");
     for(int col=0;col<16;col++) {
         printf("<th>%2X</th>",col);
     }
     printf("</tr>");

     for(int row=0;row<16;row++) {

        // label the row
        printf("<tr><th>%02X</th>",row*16);

        // display each column of the current row
        for(int col=0;col<16;col++) {
            int byte = m_pShared->m_pShMem->iIntegers[(row*16)+col];

            // odd values are bolded
            if(1 & byte) {
                // low order bit was 1
                if(m_pShared->m_pShMem->bBoldOdd) {
                    printf("<td><b>%02X</b></td>", byte);
                } else {
                    printf("<td>%02X</td>", byte);

                }
            } else {
                // low order bit was 0
                if(m_pShared->m_pShMem->bBoldEven) {
                    printf("<td><b>%02X</b></td>", byte);
                } else {
                    printf("<td>%02X</td>", byte);

                }

            }
        }
        printf("</tr>");
     }

     m_pHTML->para();
     m_pHTML->print((char *)"<h3>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC RESET,(char *)"Reset");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC STEP,(char *)"Step");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC RUN,(char *)"Run");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC STOP,(char *)"Stop");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC BOLDEVEN,(char *)"BoldEven");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC BOLDODD,(char *)"BoldOdd");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC BOLDNONE,(char *)"BoldNone");

     m_pHTML->print((char *)"</h3>");
     m_pHTML->para();
     std::cout << "<p>m_query_string is " << m_query_string << std::endl;
     m_pHTML->close_body();

 }

 void mwcgi::gen_keypad()
 {
    m_pHTML->open_table((2));
    printf("<tr><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC ONE,(char *)"1");
    printf("</td><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC TWO,(char *)"2");
     printf("</td><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC THREE,(char *)"3");
    printf("</tr><tr><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC FOUR,(char *)"4");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC FIVE,(char *)"5");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC SIX,(char *)"6");
    printf("</tr><tr><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC SEVEN,(char *)"7");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC EIGHT,(char *)"8");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC NINE,(char *)"9");
    printf("</tr><tr><td>");
    m_pHTML->ahref((char *)CGIROOT CGI FUNC STAR,(char *)"*");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC ZERO,(char *)"0");
     printf("</td><td>");
     m_pHTML->ahref((char *)CGIROOT CGI FUNC POUND,(char *)"#");
    printf("</td></tr>");
    m_pHTML->close_table();
 }

 char * mwcgi::get_userdir()
 {
    return (char *)"/home/doug/public_html";

 }

int main(int argc, char **argv) {
    std::cout << "Content-type: text/html\n\n";
    mwcgi *pCGI = new mwcgi();
    delete pCGI; // Avoid memory leaks
    return 0;
}

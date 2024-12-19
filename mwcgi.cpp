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

enum {
    Reset = '0',
    Step,
    Run,
    Stop
};

mwcgi::mwcgi() {
    //printf("%s", __PRETTY_FUNCTION__);
    m_pShared = new cgishared();
//    if (UNIVERSAL_ANSWER == pShared->m_pShMem->iSignature) {
//        std::cout << "<p>established addressability to shared region"
//                  << std::endl;
//    }

    //pShared->m_pShMem->pVPA = new vpa();
    //std::cout << pShared->m_pShMem->pVPA.
    generate();

    char szQueryString[BUFSIZ];
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
            // extract the character determining the function number
            char  cFunction = szQueryString[5];

            switch(cFunction) {
                case Reset:
                    reset();
                    break;
                case Step:
                    step();
                    break;
                case Run:
                    run();
                    break;
                case Stop:
                    stop();
                    break;
            }
        }
    }

 }

 void mwcgi::reset()
 {
    m_pHTML->para();
    m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));
 }

 void mwcgi::step()
 {
     m_pHTML->para();
     m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));

 }

 void mwcgi::run()
 {
     m_pHTML->para();
     m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));

 }

 void mwcgi::stop()
 {
     m_pHTML->para();
     m_pHTML->print(const_cast<char *>(__PRETTY_FUNCTION__));

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
     m_pHTML->open_table(1);

     // label the rows
     printf("<tr><th> + </th>");
     for(int col=0;col<16;col++) {
         printf("<th>%2X</th>",col);
     }
     printf("</tr>");

     for(int row=0;row<16;row++) {

        // label the columns
        printf("<tr><th>%02X</th>",row*16);

        // display each column of the current ro
        for(int col=0;col<16;col++) {
            int byte = m_pShared->m_pShMem->iIntegers[(row*16)+col];

            // odd values are bolded
            if(1 & byte) {
                printf("<td><b>%02X</b></td>",byte);
            } else {
                printf("<td>%02X</td>",byte);

            }
        }
        printf("</tr>");
     }

     m_pHTML->para();
     m_pHTML->print((char *)"<h1>");
     m_pHTML->ahref((char *)CGIROOT "mwcgi.cgi?func=0",(char *)"Reset");
     m_pHTML->ahref((char *)CGIROOT "mwcgi.cgi?func=1",(char *)"Step");
     m_pHTML->ahref((char *)CGIROOT "mwcgi.cgi?func=2",(char *)"Run");
     m_pHTML->ahref((char *)CGIROOT "mwcgi.cgi?func=3",(char *)"Stop");
     m_pHTML->print((char *)"</h1>");
     m_pHTML->para();
     //std::cout << "<p>m_query_string is " << m_query_string << std::endl;
     m_pHTML->close_body();

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

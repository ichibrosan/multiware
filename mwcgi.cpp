/////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/CLionProjects/multiware/mwcgi.cpp //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include "std.h"
#include "cgishared.h"
#include "cgihtml.h"
#include "mwcgi.h"

#define IMGROOT "http://127.0.0.1/~doug/"
#define CGIROOT "http://127.0.0.1/~doug/"

mwcgi::mwcgi() {
    //printf("%s", __PRETTY_FUNCTION__);
    cgishared * pShared = new cgishared();
//    if (UNIVERSAL_ANSWER == pShared->m_pShMem->iSignature) {
//        std::cout << "<p>established addressability to shared region"
//                  << std::endl;
//    }

    generate();

    char szQueryString[BUFSIZ];
    char * p = getenv("QUERY_STRING");
    if(nullptr != p) {
        m_query_string = p;
        if(0 < m_query_string.length()) {
            strcpy(szQueryString,p);
            switch(szQueryString[5]) {
                case '0':
                    reset();
                    break;
                case '1':
                    step();
                    break;
                case '2':
                    run();
                    break;
                case '3':
                    stop();
                    break;
            }
        }
    }
//    printf("<p>QUERY_STRING is %s",p);
//    std::cout << "<p>m_query_string is " << m_query_string << std::endl;




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
     m_pHTML->print("<h1>");
     m_pHTML->ahref( (char *)CGIROOT "mwcgi.cgi?func=0",(char *)"Reset");
     m_pHTML->ahref( (char *)CGIROOT "mwcgi.cgi?func=1",(char *)"Step");
     m_pHTML->ahref( (char *)CGIROOT "mwcgi.cgi?func=2",(char *)"Run");
     m_pHTML->ahref( (char *)CGIROOT "mwcgi.cgi?func=3",(char *)"Stop");
     m_pHTML->print("</h1>");
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

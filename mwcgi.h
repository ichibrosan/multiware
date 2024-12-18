//
// Created by doug on 12/18/24.
//

#ifndef MULTIWARE_MWCGI_H
#define MULTIWARE_MWCGI_H

class mwcgi {
    std::string m_query_string;
    char m_sz_query_string[FILENAME_MAX];
    cgihtml * m_pHTML;
    cgishared * m_pShared;
    bool m_bBoldEven;
    bool m_bBoldOdd;
public:
    mwcgi();
    void reset();
    void step();
    void run();
    void stop();
    void bold_even();
    void bold_odd();
    void bold_none();
    char * get_userdir();
    void generate();
};


#endif //MULTIWARE_MWCGI_H

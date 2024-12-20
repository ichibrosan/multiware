//
// Created by doug on 12/8/24.
//

#ifndef MULTIWARE_CGIHTML_H
#define MULTIWARE_CGIHTML_H


enum HTML_LOCATION {
    HTML_USERDIR,
    HTML_VARWWW
};

class cgihtml {
    char m_page[BUFSIZ];
public:
    cgihtml();
    void ahref(char *,char *);
    void open_head();
    void open_style();
    void close_style();
    void title(char *);
    void close_head();
    void open_body();
    void imgsrc(char *,int,int);
    void para();
    void print(char *);
    void open_table(int border);
    void close_table();
    void close_body();
    ~cgihtml();
};


#endif //MULTIWARE_CGIHTML_H

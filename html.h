//
// Created by doug on 12/8/24.
//

#ifndef MULTIWARE_HTML_H
#define MULTIWARE_HTML_H

#include "mfw.h"

enum HTML_LOCATION {
    HTML_USERDIR,
    HTML_VARWWW
};

class html {
    FILE * m_fd;
    char szFQFS[FILENAME_MAX];
public:
    html(const char * szPQFS);
    void ahref(const char *,const char *);
    void open_head();
    void title(const char *);
    void close_head();
    void open_body();
    void imgsrc(const char *);
    void print(const char *);
    void close_body();
    ~html();
};


#endif //MULTIWARE_HTML_H

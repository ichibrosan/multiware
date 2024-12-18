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
    html(char * szPQFS);
    void ahref(char *,char *);
    void open_head();
    void title(char *);
    void close_head();
    void open_body();
    void imgsrc(char *);
    void print(char *);
    void close_body();
    ~html();
};


#endif //MULTIWARE_HTML_H

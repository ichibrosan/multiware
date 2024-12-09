//
// Created by doug on 12/8/24.
//

#include "mfw.h"
#include "html.h"

html::html(char * szFQFS)
{
    m_fd = fopen(szFQFS,"w");
    fprintf(m_fd,"<html>\n");
}


void html::open_head()
{
    fprintf(m_fd,"  <head>\n");
}

void html::title(char * szTitle)
{
    fprintf(m_fd,"      <title>\n");
    fprintf(m_fd,"          %s\n",szTitle);
    fprintf(m_fd,"      </title>\n");
}

void html::close_head()
{
    fprintf(m_fd,"  </head>\n");
}

void html::open_body()
{
    fprintf(m_fd,"  <body>\n");
}

void html::print(char *szText)
{
    fprintf(m_fd,"%s\n",szText);
}

void html::close_body()
{
    fprintf(m_fd,"  </body>\n");
}

html::~html()
{
    fprintf(m_fd,"</html>\n");
    fclose(m_fd);
}

//
// Created by doug on 12/8/24.
//

#include "std.h"
#include "cgihtml.h"

cgihtml::cgihtml()
{
     printf("<html>\n");
}

void cgihtml::open_style()
{
    print((char *)"<style>");
}

void cgihtml::close_style()
{
    print((char *)"</style>");
}

void cgihtml::open_table(int border)
{
    printf("<table border=%d>",border);
}

void cgihtml::close_table()
{
    printf("</table>");
}

void cgihtml::ahref(char *szURL,char * szVisible)
{
    printf("        <a href=\"%s\">%s</a>\n",szURL,szVisible);
}

void cgihtml::open_head()
{
    printf("  <head>\n");
}

void cgihtml::title(char * szTitle)
{
    printf("      <title>\n");
    printf("          %s\n",szTitle);
    printf("      </title>\n");
}

void cgihtml::close_head()
{
    printf("  </head>\n");
}

void cgihtml::open_body()
{
    printf("  <body>\n");
}

void cgihtml::imgsrc(char * szURL,int width,int height)
{
    char szTag[FILENAME_MAX];
    sprintf(szTag,"<img src=\"%s\" width=\"%d\" height=\"%d\">\n",
            szURL,width,height);
    print(szTag);
}

void cgihtml::para()
{
    printf("<p>");
}

void cgihtml::print(char *szText)
{
    printf("%s\n",szText);
}

void cgihtml::close_body()
{
    printf("  </body>\n");
}

cgihtml::~cgihtml()
{
    printf("</html>\n");
}

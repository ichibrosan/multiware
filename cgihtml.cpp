///////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/CLionProjects/multiware/cgihtml.cpp //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.     //
///////////////////////////////////////////////////////////////////////

#include "std.h"
#include "cgihtml.h"


/******************************************************
 * This is the constructor for the cgihtml class.
 * It emits the html tag which identifies the document
 * as an HTML page.
 ******************************************************/
cgihtml::cgihtml()
{
     printf("<html>\n");
}

void cgihtml::open_style()
{
    print("<style>");
}

void cgihtml::close_style()
{
    print("</style>");
}

void cgihtml::open_table(int border)
{
    printf("<table border=%d>",border);
}

void cgihtml::close_table()
{
    printf("</table>");
}


/***************************************************************
 * This function emits a fully formed A HREF tag for the purpose
 * of creating a visible linkk on the web page.
 * @param szURL A C string containing the URL of the target
 * @param szVisible A pointer top a null terminated string
 * containing the visible portion of the link.
 ***************************************************************/
void cgihtml::ahref(const char *szURL,const char * szVisible)
{
    printf("<a href=\"%s\">%s</a>\n",szURL,szVisible);
}


void cgihtml::open_head()
{
    printf("  <head>\n");
}


/*********************************************************************
 * Emit a title field (used in the head section of the HTML document.
 * @param szTitle A pointer to a null terminated string containing the
 * title of the web page.
 *********************************************************************/
void cgihtml::title(const char * szTitle)
{
    printf("      <title>\n");
    printf("          %s\n",szTitle);
    printf("      </title>\n");
}


/***************************************************
 * Emits a tag closing head section of the web page.
 ***************************************************/
void cgihtml::close_head()
{
    printf("  </head>\n");
}

void cgihtml::open_body()
{
    printf("  <body>\n");
}


/******************************************************************
 * Emits a fully formed IMG SRC tag containing the URL of the image
 * adjusted to the size indicated.
 * @param szURL A pointer to a null terminated string containing the
 * URL of the image to be displayed.
 * @param width The image width in pixels
 * @param height The image height in pixels
 *******************************************************************/
void cgihtml::imgsrc(const char * szURL,int width,int height)
{
    char szTag[FILENAME_MAX];
    sprintf(szTag,"<img "
            "src=\"%s\" "
            "width=\"%d\" "
            "height=\"%d\">\n",
            szURL,width,height);
    print(szTag);
}


/**********************
 * Emits a pargraph tag
 **********************/
void cgihtml::para()
{
    printf("<p>");
}

void cgihtml::print(const char *szText)
{
    printf("%s\n",szText);
}

void cgihtml::close_body()
{
    printf("  </body>\n");
}

/***************************************************************
 * This is the destructor of the cgihtml class which closes the
 * html tag.
 ***************************************************************/
cgihtml::~cgihtml()
{
    printf("</html>\n");
}

///////////////////////
// eof - cgihtml.cpp //
///////////////////////
// daphne.goodall.com:/home/doug/CLionProjects/multiware/termbind.cpp
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.

#include "mfw.h"
#include "termbind.h"

/**
 * The purpose of this module is to provide methods for controlling
 * the display when running in a terminal session and TERM=xterm
 */

/**
 * See https://www.x.org/docs/xterm/ctlseqs.pdf
 */

#define ASCII_ESCAPE 27

/**
 * This is the termbind constructor
 */
termbind::termbind()
{
    crtclr();
}

/**
 * Position cursor to line and column
 * @param line
 * @param col
 */
void termbind::crtlc(int line,int col)
{
    printf("%c[%d;%dH",ASCII_ESCAPE,line,col);
}

/**
 * Clear Screen
 */
void termbind::crtclr()
{
    // Erase in Display (Clear All)
    printf("%c[2J",27);
}

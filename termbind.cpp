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

extern termbind *pTerm;

#define ASCII_ESCAPE 27

/**
 * This is the termbind constructor
 */
termbind::termbind()
{
    crtclr();
}

void termbind::crtcntl(int abbr,int n)
{
    switch(abbr) {
        case CUU:    // Cursor Up
            printf("%s%dA",CSI,n);      break;
        case CUD:    // Cursor Down
            printf("%s%dB",CSI,n);      break;
        case CUF:    // Cursor Forward
            printf("%s%dC",CSI,n);      break;
        case CUB:    // Cursor Back
            printf("%s%dD",CSI,n);      break;
        case CNL:    // Cursor Next Line
            printf("%s%dE",CSI,n);      break;
        case CPL:    // Cursor Previous Line
            printf("%s%dF",CSI,n);      break;
        case CHA:    // Cursor Horizontal Absolute
            printf("%s%dG",CSI,n);      break;
//        case CUP:    // Cursor Position
//            printf("%s%dH",CSI,n);            break;
        case ED:     // Erase In Display
            printf("%s%dJ",CSI,n);      break;
        case EL:     // Erase In Line
            printf("%s%dK",CSI,n);      break;
        case SU:     // Scroll Up
            printf("%s%dS",CSI,n);      break;
        case SD:     // Scroll Down
            printf("%s%dT",CSI,n);      break;
        case SGR:    // Select Graphic Rendition
            printf("%s%dm",CSI,n);      break;
        case DSR:    // Device Status Report
            printf("%s6%d",CSI,n);      break;

    }
}
void termbind::crtcntl(int abbr,int n,int m)
{
    switch(abbr) {
        case CUP:    // Cursor Position
            printf("%s%d;%dH",CSI,n,m);   break;
        case HVP:   // Horizontal Vertical Position
            printf("%s%d;%df",CSI,n,m);     break;
    }

}



void termbind::crtfg(int color)
{
    printf("%c[38:5:%dm",27,color);
}

void termbind::crtbg(int color)
{
    printf("%c[48:5:%dm",27,color);
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

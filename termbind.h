//
// Created by doug on 12/9/24.
//

#ifndef MULTIWARE_TERMBIND_H
#define MULTIWARE_TERMBIND_H

enum {
    // Standard Colors
    SC_BLACK,SC_RED,SC_GREEN,SC_BROWN,SC_BLUE,SC_VIOLET,SC_TEAL,SC_GRAY,
    // High Intensity Colors
    HI_GRAY,HI_RED,HI_LTGREEN,HGI_YELLOW,HI_BLUE,HI_MAGENTA,HI_LTBLUE,
    // 216 Colors
    BLACK
};

// Control Sequence Introducer
#define CSI "\x1B["

enum CRTCNTL_T {
    CUU,    // Cursor Up
    CUD,    // Cursor Down
    CUF,    // Cursor Forward
    CUB,    // Cursor Back
    CNL,    // Cursor Next Line
    CPL,    // Cursor Previous Line
    CHA,    // Cursor Horizontal Absolute
    CUP,    // Cursor Position
    ED,     // Erase In Display
    EL,     // Erase In Line
    SU,     // Scroll Up
    SD,     // Scroll Down
    HVP,    // Horizontal Vertical Position
    SGR,    // Select Graphic Rendition
    DSR     // Device Status Report
};

enum FGCOLORS_T {
       FG_BLACK   = 30,
       FG_RED     = 31,
       FG_GREEN   = 32,
       FG_YELLOW  = 33,
       FG_BLUE    = 34,
       FG_MAGENTA = 35,
       FG_CYAN    = 36,
       FG_WHITE   = 37,
       FG_BR_BLACK = 90,
       FG_BR_RED   = 91,
       FG_BR_GREEN = 92,
       FG_BR_YELLOW = 93,
       FG_BR_BLUE   = 94,
       FG_BR_MAGENTA = 95,
       FG_BR_CYAN    = 96,
       FG_BR_WHITE   = 97
};

class termbind {
public:
    termbind();                     // Constructor
    void crtlc(int line,int col);   // set cursor position
    void crtclr();                  // clear screen
    void crtfg(int color);          // set foreground color
    void crtbg(int color);          // set background color

    /**************************************************************
     * Overloaded function crtcntl can have two or three parameters
     * @param abbr
     * @param n
     */
    void crtcntl(int abbr,int n);           // two parm call
    void crtcntl(int abbr,int n,int m);     // three parm call
};


#endif //MULTIWARE_TERMBIND_H

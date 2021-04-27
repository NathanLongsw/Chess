#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

/*  This class is used to construct and design the window pertaining to
    the graphical display.  */

class Xwindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];

 public:
    // Constructor; displays the window.
    Xwindow(int width=500, int height=500); 

    // Destructor; destroys the window.
    ~Xwindow();
    
    Xwindow(const Xwindow&) = delete;
    Xwindow &operator=(const Xwindow&) = delete;

    // Available colours.   
    enum {White=0, Black, Red, Green, Blue};

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg);

};

#endif

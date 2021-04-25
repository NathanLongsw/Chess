#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
#include "observer.h"
#include "info.h"
#include "state.h"
#include <vector>
#include <memory>
#include "window.h"
#include <string>
#include "playermove.h"

class Xwindow;

class GraphicsDisplay: public Observer<Info, State> {
    std::unique_ptr<Xwindow> gwindow;
    std::vector<std::vector<std::string>> OldDisplay;
    std::vector<std::vector<std::string>> NewDisplay;
    size_t dimension;
    size_t dx;

    int SquareColour(size_t x, size_t y) const;
    std::string getIcon(Rank rank, Colour colour) const;
    
public:
    GraphicsDisplay(size_t dimension = 500);
    ~GraphicsDisplay();
    void notify(Subject<Info, State> &whoNotified) override;
    void drawGraphics();

};


#endif

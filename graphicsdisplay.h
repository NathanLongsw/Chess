#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
#include <vector>
#include <memory>
#include <string>
#include "window.h"
#include "piece.h"

class Xwindow;

class GraphicsDisplay: public Observer<Info, State> {
    std::unique_ptr<Xwindow> gwindow;
    std::vector<std::vector<std::string>> OldDisplay;
    std::vector<std::vector<std::string>> NewDisplay;
    size_t dimension;
    size_t dx;

    int SquareColour(size_t x, size_t y) const noexcept;
    std::string getIcon(Rank rank, Colour colour) const noexcept;
    
public:
    GraphicsDisplay(size_t dimension = 500);
    ~GraphicsDisplay();
    void notify(Subject<Info, State> &whoNotified) override;
    void drawGraphics();

};

#endif

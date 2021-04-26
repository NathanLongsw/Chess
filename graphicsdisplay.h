#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
#include <vector>
#include <memory>
#include <string>
#include "window.h"
#include "piece.h"

/* Derived class which inhertis from Observer */

class Xwindow;

class GraphicsDisplay: public Observer<Info, State> {
    std::unique_ptr<Xwindow> gwindow;
    
    // Copy of old display
    std::vector<std::vector<std::string>> OldDisplay;

    // Current display
    std::vector<std::vector<std::string>> NewDisplay;
    size_t dimension;
    size_t dx;

    // Sets colour of square 
    int SquareColour(size_t x, size_t y) const noexcept;

    // Returns appropriate icon for peice of specific colour
    std::string getIcon(Rank rank, Colour colour) const noexcept;
    
public:
    GraphicsDisplay(size_t dimension = 500);
    ~GraphicsDisplay();

    // Reacts to changes in Piece position 
    void notify(Subject<Info, State> &whoNotified) override;

    // Prints graphical display
    void drawGraphics() noexcept;

};

#endif

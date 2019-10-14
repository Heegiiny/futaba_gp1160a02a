#include <math.h>
#include "utils.h"
#include "display.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

class graphics
{
public:
    graphics();
    setPixel(uint16_t x, uint8_t y, bool color = true);
    drawLine(uint16_t x, uint8_t y, int16_t dx, int8_t dy, bool color = true);
    drawCircle(uint16_t x, uint8_t y, uint8_t D, bool color = true);
    drawRectangle(uint16_t x, uint8_t y, int16_t dx, int8_t dy, bool color = true);
    flushTrasaction();
    beginTrasaction() { this->transaction = true; };
    clear();

private:
    char pixelData[DISPLAY_WIDTH_BYTES][DISPLAY_HEIGHT];
    bool transaction = false;
};

extern graphics Graphics;

#endif
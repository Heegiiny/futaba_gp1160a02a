#include "serial.h"

#ifndef DISPLAY_H
#define DISPLAY_H

#define BYTE_SIZE 8
#define DISPLAY_WIDTH 256
#define DISPLAY_WIDTH_BYTES DISPLAY_WIDTH / 8
#define DISPLAY_HEIGHT 64

#define MODE_8_ROWS 1
#define MODE_3_ROWS 2
#define MODE_2_ROWS 3
#define MODE_1_2_ROWS 4
#define MODE_4_ROWS 5
#define MODE_D_3_ROWS 6
#define MODE_3_D_ROWS 7

class Display
{
public:
    Display();
    clear();
    beginTrasaction() { this->transaction = true; };
    flushTrasaction();
    sendGraphics(uint16_t x, uint8_t y, uint8_t h, uint16_t w, const char *data);
    setScreenMode(uint8_t screen_mode);
    setCursor(uint16_t x, uint8_t y);

private:
    bool transaction = false;
};

extern Display display;

#endif
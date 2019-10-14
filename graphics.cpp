#include "graphics.h"

graphics::graphics()
{
    std::cout << "sizeof(this->pixelData): " << sizeof(this->pixelData)
              << "\n";
    memset(this->pixelData, 0, sizeof(this->pixelData));
}
graphics::clear()
{
    memset(this->pixelData, 0, sizeof(this->pixelData));
}

graphics::setPixel(uint16_t x, uint8_t y, bool color)
{
    const uint8_t x_bytes = (uint8_t)floor(x / BYTE_SIZE);
    const uint8_t x_bits = x % BYTE_SIZE;
    if (color)
    {
        if (x_bits > 0)
        {
            pixelData[x_bytes][y] |= 1 << (BYTE_SIZE - 1 - x_bits);
        }
        else
        {
            pixelData[x_bytes][y] |= 1 << (BYTE_SIZE - 1 - x_bits);
        }
    }
    else
    {
        if (x_bits > 0)
        {
            pixelData[x_bytes][y] &= ~(1 << (BYTE_SIZE - 1 - x_bits));
        }
        else
        {
            pixelData[x_bytes][y] &= ~(1 << (BYTE_SIZE - 1 - x_bits));
        }
        //pixelData[x_bytes][y] &= ~(1) << (BYTE_SIZE - 1 - x_bits);
    }
    //this->pixelData[x][y] = color;
}

graphics::flushTrasaction()
{
    char data[DISPLAY_WIDTH_BYTES * DISPLAY_HEIGHT];

    for (int row = 0; row < DISPLAY_HEIGHT; row++)
    {
        for (int col = 0; col < DISPLAY_WIDTH_BYTES; col++)
        {
            data[row * DISPLAY_WIDTH_BYTES + col] = this->pixelData[col][row];
        }
    }

    display.sendGraphics(0, 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, reinterpret_cast<const char *>(data));
    this->transaction = false;
}

graphics::drawLine(uint16_t x, uint8_t y, int16_t dx, int8_t dy, bool color)
{
    float x1, y1, x_step, y_step, step;
    step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    x_step = dx / step;
    y_step = dy / step;

    x1 = x;
    y1 = y;
    for (int i = 0; i <= step; i++)
    {
        setPixel(round(x1), round(y1), color);
        x1 += x_step;
        y1 += y_step;
    }
}

graphics::drawRectangle(uint16_t x, uint8_t y, int16_t dx, int8_t dy, bool color)
{
    int8_t sign_x = sgn(dx);
    int8_t sign_y = sgn(dy);
    uint16_t x1 = x;

    while (x1 != x + dx)
    {
        uint8_t y1 = y;
        while (y1 != y + dy)
        {
            setPixel(x1, y1, color);
            y1 += sign_y;
        }

        x1 += sign_x;
    }
}

graphics::drawCircle(uint16_t x, uint8_t y, uint8_t D, bool color)
{
    int16_t x1 = 0;
    int8_t y1 = D / 2;
    int16_t delta = 1 - D;
    int16_t error = 0;
    while (y1 >= 0)
    {
        /*std::cout << "y1: " << (uint16_t)y1
                  << "\n";*/
        setPixel(x + x1, y + y1);
        setPixel(x + x1, y - y1);
        setPixel(x - x1, y + y1);
        setPixel(x - x1, y - y1);
        error = 2 * (delta + y1) - 1;
        if (delta < 0 && error <= 0)
        {
            ++x1;
            delta += 2 * x1 + 1;
            continue;
        }
        error = 2 * (delta - x1) - 1;
        if (delta > 0 && error > 0)
        {
            --y1;
            delta += 1 - 2 * y1;
            continue;
        }
        ++x1;
        delta += 2 * (x1 - y1);
        --y1;
    }
}

graphics Graphics;
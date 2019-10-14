#include <cstdio>
#include "utils.h"
#include "graphics.h"

#ifndef CLOCKS_H
#define CLOCKS_H

class Clock
{
public:
    drawClock();
    runClock();
};

extern Clock analogClock;

#endif
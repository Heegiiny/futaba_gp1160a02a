#include <iostream>
#include <Winbase.h>
#include <windows.h>
#include "utils.h"
#include "serial.h"
#include "display.h"
#include "graphics.h"
#include "clock.h"
#include "getTime.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if (Serial.init())
    {
        return 1;
    }

    display.clear();

    display.setScreenMode(MODE_2_ROWS);
    //display.setCursor(10, 0);
    //Serial.write("hello World");
    analogClock.runClock();

    Serial.close();

    return 0;
}

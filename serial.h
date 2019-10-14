#include <Winbase.h>
#include <windows.h>
#include <iostream>

#ifndef SERIAL_H
#define SERIAL_H

struct TTYException
{
};

class serial
{
private:
    HANDLE hSerial;

public:
    init();
    write(const char *data, DWORD len = 0);
    close() { CloseHandle(this->hSerial); };
};

extern serial Serial;

#endif
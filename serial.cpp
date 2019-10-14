#include "serial.h"

serial::init()
{
    this->hSerial = CreateFile("\\\\.\\COM15",
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               0,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               0);

    if (this->hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cerr << "Serial port does not exist";
            return 1;
        }

        std::cerr << "Some error occurred";
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(this->hSerial, &dcbSerialParams))
    {
        std::cerr << "Error getting serial port state";
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_19200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = ODDPARITY;
    if (!SetCommState(this->hSerial, &dcbSerialParams))
    {
        std::cerr << "error setting serial port state";
        return 1;
    }

    return 0;
}

serial::write(const char *data, DWORD len)
{
    if (this->hSerial == INVALID_HANDLE_VALUE)
    {
        throw TTYException();
    }

    DWORD feedback;

    if (len == 0)
    {
        len = strlen(data);
    }

    if (!WriteFile(this->hSerial, &data[0], len, &feedback, 0) || feedback != len)
    {
        //CloseHandle(this->hSerial);
        this->hSerial = INVALID_HANDLE_VALUE;
        throw TTYException();
    }

    // In some cases it's worth uncommenting
    FlushFileBuffers(this->hSerial);
}

serial Serial;
#include <ctime>
#include <chrono>
#include <iostream>

#ifndef GETTIME_H
#define GETTIME_H

class GetTime
{
public:
    GetTime();
    refresh();
    h();
    m();
    s();
    D();
    M();
    Y();

private:
    time_t t;
    tm *now;
};

extern GetTime getTime;

#endif
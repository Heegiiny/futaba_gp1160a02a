#include "getTime.h"

GetTime::GetTime()
{
    this->refresh();
}
GetTime::refresh()
{
    this->t = std::time(0);
    this->now = std::localtime(&t);
}
GetTime::Y()
{
    return this->now->tm_year + 1900;
}
GetTime::M()
{
    return this->now->tm_mon + 1;
}
GetTime::D()
{
    return this->now->tm_mday;
}
GetTime::h()
{
    return this->now->tm_hour;
}
GetTime::m()
{
    return this->now->tm_min;
}
GetTime::s()
{
    return this->now->tm_sec;
}

GetTime getTime;
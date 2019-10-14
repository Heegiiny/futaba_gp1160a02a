#include <math.h>

#ifndef UTILS_H
#define UTILS_H

#define BYTE_SIZE 8
#define PI 3.14159265

template <class T>
inline int
sgn(T v)
{
    return (v > T(0)) - (v < T(0));
}

template <class T>
inline T
round_6(T v)
{
    return round(pow(10, 6) * v) / pow(10, 6);
}

template <class T>
inline T
deg_to_rad(T v)
{
    return v * PI / 180.0;
}

#endif
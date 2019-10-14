#include "clock.h"
#include "getTime.h"

double cotan(double fi)
{
    double tan_fi = round_6(tan(fi));

    return (sgn(tan_fi) == 0) ? (cos(fi) * 1.725) : (1 / tan_fi);
}
drawScale()
{
    for (double phi = 0; phi < 360; phi += 30)
    {
        int x, y, dx, dy;
        double sine = sin(deg_to_rad(phi));
        sine = round_6(sine);
        double cotane = cotan(deg_to_rad(phi));

        x = 51; //(sine >= 0 ? 31 : 32) + 0 * sine;
        y = 32; //(cosine >= 0 ? 31 : 32) + 0 * cosine;
        dx = 30 * cotane;
        dy = sgn(sine) * 31;

        Graphics.drawLine(x, y, dx, dy);
    }
    //Graphics.drawRectangle(1, 2, 110, 60);
    Graphics.drawRectangle(5, 6, 93, 53, false);
    Graphics.setPixel(51, 32);
}

drawHoursLine(int h, int m)
{
    int h12 = h % 12;
    double m_in_h = (double)m / 60.0;
    double phi = 180 - (360.0 * (((double)h12 / 12.0) + 0.1 * m_in_h));
    //for (double phi = 0; phi < 360; phi += 30)
    //{
    int x, y, dx, dy;
    double sine = sin(deg_to_rad(phi));
    double cosine = cos(deg_to_rad(phi));

    x = 51 - (5 * sine);
    y = 32 - (5 * cosine);
    //x = (sine >= 0 ? 31 : 31) + 0 * sine;
    //y = (cosine >= 0 ? 31 : 32) + 0 * cosine;
    dx = 28 * sine;
    dy = 28 * cosine;

    Graphics.drawLine(x, y, dx, dy);
    Graphics.drawLine(x + 1, y, dx, dy);
    Graphics.drawLine(x - 1, y, dx, dy);
    //}
}
drawMinutesLine(int m)
{
    double phi = 180 - (360.0 * ((double)m / 60.0));
    //for (double phi = 0; phi < 360; phi += 30)
    //{
    int x, y, dx, dy;
    double sine = sin(deg_to_rad(phi));
    double cosine = cos(deg_to_rad(phi));

    x = 51 - (12 * sine);
    y = 32 - (12 * cosine);
    //x = (sine >= 0 ? 31 : 31) + 0 * sine;
    //y = (cosine >= 0 ? 31 : 32) + 0 * cosine;
    dx = 43 * sine;
    dy = 43 * cosine;

    Graphics.drawLine(x, y, dx, dy);
    //}
}

Clock::drawClock()
{
    Graphics.clear();
    drawScale();
    getTime.refresh();
    drawHoursLine(getTime.h(), getTime.m());
    drawMinutesLine(getTime.m());
    Graphics.flushTrasaction();
}

Clock::runClock()
{
    getTime.refresh();
    int mm = 0;
    while (1)
    {

        getTime.refresh();
        if (getTime.m() != mm)
        {
            std::cout << "mm0: " << mm
                      << "\n";
            mm = getTime.m();
            std::cout << "mm1: " << mm
                      << "\n";
            analogClock.drawClock();

            display.setCursor(10, 2);
            char date_str[10];
            //memset(date_str, 0, 10);
            sprintf(date_str, "%d.%d.%d", getTime.D(), getTime.M(), getTime.Y());
            Serial.write(date_str);

            display.setCursor(10, 1);
            char time_str[5];
            //memset(time_str, 0, 5);
            sprintf(time_str, "%d:%d", getTime.h(), getTime.m());
            Serial.write(time_str);
            mm = getTime.m();
        }
    }
}

Clock analogClock;
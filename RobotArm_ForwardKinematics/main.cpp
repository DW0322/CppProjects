#include <cmath>
#include <iostream>

struct Coords
{
    double x;
    double y;
};

struct Joints
{
    double length;
    double angle;
};

double degreeToRads(double angle)
{
    return angle * (M_PI / 180);
}

Coords armCoords(Joints arm)
{
    Coords c;
    c.x = std::sin(arm.angle) * arm.length;
    c.y = std::cos(arm.angle) * arm.length;
    return c;
}

int main()
{
    Joints l1{10.0, degreeToRads(45.0)};
    Coords c{armCoords(l1)};
    std::cout << c.x << ',' << c.y << std::endl;
    return 0;
}

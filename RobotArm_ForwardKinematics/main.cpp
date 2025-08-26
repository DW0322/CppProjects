#include "clean.hpp"
#include <cmath>
#include <iostream>

class RobotJoint
{
  public:
    struct Coords
    {
        double x;
        double y;
    };
    double length;
    double angle;
    Coords coords;

    RobotJoint(double l, double a)
    {
        length = l;
        angle = angleRads(a);
        coords = findCoords(length, angle);
    }

    double angleRads(double angle)
    {
        return angle * (M_PI / 180);
    }

    Coords findCoords(double length, double angle)
    {
        Coords c;
        c.x = clean(std::sin(angle) * length);
        c.y = clean(std::cos(angle) * length);
        return c;
    }

    RobotJoint operator+(const RobotJoint &other) const
    {
        RobotJoint result(0, 0);

        result.coords.x = this->coords.x + other.coords.x;
        result.coords.y = this->coords.y + other.coords.y;

        return result;
    }
};

int main()
{
    RobotJoint upperArm(10.0, 40.0);
    RobotJoint forearm(10.0, 30.0);
    RobotJoint hand(5.0, 45.0);
    RobotJoint arm = upperArm + forearm + hand;
    std::cout.precision(4);
    std::cout << arm.coords.x << ',' << arm.coords.y << std::endl;
    return 0;
}

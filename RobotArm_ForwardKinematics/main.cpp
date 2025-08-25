#include <iostream>
#include <vector>
#include <cmath>

struct Coords
{
  double x;
  double y;
};

struct Joints
{
  double length;
  double angle;
  Coords coords;
};

double degreeToRads(double angle)
{
  return angle * (M_PI/180);
}

Coords rotate(const Coords &arm, double angle)
{
  Coords NewCoords{};
  NewCoords.x = arm.x * std::cos(angle) - std::sin(angle) * arm.y;
  NewCoords.y = arm.x * std::sin(angle) + std::cos(angle) * arm.y;
  return NewCoords;
}

int main()
{
  Joints l1 {10, 80, {1, 10.0}};
  Coords NewArm {rotate(l1.coords, degreeToRads(l1.angle))};
  std::cout << NewArm.x << ',' << NewArm.y << std::endl;
  return 0;
}

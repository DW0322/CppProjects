#include <cmath>
#include <iostream>
#include <vector>

struct Joints
{
    double length{};
    double angle{};
};

struct coords
{
    double x{};
    double y{};
};

std::vector<std::vector<double>> rotationMatrix(double angle)
{
    return {{std::cos(angle), -std::sin(angle)}, {std::sin(angle), std::cos(angle)}};
}

coords applyRotation(coords c, std::vector<std::vector<double>> r)
{
    coords result{};
    result.x = r[0][0] * c.x + r[1][0] * c.x;
    result.y = r[1][1] * c.y + r[0][1] * c.y;
    return result;
}
int main()
{
    coords arm{2.0, 2.0};
    Joints l1{10.0, 1.0};

    coords r{applyRotation(arm, rotationMatrix(360.0))};
    std::cout << r.x << ',' << r.y << std::endl;

    return 0;
}

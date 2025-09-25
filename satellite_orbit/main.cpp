// develop a program to simulate a satellite's orbit around Earth, incorporating orbital mechanics.

// Implement two-body problem solver using numerical integration
// e.g. Runge-Kutta

// Calculate orbital parameters (semi-majors axis, eccentricity)

// Visualise the orbit in 2D/3D using python-matplotlib

#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

constexpr double EARTH_MASS{5.972e24};       // kg
constexpr double EARTH_RADIUS{6.371e6};      // m
constexpr double GRAV_CONST{6.67430e-11};    // m^3 kg^-1 s^-2
constexpr double DISTANCE_SURFACE{400000.0}; // m from earth surface
constexpr double DISTANCE_CENTER = (DISTANCE_SURFACE + EARTH_RADIUS);

struct Vector
{
    double x{};
    double y{};
};

double orbitalPeriod()
{
    return 2 * M_PI * std::sqrt(std::pow(DISTANCE_CENTER, 3) / (GRAV_CONST * EARTH_MASS));
}

double netDist(Vector r)
{
    return std::sqrt(r.x * r.x + r.y * r.y);
}

Vector vectorToEarth(Vector r)
{
    Vector a;
    a.x = -(GRAV_CONST * EARTH_MASS * r.x / std::pow(netDist(r), 3));
    a.y = -(GRAV_CONST * EARTH_MASS * r.y / std::pow(netDist(r), 3));
    return a;
}

double initialVelocity()
{
    return std::sqrt(GRAV_CONST * EARTH_MASS / DISTANCE_CENTER);
}
// Change velocity each dt time step
void EulerMethodV(const Vector &r, Vector &v, double dt)
{
    Vector a = vectorToEarth(r);
    v.x = v.x + a.x * dt;
    v.y = v.y + a.y * dt;
}
// Change distance from earth centre each dt time step
void EulerMethodR(Vector &r, const Vector &v, double dt)
{
    r.x = r.x + v.x * dt;
    r.y = r.y + v.y * dt;
}

int main()
{
    const double dt = 0.1;
    double count = 0.0;
    Vector velocity{0, initialVelocity()};
    Vector position{DISTANCE_CENTER, 0};
    std::vector<Vector> orbit;

    while (count < orbitalPeriod())
    {
        EulerMethodV(position, velocity, dt);
        EulerMethodR(position, velocity, dt);
        orbit.push_back(position);
        count += 0.1;
    }

    // CSV file creation
    std::fstream myFile;
    myFile.open("orbitData.csv", std::ios::out);
    if (myFile.is_open())
    {
        myFile << 'x' << ',' << 'y' << std::endl;
        for (int i{}; i < orbit.size(); ++i)
        {
            myFile << orbit[i].x << ',' << orbit[i].y << std::endl;
        }
    }
    myFile.close();
    return 0;
}

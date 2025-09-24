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
constexpr double SAT_MASS{3000.0};           // kg
constexpr double DISTANCE_SURFACE{3.5786e7}; // m from earth surface
constexpr double DISTANCE_CENTER = (DISTANCE_SURFACE + EARTH_RADIUS);

constexpr double vectorToEarth(double r)
{
    return -(GRAV_CONST * EARTH_MASS / (r * r));
}

double initialVelocity()
{
    return std::sqrt(GRAV_CONST * EARTH_MASS / DISTANCE_CENTER);
}
// Change velocity each dt time step
void EulerMethodV(double r, double &v, double dt)
{
    v = v + vectorToEarth(r) * dt;
}
// Change distance from earth centre each dt time step
void EulerMethodR(double &r, double v, double dt)
{
    r = r + v * dt;
}

// this simulation represents a satellite in free fall, outputs velocity and radius at each step.
// and then finally outputs the time in seconds it took to fall to the ground.
int main()
{
    const double dt = 0.1;
    double count = 0.0;
    double velocity = 0;
    std::vector<double> time;
    std::vector<double> position;
    double distanceCenter{DISTANCE_CENTER};

    while (true)
    {
        EulerMethodV(distanceCenter, velocity, dt);
        std::cout << velocity << std::endl;
        time.push_back(count);
        EulerMethodR(distanceCenter, velocity, dt);
        std::cout << distanceCenter << std::endl;
        position.push_back(distanceCenter);
        count += 0.1;
        if (distanceCenter <= EARTH_RADIUS)
        {
            std::cout << count << std::endl;
            break;
        }
    }

    // CSV file creation
    std::fstream myFile;
    myFile.open("orbitData.csv", std::ios::out);
    if (myFile.is_open())
    {
        myFile << "time" << ',' << "position" << std::endl;
        for (int i{}; i < time.size(); ++i)
        {
            myFile << time[i] << ',' << position[i] << std::endl;
        }
    }
    myFile.close();
    return 0;
}

#ifndef CONSTANTS_H
#define CONSTANTS_H

inline constexpr double EARTH_MASS{5.972e24};       // kg
inline constexpr double EARTH_RADIUS{6.371e6};      // m
inline constexpr double GRAV_CONST{6.67430e-11};    // m^3 kg^-1 s^-2
inline constexpr double DISTANCE_SURFACE{400000.0}; // m from earth surface
inline constexpr double DISTANCE_CENTER = (DISTANCE_SURFACE + EARTH_RADIUS);

#endif // !CONSTANTS_H

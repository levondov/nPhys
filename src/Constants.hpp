#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants
{
    constexpr size_t MAX_SHAPES = 100;

    constexpr double PI = 3.14159265358979323846;
    constexpr double RAD_TO_DEG = 180.0 / PI;
    constexpr double DEG_TO_RAD = PI / 180.0;
    constexpr double GRAVITY = 9.81; // m/s^2
    constexpr double EPSILON = 1e-6; // Small value for floating-point comparisons
}

#endif // CONSTANTS_HPP

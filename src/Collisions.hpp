#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "object_types.hpp"

class Collisions
{
    public:
        Collisions() = delete;
        ~Collisions() = delete;

        static void calcCollisionsWallsCircle(shape* s, simulation_settings* settings);
};

#endif // COLLISIONS_HPP
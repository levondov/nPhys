#ifndef EOMs_HPP
#define EOMs_HPP

#include "object_types.hpp"

class EOMs
{
    public:
        EOMs() = delete;
        ~EOMs() = delete;

        static void calcDynamics(shape* shapes[], simulation_settings* settings);
        static void calcEOMs(shape* shapes[]);

        static void calcCollisions(shape* shape, simulation_settings* settings);        
};
#endif // EOMs_HPP
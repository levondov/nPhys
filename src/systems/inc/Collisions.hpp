#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "object_types.hpp"
#include "setting_types.hpp"

namespace Collisions
{
    void walls(shape_pool& pool, const simulation_settings& settings);
}

#endif // COLLISIONS_HPP

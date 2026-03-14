#ifndef DYNAMICS_HPP
#define DYNAMICS_HPP

#include "object_types.hpp"
#include "setting_types.hpp"

namespace Dynamics
{
    void calculate(shape_pool& pool, const simulation_settings& settings);
}

#endif // DYNAMICS_HPP
#include "Dynamics.hpp"
#include "Constants.hpp"
#include "Frames.hpp"
#include "Collisions.hpp"

namespace Dynamics
{
    void calculate(shape_pool& pool, const simulation_settings& settings)
    {
        double g_acc_body[2] = {0.0, 0.0};
        for (size_t i = 0; i < pool.count; i++)
        {
            pool.fx[i] = 0.0;
            pool.fy[i] = 0.0;
            pool.my[i] = 0.0;

            Frames::get_gravity(pool.theta[i], Frames::FrameType::Body, g_acc_body);

            pool.fx[i] = g_acc_body[0] * settings.gravity_scale * pool.mass[i];
            pool.fy[i] = g_acc_body[1] * settings.gravity_scale * pool.mass[i];
        }
    }
}
#include "Collisions.hpp"
#include "Frames.hpp"
#include "Constants.hpp"
#include <cmath>

namespace Collisions
{
    void walls(shape_pool& pool, const simulation_settings& settings)
    {
        for (size_t i = 0; i < pool.count; i++)
        {
            if (pool.type[i] != shape_type::Circle) { continue; }

            double radius = pool.size1[i];
            double e      = pool.e[i];

            // Right wall
            if (pool.x[i] >= settings.scene_width - radius && pool.xd[i] > 0.0)
            {
                pool.x[i]  = settings.scene_width - radius;
                pool.xd[i] = -e * pool.xd[i];
            }
            // Left wall
            else if (pool.x[i] <= radius && pool.xd[i] < 0.0)
            {
                pool.x[i]  = radius;
                pool.xd[i] = -e * pool.xd[i];
            }

            // Top wall
            if (pool.y[i] >= settings.scene_height - radius && pool.yd[i] > 0.0)
            {
                pool.y[i]  = settings.scene_height - radius;
                pool.yd[i] = -e * pool.yd[i];
            }
            // Bottom wall
            else if (pool.y[i] <= radius && pool.yd[i] < 0.0)
            {
                pool.y[i]  = radius;
                pool.yd[i] = -e * pool.yd[i];

                // Kill velocity if nearly at rest to prevent jitter
                if (std::abs(pool.yd[i]) < constants::EPSILON)
                {
                    pool.yd[i] = 0.0;

                    // Counter gravity in body frame so resting shapes don't sink
                    double f_rest_inertial[2] = {0.0, pool.mass[i] * settings.gravity_scale * constants::GRAVITY};
                    double f_rest_body[2]     = {0.0, 0.0};
                    Frames::rotate_vec(pool.theta[i], f_rest_inertial, f_rest_body);
                    pool.fx[i] += f_rest_body[0];
                    pool.fy[i] += f_rest_body[1];
                }
            }
        }
    }
}

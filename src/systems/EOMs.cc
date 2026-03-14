#include "EOMs.hpp"
#include "Frames.hpp"

namespace EOMs
{
    void calculate(shape_pool& pool)
    {
        double force_inertial[2] = {0.0, 0.0};
        double force_body[2] = {0.0, 0.0};

        for (size_t i = 0; i < pool.count; i++)
        {
            // rotate forces from body to inertial frame
            force_body[0] = pool.fx[i];
            force_body[1] = pool.fy[i];
            Frames::rotate_vec(pool.theta[i], force_body, force_inertial);

            // calculate accelerations
            pool.xdd[i] = force_inertial[0] / pool.mass[i];
            pool.ydd[i] = force_inertial[1] / pool.mass[i];
            pool.thetadd[i] = pool.my[i] / pool.Iyy[i];
        }
    }
}
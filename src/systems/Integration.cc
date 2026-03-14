#include "Integration.hpp"

namespace Integration
{
    void step(shape_pool& pool, double dt)
    {
        for (size_t i = 0; i < pool.count; i++)
        {
            // x
            pool.xd[i] = pool.xd[i] + pool.xdd[i] * dt;
            pool.x[i]  = pool.x[i]  + pool.xd[i]  * dt + 0.5 * pool.xdd[i] * dt * dt;

            // y
            pool.yd[i] = pool.yd[i] + pool.ydd[i] * dt;
            pool.y[i]  = pool.y[i]  + pool.yd[i]  * dt + 0.5 * pool.ydd[i] * dt * dt;

            // theta
            pool.thetad[i] = pool.thetad[i] + pool.thetadd[i] * dt;
            pool.theta[i]  = pool.theta[i]  + pool.thetad[i]  * dt + 0.5 * pool.thetadd[i] * dt * dt;
        }
    }
}
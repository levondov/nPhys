#include "EOMs.hpp"

#include "Frames.hpp"
#include "Constants.hpp"
#include "Collisions.hpp"

#include <iostream>

void EOMs::calcCollisions(shape* s, simulation_settings* settings) 
{
    switch ( s->base_shape->type ) 
    {
        case shape_type::Circle:
        {
            Collisions::calcCollisionsWallsCircle(s, settings);
            break;
        }
        default:
            std::cerr << "Unknown shape type! Skipping collision" << std::endl;
            break;
    }
}

void EOMs::calcDynamics(shape* shapes[], simulation_settings* settings) 
{
    double g_accl[2] = {0.0, 0.0};
    for (size_t i = 0; i < constants::MAX_SHAPES; ++i) 
    {
        if (shapes[i] != nullptr) 
        {
            shape* s = shapes[i];

            s->dyn.fx = 0.0;
            s->dyn.fy = 0.0;
            s->dyn.my = 0.0;

            Frames::getGravity(s, FrameType::Body, g_accl);

            s->dyn.fx += g_accl[0] * settings->gravity_scale * s->dyn.mass;
            s->dyn.fy += g_accl[1] * settings->gravity_scale * s->dyn.mass;            
            
            calcCollisions(s, settings);
        }
    }
}

void EOMs::calcEOMs(shape* shapes[]) 
{
    for (size_t i = 0; i < constants::MAX_SHAPES; ++i) 
    {
        if (shapes[i] != nullptr) 
        {
            shape* s = shapes[i];

            double force_body[2] = {s->dyn.fx, s->dyn.fy};
            double force_inertia[2] = {0.0, 0.0};
            Frames::rotateVec(s->st.theta.x[0], force_body, force_inertia);

            // calculate accels
            s->st.x.xdd = force_inertia[0] / s->dyn.mass;
            s->st.y.xdd = force_inertia[1] / s->dyn.mass;
            s->st.theta.xdd = s->dyn.my / s->dyn.Iyy;

            // update positions && velocities
            s->st.x.advance();
            s->st.y.advance();
            s->st.theta.advance();
        }
    }
}
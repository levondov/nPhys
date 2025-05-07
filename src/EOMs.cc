#include "EOMs.hpp"

#include "Frames.hpp"
#include "Constants.hpp"
#include <iostream>

void EOMs::calcCollisions(shape* s, simulation_settings* settings) 
{
    switch ( s->base_shape->type ) 
    {
        case shape_type::Circle:
        {
            double radius = dynamic_cast<shape_circle*>(s->base_shape.get())->radius;
            double p[2] = {s->st.x.x[0], s->st.y.x[0]};                    
            double vrel[2] = {s->st.x.xd[0], s->st.y.xd[0]};
            double m = (s->dyn.mass * s->dyn.Iyy) / (s->dyn.mass + s->dyn.Iyy);
            double vn[2] = {0.0, 0.0};

            // touching right wall
            if ( (settings->scene_width - s->st.x.x[0]) <= radius ) 
            {
                // vn = vrel * n , here n = (-1,0)
                vn[0] = -vrel[0]; vn[1] = 0.0;
            }
            // touching left wall
            else if ( s->st.x.x[0] <= radius ) 
            {
                // vn = vrel * n , here n = (1,0)
                vn[0] = vrel[0]; vn[1] = 0.0;
            }
            // touching top wall
            else if ( (settings->scene_height - s->st.y.x[0]) <= radius ) 
            {
                // vn = vrel * n , here n = (0,-1)
                vn[0] = 0.0; vn[1] = -vrel[1];
            }
            // touching bottom wall
            else if ( s->st.y.x[0] <= radius ) 
            {
                // vn = vrel * n , here n = (0,1)
                vn[0] = 0.0;
                if (vrel[1] < 0.0)  { vn[1] = vrel[1]; }
                else if (vrel[1] < 0.01) 
                {
                    // Apply resting contact force
                    s->dyn.fy += s->dyn.mass * settings->gravity_scale * 9.81;
                }
            
                // Positional correction to resolve penetration
                s->st.y.x[1] = radius;
            }

            // Calculate impulse
            double j[2] = { -(1 + s->dyn.e) * vn[0] * m, -(1 + s->dyn.e) * vn[1] * m };

            // Convert impulse to force for integration
            s->dyn.fx += j[0] / settings->dt;
            s->dyn.fy += j[1] / settings->dt;         
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
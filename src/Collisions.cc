#include "Collisions.hpp"

#include "Constants.hpp"

void Collisions::calcCollisionsWallsCircle(shape* s, simulation_settings* settings)
{
    double radius = dynamic_cast<shape_circle*>(s->base_shape.get())->radius;
    double p[2] = {s->st.x.x[0], s->st.y.x[0]};
    double vrel[2] = {s->st.x.xd[0], s->st.y.xd[0]};
    double m = (s->dyn.mass * s->dyn.Iyy) / (s->dyn.mass + s->dyn.Iyy);
    double vn[2] = {0.0, 0.0};

    // touching right wall
    if ( (settings->scene_width - p[0]) <= radius ) 
    {
        vn[1] = 0.0;
        if ( vrel[0] > 0.0 )
        {
            vn[0] = vrel[0];
        }

        // Positional correction to resolve penetration
        s->st.x.x[1] = settings->scene_width - radius;
    }
    // touching left wall
    else if ( p[0] <= radius ) 
    {
        vn[1] = 0.0;
        if ( vrel[0] < 0.0 )
        {
            vn[0] = vrel[0];
        }

        // Positional correction to resolve penetration
        s->st.x.x[1] = radius;
    }
    // touching top wall
    else if ( (settings->scene_height - p[1]) <= radius ) 
    {
        vn[0] = 0.0;
        if (vrel[1] > 0.0)
        {
            vn[1] = vrel[1]; 
        }

        // Positional correction to resolve penetration
        s->st.y.x[1] = settings->scene_height - radius;
    }
    // touching bottom wall
    else if ( p[1] <= radius ) 
    {
        vn[0] = 0.0;
        if (vrel[1] < 0.0)
        {
            vn[1] = vrel[1]; 
        }
        else if (vrel[1] < 0.01) 
        {
            // Apply resting contact force
            s->dyn.fy += s->dyn.mass * settings->gravity_scale * constants::GRAVITY;
        }
    
        // Positional correction to resolve penetration
        s->st.y.x[1] = radius;
    }

    // Convert impulse to force for integration
    s->dyn.fx += -(1 + s->dyn.e) * vn[0] * m / settings->dt;
    s->dyn.fy += -(1 + s->dyn.e) * vn[1] * m / settings->dt;   
}
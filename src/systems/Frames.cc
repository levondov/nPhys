#include "Frames.hpp"

#include "Constants.hpp"
#include <cmath>

namespace Frames
{
    void rotate_vec(double& theta_rad, double vec_in[2], double vec_out[2])
    {
        vec_out[0] = vec_in[0] * cos(theta_rad) - vec_in[1] * sin(theta_rad);
        vec_out[1] = vec_in[0] * sin(theta_rad) + vec_in[1] * cos(theta_rad);
    }

    double get_distance(double p1[2], double p2[2])
    {
        return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
    }

    void get_gravity(double& theta_rad, FrameType ftype, double vec_out[2])
    {
        double vec_in_inertia[2] = {0.0, -constants::GRAVITY};

        if (ftype == FrameType::Body) 
        {
            rotate_vec(theta_rad, vec_in_inertia, vec_out);
        } 
        else if (ftype == FrameType::Inertial) 
        {
            vec_out[0] = vec_in_inertia[0];
            vec_out[1] = vec_in_inertia[1];
        }
    }
}
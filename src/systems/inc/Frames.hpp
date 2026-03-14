#ifndef FRAMES_HPP
#define FRAMES_HPP

#include "object_types.hpp"

namespace Frames
{
    enum FrameType: int
    {
        Body = 0,
        Inertial = 1,
    };

    void get_gravity(double& theta_rad, FrameType ftype, double vec_out[2]);

    void rotate_vec(double& theta_rad, double vec_in[2], double vec_out[2]);

    double get_distance(double p1[2], double p2[2]);
}

#endif // FRAMES_HPP
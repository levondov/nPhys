#include "Frames.hpp"

#include "Constants.hpp"
#include <cmath>

void Frames::getGravity(shape* shape, FrameType ftype, double* g_accl)
{
    double vec_in_inertia[2] = {0.0, -constants::GRAVITY};
    double vec_out[2] = {0.0, 0.0};

    if (ftype == FrameType::Body) 
    {
        Frames::rotateVec(-shape->st.theta.x[0], vec_in_inertia, vec_out);
        g_accl[0] = vec_out[0];
        g_accl[1] = vec_out[1];
    } 
    else if (ftype == FrameType::Inertial) 
    {
        g_accl[0] = vec_in_inertia[0];
        g_accl[1] = vec_in_inertia[1];
    }
}

void Frames::rotateVec(double theta_rad, double vec_in[2], double vec_out[2])
{
    vec_out[0] = vec_in[0] * cos(theta_rad) - vec_in[1] * sin(theta_rad);
    vec_out[1] = vec_in[0] * sin(theta_rad) + vec_in[1] * cos(theta_rad);
}

double Frames::getDistance(double p1[2], double p2[2])
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
}
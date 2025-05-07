#ifndef FRAMES_HPP
#define FRAMES_HPP

#include "object_types.hpp"

enum FrameType: int
{
    Body = 0,
    Inertial = 1,
};

class Frames
{
    public:
        Frames() = delete;
        ~Frames() = delete;

        static void getGravity(shape* shape, FrameType ftype, double* g_accl);

        static void rotateVec(double theta_rad, double vec_in[2], double vec_out[2]);

        static double getDistance(double p1[2], double p2[2]);
};

#endif // FRAMES_HPP
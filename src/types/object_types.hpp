#ifndef OJBECT_TYPES_HPP
#define OJBECT_TYPES_HPP

#include <pybind11/pybind11.h>
#include "Constants.hpp"
using namespace constants;

namespace py = pybind11;

enum shape_type : int
{
    Circle = 0,
    Rectangle = 1,
    Polygon = 2,
    // Add more shape types as needed
};

// DoA w/ SoA
struct shape_pool
{
    // states
    double x[MAX_OBJECTS];
    double y[MAX_OBJECTS];
    double theta[MAX_OBJECTS];
    double xd[MAX_OBJECTS];
    double yd[MAX_OBJECTS];
    double thetad[MAX_OBJECTS];
    double xdd[MAX_OBJECTS];
    double ydd[MAX_OBJECTS];
    double thetadd[MAX_OBJECTS];

    // dynamics
    double fx[MAX_OBJECTS];
    double fy[MAX_OBJECTS];
    double my[MAX_OBJECTS];

    double mass[MAX_OBJECTS];
    double Iyy[MAX_OBJECTS];
    double cgx[MAX_OBJECTS];
    double cgy[MAX_OBJECTS];
    double e[MAX_OBJECTS]; // restitution coefficient

    double size1[MAX_OBJECTS];
    double size2[MAX_OBJECTS];
    
    shape_type type[MAX_OBJECTS];
    size_t count = 0;

    bool add(double _x, double _y, double _mass, shape_type _type, double _radius = 1.0, double _e = 0.5)
    {
        if (count >= MAX_OBJECTS) { return false; }

        x[count]      = _x;
        y[count]      = _y;
        xd[count]     = 0.0;
        yd[count]     = 0.0;
        xdd[count]    = 0.0;
        ydd[count]    = 0.0;
        theta[count]  = 0.0;
        thetad[count] = 0.0;
        thetadd[count]= 0.0;
        fx[count]     = 0.0;
        fy[count]     = 0.0;
        my[count]     = 0.0;
        mass[count]   = _mass;
        Iyy[count]    = 0.5 * _mass * _radius * _radius; // solid disk inertia
        cgx[count]    = 0.0;
        cgy[count]    = 0.0;
        e[count]      = _e;
        size1[count]  = _radius;
        size2[count]  = _radius;
        type[count]   = _type;

        count++;
        return true;
    }

    // LIFO
    bool remove()
    {
        if (count == 0) { return false; }
        count--;
        return true;
    }
};

inline void bind_object_types(py::module_ &m)
{
    py::enum_<shape_type>(m, "shape_type")
        .value("Circle",    shape_type::Circle)
        .value("Rectangle", shape_type::Rectangle)
        .value("Polygon",   shape_type::Polygon)
        .export_values();
}

#endif // OBJECT_TYPES_HPP
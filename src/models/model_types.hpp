#ifndef MODEL_TYPES_HPP
#define MODEL_TYPES_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For std::string and STL containers

// Include your struct definitions
#include <string>

struct state 
{
    double x_init;
    double x;
    double xd;
    double xdd;
    double dt;

    void advance() 
    {
        xd += xdd * dt;
        x += xd * dt;
    }
};

struct dynamics 
{
    double fx;
    double fy;
    double my;

    double Iyy;
    double mass;

    double cgx;
    double cgy;

    double size1;
    double size2;
};

struct states 
{
    state x;
    state y;
    state theta;
};

struct shape 
{
    std::string name = "";
    dynamics dyn;
    states st;
};

// Function to bind the structs
namespace py = pybind11;

inline void bind_model_types(py::module_ &m) 
{
    py::class_<state>(m, "state")
        .def(py::init<>())
        .def_readwrite("x_init", &state::x_init)
        .def_readwrite("x", &state::x)
        .def_readwrite("xd", &state::xd)
        .def_readwrite("xdd", &state::xdd)
        .def_readwrite("dt", &state::dt)
        .def("advance", &state::advance);

    py::class_<dynamics>(m, "dynamics")
        .def(py::init<>())
        .def_readwrite("fx", &dynamics::fx)
        .def_readwrite("fy", &dynamics::fy)
        .def_readwrite("my", &dynamics::my)
        .def_readwrite("Iyy", &dynamics::Iyy)
        .def_readwrite("mass", &dynamics::mass)
        .def_readwrite("cgx", &dynamics::cgx)
        .def_readwrite("cgy", &dynamics::cgy)
        .def_readwrite("size1", &dynamics::size1)
        .def_readwrite("size2", &dynamics::size2);

    py::class_<states>(m, "states")
        .def(py::init<>())
        .def_readwrite("x", &states::x)
        .def_readwrite("y", &states::y)
        .def_readwrite("theta", &states::theta);

    py::class_<shape>(m, "shape")
        .def(py::init<>())
        .def_readwrite("name", &shape::name)
        .def_readwrite("dyn", &shape::dyn)
        .def_readwrite("st", &shape::st);
}

#endif // MODEL_TYPES_HPP
#ifndef OJBECT_TYPES_HPP
#define OJBECT_TYPES_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For std::string and STL containers

#include "models/shape_types.hpp"

// Include your struct definitions
#include <string>
#include <array>

struct state 
{
    double x_init;
    double xd_init;
    std::array<double, 2> x;
    std::array<double, 2> xd;
    double xdd;
    double dt;

    state() {}

    state(double _x_init, double _xd_init) : x_init(_x_init), xd_init(_xd_init)
    {
        x = {x_init, x_init};
        xd = {xd_init, xd_init};
        xdd = 0.0;
    }

    void advance()
    {
        xd[0] = xd[1] + xdd * dt;
        x[0] = x[1] + xd[1] * dt + 0.5 * xdd * dt * dt;
        xd[1] = xd[0];
        x[1] = x[0];
    }
};

struct dynamics 
{
    double fx = 0.0;
    double fy = 0.0;
    double my = 0.0;

    double jx = 0.0;
    double jy = 0.0;

    double e = 0.1; // restitution coefficient

    double Iyy = 0.001;
    double mass = 1.0;

    double cgx = 0.0;
    double cgy = 0.0;

    double size1 = 1.0;
    double size2 = 1.0;
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
    std::shared_ptr<shape_basic> base_shape;
    dynamics dyn;
    states st;

    shape (
        double _mass, 
        double _inertia,
        std::shared_ptr<shape_basic> _base_shape,        
        const std::string& _name,
        double x_init,
        double y_init,
        double theta_init,
        double xdd_init,
        double ydd_init,
        double thetadd_init
    ) : base_shape(std::move(_base_shape))
    {
        dyn.mass = _mass;
        dyn.Iyy = _inertia;

        st.x = state(x_init, xdd_init);
        st.y = state(y_init, ydd_init);
        st.theta = state(theta_init, thetadd_init);

        name = _name;
    }    
};

struct simulation_settings
{
    double dt = 0.01;
    double t_min;
    double t_max;    
    double t = 0.0;
    int n_steps = 0;

    double gravity_scale = 1.0;
    double friction_scale = 1.0;

    double scene_width = 50.0;
    double scene_height = 50.0;
};

// Function to bind the structs
namespace py = pybind11;

inline void bind_model_types(py::module_ &m) 
{
    // Bind the simulation_settings struct
    py::class_<simulation_settings>(m, "simulation_settings")
        .def(py::init<>())
        .def_readwrite("dt", &simulation_settings::dt)
        .def_readwrite("t_min", &simulation_settings::t_min)
        .def_readwrite("t_max", &simulation_settings::t_max)
        .def_readwrite("t", &simulation_settings::t)
        .def_readwrite("n_steps", &simulation_settings::n_steps)
        .def_readwrite("gravity_scale", &simulation_settings::gravity_scale)
        .def_readwrite("friction_scale", &simulation_settings::friction_scale)
        .def_readwrite("scene_width", &simulation_settings::scene_width)
        .def_readwrite("scene_height", &simulation_settings::scene_height);

    // Bind the state struct
    py::class_<state>(m, "state")
        .def(py::init<>([](double x_init, double xd_init) { return state(x_init, xd_init); }))
        .def_readwrite("x_init", &state::x_init)
        .def_readwrite("x", &state::x)
        .def_readwrite("xd", &state::xd)
        .def_readwrite("xdd", &state::xdd)
        .def_readwrite("dt", &state::dt)
        .def("advance", &state::advance);

    // Bind the dynamics struct
    py::class_<dynamics>(m, "dynamics")
        .def(py::init<>())
        .def_readwrite("fx", &dynamics::fx)
        .def_readwrite("fy", &dynamics::fy)
        .def_readwrite("my", &dynamics::my)
        .def_readwrite("jx", &dynamics::jx)
        .def_readwrite("jy", &dynamics::jy)
        .def_readwrite("e", &dynamics::e)
        .def_readwrite("Iyy", &dynamics::Iyy)
        .def_readwrite("mass", &dynamics::mass)
        .def_readwrite("cgx", &dynamics::cgx)
        .def_readwrite("cgy", &dynamics::cgy)
        .def_readwrite("size1", &dynamics::size1)
        .def_readwrite("size2", &dynamics::size2);

    // Bind the states struct
    py::class_<states>(m, "states")
        .def(py::init<>())
        .def_readwrite("x", &states::x)
        .def_readwrite("y", &states::y)
        .def_readwrite("theta", &states::theta);

    // Bind the shape struct
    py::class_<shape>(m, "shape")
        .def(py::init<double, double, std::shared_ptr<shape_basic>, const std::string&, double, double, double, double, double, double>(),
             py::arg("_mass") = 1.0,
             py::arg("_inertia") = 0.001,
             py::arg("_base_shape"),
             py::arg("_name") = "shape",
             py::arg("x_init") = 0.0,
             py::arg("y_init") = 0.0,
             py::arg("theta_init") = 0.0,
             py::arg("xdd_init") = 0.0,
             py::arg("ydd_init") = 0.0,
             py::arg("thetadd_init") = 0.0)
        .def_readwrite("name", &shape::name)
        .def_readwrite("base_shape", &shape::base_shape) // Expose base_shape
        .def_readwrite("dyn", &shape::dyn)
        .def_readwrite("st", &shape::st);
}

#endif // OBJECT_TYPES_HPP
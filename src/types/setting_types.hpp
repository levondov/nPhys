#ifndef SETTING_TYPES_HPP
#define SETTING_TYPES_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For std::string and STL containers
//   ┌──────────────────┬───────────────┐
//   │     C++ type     │  Python type  │
//   ├──────────────────┼───────────────┤
//   │ std::vector<T>   │ list          │
//   ├──────────────────┼───────────────┤
//   │ std::array<T, N> │ list          │
//   ├──────────────────┼───────────────┤
//   │ std::map<K,V>    │ dict          │
//   ├──────────────────┼───────────────┤
//   │ std::string      │ str           │
//   ├──────────────────┼───────────────┤
//   │ std::optional<T> │ value or None │
//   └──────────────────┴───────────────┘

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

inline void bind_setting_types(pybind11::module_ &m) 
{
    // Bind the simulation_settings struct
    pybind11::class_<simulation_settings>(m, "simulation_settings")
        .def(pybind11::init<>())
        .def_readwrite("dt", &simulation_settings::dt)
        .def_readwrite("t_min", &simulation_settings::t_min)
        .def_readwrite("t_max", &simulation_settings::t_max)
        .def_readwrite("t", &simulation_settings::t)
        .def_readwrite("n_steps", &simulation_settings::n_steps)
        .def_readwrite("gravity_scale", &simulation_settings::gravity_scale)
        .def_readwrite("friction_scale", &simulation_settings::friction_scale)
        .def_readwrite("scene_width", &simulation_settings::scene_width)
        .def_readwrite("scene_height", &simulation_settings::scene_height);
}

#endif // SETTING_TYPES_HPP
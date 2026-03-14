#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Engine.hpp"
#include "object_types.hpp"
#include "setting_types.hpp"

namespace py = pybind11;

PYBIND11_MODULE(nphys, m) {
    py::class_<Engine>(m, "Engine")
        .def(py::init<>())
        .def("initialize", &Engine::initialize)
        .def("reset", &Engine::reset)
        .def("run", &Engine::run)
        .def("add_shape", &Engine::add_shape,
             py::arg("x"), py::arg("y"), py::arg("mass"), py::arg("type"),
             py::arg("radius") = 1.0, py::arg("e") = 0.5)
        .def("get_positions", &Engine::get_positions)
        .def("shutdown", &Engine::shutdown);

        // Bind sim settings
        bind_setting_types(m);
        // Bind object types (shape_type enum)
        bind_object_types(m);
}

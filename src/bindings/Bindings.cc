#include <pybind11/pybind11.h>
#include "../Engine.hpp"
#include "../models/model_types.hpp"

namespace py = pybind11;

PYBIND11_MODULE(nphys, m) {
    py::class_<Engine>(m, "Engine")
        .def(py::init<>())
        .def("initialize", &Engine::initialize)
        .def("run", &Engine::run)
        .def("addShape", &Engine::addShape)
        .def("shutdown", &Engine::shutdown);

        // Bind the model types
        bind_model_types(m); // Call the function to bind structs
}

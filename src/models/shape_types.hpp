#ifndef SHAPE_TYPES_HPP
#define SHAPE_TYPES_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For std::string and STL containers

// Include your struct definitions
#include <string>
#include <array>

enum shape_type : int
{
    Circle = 0,
    Rectangle = 1,
    Polygon = 2,
    // Add more shape types as needed
};

struct shape_basic
{
    shape_type type;

    shape_basic(shape_type t) : type(t) {}
    virtual ~shape_basic() {};
};

struct shape_circle : public shape_basic
{
    double radius;

    shape_circle(double r) : shape_basic(shape_type::Circle), radius(r) {}
};

struct shape_rectangle : public shape_basic
{
    double width;
    double height;

    shape_rectangle(double w, double h) : shape_basic(shape_type::Rectangle), width(w), height(h) {}
};

// Function to bind the structs to Python
namespace py = pybind11;

inline void bind_shape_types(py::module_ &m)
{
    // Bind the shape_basic base class
    py::class_<shape_basic, std::shared_ptr<shape_basic>>(m, "shape_basic")
        .def(py::init<shape_type>(), py::arg("type"))
        .def_readwrite("type", &shape_basic::type);

    // Bind the shape_circle derived class
    py::class_<shape_circle, shape_basic, std::shared_ptr<shape_circle>>(m, "shape_circle")
        .def(py::init<double>(), py::arg("radius"))
        .def_readwrite("radius", &shape_circle::radius);

    // Bind the shape_rectangle derived class
    py::class_<shape_rectangle, shape_basic, std::shared_ptr<shape_rectangle>>(m, "shape_rectangle")
        .def(py::init<double, double>(), py::arg("width"), py::arg("height"))
        .def_readwrite("width", &shape_rectangle::width)
        .def_readwrite("height", &shape_rectangle::height);
}

#endif // SHAPE_TYPES_HPP
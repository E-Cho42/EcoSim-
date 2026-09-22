#include <pybind11/pybind11.h>
#include <pybind11/stl.h>   // needed so pybind11 knows how to convert std::vector to a Python list
#include "Grid.h"          // adjust this if your header is actually named/located differently
#include "Herb.h"

namespace py = pybind11;

int add(int a, int b){
    return a + b;
}

PYBIND11_MODULE(ecosim, m) {
    m.doc() = "EcoSim++ C++ core module";

    m.def("add", &add, "Adds two integers");

    py::class_<Grid>(m, "Grid")
        .def(py::init<>())                 // default constructor: Grid()
        .def(py::init<int, int>())         // parameterized constructor: Grid(size, time_step)
        .def("step", &Grid::step)
        .def("get_grid", &Grid::get_grid)
        .def("set_cell", &Grid::set_cell);

    py::class_<Herb>(m, "Herb")
        .def(py::init<>())                              // default constructor: Herb()
        .def(py::init<int, int, int, int>())             // Herb(x_pos, y_pos, id, size)
        .def("step", &Herb::step)
        .def("get_x", &Herb::get_x)
        .def("get_y", &Herb::get_y)
        .def("get_energy", &Herb::get_energy)
        .def("is_alive", &Herb::is_alive)
        .def("get_id", &Herb::get_id);
}
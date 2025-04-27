#include <pybind11/stl.h> // <-- Important to support std::vector automatically!
#include "DotProduct/DotProductCPU.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(DotProductModule, m) {
    py::class_<DotProductCPU>(m, "DotProduct")
        .def(py::init<>())
        .def("dotProduct", &DotProductCPU::dotProduct)
        .def("dotProduct_conv", [](DotProductCPU& self, py::array_t<double> a, py::array_t<double> b) {
            if (a.size() != b.size()) throw std::runtime_error("Input sizes must match");

            auto a_ptr = static_cast<double*>(a.request().ptr);
            auto b_ptr = static_cast<double*>(b.request().ptr);

            double result = 0.0;
            for (ssize_t i = 0; i < a.size(); ++i) {
                result += a_ptr[i] * b_ptr[i];
            }
            return result;
        })
        .def("dotProduct_pyarray", &DotProductCPU::dotProduct_pyarray);
}

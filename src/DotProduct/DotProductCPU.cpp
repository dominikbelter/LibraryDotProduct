#include "DotProduct/DotProductCPU.h"

using namespace tutorial;


DotProductCPU::DotProductCPU(void) : tutorial::DotProduct("CPU", tutorial::DotProduct::Type::CPU) {

}

/// CPU imeplementation - dotproduct
double DotProductCPU::dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Input arrays must have the same size!\n");
    }
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

/// CPU imeplementation - dotproduct
double DotProductCPU::dotProduct_pyarray(const py::array_t<double>& a, const py::array_t<double>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Input arrays must have the same size!\n");
    }

    // Access the raw pointer to the data in the arrays
    const double* ptr_a = a.data();
    const double* ptr_b = b.data();

    double result = 0.0;
    for (ssize_t i = 0; i < a.size(); ++i) {
        result += ptr_a[i] * ptr_b[i];
    }
    return result;
}

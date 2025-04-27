/** @file DotProductCPU.h
 *
 * implementation - Dot product CPU
 *
 * @author Dominik Belter
 */

#ifndef DOTPRODUCTCPU_H
#define DOTPRODUCTCPU_H

#include "dotProduct.h"
#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class DotProductCPU : public tutorial::DotProduct {

public:

    /// Pointer
    using Ptr = std::unique_ptr<DotProductCPU>;

    /// Construction
    DotProductCPU(void);

    /// dot product
    double dotProduct(const std::vector<double>& a, const std::vector<double>& b);

    /// dot product
    double dotProduct_pyarray(const py::array_t<double>& a, const py::array_t<double>& b);

    virtual ~DotProductCPU() = default;

protected:


private:


};


#endif // DOTPRODUCTCPU_H

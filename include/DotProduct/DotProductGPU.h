/** @file DotProductGPU.h
 *
 * implementation - Dot product GPU
 *
 * @author Dominik Belter
 */

#ifndef DOTPRODUCTGPU_H
#define DOTPRODUCTGPU_H

#include "dotProduct.h"
#include <memory>

void CUDAdotProduct(const float* vect1, const float* vect2, size_t elementsNo, float* result);

class DotProductGPU : public tutorial::DotProduct {

public:

    /// Pointer
    using Ptr = std::unique_ptr<DotProductGPU>;

    /// Construction
    DotProductGPU(void);

    /// dot product
    float dotProduct(const std::vector<float>& a, const std::vector<float>& b);

protected:


private:


};


#endif // DOTPRODUCTGPU_H

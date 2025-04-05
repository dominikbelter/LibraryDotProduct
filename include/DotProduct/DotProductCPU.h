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

class DotProductCPU : public tutorial::DotProduct {

public:

    /// Pointer
    using Ptr = std::unique_ptr<DotProductCPU>;

    /// Construction
    DotProductCPU(void);

    /// dot product
    float dotProduct(const std::vector<float>& a, const std::vector<float>& b);

protected:


private:


};


#endif // DOTPRODUCTCPU_H

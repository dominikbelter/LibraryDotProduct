#include "DotProduct/DotProductGPU.h"

using namespace tutorial;


DotProductGPU::DotProductGPU(void) : tutorial::DotProduct("GPU", tutorial::DotProduct::Type::GPU) {

}

/// GPU imeplementation - dotproduct
float DotProductGPU::dotProduct(const std::vector<float>& a, const std::vector<float>& b) {
    float result = 0.0;
#ifdef BUILD_WITH_CUDA
    CUDAdotProduct(a.data(), b.data(), a.size(), &result);
#else
    result = 0.0;
#endif
    return result;
}

#include "DotProduct/DotProductCPU.h"

using namespace tutorial;


DotProductCPU::DotProductCPU(void) : tutorial::DotProduct("CPU", tutorial::DotProduct::Type::CPU) {

}

/// CPU imeplementation - dotproduct
float DotProductCPU::dotProduct(const std::vector<float>& a, const std::vector<float>& b) {
    float result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

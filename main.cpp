#include "DotProduct/dotProduct.h"
#include "DotProduct/DotProductCPU.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <iomanip>

using namespace std;

int main()
{
    try {
        using namespace tutorial;

        // create DotProductCPU implementation
        std::unique_ptr<DotProduct> dotProductCPU = std::make_unique<DotProductCPU>();

        std::vector<double> a(1e8, 1.0);
        std::vector<double> b(1e8, 2.0);
        auto start = std::chrono::high_resolution_clock::now();
        double resultDotCPU = dotProductCPU->dotProduct(a, b);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = end - start;
        std::cout << "Result CPU: " << std::fixed << std::setprecision(3) << resultDotCPU << std::endl;
        std::cout << "CPU execution time: " << duration.count() << " seconds" << std::endl;

#ifdef BUILD_WITH_CUDA
        // create DotProductGPU implementation
        std::unique_ptr<DotProduct> dotProductGPU = std::make_unique<DotProductGPU>();

        auto startGPU = std::chrono::high_resolution_clock::now();
        double resultDotGPU = dotProductGPU->dotProduct(a, b);
        auto endGPU = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> durationGPU = endGPU - startGPU;
        std::cout << "Result GPU: " << std::fixed << std::setprecision(3) << resultDotGPU << std::endl;
        std::cout << "GPU execution time: " << durationGPU.count() << " seconds" << std::endl;
#endif

        return 0;

		getchar();
    }
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

//#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <cuda_runtime.h>

#include <cublas_v2.h>
#include <cusolverDn.h>

/// Kernel
__global__ void KernelTemplate(size_t elementsNo)
{
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < elementsNo; i+=stride) {
        printf("index : %d\n", i);
    }

}

/// Main function
__host__ void CUDAfunctionTemplate(size_t elementsNo)
{
    // Send current data to GPU
//    sendDataToGPU(camPoseArray, cloudSize);

    // Kernel launch parameters
    int blockSize = 256;
    int numBlocks = (elementsNo + blockSize - 1) / blockSize;

    // Launch kernel
    KernelTemplate<<<numBlocks, blockSize>>>(elementsNo);

    // Wait for all kernels to finish
    cudaDeviceSynchronize();

    // Get point cloud data from GPU
//    getDataFromGPU(cloudSize);
}

/// Kernel
__global__ void dotProductKernel(const float* vect1, const float* vect2, float *partialSum, size_t elementsNo)
{
    extern __shared__ float sdata[];

    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    // printf("dupae3 %f\n", vect1[0]);
    float temp = 0.0f;
    // printf("index : %d, value1: %f, value2: %f\n", index, vect1[index], vect2[index]);
    for (int idx = index; idx < elementsNo; idx+=stride) {
        temp += vect1[idx] * vect2[idx];
        // printf("index : %d, value1: %f, value2: %f\n", idx, vect1[idx], vect2[idx]);
    }

    int cacheIdx = threadIdx.x;
    sdata[cacheIdx] = temp;

    __syncthreads();  // Synchronize before reduction

    // Reduction within block
    int i = blockDim.x / 2;
    while (i != 0) {
        if (cacheIdx < i) {
            sdata[cacheIdx] += sdata[cacheIdx + i];
        }
        __syncthreads();
        i /= 2;
    }

    // Write result from each block to global memory
    if (cacheIdx == 0) {
        // printf("cache id: %d, cache val %f\n", blockIdx.x, sdata[0]);
        partialSum[blockIdx.x] = sdata[0];
    }

}

/// Main function
__host__ void CUDAdotProduct(const float* vect1, const float* vect2, size_t elementsNo, float* result)
{
    int deviceId;
    int numberOfSMs;

    cudaGetDevice(&deviceId);
    cudaDeviceGetAttribute(&numberOfSMs, cudaDevAttrMultiProcessorCount, deviceId);

    // Kernel launch parameters
    int threadsPerBlock = 256;
    // int numberOfBlocks = (elementsNo + threadsPerBlock - 1) / threadsPerBlock;
    int numBlocks = 32 * numberOfSMs;

    // Send current data to GPU
    float *vect1_d, *vect2_d, *d_partialSum;
    cudaMalloc(&vect1_d, elementsNo * sizeof(float));
    cudaMalloc(&vect2_d, elementsNo * sizeof(float));

    cudaMemcpy(vect1_d, vect1, elementsNo * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(vect2_d, vect2, elementsNo * sizeof(float), cudaMemcpyHostToDevice);

    cudaMalloc(&d_partialSum, numBlocks * sizeof(float));

    printf("dupae1 %f\n", vect1[0]);
    // Launch kernel
    printf("num blocks %d, blocksize %d\n", numBlocks, threadsPerBlock);
    dotProductKernel<<<numBlocks, threadsPerBlock>>>(vect1_d, vect2_d, d_partialSum, elementsNo);
    printf("dupae2 %f\n", vect2[0]);

    cudaError_t addVectorsErr;
    cudaError_t asyncErr;

    addVectorsErr = cudaGetLastError();
    if(addVectorsErr != cudaSuccess) printf("Error: %s\n", cudaGetErrorString(addVectorsErr));

    // Wait for all kernels to finish
    asyncErr = cudaDeviceSynchronize();
    if(asyncErr != cudaSuccess) printf("Error: %s\n", cudaGetErrorString(asyncErr));


    // Copy partial sums back to CPU
    float* h_partialSum = new float[numBlocks];
    cudaMemcpy(h_partialSum, d_partialSum, numBlocks * sizeof(float), cudaMemcpyDeviceToHost);
    printf("partial sum[0] %f\n", h_partialSum[0]);

    // Final CPU reduction
    *result = 0;
    for (int i = 0; i < numBlocks; ++i)
        *result += h_partialSum[i];

    // Get point cloud data from GPU
    //    getDataFromGPU(cloudSize);
}

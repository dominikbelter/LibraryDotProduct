#!/usr/bin/env python3

import numpy as np
import time
import sys
sys.path.append('../build/bin')
import DotProductModule

# this is just a dummy example (please, do not complain that this is inefficient):
def dot_product(a, b):
    result = 0.0
    for i in range(len(a)):
        result += a[i] * b[i]
    return result

a = np.ones(100_000_000, dtype=np.float64)
b = np.ones(100_000_000, dtype=np.float64) * 2

start = time.time()
result = dot_product(a, b);
end = time.time()
duration = end - start

print(f"Execution time (Python only): {duration:.6f} seconds")
print("Dot product (Python only):", result)

dot_product_instance = DotProductModule.DotProduct()
start = time.time()
result = dot_product_instance.dotProduct(a, b)
end = time.time()
duration = end - start

print(f"Execution time (Python bindings): {duration:.6f} seconds")
print("Dot product (Python bindings):", result)

start = time.time()
result = dot_product_instance.dotProduct_conv(a, b)
end = time.time()
duration = end - start

print(f"Execution time (Python bindings with python data to std::vector converstion interface): {duration:.6f} seconds")
print("Dot product (Python bindings with python data to std::vector converstion interface):", result)

start = time.time()
result = dot_product_instance.dotProduct_pyarray(a, b)
end = time.time()
duration = end - start

print(f"Execution time (Python bindings with python array interface): {duration:.6f} seconds")
print("Dot product (Python bindings with python array interface):", result)

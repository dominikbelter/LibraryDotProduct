#!/usr/bin/env python3

import time

def dot_product(a, b):
    result = 0.0
    for i in range(len(a)):
        result += a[i] * b[i]
    return result

a = [1.0] * 100000000
b = [2.0] * 100000000

start = time.time()
print(dot_product(a, b))
end = time.time()
duration = end - start

print(f"Execution time: {duration:.6f} seconds")

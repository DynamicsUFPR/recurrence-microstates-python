##
##      Import NumPy and RMAPy
import numpy as np
import rmapy as rma
import time

##
##      Create a "data".
data = np.random.rand(3, 10000).astype(np.float64)

##      Try apply the RMAPy.
inicio = time.time()
dist = rma.distribution(data, data, 0.2, [4, 4])
fim = time.time()

##      Print the result.
print(dist)
print(len(dist))
print(sum(dist))
print(f"Time: {(fim - inicio) * 1000:.2f} ms")
##
##      Import NumPy and RMAPy
import numpy as np
import rmapy as rma
import time

##
##      Create a "data".
data = np.random.rand(3, 1000).astype(np.float64)
data_2 = np.random.rand(3, 1000).astype(np.float64)

teste = rma.disorder(data, 2)
print(teste)

# teste = rma.distribution(data, data_2, [0.2, 0.2], 2, recurrence = rma.Recurrence.JRP)
# print(teste)
# print(sum(teste))

##      Try apply the RMAPy.
# inicio = time.time()
# dist = rma.distribution(data, 0.2, 3)
# s = rma.entropy(dist)
# rr = rma.rate(dist)
# fim = time.time()

##      Print the result.
# print(dist)
# print(s)
# print(rr)
# print(len(dist))
# print(sum(dist))
# print(f"Time: {(fim - inicio) * 1000:.2f} ms")

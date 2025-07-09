##
##      Import NumPy and RMAPy
import numpy as np
import rmapy as rma

##
##      Create a "data".
data = np.random.rand(3, 1000).astype(np.float64)

##      Try apply the RMAPy.
dist = rma.distribution(data, data, 0.2, [2, 2], threads = 2)

##      Print the result.
print(dist)
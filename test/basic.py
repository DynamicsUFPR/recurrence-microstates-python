##
##      Import NumPy and RMAPy
import numpy as np
import RMAPy as rma

##
##      Create a "data".
data = np.zeros((3, 1000), dtype=np.float64)

##      Try apply the RMAPy.
dist = rma.distribution(data, data, 0.2, [2, 2])

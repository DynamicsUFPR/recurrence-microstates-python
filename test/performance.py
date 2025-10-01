import timeit
import numpy as np
import pandas as pd
import recurrence_microstates as rma
from pyunicorn.timeseries import RecurrencePlot

##
##      Benchmark test using RMA
def rma_test(data):
    det = rma.determinism(data, 0.27)
    lam = rma.laminarity(data, 0.27)

    return det, lam

##
##      Benchmark test using PyUnicorn
def unicorn_test(data):
    rp = RecurrencePlot(data, threshold = 0.27, normalize = False, v_min = 2, l_min = 2)
    det = rp.determinism()
    lam = rp.laminarity()

    return det, lam

##
##      Load range
df = pd.read_csv("range.csv")
rng = df["rng"].values

##
##      Alocate memory for our results.
results_pyunicorn = np.zeros(len(rng))
results_rma = np.zeros(len(rng))

for i in range(len(rng)):
    df_data = pd.read_csv(f"perf_data/db_{i + 1}_{rng[i]}.csv")
    data = df_data["data"].values
    
    def wrapper_rma(data = data):
        return rma_test(data)
    
    def wrapper_pyunicorn(data = data):
        return unicorn_test(data)
    
    tests_unicorn = np.zeros(40)
    tests_rma = np.zeros(40)

    for j in range(40):
        tests_unicorn[j] = timeit.timeit(wrapper_pyunicorn, number = 1)
        tests_rma[j] = timeit.timeit(wrapper_rma, number = 1)
    
    results_pyunicorn[i] = np.mean(tests_unicorn)
    results_rma[i] = np.mean(tests_rma)

df_results = pd.DataFrame({
    "rng": rng,
    "rma_time": results_rma,
    "pyunicorn_time": results_pyunicorn
})
df_results.to_csv("benchmark_py_results.csv", index = False)
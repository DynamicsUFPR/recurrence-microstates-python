using CSV
using DataFrames
using BenchmarkTools

import RecurrenceAnalysis as RA
import RecurrenceMicrostatesAnalysis as RMA

function rma_test(data)
    det = RMA.determinism(data, 0.27)[1]
    lam = RMA.laminarity(data, 0.27)[1]

    return det, lam
end

function ra_test(data)
    rp = RA.RecurrenceMatrix(data, 0.27)
    det = RA.determinism(rp)
    lam = RA.laminarity(rp)

    return det, lam
end

rng_df = CSV.read("range.csv", DataFrame)
rng = rng_df[!, 1]

results_ra = zeros(Float64, length(rng))
results_rma = zeros(Float64, length(rng))

data_gl = (CSV.read("perf_data/db_1_500.csv", DataFrame))[!, :]

for i in eachindex(rng)
    data_df = CSV.read("perf_data/db_$(i)_$(rng[i]).csv", DataFrame)
    global data_gl = data_df[!, 1]

    bm_ra = @benchmark ra_test(data_gl)
    bm_rma = @benchmark rma_test(data_gl)
    

    results_ra[i] = mean(bm_ra.times) / 1e9
    results_rma[i] = mean(bm_rma.times) / 1e9
end

df_results = DataFrame(rng = rng, rma_res = results_rma, ra_res = results_ra)
CSV.write("benchmark_jl_results.csv", df_results)
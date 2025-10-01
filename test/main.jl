using BSON
using Dates
using PyCall
using Statistics
using ProgressMeter

import RecurrenceAnalysis as RAJl
import RecurrenceMicrostatesAnalysis as RMAJl
RMAPy = pyimport("recurrence_microstates")
PyUni = pyimport("pyunicorn.timeseries")

##
##      Import needed systems / data generators
include("systems.jl")
import .Systems as Data

##
##      Settings
##  * global
data_len = floor.(Int, range(100, 3000, 40))
dist_len::Int = 100
##  * system
lorenz_σ::Float64 = 10.0
lorenz_b::Float64 = 8.0 / 3.0
lorenz_ρ::Float64 = 28.0

rossler_a::Float64 = 0.2
rossler_b::Float64 = 0.2
rossler_c::Float64 = 18.0

logistic_r::Float64 = 3.99
beta_x_β::Float64 = 2.99

##
##      Alocate memory to store our results
results::Array{Float64, 5} = zeros(Float64, (dist_len, length(data_len), 2, 4, 6))

##
##      Run the computation process
@showprogress for j in eachindex(data_len)
    for i in 1:dist_len
        data_uniform = Data.white_noise(data_len[j])
        data_logistic = Data.logistic_map(logistic_r, data_len[j], 10000)
        data_beta_x = Data.beta_x(beta_x_β, data_len[j], 10000)
        data_rossler = Data.rossler(rossler_a, rossler_b, rossler_c, data_len[j], 3000)[1, :]
        data_lorenz = Data.lorenz(lorenz_σ, lorenz_ρ, lorenz_b, data_len[j], 5000)[1, :]

        ## -- Uniform
        th, _ = RMAJl.find_parameters(data_uniform, 3)
        rp_jl = RAJl.RecurrenceMatrix(data_uniform, th)
        rp_py = PyUni["RecurrencePlot"](data_uniform, threshold = th, normalize = false, norm="euclidean", theiler=1, v_min = 2, l_min = 2)

        results[i, j, 1, 1, 1] = RAJl.determinism(rp_jl)
        results[i, j, 2, 1, 1] = RAJl.laminarity(rp_jl)
        results[i, j, 1, 2, 1] = rp_py.determinism()
        results[i, j, 2, 2, 1] = rp_py.laminarity()
        results[i, j, 1, 3, 1] = RMAJl.determinism(data_uniform, th)[1]
        results[i, j, 2, 3, 1] = RMAJl.laminarity(data_uniform, th)[1]
        results[i, j, 1, 4, 1] = RMAPy.determinism(data_uniform, th)
        results[i, j, 2, 4, 1] = RMAPy.laminarity(data_uniform, th)

        ## -- Logistic Map
        th, _ = RMAJl.find_parameters(data_logistic, 3)
        rp_jl = RAJl.RecurrenceMatrix(data_logistic, th)
        rp_py = PyUni["RecurrencePlot"](data_logistic, threshold = th, normalize = false, norm="euclidean", theiler=1, v_min = 2, l_min = 2)

        results[i, j, 1, 1, 2] = RAJl.determinism(rp_jl)
        results[i, j, 2, 1, 2] = RAJl.laminarity(rp_jl)
        results[i, j, 1, 2, 2] = rp_py.determinism()
        results[i, j, 2, 2, 2] = rp_py.laminarity()
        results[i, j, 1, 3, 2] = RMAJl.determinism(data_logistic, th)[1]
        results[i, j, 2, 3, 2] = RMAJl.laminarity(data_logistic, th)[1]
        results[i, j, 1, 4, 2] = RMAPy.determinism(data_logistic, th)
        results[i, j, 2, 4, 2] = RMAPy.laminarity(data_logistic, th)

        ## -- Beta-X
        th, _ = RMAJl.find_parameters(data_beta_x, 3)
        rp_jl = RAJl.RecurrenceMatrix(data_beta_x, th)
        rp_py = PyUni["RecurrencePlot"](data_beta_x, threshold = th, normalize = false, norm="euclidean", theiler=1, v_min = 2, l_min = 2)

        results[i, j, 1, 1, 3] = RAJl.determinism(rp_jl)
        results[i, j, 2, 1, 3] = RAJl.laminarity(rp_jl)
        results[i, j, 1, 2, 3] = rp_py.determinism()
        results[i, j, 2, 2, 3] = rp_py.laminarity()
        results[i, j, 1, 3, 3] = RMAJl.determinism(data_beta_x, th)[1]
        results[i, j, 2, 3, 3] = RMAJl.laminarity(data_beta_x, th)[1]
        results[i, j, 1, 4, 3] = RMAPy.determinism(data_beta_x, th)
        results[i, j, 2, 4, 3] = RMAPy.laminarity(data_beta_x, th)

        ## -- Lorenz
        th, _ = RMAJl.find_parameters(data_lorenz, 3)
        rp_jl = RAJl.RecurrenceMatrix(data_lorenz, th)
        rp_py = PyUni["RecurrencePlot"](data_lorenz, threshold = th, normalize = false, norm="euclidean", theiler=1, v_min = 2, l_min = 2)

        results[i, j, 1, 1, 4] = RAJl.determinism(rp_jl)
        results[i, j, 2, 1, 4] = RAJl.laminarity(rp_jl)
        results[i, j, 1, 2, 4] = rp_py.determinism()
        results[i, j, 2, 2, 4] = rp_py.laminarity()
        results[i, j, 1, 3, 4] = RMAJl.determinism(data_lorenz, th)[1]
        results[i, j, 2, 3, 4] = RMAJl.laminarity(data_lorenz, th)[1]
        results[i, j, 1, 4, 4] = RMAPy.determinism(data_lorenz, th)
        results[i, j, 2, 4, 4] = RMAPy.laminarity(data_lorenz, th)

        ## -- Rössler
        th, _ = RMAJl.find_parameters(data_rossler, 3)
        rp_jl = RAJl.RecurrenceMatrix(data_rossler, th)
        rp_py = PyUni["RecurrencePlot"](data_rossler, threshold = th, normalize = false, norm="euclidean", theiler=1, v_min = 2, l_min = 2)

        results[i, j, 1, 1, 5] = RAJl.determinism(rp_jl)
        results[i, j, 2, 1, 5] = RAJl.laminarity(rp_jl)
        results[i, j, 1, 2, 5] = rp_py.determinism()
        results[i, j, 2, 2, 5] = rp_py.laminarity()
        results[i, j, 1, 3, 5] = RMAJl.determinism(data_rossler, th)[1]
        results[i, j, 2, 3, 5] = RMAJl.laminarity(data_rossler, th)[1]
        results[i, j, 1, 4, 5] = RMAPy.determinism(data_rossler, th)
        results[i, j, 2, 4, 5] = RMAPy.laminarity(data_rossler, th)

        ##  -- Overview
        for s in 1:2
            for k in 1:4
                results[i, j, s, k, 6] = mean(results[i, j, s, k, 1:5])
            end
        end
    end
end

##
##      Save the result
today_str = Dates.format(now(), "yyyy_mm_dd_HH-MM-SS")
mkpath("data")
BSON.@save "data/$(today_str).bson" results
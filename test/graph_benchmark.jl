using CSV
using Makie
using DataFrames
using CairoMakie

py_results_df = CSV.read("benchmark_py_results.csv", DataFrame)
jl_results_df = CSV.read("benchmark_jl_results.csv", DataFrame)

rng = (CSV.read("range.csv", DataFrame))[!, 1]

fig = Figure(size = (800, 600))
ax = Axis(fig[1, 1], ylabel = "Mean computation time [s]", xlabel = "Data length", xticklabelsize = 14, yticklabelsize = 14, xlabelsize = 18, ylabelsize = 18,)

scatter!(ax, rng, py_results_df[!, 2], label = "RMAPy", color = :white, marker = :rect, strokecolor = Makie.to_color("#E69F00"), markersize = 10, strokewidth = 2)
scatter!(ax, rng, py_results_df[!, 3], label = "PyUnicorn", color = :white, marker = :rect, strokecolor = Makie.to_color("#CC79A7"), markersize = 10, strokewidth = 2)
scatter!(ax, rng, jl_results_df[!, 2], label = "RecurrenceMicrostatesAnalysis.jl", color = :white, marker = :rect, strokecolor = Makie.to_color("#56B4E9"), markersize = 10, strokewidth = 2)
scatter!(ax, rng, jl_results_df[!, 3], label = "RecurrenceAnalysis.jl", color = :white, marker = :rect, strokecolor = Makie.to_color("#999999"), markersize = 10, strokewidth = 2)

axislegend(ax, position = :lt, fontsize = 18)

save("performance.png", fig; dpi = 300)
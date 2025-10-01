using BSON
using Makie
using Colors
using CairoMakie
using Statistics
using ProgressMeter

data_len = floor.(Int, range(100, 3000, 40))

##
##      Read all files, and select a data input
files = readdir("data/")
println("> Select the data file:")
for f in eachindex(files)
    println("\t[$f] $(files[f])")
end

file_index = 2

while true
    print("> Select a data file: ")
    try
        idx = parse(Int, readline())

        if 1 <= idx <= length(files)
            global file_index = idx
            break
        end
    catch
        println("Invalid input")
    end
end

println("> Selected file: $(file_index) - $(files[file_index])")

##
##      Load the data file
BSON.@load "data/$(files[file_index])" results

##
##      Compute the relations between the methods
comp::Array{Float64, 5} = zeros(Float64, (size(results, 1), size(results, 2), 2, 3, 6))

@showprogress for i in axes(results, 1)
    for j in axes(results, 2)
        for s in axes(results, 5)
            for t in 1:2
                comp[i, j, t, 1, s] = (abs(results[i, j, t, 1, s] - results[i, j, t, 4, s]) / results[i, j, t, 1, s]) * 100     ## RecurrenceAnalysis X RMAPy
                comp[i, j, t, 2, s] = (abs(results[i, j, t, 2, s] - results[i, j, t, 4, s]) / results[i, j, t, 1, s]) * 100     ## PyUnicorn X RMAPy
                comp[i, j, t, 3, s] = (abs(results[i, j, t, 3, s] - results[i, j, t, 4, s]) / results[i, j, t, 1, s]) * 100     ## RecurrenceMicrostatesAnalysis X RMAPy
            end
        end
    end
end

data_means::Array{Float64, 4} = zeros(Float64, (size(comp, 2), 2, 3, 6))
data_stds::Array{Float64, 4} = zeros(Float64, (size(comp, 2), 2, 3, 6))
@showprogress for i in axes(comp, 2)
    for j in axes(comp, 3)
        for t in axes(comp, 4)
            for s in axes(comp, 5)
                data_means[i, j, t, s] = mean(comp[:, i, j, t, s])
                data_stds[i, j, t, s] = std(comp[:, i, j, t, s])
            end
        end
    end
end

##
##      Construct the graphics
function graph(means::Array{Float64, 3}, stds::Array{Float64, 3})
    fig = Figure(size = (1200, 1000))
    pos = [1, 1]
    labels = [
        "(a) Uniform distribution", 
        "(b) Logistic map", 
        "(c) Generalized Bernoulli-shift map", 
        "(d) Lorenz' system", 
        "(e) Rössler's system", 
        "(f) (Overview)"]

    for i in 1:6

        b_than_m = 0
        for j in eachindex(data_len)
            if (means[j, 1, i] <= 0.5) || (means[j, 2, i] <= 0.5) || (means[j, 3, i] <= 0.5)
                b_than_m = j
                break
            end
        end

        ax = Axis(fig[pos...], title = labels[i], titlesize = 16.0f0, ylabel = "Mean relative error", xlabel = "Data length",
            ytickformat = xs -> string.(round.(xs; digits=1), "%"))

        ## RecurrenceAnalysis X RMAPy
        lines!(ax, data_len, means[:, 1, i], label = "RecurrenceAnalysis.jl", color = Makie.to_color("#009E73"))
        band!(ax, data_len, means[:, 1, i] - stds[:, 1, i], means[:, 1, i] + stds[:, 1, i], color = Makie.to_color("#009E7315"))

        lines!(ax, data_len, means[:, 2, i], label = "PyUnicorn", color = Makie.to_color("#E69F00"))
        band!(ax, data_len, means[:, 2, i] - stds[:, 2, i], means[:, 2, i] + stds[:, 2, i], color = Makie.to_color("#E69F0015"))


        lines!(ax, data_len, means[:, 3, i], label = "RMA.jl", color = Makie.to_color("#555555"))
        band!(ax, data_len, means[:, 3, i] - stds[:, 3, i], means[:, 3, i] + stds[:, 3, i], color = Makie.to_color("#55555515"))

        vlines!(ax, data_len[b_than_m]; color = :red, linestyle = :dash, linewidth = 2, label = "K = $(data_len[b_than_m])")

        axislegend(ax, position = :rt)


        pos[2] += 1
        if (pos[2] > 2)
            pos[2] = 1
            pos[1] += 1
        end
    end

    return fig
end


mkpath("images")

det_graph = graph(data_means[:, 1, :, :], data_stds[:, 1, :, :])
lam_graph = graph(data_means[:, 2, :, :], data_stds[:, 2, :, :])

save("images/$(files[file_index])_det.png", det_graph)
save("images/$(files[file_index])_lam.png", lam_graph)
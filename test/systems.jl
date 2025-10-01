module Systems

    using Distributions
    using DifferentialEquations
    import RecurrenceMicrostatesAnalysis: prepare

    ## -----------------------------------------------------------------------------------------

    """
        white_noise(K::Int = 1000)

    Generate a white noise from a uniform distribution, with length `K`.
    """
    function white_noise(K::Int = 1000)
        return rand(Uniform(0, 1), K)
    end

    ## -----------------------------------------------------------------------------------------

    """
        logistic_map(r::Float64, K::Int = 1000), transient::Int = 10 * K

    Generate a series of a logictic map, with length K after a transient of 10 * K time steps.
    This function also receives the parameter `r`, that needed to be between 0 and 4.
    """
    function logistic_map(r::Float64, K::Int = 1000, transient::Int = 10 * K)
        @assert (r > 0) && (r < 4) "`r` needed to be in the interval (0, 4)"
        
        data::Vector{Float64} = zeros(Float64, (K))
        x = rand(Uniform(0, 1))

        for t in 1:(transient + K)
            x = r * x * (1 - x)

            if (t > transient)
                data[t - transient] = x
            end
        end

        return data
    end

    ## -----------------------------------------------------------------------------------------

    """
        beta_x(β::Float64, K::Int = 1000, transient::Int = 10 * K)
    
    Generate a series of a generalized Bernoulli-shifted map, with length K after a transient 
    of 10 * K time steps. This function also receives the parameter `r`, that needed to be greater
    than 1.
    """
    function beta_x(β::Float64, K::Int = 1000, transient::Int = 10 * K)
        @assert (β > 1) "`β` needed to be greater than 1"

        data::Vector{Float64} = zeros(Float64, (K))
        x = rand(Uniform(0, 1))

        for t in 1:(transient + K)
            x = β * x
            while (x > 1)
                x -= 1.0
            end

            if (t > transient)
                data[t - transient] = x
            end
        end

        return data
    end

    ## -----------------------------------------------------------------------------------------

    """
        lorenz(σ::Float64, ρ::Float64, b::Float64, K::Int = 1000, transient::Int = 3 * K)
    
    Generate a series of a lorenz Systems, with length K after a transient of 10 * K time steps. 
    """
    function lorenz(σ::Float64, ρ::Float64, b::Float64, K::Int = 1000, transient::Int = 3 * K)
        
        ##      Allocate memory
        data::Matrix{Float64} = zeros(Float64, (3, K))
        t_max = 3000

        ##      Lorenz system
        function lorenz!(du, u, _, _)
            x, y, z = u
            
            du[1] = σ * (y - x)
            du[2] = x * (ρ - z) - y
            du[3] = x * y - b * z
        end

        while true
            try
                prob = ODEProblem(lorenz!, rand(Uniform(0, 1), 3) .* 10, (0.0, t_max))
                sol = solve(prob)
                data[:, :] .= prepare(sol, 0.25; transient = transient, K = K)
                return data
            catch
                println("Fail to apply the transient to Lorenz, trying again...")
                t_max += 2000
                continue
            end
        end
    end

    ## -----------------------------------------------------------------------------------------

    """
        rossler(σ::Float64, ρ::Float64, b::Float64, K::Int = 1000, transient::Int = 3 * K)
    
    Generate a series of a lorenz Systems, with length K after a transient of K time steps. 
    """
    function rossler(a::Float64, b::Float64, c::Float64, K::Int = 1000, transient::Int = 3 * K)
        
        ##      Allocate memory
        data::Matrix{Float64} = zeros(Float64, (3, K))
        t_max = 3000

        ##      Lorenz system
        function rossler!(du, u, _, _)
            x, y, z = u
            
            du[1] = - y - z
            du[2] = x + a * y
            du[3] = b + z * (x - c)
        end

        while true
            try
                prob = ODEProblem(rossler!, rand(Uniform(0, 1), 3) .* 10, (0.0, t_max))
                sol = solve(prob)
                data[:, :] .= prepare(sol, 0.94; transient = transient, K = K)
                return data
            catch
                println("Fail to apply the transient to Rössler, trying again...")
                t_max += 2000
                continue
            end
        end
    end
end
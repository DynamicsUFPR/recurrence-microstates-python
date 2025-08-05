from rmapy import distribution

# An optimized Python library for analyzing dynamical systems with recurrence microstates

### 📦 Dependencies

You will need the libraries `pybind11` and `setuptools` to compile `recurrence_microstates`. Moreover, when using `rmapy`,
the `numpy` library is required to provide input data and receive output, so it is also necessary.

To install the dependencies, please run:
```text
pip install pybind11 setuptools numpy
```

### ⚙️ Installation

With the dependencies installed on your system, clone the `recurrence_microstates` GitHub
repository into any directory and access the cloned repo folder:
```text
git clone https://github.com/DynamicsUFPR/recurrence-microstates-python.git
cd recurrence-microstates-python
```

Then, try to install it using:
```text
pip install .
```

There might be an issue with the `.so` file name. If this happens,
try renaming the folder `recurrence-microstates-python` to `recurrence_microstates`, and run `pip install .` again.

## Library usage guide

The library has been written with a structure similar to [Julia version](https://github.com/DynamicsUFPR/RecurrenceMicrostatesAnalysis.jl),
so you can use its documentation as a reference. However, since `recurrence_microstates` is not a native library like 
`RecurrenceMicrostatesAnalysis.jl`, there are some variations in how *kwarg* settings are implemented.

### Importing

To use `recurrence_microstates` it is necessary to include `numpy`, we recommend that you import the library using:
```python
import numpy as np
import recurrence_microstates as rma
```

### Computing distributions

To compute a recurrence microstates distribution, you may use the function `distribution`, such as:
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 2

data = np.random.uniform(0, 1, 1000).astype(np.float64)
dist = rma.distribution(data, threshold, motif_size)
```

By default, the library works with a random sampling mode with 5% of sampling rate, and square motifs. To set other configurations,
you may use the parameters `sampling`, `sampling_mode`, `shape`, and `recurrence`.

`sampling` defines the rate of total microstates used to random sampling, being a value between 0 and 1. For example,
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 2

data = np.random.uniform(0, 1, 1000).astype(np.float64)
dist = rma.distribution(data, threshold, motif_size, sampling = 0.1)
```

`sampling_mode` set how the library will take motifs from the RP (or the trajectory, since the RP is not explicitly computed). 
The current sampling modes implemented are

- SamplingMode.Full: take all available motifs.
- SamplingMode.Random: take randomly a rate `sampling` of all available motifs, without caring about overlap or repetition.

Example of use:
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 2

data = np.random.uniform(0, 1, 1000).astype(np.float64)
dist = rma.distribution(data, threshold, motif_size, sampling_mode = rma.SamplingMode.Full)
```

`shape` defines the microstate / motif format. Actually, there are two shapes implemented in the library:

- Shape.Square: the default motif constrained shape, it defines a square-shaped motif. It can also be used to get a rectangle motif, we will
demonstrate it in the examples.
- Shape.Diagonal: this motif constrained shape was introduced to simplify the estimation of determinism using RMA.

Example using square-shaped motifs to construct a rectangle motif (in this case, we compute a line-shaped motif necessary to estimate laminarity):
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27

data = np.random.uniform(0, 1, 1000).astype(np.float64)

# Here we take a motif with 1 line and 3 columns.
dist = rma.distribution(data, data, threshold, [1, 3])
```

Example using diagonal motifs:
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 3

data = np.random.uniform(0, 1, 1000).astype(np.float64)

dist = rma.distribution(data, threshold, motif_size, shape = rma.Shape.Diagonal)
```

Finally, `recurrence` set a recurrence function to compute the recurrences from the trajectory. By default, the library uses

$R_{i,j} = \Theta(\varepsilon - \|\vec x_i - \vec y_j \|)$

that gives to the library a compatibility with Cross-Recurrence Plots, for example:
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 2

x = np.random.uniform(0, 1, 1000).astype(np.float64)
y = np.random.uniform(0, 1, 1000).astype(np.float64)

dist = rma.distribution(x, y, threshold, motif_size)
```

There recurrence functions currently implemented in the library are:
- Recurrence.Standard: the standard recurrence function, $R_{i,j} = \Theta(\varepsilon - \|\vec x_i - \vec y_j \|)$.
- Recurrence.Corridor: an extension of recurrence function with a corridor threshold, 
$R_{i,j} = \Theta(\|\vec x_i - \vec y_j \| - \varepsilon_{min}) \cdot \Theta(\varepsilon_{max} - \|\vec x_i - \vec y_j \|)$.
- Recurrence.JRP: an extension of Recurrence Plot where we compare the recurrence between two RPs. Here we write a recurrence function
$R_{i,j} = \Theta(\varepsilon_{x} - \|\vec x_i - \vec x_j \|) \cdot \Theta(\varepsilon_{y} - \|\vec y_i - \vec y_j \|)$ to represent it.

Example of use with `Recurrence.Corridor`:
```python
import numpy as np
import recurrence_microstates as rma

threshold_min = 0.01
threshold_max = 0.27
motif_size = 2

x = np.random.uniform(0, 1, 1000).astype(np.float64)

dist = rma.distribution(x, [threshold_min, threshold_max], motif_size, recurrence = rma.Recurrence.Corridor)
```

Example of use with `Recurrence.JRP`:
```python
import numpy as np
import recurrence_microstates as rma

threshold_x = 0.27
threshold_y = 0.25
motif_size = 2

x = np.random.uniform(0, 1, 1000).astype(np.float64)
y = np.random.uniform(0, 1, 1000).astype(np.float64)

dist = rma.distribution(x, y, [threshold_x, threshold_y], motif_size, recurrence = rma.Recurrence.JRP)
```

### Computing RQA

Currently, RMA has five RQA measures that can be computed directly with its methods. They are: recurrence microstates entropy (RME),
recurrence rate (RR), determinism (DET), laminarity (LAM), and disorder ($\Xi$). 

RME and RR are computed from a recurrence microstates distribution, such as
```python
import numpy as np
import recurrence_microstates as rma

threshold = 0.27
motif_size = 2

x = np.random.uniform(0, 1, 1000).astype(np.float64)
dist = rma.distribution(x, threshold, motif_size)

rme = rma.entropy(dist)
rr = rma.rate(dist)
```

DET and LAM are estimated directly from a trajectory, such as
```python
import numpy as np
import recurrence_microstates as rma

x = np.random.uniform(0, 1, 1000).astype(np.float64)

# It is necessary to define a threshold for DET and LAM.
threshold = 0.27

det = rma.determinism(x, threshold)
lam = rma.laminarity(x, threshold)
```

Disorder is also computed from a trajectory:
```python
import numpy as np
import recurrence_microstates as rma

x = np.random.uniform(0, 1, 1000).astype(np.float64)

# It defines a 'mean' threshold, disorder is computed using a 
# range of values around this in order to find the maximum disorder
threshold = 0.27

# Square-shaped motifs size, it can be: 2, 3, or 4
motif_size = 4

# Range around `threshold` to use, in this case we are taking values between 0.07 and 0.47
# Default: 0.1
threshold_range = 0.2

# Number of values taken from the interval
# Default: 10
segment_size = 10

# Compute disorder
disorder = rma.disorder(x, threshold, motif_size, threshold_range = threshold_range, segment_size = segment_size)
```

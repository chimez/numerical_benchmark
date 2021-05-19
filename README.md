# Numerical Benchmark

## Results

1. rust is really fast!
2. rust with rayon > rust plain for-loop ~ c with openmp > c plain for-loop > python parallel numba > python numba > python numpy

## problem set

$$
c_i = 
\begin{cases}
a_i^2 + b_i^2 + a_i b_i, \quad i=0 \\
a_i^2 + b_{i-1}^2 + a_i b_i + a_i + b_i, \quad \mathrm{otherwise}.
\end{cases}
$$

## data

| python numpy| 399 µs |
| python numba| 266 µs  |
| python numba parallel | 150 µs  |
| c for-loop | 97 µs  |
| c openmp | 82 µs  |
| rust for-loop | 85 µs  |
| rust rayon | 68 µs  |

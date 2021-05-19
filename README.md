# Numerical Benchmark

## Results

1. rust is really fast!
2. rust with rayon > rust plain for-loop ~ c with openmp > c plain for-loop > python parallel numba > python numba > python numpy

## problem set

<img src="https://render.githubusercontent.com/render/math?math=c_i = \begin{cases} a_i^2 %2B b_i^2 %2B a_i b_i, \quad i=0 \\ a_i^2 %2B b_{i-1}^2 %2B a_i b_i %2B a_i %2B b_i, \quad \mathrm{otherwise}.\end{cases}">

## data
                        
| target                | time   |
|:---------------------:|:------:|
| python numpy          | 399 µs |
| python numba          | 266 µs |
| python numba parallel | 150 µs |
| c for-loop            | 97 µs  |
| c openmp              | 82 µs  |
| rust for-loop         | 85 µs  |
| rust rayon            | 68 µs  |

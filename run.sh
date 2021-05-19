#!/usr/bin/bash

echo "=====     python     ====="
ipython benchmark.py

echo "=====     c     ====="
gcc -o benchmark_c -ffast-math -O3 -lm -fopenmp benchmark.c
./benchmark_c

echo "=====     rust     ====="
cd benchmark_rust
cargo run --release
cd ..

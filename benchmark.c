/**
 *  gcc -o benchmark_c -O3 -ffast-math -lm -fopenmp benchmark.c
 */

#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

void f_for(double *a, double *b, double *c) {
  for (int i = 0; i < N; ++i) {
    if (i == 0) {
      c[i] = pow(a[i], 2.0) + pow(b[i], 2.0) + a[i] * b[i];
      continue;
    }

    c[i] = pow(a[i], 2.0) + pow(b[i-1], 2.0) + a[i] * b[i] + a[i] + b[i];
  }
}

void f_omp(double *a, double *b, double *c) {
  /* if (i == 0) { */
  c[0] = pow(a[0], 2.0) + pow(b[0], 2.0) + a[0] * b[0];
  /* continue; */
  /* } */

#pragma omp parallel for
  for (int i = 1; i < N; ++i) {
    c[i] = pow(a[i], 2.0) + pow(b[i-1], 2.0) + a[i] * b[i] + a[i] + b[i];
  }
}

double measure_function(void (*func)(void), int n) {
  clock_t begin = clock();

  for (int i = 0; i < n; ++i) {
    func();
  }

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  return time_spent;
}

int main() {

  double *a = malloc(N * sizeof(double));
  double *b = malloc(N * sizeof(double));
  double *c = malloc(N * sizeof(double));

  for (int i = 0; i < N; ++i) {
    a[i] = i + 0.2174;
    b[i] = i + 0.8903;
  }

  int n_loop = 7;
  int n_each = 1000;

  clock_t begin;
  clock_t end;
  double time_spent;

  begin = clock();

  for (int i = 0; i < n_loop; ++i) {
    for (int j = 0; j < n_each; ++j) {
      f_for(a, b, c);
    }
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("for:        %0.10f us\n", time_spent / n_loop / n_each * 1000000);
  printf("%0.3f\n", c[N-3]);

  begin = clock();

  for (int i = 0; i < n_loop; ++i) {
    for (int j = 0; j < n_each; ++j) {
      f_omp(a, b, c);
    }
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("openmp for: %0.10f us\n", time_spent / n_loop / n_each * 1000000);
  printf("%0.3f\n", c[N-3]);
  printf("%0.3f\n", c[0]);

  return 0;
}

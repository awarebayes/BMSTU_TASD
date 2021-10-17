#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <stdio.h>

typedef struct 
{
    size_t dense;
    size_t sparse;
} time_measurement_t;


typedef struct
{
  size_t dense;
  size_t sparse;
} mem_measurement_t;

time_measurement_t measure_time(int n_rows, int n_cols, int percentage);
mem_measurement_t measure_memory(int n_rows, int n_cols, int percentage);
int *gen_arr(int size, int percentage);

#endif // !__PROFILE_H__

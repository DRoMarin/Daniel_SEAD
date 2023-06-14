/*
This program will numerically compute the integral of
                  4/(1+x*x)
from 0 to 1.
History: Written by Tim Mattson, 11/99.
*/

#include <omp.h>
#include <stdio.h>
static long num_steps = 100000000;
double step;


void main() {
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;

    start_time = omp_get_wtime();
    #pragma omp teams //teams is a construct that creates a predefined number of teams with a number of threads
                      //both can be controlled with the clauses num_teams and thread_limit 
    {
        #pragma omp distribute  //distribute is a construct that divides the work of the following functional block among the teams
        for (i = 1; i <= num_steps; i++) {
            x = (i - 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }

    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);
}
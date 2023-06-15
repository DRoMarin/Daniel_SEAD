/*
This program will numerically compute the integral of
                  4/(1+x*x)
from 0 to 1.
History: Written by Tim Mattson, 11/99.
*/

#include <omp.h>
#include <stdio.h>
#include <unistd.h>

static long num_steps = 100000000;
double step;

void main()
{
    int i;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;

    int proc_num = sysconf(_SC_NPROCESSORS_ONLN);
    printf("number of procs: %d\n", proc_num);

    for (int thread_num = 1; thread_num < 3 * proc_num + 1; thread_num++)
    {
        double x, pi, sum = 0.0;
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(thread_num) //parallel declares a block to parallelize 
                                                     //while num_threads clause defines the # of threads to use for parallel
        {
            #pragma omp single                      //single construct signals a functional block to only be executed by a single thread
            printf("num_threads = %d\n", omp_get_num_threads());
            #pragma omp single
            start_time = omp_get_wtime();
            
            #pragma omp for reduction(+ : sum) private(x) // reduction applies an operation to a variable shared among loops, 
                                                          // in this case this sums up all "sum" values to get the final sum
            for (i = 1; i <= num_steps; i++)
            {
                x = (i - 0.5) * step;
                sum = sum + 4.0 / (1.0 + x * x);
            }
        }
        pi = step * sum;
        run_time = omp_get_wtime() - start_time;
        printf("pi with %ld steps is %lf in %lf seconds and %d threads\n", num_steps, pi, run_time,thread_num);
    }
}
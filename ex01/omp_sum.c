#include <omp.h>
#include "header.h"

float omp_sum(int global_start, int global_stop){
    float sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = global_start; i <= global_stop; i++){
        sum += 1.0f/(i*(i+1.0f));
    }
    return sum;
}
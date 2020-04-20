#include <stdio.h>
#include <omp.h>

int main(){
    int number_of_threads = 4;
    long ns = 10000;
    int t = 0;
    double s = 1.0/(double)ns;
    omp_set_num_threads(4);
    double sum[4];

    #pragma omp parallel
    {
        long cal = 0;
        double val;
        int thread_id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        if (thread_id == 0) {
            t = omp_get_num_threads();
        }
        sum[thread_id] = 0.0;
        for (cal = thread_id; cal < ns; cal += nt){
            val = (double)(cal)*s;
            sum[thread_id] += 4.0/(1.0+val*val);
        }
    }

    double result = 0.0;
    for (int i = 0; i < t; i++)
        result+=sum[i]*s;

    printf("The value is: ");
    printf("%lf\n",result);
}
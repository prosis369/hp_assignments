#include <stdio.h>
#include <omp.h>

int main(){
    int number_of_threads = 4;
    long ns = 10000;
    double result = 0.0;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long i =0; i < ns; i++){
            double x = (double)(i)*(1.0/ns);
            sum += 4.0/(1.0+x*x);
    }
    result = sum*(1.0/ns);

    printf("The value is: ");
    printf("%lf\n",result);
}
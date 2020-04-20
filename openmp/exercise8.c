#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

#define N  10000
int randy = 2000;


void fill(int length, double *a)
{
   int i; 
   for (i=0;i<length;i++) {
     randy = (1344 * randy + 150888) % 71400;
     *(a+i) = ((double) randy)/((double) 71400);
   }   
}


double sum_(int length, double *a)
{
   int i;  double sum = 0.0;
   for (i=0;i<length;i++)  sum += *(a+i);  
   return sum; 
}
  
int main()
{
  double *A, sum, runtime;
  int num, flag = 0;

  omp_set_num_threads(2);

  A = (double *)malloc(N*sizeof(double));

  #pragma omp parallel
  {
     #pragma omp master
     {
        num = omp_get_num_threads();
        if(num != 2)
        {
           printf("error: incorect number of threads, %d \n",num);
           exit(-1);
        }
        runtime = omp_get_wtime();
     }
     #pragma omp barrier

     #pragma omp sections
     {
        #pragma omp section
        {
           fill(N, A);
           #pragma omp flush
           flag = 1;
           #pragma omp flush (flag)
        }
        #pragma omp section
        {
           #pragma omp flush (flag)
           while (flag != 1){
              #pragma omp flush (flag)
           }

           #pragma omp flush 
           sum = sum_(N, A);
        }
      }
      #pragma omp master
         runtime = omp_get_wtime() - runtime;
   }  

   printf("sum is %lf \n",sum);
}
 

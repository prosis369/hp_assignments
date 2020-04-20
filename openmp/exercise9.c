#include <stdio.h>
#include <omp.h>
#include "random.h"


static long num = 100000;

int main ()
{
   long i;  
   long Ncirc = 0;
   double pi, x, y, test, time;
   double r = 1.0; 

   time = omp_get_wtime();
   #pragma omp parallel
   {

      #pragma omp single
          printf(" %d threads ",omp_get_num_threads());

      seed(-r, r);  
      #pragma omp for reduction(+:Ncirc) private(x,y,test)
      for(i=0;i<num; i++)
      {
         x_x = drandom(); 
         y_y = drandom();

         test = x_x*x_x + y_y*y_y;

         if (test <= r*r){
            Ncirc++;
         }
       }
    }

    pi = 4.0 * ((double)Ncirc/(double)num);

    printf("\n PI is %lf ",pi);
    printf("Time \n",omp_get_wtime()-time);

    return 0;
}

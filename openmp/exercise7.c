#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fib;
   struct node* next;
};

struct node* init_list(struct node* p);
void update(struct node* p); 
int fibonacci(int n); 

int fibonacci(int n) 
{
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fibonacci(n - 1);
      y = fibonacci(n - 2);
	  return (x + y);
   }
}

void update(struct node* p) 
{
   int n, temp;
   n = p->data;
   temp = fibonacci(n);

   p->fib = temp;

}

struct node* init_list(struct node* p) 
{
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fib = 0;
    for (i=0; i< N; i++) {
       temp  = malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fib = i+1;
    }
    p->next = NULL;
    return head;
}

int main() 
{
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;

     printf("Process linked list\n");
     printf("Fibonacci numbers beginning with %d\n",FS);      

     p = init_list(p);
     head = p;

     start = omp_get_wtime();

	#pragma omp parallel 
	{
            #pragma omp master
                  printf("%d threads:\n", omp_get_num_threads());

		#pragma omp single
		{
			p=head;
			while (p) {
				#pragma omp task firstprivate(p)
				{
					update(p);
				}
			  p = p->next;
		   }
		}
	}

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fib);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Time: %f seconds\n", end - start);

     return 0;
}


#include<stdio.h>
#include <stdlib.h>
#include <amp.h>
using namespace concurrency;
void MultiplyWithAMP() {
int aMatrix[] = { 1, 4, 2, 5, 3, 6 };
int bMatrix[] = { 7, 8, 9, 10, 11, 12 };
int productMatrix[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

array_view<int, 2> a(3, 2, aMatrix);

array_view<int, 2> b(2, 3, bMatrix);

array_view<int, 2> product(3, 3, productMatrix);

parallel_for_each(product.extent,
   [=] (index<2> idx) restrict(amp) {
       int row = idx[0];
       int col = idx[1];
       for (int inner = 0; inner <2; inner++) {
           product[idx] += a(row, inner)* b(inner, col);
       }
   });

product.synchronize();

for (int row = 0; row <3; row++) {
   for (int col = 0; col <3; col++) {
       //std::cout << productMatrix[row*3 + col] << "  ";
       std::cout << product(row, col) << "  ";
   }
   std::cout << "\n";
  }
}
int main() {
    MultiplyWithOutAMP();
    MultiplyWithAMP();
    getchar();
}
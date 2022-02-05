
#include <mkl.h>
#include <stdio.h>
#include <sys/time.h> 
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
  int m=3 , n=3 , k=2;       // parameters for cblas_dgemm function
  double *A , *B , *C;                                  //matrices
  
  A = (double *) malloc( sizeof(double) * m * k );
  B = (double *) malloc( sizeof(double) * k * n );
  C = (double *) malloc( sizeof(double) * m * n );

  cblas_dgemm ( CblasRowMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , k , B , n , 0.0 , C , n );
  return 0;
}

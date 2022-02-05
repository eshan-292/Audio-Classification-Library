#include <stdio.h>
#include <time.h>
//#include </opt/homebrew/opt/openblas/include/cblas.h>
#include <cblas.h>
 

 
 
using namespace std;

int main(){
    double start , finish ;
    int NUM = 100;      // no of iterations to be performed
    double a1[3*2] = {  1, 3, 5,  /* CblasColMajor */
                        2, 4, 6
                };
    double b[2*3] = {  7,1,        /* CblasColMajor */
                       8,2, 
                       9,3
                };

    double c[3*3] = {0,0,0,0,0,0,0,0,0};

    start = clock();

    for( int k=0 ; k<NUM ;k++)
    {
        for(int i=0 ; i<3 ; i++)
        {
            for(int j=0;j<3;j++){
                for (int p = 0; p < 2 ; ++p) 
                    c[i*3 +j] = c[i*3 +j] + a1[i*2+p]*b[p*3+j];         
            }
        }
    }

    finish = clock();
    printf("Simple Matrix Multiplication : %f seconds\n",(finish-start)/1000);

    start = clock();

    for( int k=0 ; k<NUM ;k++)
    {
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 3,    3,    2, 1.0,   a1,   2, b, 3,  0.0, c,  3);
    }
    finish = clock();
    printf("OpenBLAS : %f seconds\n",(finish-start)/1000);
    return 0;
}
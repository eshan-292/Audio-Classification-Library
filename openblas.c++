#include <stdio.h>
#include <time.h>
//#include </opt/homebrew/opt/openblas/include/cblas.h>
#include </home/eshan/OpenBLAS/cblas.h>
 
using namespace std;

int main(){
    double s , f ;
    double a[3*2] = {  1,2,
                        3,4,
                        5,6,
                };
    double b[2*3] = {  1,2,3,
                       7,8,9,        /* CblasColMajor */
                       
                };

    double c[3*3] = {0,0,0,0,0,0,0,0,0};

    s = clock();
    for(int i=0 ; i<3 ; i++)
        {
            for(int j=0;j<3;j++){
                for (int p = 0; p < 2 ; ++p) 
                    c[i*3 +j] = c[i*3 +j] + a[i*2+p]*b[p*3+j];         
            }
        }

    f = clock();
    printf("Naive Matrix Multiplication take %f seconds\n",(f-s)/1000);
    double temp=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp = c[i*3 + j] ;
            printf("%f ", temp) ;
            //cout << c[i*3 + j] << " ";
        }
        //cout << endl ;
        printf("\n") ;
    }

    s = clock();

    for( int k=0 ; k<1 ;k++)
    {
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 3,    3,    2, 1.0,   &a[0],   2, &b[0], 3,  0.0, c,  3);
    }
    f = clock();


    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp = c[i*3 + j] ;
            printf("%f ", temp) ;
            //cout << c[i*3 + j] << " ";
        }
        //cout << endl ;
        printf("\n") ;
    }

    printf("OpenBLAS : %f seconds\n",(f-s)/1000);
    return 0;
}

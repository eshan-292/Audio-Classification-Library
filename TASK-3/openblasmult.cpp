#include <stdio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <chrono>
//#include </opt/homebrew/opt/openblas/include/cblas.h>
// #include </home/eshan/OpenBLAS/cblas.h>
// #include "openblasmult.h"
#include <cblas.h>




using namespace std;

namespace OPENBLAS{
  float* openblasmult(float*A, float*B, float*D, int m, int k, int n){

      cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );

      for(int i=0;i<m*n;i++){
        C[i]+=D[i];             // add to the product bias
      }
      return C;
    }
}

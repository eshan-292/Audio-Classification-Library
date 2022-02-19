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
#include </home/eshan/OpenBLAS/cblas.h>
 
using namespace std;

int main(){
    
  auto time_start=chrono::high_resolution_clock::now();
  auto time_end=chrono::high_resolution_clock::now();
  double openblas_time;
  ofstream ofs;
  ofs.open("openBlasMultBox.dat");				// storing the time of computations on corresponding .dat files
  ifstream ifsInputMatrices,ifsBiasMatrices, ifsWeightMatrices;	// getting various matrices for testing from respective files
  ifsInputMatrices.open("inputMatrices.txt");
  ifsWeightMatrices.open("weightMatrices.txt");
  ifsBiasMatrices.open("biasMatrices.txt");
  int n,m,k;
  float *A , *B , *C, *D;
  string s;
  
  for(int i=100;i<=400;i++){					// 301 matrices of size 100*100 - 400*400 are used
    ifsInputMatrices>>s;
    k = stoi(s);
    ifsInputMatrices>>s;
    m = stoi(s);
    A = (float *) malloc( sizeof(float) * m * k ); // inputmatrix

    for(int i=0;i<m*k;i++){
      ifsInputMatrices>>s;
      A[i] = stof(s);
    }

    ifsWeightMatrices>>s;
    n = stoi(s);
    ifsWeightMatrices>>s;
    k = stoi(s);

    B = (float *) malloc( sizeof(float) * k * n ); // weightmatrix

    for(int i=0;i<k*n;i++){
      ifsWeightMatrices>>s;
      B[i] = stof(s);
    }

    ifsBiasMatrices>>s;
    n = stoi(s);
    ifsBiasMatrices>>s;
    m = stoi(s);

    C = (float *) malloc( sizeof(float) * m * n ); // for storing the result matrix

    D = (float *) malloc( sizeof(float) * m * n ); // for storing the bias matrix
    for(int i=0;i<m*n;i++){
      ifsBiasMatrices>>s;
      D[i] = stof(s);
    }
    time_start = chrono::high_resolution_clock::now();

    cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );         // parameters for cblas_dgemm function
 
   

    for(int i=0;i<m*n;i++){
      C[i]+=D[i];             // add to the product bias
    }
    
    time_end = chrono::high_resolution_clock::now();
    openblas_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
    openblas_time*= 1e-9;
    ofs<<openblas_time<<"\n";  // total time will be the time for product and addition of bias

  }
    
 

    return 0;
}

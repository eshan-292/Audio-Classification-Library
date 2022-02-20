#include </usr/include/mkl/mkl_cblas.h>
#include <stdio.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <vector>
#include "mklmult.h"

using namespace std;


void mklmult(string f1, string f2, string f3, string f4){

  ofstream ofs;
  ofs.open(f4);
  ifstream ifsInputMatrices,ifsBiasMatrices, ifsWeightMatrices;
  //ifsInputMatrices.open("inputMatrices.txt");
  //ifsWeightMatrices.open("weightMatrices.txt");
  //ifsBiasMatrices.open("biasMatrices.txt");
  ifsInputMatrices.open(f1);
  ifsWeightMatrices.open(f2);
  ifsBiasMatrices.open(f3);

  int n,m,k;
  float *A , *B , *C, *D;
  string s;
  for(int i=100;i<=400;i++){
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

    cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );   // calling cblas_sgemm function with appropriate arguments
    
    for(int i=0;i<m*n;i++){
      C[i]+=D[i];             // add to the product bias
    }

    for(int i=0;i<m*n;i++){
        ofs << C[i] << endl ;
    }
  }
}

#include <iostream>
#include <cmath>

using namespace std;


void relu(float *A, int rowSize, int colSize){
  for(int i=0;i<rowSize*colSize;i++){
    A[i] = max(A[i], (float)0.0);
  }
}

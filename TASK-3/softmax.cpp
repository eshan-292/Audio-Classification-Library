#include <iostream>
#include <cmath>

using namespace std;

void softmax(float *A, int size){
  float denominator = 0;
  for(int i=0;i<size;i++){
    denominator += A[i];
  }
  for(int i=0;i<size;i++){
    A[i] = A[i]/denominator;
  }
}

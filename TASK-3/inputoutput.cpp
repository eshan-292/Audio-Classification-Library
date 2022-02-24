#include <iostream>
#include <fstream>
#include "inputoutput.h"
using namespace std;

float* getMatrix(string filename){
  ifstream ifs;
  ifs.open(filename);
  string s;
  ifs>>s;
  int colSize = stoi(s);
  ifs>>s;
  int rowSize = stoi(s);
  float* result = (float *) malloc( sizeof(float) * colSize* rowSize );
  for(int i=0;i<rowSize*colSize;i++){
    ifs>>s;
    result[i] = stof(s);
  }

  return result;
}

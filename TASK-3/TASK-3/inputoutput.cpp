#include <iostream>
#include <fstream>
#include "inputoutput.h"
using namespace std;

float* getMatrixOfFixedSize(string filename){
  ifstream ifs;
  ifs.open(filename);
  if(!ifs){                                              // if the file does not exists error is thrown
      throw "Please check name of your file; unable to find "+filename+"\n";
  }
  int rowSize = 1;
  int colSize = 250;
  float* result = (float *) malloc( sizeof(float) * colSize* rowSize );
  string s;
  for(int i=0;i<rowSize*colSize;i++){
    ifs>>s;
    result[i] = stof(s);
  }

  return result;
}

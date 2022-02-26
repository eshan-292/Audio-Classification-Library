#include <iostream>
#include <fstream>
#include "classifier.h"
#include "DNN.h"
using namespace std;

int main(int argc, char const *argv[]) {
  try{
    float * probabilities = DNN(argv[1]);
    classify(probabilities, 12, argv[2], argv[1]);
  }
  catch(string s){
    cout<<s;
  }

  return 0;
}

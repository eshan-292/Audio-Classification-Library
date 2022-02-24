#include <iostream>
#include "openblasmult.h"
#include "relu.h"
#include "softmax.h"
#include "inputoutput.h"
using namespace std;

void DNN (string inputVectorFile, string fc1Weights, string fc1Bias, string fc2Weights, string fc2Bias, string fc3Weights, string fc3Bias, string fc4Weights, string fc4Bias ){
  float * inputMatrix = getMatrix(inputVectorFile);
  float * fc1WeightMatrix = getMatrix(fc1Weights);
  float * fc1BiasMatrix = getMatrix(fc1Bias);
  float * result_1 = OPENBLAS::openblasmult(inputMatrix, fc1WeightMatrix, fc1BiasMatrix, 1, 250, 144);
  relu(result_1, 1, 144);
  float * fc2WeightMatrix = getMatrix(fc2Weights);
  float * fc2BiasMatrix = getMatrix(fc2Bias);
  float * result_2 = OPENBLAS::openblasmult(result_1, fc2WeightMatrix, fc2BiasMatrix, 1, 144, 144);
  relu(result_2, 1, 144);
  float * fc3WeightMatrix = getMatrix(fc3Weights);
  float * fc3BiasMatrix = getMatrix(fc3Bias);
  float * result_3 = OPENBLAS::openblasmult(result_2, fc3WeightMatrix, fc3BiasMatrix, 1, 144, 144);
  relu(result_3, 1, 144);
  float * fc4WeightMatrix = getMatrix(fc4Weights);
  float * fc4BiasMatrix = getMatrix(fc4Bias);
  float * result_4 = OPENBLAS::openblasmult(result_3, fc4WeightMatrix, fc4BiasMatrix, 1, 144, 12);

  softmax(result_4, 12);




}

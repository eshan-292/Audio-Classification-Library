#include <iostream>
#include "openblasmult.h"
#include "relu.h"
#include "softmax.h"
#include "inputoutput.h"
#include "dnn_weights.h"
using namespace std;

float* DNN (string inputVectorFile ){
  float * inputMatrix = getMatrixOfFixedSize(inputVectorFile);
  float * fc1WeightMatrix = new float [250*144] IP1_WT;
  float * fc1BiasMatrix = new float [1*144] IP1_BIAS;
  float * result_1 = OPENBLAS::openblasmult(inputMatrix, fc1WeightMatrix, fc1BiasMatrix, 1, 250, 144);
  relu(result_1, 1, 144);
  float * fc2WeightMatrix = new float [144*144] IP2_WT;
  float * fc2BiasMatrix = new float [1*144] IP2_BIAS;
  float * result_2 = OPENBLAS::openblasmult(result_1, fc2WeightMatrix, fc2BiasMatrix, 1, 144, 144);
  relu(result_2, 1, 144);
  float * fc3WeightMatrix = new float [144*144] IP3_WT;
  float * fc3BiasMatrix = new float [1*144] IP3_BIAS;
  float * result_3 = OPENBLAS::openblasmult(result_2, fc3WeightMatrix, fc3BiasMatrix, 1, 144, 144);
  relu(result_3, 1, 144);
  float * fc4WeightMatrix = new float [144*144] IP4_WT;
  float * fc4BiasMatrix = new float [1*144] IP4_BIAS;
  float * result_4 = OPENBLAS::openblasmult(result_3, fc4WeightMatrix, fc4BiasMatrix, 1, 144, 12);

  softmax(result_4, 12);

  return result_4;


}

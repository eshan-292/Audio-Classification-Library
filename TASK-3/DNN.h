#include <iostream>
#include "openblasmult.h"
#include "relu.h"
#include "softmax.h"
#include "inputoutput.h"
#include "dnn_weights.h"
using namespace std;

#ifndef DNN_H
#define DNN_H

float* DNN (string inputVectorFile );

#endif

#include <iostream>
#include <string>
#include "libaudio.h"
#include "DNN.h"
#include "classifier.h"
using namespace std;
pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){
    string keywords[12] =  {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    float* probabilities = DNN(audiofeatures);
    pred_t* ans = classify(probabilities, 12, pred);
    return ans ;
}
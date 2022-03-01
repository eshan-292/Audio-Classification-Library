#include <string>
#include <iostream>
using namespace std;
#ifndef libaudio
#define libaudio

typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

#endif 

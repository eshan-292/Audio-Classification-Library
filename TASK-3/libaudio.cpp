#include <iostream>
#include <string>
#include "libaudio.h"

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){
    string keywords[12] =  {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    pred_t ans[3] ;
    //call main function here, and it should return the required array (I have modified classify.cpp accordingly) and store it in ans
    return ans ;
}
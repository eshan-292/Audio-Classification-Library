#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include "helper.h"
using namespace std;

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H


void outputMatrix(string fileName, vector<vector<float>> &result);
vector<vector<float>> getMatrix(string fileName);


#endif

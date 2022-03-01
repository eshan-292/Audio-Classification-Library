// #include </home/eshan/OpenBLAS/cblas.h>
#include <stdio.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cblas.h>

using namespace std;

#ifndef OPENBLASMULT_H
#define OPENBLASMULT_H

namespace OPENBLAS{
	float* openblasmult(float*A, float*B, float*D, int m, int k, int n);

}
#endif

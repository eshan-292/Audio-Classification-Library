#include <iostream>
#include <bits/stdc++.h>
#include "openblasmult.h"
using namespace std;


int main(int argc, char const *argv[])
{
	float* A = new float[2] {1,2};
	float* B = new float[2] {3,1};
	float* D = new float[1] {0};
	float*C = OPENBLAS::openblasmult(A,B,C,1,2,1);
	cout<<C[0]<<"\n";
	return 0;
}
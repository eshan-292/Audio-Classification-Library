#include <pthread.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <fstream>
#include "inputoutput.h"
using namespace std;


vector<vector<float>> generateRandomMatrix(int rowSize, int colSize, float upperLimit){	// generates a matrix with the given rowSize and colSize generates a random matrix of size rowSize*colSize and each element having value less than upperlimit
	vector<vector<float>> result(rowSize,vector<float> (colSize,0));
	srand(5);									// setting the random seed
	for(int row=0;row<rowSize;row++){
		for(int col=0;col<colSize;col++){
			result[row][col] = (float)rand()/(float)(RAND_MAX/upperLimit);	// generating a random matrix of size i*i with elements lying from 0 to upperLimit
		}
	}
	return result;									// returning the random matrix generated
}

int main()
{
	vector<vector<float>> inputMatrix,weightMatrix,biasMatrix;
	ofstream ofsInputMatrices;
	ofstream ofsWeightMatrices;
	ofstream ofsBiasMatrices;
	ofsInputMatrices.open("inputMatrices.txt");
	ofsWeightMatrices.open("weightMatrices.txt");
	ofsBiasMatrices.open("biasMatrices.txt");
	for(int i=100;i<=400;i++){							//- generating random matrices, storing these in column major format and also computing the time taken by pthread based implementation(storing these times in pthreadMultBox.dat)
		inputMatrix = generateRandomMatrix(i,i,10);				// generating random inputMatrix of size i*i and printing it in column major form in inputMatrices.txt
		outputMatrix("inputMatrices.txt",inputMatrix);
		weightMatrix = generateRandomMatrix(i,i,10);				// generating random weightMatrix of size i*i and printing it in column major form in weightMatrices.txt
		outputMatrix("weightMatrices.txt",weightMatrix);
		biasMatrix = generateRandomMatrix(i,i,10);				// generating random biasMatrix of size i*i and printing it in column major form in biasMatrices.txt
		outputMatrix("biasMatrices.txt",biasMatrix);
	}
	return 0;
}

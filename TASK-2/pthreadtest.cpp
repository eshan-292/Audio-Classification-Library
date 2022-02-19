#include <pthread.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <fstream>
#include "fullyconnectedpthread.h"
#include "inputoutput.h"


using namespace std;


int main() {
  auto time_start=chrono::high_resolution_clock::now();		// using chrono to compute time of evaluation of function on different matrices
  auto time_end=chrono::high_resolution_clock::now();
  double pthread_time;
  ofstream ofs;
  ofs.open("pthreadMultBox.dat");				// the time of evaluations will be stored in file pthreadMultBox.dat
  vector<vector<float>> inputMatrix;
  vector<vector<float>> weightMatrix;
  vector<vector<float>> biasMatrix;

  ifstream inputfstream;
  inputfstream.open("inputMatrices.txt") ;			// inputMatrix, weightMatrix, biasMatrix are generated from their respective files
  ifstream weightfstream;
  weightfstream.open("weightMatrices.txt") ;
  ifstream biasfstream;
  biasfstream.open("biasMatrices.txt") ;
  
    int r,c;
  	string s;
	//testing on 301 matrices of size 100*100 to 400*400
  	for(int i=100;i<=400;i++){				// each matrix will be stored in column major form
  		inputfstream>>s;
  		c = stoi(s);					// c is the number of columns in the matrix
  		inputfstream>>s;				// r is the number of rows in the matrix
  		r = stoi(s);
  		vector<vector<float>> inputMatrix(r,vector<float> (c,0));	//creating inputMatrix of size i*i
  		for(int col = 0;col<c;col++){
  			for(int row = 0;row<r;row++){
  				inputfstream>>s;
  				inputMatrix[row][col] = stof(s);
  			}
  		}

  		weightfstream>>s;
  		c = stoi(s);
  		weightfstream>>s;
  		r = stoi(s);
  		vector<vector<float>> weightMatrix(r,vector<float> (c,0));	// creating weightMatrix of size i*i
  		for(int col = 0;col<c;col++){
  			for(int row = 0;row<r;row++){
  				weightfstream>>s;
  				weightMatrix[row][col] = stof(s);
  			}
  		}


  		biasfstream>>s;
  		c = stoi(s);
  		biasfstream>>s;
  		r = stoi(s);
  		vector<vector<float>> biasMatrix(r,vector<float> (c,0));	// creating biasMatrix of size i*i
  		for(int col = 0;col<c;col++){
  			for(int row = 0;row<r;row++){
  				biasfstream>>s;
  				biasMatrix[row][col] = stof(s);
  			}
  		}

  		time_start = chrono::high_resolution_clock::now();

  		fullyConnectedPthread(inputMatrix, weightMatrix, biasMatrix);	// computing the time taken to do multiplication via pthread and addBias matrix
  		time_end = chrono::high_resolution_clock::now();
  		pthread_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
        	pthread_time*= 1e-9;
  		ofs<<pthread_time<<"\n";					// printing the time required for i*i matrix in the given file
  }

return 0;
}

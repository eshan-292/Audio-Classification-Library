
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "basicmultiplication.h"
#include "inputoutput.h"
using namespace std;





int main() {
  auto time_start=chrono::high_resolution_clock::now();
  auto time_end=chrono::high_resolution_clock::now();
  double basicmult_time;
  ofstream ofs;
  ofs.open("basicMultBox.dat");					// print the time of execution on respective .dat file
  vector<vector<float>> inputMatrix;
  vector<vector<float>> weightMatrix;
  vector<vector<float>> biasMatrix;

  ifstream inputfstream;
  inputfstream.open("inputMatrices.txt") ;			// for getting inputMatrix, weightMatrix, biasMatrix
  ifstream weightfstream;
  weightfstream.open("weightMatrices.txt") ;
  ifstream biasfstream;
  biasfstream.open("biasMatrices.txt") ;

    int r,c;
  	string s;
  	for(int i=100;i<=400;i++){				// get 301 matrices (input, weight, bias) each having size between 100*100 and 400*400
  		inputfstream>>s;
  		c = stoi(s);					// c is the number of columns in the given matrix(i)
  		inputfstream>>s;
  		r = stoi(s);					// r is the number of rows in the given matrix(i)
  		vector<vector<float>> inputMatrix(r,vector<float> (c,0));	// taking input inputMatrix
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
  		vector<vector<float>> weightMatrix(r,vector<float> (c,0));
  		for(int col = 0;col<c;col++){					// taking input weightMatrix
  			for(int row = 0;row<r;row++){
  				weightfstream>>s;
  				weightMatrix[row][col] = stof(s);
  			}
  		}


  		biasfstream>>s;
  		c = stoi(s);
  		biasfstream>>s;
  		r = stoi(s);
  		vector<vector<float>> biasMatrix(r,vector<float> (c,0));
  		for(int col = 0;col<c;col++){					// taking input biasMatrix
  			for(int row = 0;row<r;row++){
  				biasfstream>>s;
  				biasMatrix[row][col] = stof(s);
  			}
  		}

  		time_start = chrono::high_resolution_clock::now();

  		basicMult(inputMatrix, weightMatrix, biasMatrix);		// calculating the result on these 3 matrices by basicMult
  		time_end = chrono::high_resolution_clock::now();
  		basicmult_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
       	basicmult_time*= 1e-9;
  		ofs<<basicmult_time<<"\n";					// printing the time on i*i matrix in dat file
  }

return 0;
}

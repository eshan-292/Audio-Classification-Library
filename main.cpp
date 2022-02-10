#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include "helper.h"
#include "fullyconnected.h"
using namespace std;




vector<vector<float>> getMatrix(string fileName){         //getMatrix function takes name of file as argument from where matrix is to be constructed,  constructs a matrix(vector of vectors) made according to the specification given and returns it.
    ifstream fs;
    fs.open(fileName);
    if(!fs){                                              // if the file does not exists error is thrown
        throw "Please check name of your file; unable to find "+fileName+"\n";
    }
    string s;
    fs>>s;
    if(!canBeConvertedToInt(s)){
        throw "Incorrect column dimension is given in "+fileName+"\n";
    }
    int matrixColSize = stoi(s);                          // matrixColSize = number of columns in matrix
    if(matrixColSize<=0){                                 // errors are thrown if any dimension of matrix is less than or equal to zero
        throw "Given number of columns in matrix is nonpositive in "+fileName+"\n";
    }
    fs>>s;
    if(!canBeConvertedToInt(s)){
        throw "Incorrect row dimension is given in "+fileName+"\n";
    }
    int matrixRowSize = stoi(s);                          // matrixRowSize = number of rows in matrix
    if(matrixRowSize<=0){
        throw "Given number of rows in matrix is nonpositive in "+fileName+"\n";
    }
    vector<vector<float>>matrix(matrixRowSize, vector<float>(matrixColSize, 0));   // a vector of vector of floats is constructed and initialized with zero
    for (int column = 0; column < matrixColSize; ++column)// for every column of matrix    
    {
        for (int row = 0; row < matrixRowSize; ++row)     // for every row of a given column
        {
            fs>>s;                
            if(!canBeConvertedToFloat(s)){
                cout<<canBeConvertedToFloat(s)<<"\n";
                throw "Incorrect value of element of the matrix is given in "+fileName+"\n";
            }                          
            matrix[row][column] = stof(s);                // get the corresponding entry of matrix
        }
    }
    return matrix;
}


void outputMatrix(string fileName, vector<vector<float>> &result){ // outMatrix function outputs the given result matrix to a file name fileName as per the specification given 
    ofstream ofs;                                         // create outputstream 
    ofs.open(fileName);                                   // create the file where you want to output
    ofs<<result[0].size()<<"\n";                          // result[0].size() = no of columns in output matrix
    ofs<<result.size()<<"\n";                             // result.size() = no of rows in output matrix

    for(int column = 0;column<result[0].size();column++){ // for every column of outputmatrix
        for(int row = 0; row<result.size();row++ ){       // for every row of a given column
            ofs<<result[row][column]<<"\n";               // output the corresponding element of the matrix in the file
        }
    }
}

int main(int argc, char const *argv[])
{
	
	if(strcmp(argv[1],"fullyconnected")==0){
		try{
			vector<vector<float>>inputMatrix = getMatrix(argv[2]);
			vector<vector<float>>weightMatrix = getMatrix(argv[3]);
			vector<vector<float>>biasMatrix = getMatrix(argv[4]);
			vector<vector<float>> result = fullyConnected(inputMatrix,weightMatrix,biasMatrix, argv[6]);
		}
		catch(string s){
			cout<<s;
		}
	}
	else{
		incorrectFunction(argv[1]);
	}

	return 0;
}

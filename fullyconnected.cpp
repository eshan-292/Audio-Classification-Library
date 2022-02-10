#include <pthread.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <fstream>
#include "fullyconnected.h"
using namespace std;



struct arguments
{
	vector<float> matrix1Row;								// matrix1Row is a row of the first matrix whose product is to be taken with matrix2
	vector<vector<float>> matrix2;							// matrix2 is the second matrix which comes on the right hand side of the product
	vector<vector<float>>*result;							// result is another matrix to which we will be storing the matrix multiplication
	int row;
};



void* computeVectorProduct(void* args){  					// take a structure of arguments
	struct arguments *myargs = (struct arguments *)args;
		for(int j=0;j<(myargs->matrix2)[0].size();j++){		// we will compute one row of the resultant matrix by taking each row of first matrix and multiplying it with all columns of the second matrix via 1 thread
			for(int i=0;i<(myargs->matrix1Row).size();i++){
				(*(myargs->result))[myargs->row][j]+=((myargs->matrix1Row)[i])*((myargs->matrix2[i][j]));
			}
		}
	return NULL;
}


vector<vector<float>> innerProductPthread(vector<vector<float>> &inputMatrix, vector<vector<float>> &weightMatrix){
	
	int inputMatrixRowSize = inputMatrix.size();
	int inputMatrixColSize = inputMatrix[0].size();
	int weightMatrixRowSize = weightMatrix.size();
	int weightMatrixColSize = weightMatrix[0].size();


	vector<vector<float> > result(inputMatrixRowSize,vector<float>(weightMatrixColSize,0));
	pthread_t thread_id[inputMatrixRowSize]; 				// create an array of threads, one thread for each row of inputMatrix
	struct arguments args[inputMatrixRowSize];	//creating an array of structures for passing arguments to each thread
	for(int i=0;i<inputMatrixRowSize;i++){					// for ith every row of first matrix we will create a thread, which will execute the computeVectorProduct function, and compute the ith row of the result by multiplying ith row of inputMatrix with all columns of weightMatrix
			args[i].matrix1Row = inputMatrix[i];				// passing a particular row of inputMatrix
			args[i].matrix2 = weightMatrix;							// matrix2 argument would be the weightMatrix for all the threaded functions
			args[i].result = &result;									// result argument would be the matrix result (initialized to 0) for all the threaded functions

			args[i].row = i;									// passing the index of the row of inputMatrix 
			pthread_create(&thread_id[i],NULL,&computeVectorProduct,(void *)&(args[i])); // creating a thread to compute the ith row of result matrix	
	}
	for(int i=0;i<inputMatrixRowSize;i++){
		pthread_join(thread_id[i],NULL);					// waiting for all the threads to execute
	}
	return result;
}


    vector<vector<float>> addBias(vector<vector<float>>&a, vector<vector<float>> &biasMatrix){ // given two matrices of same dimensions, returns a new matrix which is the sum of the original two matrices
        vector<vector<float>> result(a.size(),vector<float>(a[0].size(),0));    // result matrix initialized to 0

        for(int row=0;row<a.size();row++){              // for every row of matrix a
            for(int col=0;col<a[0].size();col++){       // for every column of a given row of matrix a
                result[row][col]=a[row][col]+biasMatrix[row][col]; // sum the corresponding entries of matrices and store them in result
            }
        }
        return result;                                  // return the result matrix

    }


vector<vector<float>> fullyConnectedPthread(vector<vector<float>> &inputMatrix, vector<vector<float>>&weightMatrix, vector<vector<float>>&biasMatrix){
	vector<vector<float> > result(inputMatrix.size(),vector<float>(weightMatrix[0].size(),0));
	result = innerProductPthread(inputMatrix,weightMatrix);
	result = addBias(result,biasMatrix);


	return result;
}



vector<vector<float>> generateRandomMatrix(int rowSize, int colSize, float upperLimit){
	vector<vector<float>> result(rowSize,vector<float> (colSize,0));
	for(int row=0;row<rowSize;row++){
		for(int col=0;col<colSize;col++){
			result[row][col] = (float)rand()/(float)(RAND_MAX/upperLimit);
		}
	}
	return result;
}







void outputMatrix(ofstream &ofs, vector<vector<float>> &result){ 
    ofs<<result[0].size()<<"\n";                          // result[0].size() = no of columns in output matrix
    ofs<<result.size()<<"\n";                             // result.size() = no of rows in output matrix

    for(int column = 0;column<result[0].size();column++){ // for every column of outputmatrix
        for(int row = 0; row<result.size();row++ ){       // for every row of a given column
            ofs<<result[row][column]<<"\n";               // output the corresponding element of the matrix in the file
        }
    }
}


int main()
{
	vector<vector<float>> inputMatrix,weightMatrix,biasMatrix;
	ofstream ofs;
	ofstream ofsInputMatrices;
	ofstream ofsWeightMatrices;
	ofstream ofsBiasMatrices;
	ofs.open("pthreadMultBox.dat", ios::out);
	ofsInputMatrices.open("inputMatrices.txt");
	ofsWeightMatrices.open("weightMatrices.txt");
	ofsBiasMatrices.open("biasMatrices.txt");
	auto time_start=chrono::high_resolution_clock::now();
	auto time_end=chrono::high_resolution_clock::now();
	double pthread_time;
	for(int i=100;i<=400;i++){							//- generating random matrices, storing these in column major format and also computing the time taken by pthread based implementation(storing these times in pthreadMultBox.dat)
		inputMatrix = generateRandomMatrix(i,i,10);
		outputMatrix(ofsInputMatrices,inputMatrix);
		weightMatrix = generateRandomMatrix(i,i,10);
		outputMatrix(ofsWeightMatrices,weightMatrix);
		biasMatrix = generateRandomMatrix(i,i,10);
		outputMatrix(ofsBiasMatrices,biasMatrix);
		time_start = chrono::high_resolution_clock::now();

		fullyConnectedPthread(inputMatrix,weightMatrix,biasMatrix);
		time_end = chrono::high_resolution_clock::now();
		pthread_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
     	pthread_time*= 1e-9;
		ofs<<pthread_time<<"\n";
	}
	return 0;
}

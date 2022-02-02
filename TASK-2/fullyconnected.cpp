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
	vector<vector<float>>result;							// result is another matrix to which we will be storing the matrix multiplication
	int row;
};


void* computeVectorProduct(void* args){  					// take a structure of arguments
	struct arguments *myargs = (struct arguments *)args;
		for(int j=0;j<(myargs->matrix2)[0].size();j++){
			for(int i=0;i<(myargs->matrix1Row).size();i++){
				(myargs->result)[myargs->row][j]+=((myargs->matrix1Row)[i])*((myargs->matrix2[i][j]));
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
	struct arguments args;									// a structure to pass arguments 
	args.matrix2 = weightMatrix;							// matrix2 argument would be the weightMatrix for all the threaded functions
	args.result = result;									// result argument would be the matrix result (initialized to 0) for all the threaded functions
	for(int i=0;i<inputMatrixRowSize;i++){					// for ith every row of first matrix we will create a thread, which will execute the computeVectorProduct function, and compute the ith row of the result by multiplying ith row of inputMatrix with all columns of weightMatrix
			args.matrix1Row = inputMatrix[i];				// passing a particular row of inputMatrix
			args.row = i;									// passing the index of the row of inputMatrix 
			pthread_create(&thread_id[i],NULL,&computeVectorProduct,(void *)&args); // creating a thread to compute the ith row of result matrix	
	}
	for(int i=0;i<inputMatrixRowSize;i++){
		pthread_join(thread_id[i],NULL);					// waiting for all the threads to execute
	}
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




vector<vector<float>> addBias(vector<vector<float>>&matrix, vector<vector<float>> &biasMatrix){
	vector<vector<float>> result(matrix.size(),vector<float>(matrix[0].size(),0));
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			result[i][j] = matrix[i][j]+biasMatrix[i][j];
		}
	}
	return result;
}


vector<vector<float>> fullyConnected(vector<vector<float>> &inputMatrix, vector<vector<float>>&weightMatrix, vector<vector<float>>&biasMatrix,const char* method){
	vector<vector<float>> result;
	if(strcmp("pthread",method)==0){
		result = innerProductPthread(inputMatrix,weightMatrix);
	}
	// code to execute via mkl and openblas

	result = addBias(result,biasMatrix);


	return result;
}

int main(int argc, char const *argv[])
{
	vector<vector<float> > matrix1(1000,vector<float>(1000,-0.212123));			// test case 1 (1000x1000,1000x1000,1000x1000)
	vector<vector<float> > matrix2(1000,vector<float>(1000,1.34123));
	vector<vector<float> > matrix3(1000,vector<float>(1000,0.323));
	auto start = chrono::high_resolution_clock::now();

	// start = clock();

	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	// end = clock();
	auto end = chrono::high_resolution_clock::now();

	ofstream ofs;
	ofs.open("pthread.dat");
	double time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";


	matrix1= generateRandomMatrix(200,200,2);									// test case 2 (200x200, 200x300, 200x300)
	matrix2 = generateRandomMatrix(200,300,5);
	matrix3 = generateRandomMatrix(200,300,7);


	start = chrono::high_resolution_clock::now();
	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	end = chrono::high_resolution_clock::now();

	time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";

	matrix1= generateRandomMatrix(400,900,8);									// test case 3 (400x900, 900x700, 400x700)
	matrix2 = generateRandomMatrix(900,700,4);
	matrix3 = generateRandomMatrix(400,700,6);


	start = chrono::high_resolution_clock::now();
	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	end = chrono::high_resolution_clock::now();

	time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";


	matrix1= generateRandomMatrix(4000,1000,4.849);									// test case 4 (4000x1000, 1000x300, 4000x300)
	matrix2 = generateRandomMatrix(1000,300,41.238974);
	matrix3 = generateRandomMatrix(4000,300,42.1913);


	start = chrono::high_resolution_clock::now();
	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	end = chrono::high_resolution_clock::now();

	time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";



//SMALL TEST CASES

	matrix1= generateRandomMatrix(4,6,439.23);									// test case 5 (4x6, 6x7, 4x7)
	matrix2 = generateRandomMatrix(6,7,41.238974);
	matrix3 = generateRandomMatrix(4,7,42.1913);


	start = chrono::high_resolution_clock::now();
	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	end = chrono::high_resolution_clock::now();

	time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";


	matrix1= generateRandomMatrix(10,20,4.132);									// test case 6 (10x20, 20x15, 10x15)
	matrix2 = generateRandomMatrix(20,15,54.8774);
	matrix3 = generateRandomMatrix(10,15,445.1913);


	start = chrono::high_resolution_clock::now();
	fullyConnected(matrix1,matrix2,matrix3, argv[1]);

	end = chrono::high_resolution_clock::now();

	time_taken = 
      			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

     time_taken*= 1e-9;
	ofs<<time_taken<<"\n";

	return 0;
}
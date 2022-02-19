#include <pthread.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <fstream>

#include "fullyconnectedpthread.h"

using namespace std;




struct arguments
{
	vector<vector<float>> matrix1;				// matrix1 and matrix2 are the matrices whose product has to be found
	vector<vector<float>> matrix2;
	vector<vector<float>>*result;				// resultant product will be stored in the matrix result (which will be passed by reference)
	int startRow;								// startRow and endRow together gives the portion of the matrix1 which is to be multiplied with matrix2 by the given thread
	int endRow;
};
void* computeVectorProduct(void* args){  							// take a structure of arguments
	struct arguments *myargs = (struct arguments *)args;

	for (int i = myargs->startRow; i < myargs->endRow; ++i)		// for every row in a particular segment of matrix1
	{
		for(int j=0;j<(myargs->matrix2)[0].size();j++){			// for every column of matrix2
			for(int k=0;k<myargs->matrix1[0].size();k++){
				(*(myargs->result))[i][j]+=(myargs->matrix1[i][k])*(myargs->matrix2[k][j]); // we will find the partial product of the two matrices and store it in the apt columns of result
			}
		}
	}

	return NULL;
}


vector<vector<float>> innerProductPthread(vector<vector<float>> &inputMatrix, vector<vector<float>> &weightMatrix){


	vector<vector<float> > result(inputMatrix.size(),vector<float>(weightMatrix[0].size(),0));	//matrix to store result of multiplication
	pthread_t thread_id1, thread_id2, thread_id3, thread_id4;			// creating four threads to compute product parellely
	// struct arguments args[matrix1.size()];	//creating an array of structures for passing arguments to each thread

	int n1 = inputMatrix.size()/4;					// dividing the rows of input matrix into 4 almost equal parts 0 - n1, n1 - n2, n2 - n3

	int n2 = inputMatrix.size()/4 + n1;

	int n3 = inputMatrix.size()/4 + n2;

	int n4 = inputMatrix.size()/4 + n3 + inputMatrix.size()%4;
	struct arguments args1, args2, args3, args4;

	args1.startRow = 0;						// passing the required arguments to thread_id1 and creating the thread
	args1.endRow = n1;
	args1.matrix1 = inputMatrix;
	args1.matrix2 = weightMatrix;
	args1.result = &result;

	pthread_create(&thread_id1,NULL,&computeVectorProduct,(void *)&(args1));


	args2.startRow = n1;						// passing the required arguments to thread_id2 and creating the thread
	args2.endRow = n2;
	args2.matrix1 = inputMatrix;
	args2.matrix2 = weightMatrix;
	args2.result = &result;

	pthread_create(&thread_id2,NULL,&computeVectorProduct,(void *)&(args2));


	args3.startRow = n2;						// passing the required arguments to thread_id3 and creating the thread
	args3.endRow = n3;
	args3.matrix1 = inputMatrix;
	args3.matrix2 = weightMatrix;
	args3.result = &result;

	pthread_create(&thread_id3,NULL,&computeVectorProduct,(void *)&(args3));


	args4.startRow = n3;						// passing the required arguments to thread_id4 and creating the thread
	args4.endRow = n4;
	args4.matrix1 = inputMatrix;
	args4.matrix2 = weightMatrix;
	args4.result = &result;


	pthread_create(&thread_id4,NULL,&computeVectorProduct,(void *)&(args4));

	pthread_join(thread_id1, NULL);				// joining the threads
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
	pthread_join(thread_id4, NULL);

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
	result = innerProductPthread(inputMatrix,weightMatrix);		// taking the inner product
	result = addBias(result,biasMatrix);						// adding the bias


	return result;
}

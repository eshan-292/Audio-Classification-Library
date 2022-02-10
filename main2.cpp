#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include "fullyconnected.h"
#include "helper.h"
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

////////////////////////////////////////////////////////////////////////


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


////////////////////////////////////////////////////////////////////////////////





int main(int argc, char const *argv[])
{

    if(argc<7){                                       // 6 arguments are required               
        insufficientArguments();                      // call insufficient arguments if less than arguments are there
        return 0;                                     // gracefully terminate the program  
    }
    if(strcmp(argv[1],"fullyconnected")==0){              // if the function argument is "fullyconnected"

        if(strcmp(argv[6],"pthread")==0){
	        try{
	        	

	        		                                            // error might be thrown by getMatrix and fullyConnected functions which have to be taken care for
	            	vector<vector<float>>inputMatrix = getMatrix(argv[2]); //getmatrix from inputmatrix.txt
	            	vector<vector<float>>weightMatrix = getMatrix(argv[3]);//getmatrix from weightmatrix.txt
	            	vector<vector<float>>biasMatrix = getMatrix(argv[4]);  //getmatrix from biasmatrix.txt
	            	vector<vector<float>> result = fullyConnectedPthread(inputMatrix, weightMatrix, biasMatrix); // compute the result of taking inner product and adding bias
	            	outputMatrix(argv[5],result); 
	        	
	                // output the resultant matrix to outputmatrix.txt 
	        }
	        catch(string s){                                  // inputMatrix can throw errors if fileName isnot found or the number of rows and columns in matrix are incorrect(less than or equal to zero), fullyConnected can throw errors if dimension of the input,weight, bias matrix are not compatible for the required operations
	            cout<<s;
	        }
	    }
	    else if(strcmp(argv[6],"mkl")==0){

	    }
	    else if(strcmp(argv[6],"openblas")==0){

	    }
	    else{
	    	incorrectMatrixMultiplicationMethod();
	    }
    }
    else{
        incorrectFunction(argv[1]);                       // if the function argument is anything other than fullyconnected, activation, pooling, probability
        return 0;
    }


	return 0;
}
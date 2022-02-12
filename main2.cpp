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

	int n1 = inputMatrix.size()/4;				// dividing the rows of input matrix into 4 almost equal parts 0 - n1, n1 - n2, n2 - n3

	int n2 = inputMatrix.size()/4 + n1;

	int n3 = inputMatrix.size()/4 + n2;

	int n4 = inputMatrix.size()/4 + n3 + inputMatrix.size()%4;
	struct arguments args1, args2, args3, args4;

	args1.startRow = 0;							// passing the required arguments to thread_id1 and creating the thread
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


////////////////////////////////////////////////////////////////////////////////



void mklmult(string infile1, string infile2, string outfile){
  ofstream ofs;
  ofs.open(outfile);
  ifstream ifsInputMatrices,ifsWeightMatrices;
  ifsInputMatrices.open(infile1);
  ifsWeightMatrices.open(infile2);
//  ifsBiasMatrices.open("biasMatrices.txt");
  
  int n,m,k;
  double *A , *B , *C, *D; 
  string s;

    ifsInputMatrices>>s;
    m = stoi(s);    //assuming the input file stores no of rows in the first line
    ifsInputMatrices>>s;
    k = stoi(s);
    A = (double *) malloc( sizeof(double) * m * k ); // inputmatrix
    for(int i=0;i<m*k;i++){
      ifsInputMatrices>>s;
      A[i] = stof(s);
    }

    ifsWeightMatrices>>s;
    k = stoi(s);
    ifsWeightMatrices>>s;
    n = stoi(s);

    B = (double *) malloc( sizeof(double) * k * n ); // weightmatrix
    for(int i=0;i<k*n;i++){
      ifsWeightMatrices>>s;
      B[i] = stof(s);
    }

    C = (double *) malloc( sizeof(double) * m * n ); // for storing the result matrix


    //time_start = chrono::high_resolution_clock::now();

    cblas_dgemm ( CblasRowMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , k , B , n , 0.0 , C , n );         // parameters for cblas_dgemm function

   // time_end = chrono::high_resolution_clock::now();
    //mkl_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
    //mkl_time*= 1e-9;
    //ofs<<mkl_time<<"\n";  // total time will be the time for product and addition of bias

    //writing the dimensions of the result matrix into the output file
    ofs << m << endl ;  
    ofs << n << endl ;

    //writing the result matrix in column major form into the output file
    for(int i=0;i<m*n;i++){
      ofs << C[i] << endl;
    }

}
////////////////////////////////////////////////////////////////////////////////



void openblasmult(string infile1, string infile2, string outfile){
  ofstream ofs;
  ofs.open(outfile);
  ifstream ifsInputMatrices,ifsWeightMatrices;
  ifsInputMatrices.open(infile1);
  ifsWeightMatrices.open(infile2);
//  ifsBiasMatrices.open("biasMatrices.txt");
  
  int n,m,k;
  double *A , *B , *C, *D; 
  string s;

    ifsInputMatrices>>s;
    m = stoi(s);    //assuming the input file stores no of rows in the first line
    ifsInputMatrices>>s;
    k = stoi(s);
    A = (double *) malloc( sizeof(double) * m * k ); // inputmatrix
    for(int i=0;i<m*k;i++){
      ifsInputMatrices>>s;
      A[i] = stof(s);
    }

    ifsWeightMatrices>>s;
    k = stoi(s);
    ifsWeightMatrices>>s;
    n = stoi(s);

    B = (double *) malloc( sizeof(double) * k * n ); // weightmatrix
    for(int i=0;i<k*n;i++){
      ifsWeightMatrices>>s;
      B[i] = stof(s);
    }

    C = (double *) malloc( sizeof(double) * m * n ); // for storing the result matrix


    //time_start = chrono::high_resolution_clock::now();

    cblas_dgemm ( CblasRowMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , k , B , n , 0.0 , C , n );         // parameters for cblas_dgemm function

   // time_end = chrono::high_resolution_clock::now();
    //mkl_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
    //mkl_time*= 1e-9;
    //ofs<<mkl_time<<"\n";  // total time will be the time for product and addition of bias

    //writing the dimensions of the result matrix into the output file
    ofs << m << endl ;  
    ofs << n << endl ;

    //writing the result matrix in column major form into the output file
    for(int i=0;i<m*n;i++){
      ofs << C[i] << endl;
    }

}
/////////////////////////////////////////////////////////////







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
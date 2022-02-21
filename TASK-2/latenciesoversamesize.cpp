#include <iostream>
#include <cmath>
#include <vector>
#include <cblas.h>
#include <cstring>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include "fullyconnectedpthread.h"
#include "helper.h"
#include "inputoutput.h"
#include "basicmultiplication.h"



int main(int argc, char const *argv[])
{
	float *A,*C,*B;
	A = (float *) malloc( sizeof(float) * 402* 402);
	B = (float *) malloc( sizeof(float) * 402* 402);
	C =  (float *) malloc( sizeof(float) * 402* 402);
	vector<string> matrixnames = {"m1", "m2", "m3", "m4", "m5", "m6"};
	vector<int> sizes = {-200,150,500,850,1200,1550};			// these are the x coordinates of the point about which each boxplot is going to be centered(Helps in avoiding overlap between various boxplot)
	string s;
		//basicMult

	for(int j=0;j<matrixnames.size();j++){

		string filename = matrixnames[j]+".txt";				// get the corresponding matrix
		vector<vector<float>> matrix1 = getMatrix(filename);	

		auto time_start = chrono::high_resolution_clock::now();
		auto time_end = chrono::high_resolution_clock::now();
		double basicmult_time;
		ofstream ofsBasicMult;
		ofsBasicMult.open( matrixnames[j]+"basicMult.dat");

		for(int i=0;i<100;i++){									// getting the time of computation for 100 runs of basicMult on the given matrix
			time_start = chrono::high_resolution_clock::now();
			basicMult(matrix1,matrix1,matrix1);   				// input bias weight matrix are assumed to be same
			time_end = chrono::high_resolution_clock::now();
			basicmult_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			basicmult_time*= 1e-9;
			ofsBasicMult<<sizes[j]<<" "<<basicmult_time<<"\n";
		}

			// pthread time
		double pthread_time;
		ofstream ofspthread;
		ofspthread.open(matrixnames[j]+"pthread.dat");

		for(int i=0;i<100;i++){									// getting the time of computation for 100 runs of fullyConnectedPthread on the given matrix
			time_start = chrono::high_resolution_clock::now();
			fullyConnectedPthread(matrix1,matrix1,matrix1);   				// input bias weight matrix are assumed to be same
			time_end = chrono::high_resolution_clock::now();
			pthread_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			pthread_time*= 1e-9;
			ofspthread<<sizes[j]<<" "<<pthread_time<<"\n";
		}



		int k,m;
		ifstream matrixstream;
		matrixstream.open(filename);
		matrixstream>>s;
		k = stoi(s);
		matrixstream>>s;
		m = stoi(s);


		for(int i=0;i<m*k;i++){												// getting matrix1 in column major format 
			matrixstream>>s;
			A[i] = stof(s);
			B[i] = A[i];
		}


			// mkl time
		double mkl_time;
		ofstream ofsmkl;
		ofsmkl.open(matrixnames[j]+"mkl.dat");								// getting the time of computation for 100 runs of mkl implementation on the given matrix
		for(int i=0;i<100;i++){
			time_start = chrono::high_resolution_clock::now();
			// cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );  				// input bias weight matrix are assumed to be same
			for(int i=0;i<k*m;i++){
				C[i]+=A[i];													// adding bias
			}
			time_end = chrono::high_resolution_clock::now();
			mkl_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			mkl_time*= 1e-9;
			ofsmkl<<sizes[j]<<" "<<mkl_time<<"\n";
		}

			// openblas time
		double openblas_time;
		ofstream ofsopenblas;
		ofsopenblas.open(matrixnames[j]+"openblas.dat");
		for(int i=0;i<100;i++){
			time_start = chrono::high_resolution_clock::now();               // getting the time of computation for 100 runs of openblas implementation on the given matrix
			cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , m , k , 1.0 , A , m , B , m , 0.0 , C , m );   // calling cblas_sgemm function with appropriate arguments
			for(int i=0;i<k*m;i++){
				C[i]+=A[i];													 // adding bias
			}
			time_end = chrono::high_resolution_clock::now();
			openblas_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			openblas_time*= 1e-9;
			ofsopenblas<<sizes[j]<<" "<<openblas_time<<"\n";
		}
	}


	// m2.txt




	return 0;
}

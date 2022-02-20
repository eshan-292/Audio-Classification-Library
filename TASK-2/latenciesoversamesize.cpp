#include <iostream>
#include <cmath>
#include <vector>
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
	float *A;
	A = (float *) malloc( sizeof(float) * 402* 402);

	vector<string> matrixnames = {"m1", "m2", "m3", "m4", "m5", "m6"};
	vector<int> sizes = {-200,150,500,850,1200,1550};
	ifstream matrixstream;
	string s;
		//basicMult

	for(int j=0;j<matrixnames.size();j++){

		string filename = matrixnames[j]+".txt";
		vector<vector<float>> matrix1 = getMatrix(filename);

		auto time_start = chrono::high_resolution_clock::now();
		auto time_end = chrono::high_resolution_clock::now();
		double basicmult_time;
		ofstream ofsBasicMult;
		ofsBasicMult.open( matrixnames[j]+"basicMult.dat");

		for(int i=0;i<100;i++){
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

		for(int i=0;i<100;i++){
			time_start = chrono::high_resolution_clock::now();
			fullyConnectedPthread(matrix1,matrix1,matrix1);   				// input bias weight matrix are assumed to be same
			time_end = chrono::high_resolution_clock::now();
			pthread_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			pthread_time*= 1e-9;
			ofspthread<<sizes[j]<<" "<<pthread_time<<"\n";
		}



		int k,m;
		matrixstream.open(filename);
		matrixstream>>s;
		k = stoi(s);
		matrixstream>>s;
		m = stoi(s);


		for(int i=0;i<m*k;i++){												// getting matrix1 in column major format 
			matrixstream>>s;
			A[i] = stof(s);
		}


			// mkl time
		double mkl_time;
		ofstream ofsmkl;
		ofsmkl.open(matrixnames[j]+"mkl.dat");
		for(int i=0;i<100;i++){
			time_start = chrono::high_resolution_clock::now();
			// cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );  				// input bias weight matrix are assumed to be same
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
			time_start = chrono::high_resolution_clock::now();
			// cblas_sgemm (CblasColMajor, CblasNoTrans, CblasNoTrans , m , n , k , 1.0 , A , m , B , k , 0.0 , C , m );  				// input bias weight matrix are assumed to be same
			time_end = chrono::high_resolution_clock::now();
			openblas_time = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start).count();
			openblas_time*= 1e-9;
			ofsopenblas<<sizes[j]<<" "<<openblas_time<<"\n";
		}
	}


	// m2.txt




	return 0;
}
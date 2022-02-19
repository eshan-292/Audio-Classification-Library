#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

float mean(vector<float> &v){					// function which takes a vector(population) and computes the mean of the population
	float sum = 0;						// for storing the sum of all values of the vector
	for(int i=0;i<v.size();i++){
		sum+=v[i];
	}
	float average = sum/v.size();				// average = sum of all values / number of values
	return average;						// return the average of all values
}


float standardDeviation(vector<float> &v){			// function which takes a vector(population) and cmoputes the standard deviation of the population
	float sumOfSquares = 0;					// for storing the sum of squares of deviations from mean
	float average = mean(v);
	for(int i=0;i<v.size();i++){
		sumOfSquares+=(v[i]-average)*(v[i]-average);
	}
	float variance = sumOfSquares/v.size();			// variance of vector v

	float deviation = sqrt(variance);			// std of vector v

	return deviation;					// returing the deviation

}


using namespace std;



int main(int argc, char const *argv[])
{
	//mean and std of latencies for pthread 
	ifstream ifsBasic;
	string s;
	vector<float> basicTimes;
	ifsBasic.open("basicMultBox.dat"); 			// getting the vector of latencies for basicMultiplication
	for(int i=100;i<=400;i++){
		ifsBasic>>s;
		basicTimes.push_back(stof(s));
	}							// computing and printing mean,std in the console
	cout<<"Mean of basic implementation is "<<mean(basicTimes)<<"\nStd of basic implementations is "<<standardDeviation(basicTimes)<<"\n";


	ifstream ifsPthread;
	vector<float> pthreadTimes;
	ifsPthread.open("pthreadMultBox.dat");			// getting the vector of latencies for pthreadMultiplication
	for(int i=100;i<=400;i++){
		ifsPthread>>s;
		pthreadTimes.push_back(stof(s));
	}							// computing and printing the mean,std in the console
	cout<<"Mean of pthread implementation is "<<mean(pthreadTimes)<<"\nStd of pthread implementations is "<<standardDeviation(pthreadTimes)<<"\n";

	ifstream ifsMkl;
	vector<float> mklTimes;
	ifsMkl.open("mklMultBox.dat");				// getting the vector of latencies for pthreadMultiplication
	for(int i=100;i<=400;i++){
		ifsMkl>>s;
		mklTimes.push_back(stof(s));
	}							// computing and printing the mean,std in the console
	cout<<"Mean of mkl implementation is "<<mean(mklTimes)<<"\nStd of mkl implementations is "<<standardDeviation(mklTimes)<<"\n";


	ifstream ifsOpenBlas;
	vector<float> openBlasTimes;
	ifsOpenBlas.open("openBlasMultBox.dat");		// getting the vector of latencies for openblas
	for(int i=100;i<=400;i++){
		ifsOpenBlas>>s;
		openBlasTimes.push_back(stof(s));
	}							// computing and printing the mean,std in the console
	cout<<"Mean of openblas implementation is "<<mean(openBlasTimes)<<"\nStd of openBlas implementations is "<<standardDeviation(openBlasTimes)<<"\n";




	return 0;
}

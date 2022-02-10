#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

float mean(vector<float> &v){
	float sum = 0;
	for(int i=0;i<v.size();i++){
		sum+=v[i];
	}
	float average = sum/v.size();
	return average;
}


float standardDeviation(vector<float> &v){
	float sumOfSquares = 0;
	float average = mean(v);
	for(int i=0;i<v.size();i++){
		sumOfSquares+=(v[i]-average)*(v[i]-average);
	}
	float variance = sumOfSquares/v.size();

	float deviation = sqrt(variance);

	return deviation;

}


using namespace std;



int main(int argc, char const *argv[])
{
	//mean and std of latencies for pthread 

	ifstream ifsPthread;
	string s;
	vector<float> pthreadTimes;
	ifsPthread.open("pthreadMultBox.dat");
	for(int i=100;i<=400;i++){
		ifsPthread>>s;
		pthreadTimes.push_back(stof(s));
	}
	cout<<"Mean of pthread implementation is "<<mean(pthreadTimes)<<"\nVariance of pthread implementations is "<<standardDeviation(pthreadTimes)<<"\n";

	ifstream ifsMkl;
	vector<float> mklTimes;
	ifsMkl.open("mklMultBox.dat");
	for(int i=100;i<=400;i++){
		ifsMkl>>s;
		mklTimes.push_back(stof(s));
	}
	cout<<"Mean of mkl implementation is "<<mean(mklTimes)<<"\nVariance of mkl implementations is "<<standardDeviation(mklTimes)<<"\n";


	ifstream ifsOpenBlas;
	vector<float> openBlasTimes;
	ifsOpenBlas.open("openBlasMultBox.dat");
	for(int i=100;i<=400;i++){
		ifsOpenBlas>>s;
		openBlasTimes.push_back(stof(s));
	}
	cout<<"Mean of openblas implementation is "<<mean(openBlasTimes)<<"\nVariance of openBlas implementations is "<<standardDeviation(openBlasTimes)<<"\n";




	return 0;
}
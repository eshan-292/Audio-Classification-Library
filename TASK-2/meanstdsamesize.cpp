#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
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



int main(int argc, char const *argv[])
{
	
	vector<int> sizes = {2, 20, 50, 100, 150, 200};

	string s;

	for(int i=1;i<=sizes.size();i++){							// for each matrix of size- size[i] getting the mean and standard deviation for 100 runs for different implementations
		ifstream ifsBasic;
		cout<<"Over matrix of size "<<sizes[i-1]<<", "<<sizes[i-1]<<"\n";	
		vector <float> basicTimes;
		ifsBasic.open("m"+to_string(i)+"basicMult.dat");
		for(int j=0;j<100;j++){
			getline(ifsBasic,s);
			basicTimes.push_back(stof(s.substr(4)));			// getting the time for each run in a vector
		}
		cout<<"Basic implementation\n";
		cout<<"Mean - "<<mean(basicTimes)<<" Std - "<<standardDeviation(basicTimes)<<"\n";	// computing mean and std of the vector and printing the output

		ifstream ifsPthread;
		vector <float> pthreadTimes;
		ifsPthread.open("m"+to_string(i)+"pthread.dat");
		for(int j=0;j<100;j++){
			getline(ifsPthread,s);
			pthreadTimes.push_back(stof(s.substr(4)));  		// getting the time for each run in a vector
		}
		cout<<"Pthread implementation\n";
		cout<<"Mean - "<<mean(pthreadTimes)<<" Std - "<<standardDeviation(pthreadTimes)<<"\n"; // computing mean and std of the vector and printing the output

		ifstream ifsmkl;
		vector <float> mklTimes;
		ifsmkl.open("m"+to_string(i)+"mkl.dat");
		for(int j=0;j<100;j++){
			getline(ifsmkl,s);
			mklTimes.push_back(stof(s.substr(4)));				// getting the time for each run in a vector
		}
		cout<<"Mkl implementation\n";
		cout<<"Mean - "<<mean(mklTimes)<<" Std - "<<standardDeviation(mklTimes)<<"\n";   		// computing mean and std of the vector and printing the output


		ifstream ifsOpenBlas;
		vector <float> openBlasTimes;
		ifsOpenBlas.open("m"+to_string(i)+"openblas.dat");
		for(int j=0;j<100;j++){
			getline(ifsOpenBlas,s);
			openBlasTimes.push_back(stof(s.substr(4)));			// getting the time for each run in a vector
		}
		cout<<"Openblas implementation\n";
		cout<<"Mean - "<<mean(openBlasTimes)<<" Std - "<<standardDeviation(openBlasTimes)<<"\n";// computing mean and std of the vector and printing the output
		
	}

	
	return 0;
}
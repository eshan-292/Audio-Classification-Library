#include <iostream>
#include <vector>

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
	vector<float> v = {2.31,32.32,42.2,9.42,42.9};

	cout<<mean(v)<<"\n";
	cout<<standardDeviation(v)<<"\n";	
	return 0;
}
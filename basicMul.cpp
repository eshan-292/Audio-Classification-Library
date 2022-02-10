#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;

vector<vector<float>> basicMult(vector<vector<float>> &matrix1, vector<vector<float>> &matrix2){
	vector<vector<float> > result(matrix1.size(),vector<float>(matrix2[0].size(),0));

	for(int i=0;i<matrix1.size();i++){
		for(int j=0;j<matrix2[0].size();j++){
			for(int k=0;k<matrix1[0].size();k++){
				result[i][j]+=matrix1[i][k]*matrix2[k][j];
			}
		}
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

int main(int argc, char const *argv[])
{
	vector<vector<float>> matrix1,matrix2;
	ofstream ofs;
	ofs.open("basicMult.dat");
	auto start=chrono::high_resolution_clock::now();
	auto end=chrono::high_resolution_clock::now();
	double time_taken;
	for(int i=100;i<=400;i++){
		matrix1 = generateRandomMatrix(i,i,10);
		matrix2 = generateRandomMatrix(i,i,10);
		start = chrono::high_resolution_clock::now();

		basicMult(matrix1,matrix2);
		end = chrono::high_resolution_clock::now();
		time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
     	time_taken*= 1e-9;
		ofs<<i<<" "<<time_taken<<"\n";
	}

	// for(int i=0;i<result.size();i++){
	// 	for(int j=0;j<result[0].size();j++){
	// 		cout<<result[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

	return 0;
}
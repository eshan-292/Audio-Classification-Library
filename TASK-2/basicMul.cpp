#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	vector<vector<float> > matrix1(400,vector<float>(1000,-0.212123));
	vector<vector<float> > matrix2(1000,vector<float>(400,1.34123));
	vector<vector<float> > result(matrix1.size(),vector<float>(matrix2[0].size(),0));

	for(int i=0;i<matrix1.size();i++){
		for(int j=0;j<matrix2[0].size();j++){
			for(int k=0;k<matrix1[0].size();k++){
				result[i][j]+=matrix1[i][k]*matrix2[k][j];
			}
		}
	}

	// for(int i=0;i<result.size();i++){
	// 	for(int j=0;j<result[0].size();j++){
	// 		cout<<result[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

	return 0;
}
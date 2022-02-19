#include <iostream>
#include <vector>
#include "basicmultiplication.h"
using namespace std;





vector<vector<float>> basicMult(vector<vector<float>> &inputMatrix, vector<vector<float>> &weightMatrix, vector<vector<float>> &biasMatrix){
	vector<vector<float> > result(inputMatrix.size(),vector<float>(weightMatrix[0].size(),0));

	for(int i=0;i<inputMatrix.size();i++){
		for(int j=0;j<weightMatrix[0].size();j++){
			for(int k=0;k<inputMatrix[0].size();k++){
				result[i][j]+=inputMatrix[i][k]*weightMatrix[k][j];
			}
		}
	}

  for(int i=0;i<inputMatrix.size();i++){
    for(int j=0;j<biasMatrix[0].size();j++){
      result[i][j]+=biasMatrix[i][j];
    }
  }

	return result;

}

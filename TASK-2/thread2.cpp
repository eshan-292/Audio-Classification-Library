#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;

struct arguments
{
	vector<vector<float>> matrix1;
	vector<vector<float>> matrix2;
	vector<vector<float>>result;
	int row;
	int col;
};


void* computeVectorProduct(void* args){
	struct arguments *myargs = (struct arguments *)args;
		for(int i=0;i<(myargs->matrix2).size();i++){
			(myargs->result)[myargs->row][myargs->col]+=((myargs->matrix1)[myargs->row][i])*((myargs->matrix2[i][myargs->col]));
		}
}


int main(int argc, char const *argv[])
{
	

	vector<vector<float> > matrix1(400,vector<float>(1000,-0.212123));
	vector<vector<float> > matrix2(1000,vector<float>(400,1.34123));
	vector<vector<float> > result(matrix1.size(),vector<float>(matrix2[0].size(),0));
	pthread_t thread_id[matrix1.size()][matrix2[0].size()];
	struct arguments args;
	args.matrix1 = matrix1;

	args.matrix2 = matrix2;
	args.result = result;
	for(int i=0;i<matrix1.size();i++){
			for(int j=0;j<matrix2[0].size();j++){
				args.row = i;
				args.col = j;
				pthread_create(&thread_id[i][j],NULL,&computeVectorProduct,(void *)&args);
		}
	}

	for(int i=0;i<matrix1.size();i++){
		for(int j=0;j<matrix2[0].size();j++){
			pthread_join(thread_id[i][j],NULL);

		}
	}

	// for(int i=0;i<args.result.size();i++){
	// 	for(int j=0;j<args.result[0].size();j++){
	// 		cout<<args.result[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }


	return 0;
}
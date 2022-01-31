#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;

struct arguments
{
	vector<float> matrix1;
	vector<vector<float>> matrix2;
	vector<vector<float>>result;
	int row;
};


void* computeVectorProduct(void* args){
	struct arguments *myargs = (struct arguments *)args;
		for(int j=0;j<(myargs->matrix2)[0].size();j++){
			for(int i=0;i<(myargs->matrix1).size();i++){
				(myargs->result)[myargs->row][j]+=((myargs->matrix1)[i])*((myargs->matrix2[i][j]));
			}
		}
	
}


int main(int argc, char const *argv[])
{
	

	vector<vector<float> > matrix1(1000,vector<float>(1000,-0.212123));
	vector<vector<float> > matrix2(1000,vector<float>(1000,1.34123));
	vector<vector<float> > result(matrix1.size(),vector<float>(matrix2[0].size(),0));
	pthread_t thread_id[matrix1.size()];
	struct arguments args;
	args.matrix2 = matrix2;
	args.result = result;
	for(int i=0;i<matrix1.size();i++){
			args.matrix1 = matrix1[i];
			args.row = i;
			int r = pthread_create(&thread_id[i],NULL,&computeVectorProduct,(void *)&args);	
	}
	for(int i=0;i<matrix1.size();i++){
		pthread_join(thread_id[i],NULL);

	}
	// for(int i=0;i<args.result.size();i++){
	// 	for(int j=0;j<args.result[0].size();j++){
	// 		cout<<args.result[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }


	return 0;
}
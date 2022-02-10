#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;

	struct arguments
{
	vector<float> matrix1;
	vector<vector<float>> matrix2;
	vector<vector<float>>*result;
	int row;
};


void* computeVectorProduct(void* args){
	struct arguments *myargs = (struct arguments *)args;
		for(int j=0;j<(myargs->matrix2)[0].size();j++){
			for(int i=0;i<(myargs->matrix1).size();i++){
				(*(myargs->result))[myargs->row][j]+=((myargs->matrix1)[i])*((myargs->matrix2[i][j]));
			}
		}
	
	
}


int main(int argc, char const *argv[])
{
	
					cout<<"WORKS";

	vector<vector<float> > matrix1 = {{1, 0},{0, 1}};
	vector<vector<float> > matrix2 = {{1, 0},{0, 1}};

	vector<vector<float> > result(matrix1.size(),vector<float>(matrix2[0].size(),0));
	pthread_t thread_id[matrix1.size()];
	struct arguments args[matrix1.size()];	//creating an array of structures for passing arguments to each thread

	for(int i=0;i<matrix1.size();i++){
			args[i].matrix2 = matrix2;
			args[i].result = &result;
			args[i].matrix1 = matrix1[i];
			args[i].row = i;
			pthread_create(&thread_id[i],NULL,&computeVectorProduct,(void *)&(args[i]));	

	}
	for(int i=0;i<matrix1.size();i++){
		pthread_join(thread_id[i],NULL);

	}
	for(int i=0;i<result.size();i++){
		for(int j=0;j<result[0].size();j++){
			cout<<result[i][j]<<" ";
		}
		cout<<"\n";
	}


	return 0;
}
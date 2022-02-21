#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include "fullyconnectedpthread.h"
#include "helper.h"
#include "inputoutput.h"
// #include "mklmult.h"
#include "openblasmult.h"

using namespace std;




int main(int argc, char const *argv[])
{

    if(argc<7){                                       // 6 arguments are required
        insufficientArguments();                      // call insufficient arguments if less than arguments are there
        return 0;                                     // gracefully terminate the program
    }
    if(strcmp(argv[1],"fullyconnected")==0){              // if the function argument is "fullyconnected"

        if(strcmp(argv[6],"pthread")==0){
	        try{


	        		                                            // error might be thrown by getMatrix and fullyConnected functions which have to be taken care for
	            	vector<vector<float>>inputMatrix = getMatrix(argv[2]); //getmatrix from inputmatrix.txt
	            	vector<vector<float>>weightMatrix = getMatrix(argv[3]);//getmatrix from weightmatrix.txt
	            	vector<vector<float>>biasMatrix = getMatrix(argv[4]);  //getmatrix from biasmatrix.txt
	            	vector<vector<float>> result = fullyConnectedPthread(inputMatrix, weightMatrix, biasMatrix); // compute the result of taking inner product and adding bias
	            	outputMatrix(argv[5],result);

	                // output the resultant matrix to outputmatrix.txt
	        }
	        catch(string s){                                  // inputMatrix can throw errors if fileName isnot found or the number of rows and columns in matrix are incorrect(less than or equal to zero), fullyConnected can throw errors if dimension of the input,weight, bias matrix are not compatible for the required operations
	            cout<<s;
	        }
	    }
	    else if(strcmp(argv[6],"mkl")==0){
			string f1=argv[2], f2=argv[3], f3=argv[4], f4=argv[5] ;
			// mklmult(f1,f2,f3,f4) ;			
	    }
	    else if(strcmp(argv[6],"openblas")==0){
			string f1=argv[2], f2=argv[3], f3=argv[4], f4=argv[5] ;
			openblasmult(f1,f2,f3,f4) ;	
	    }
	    else{
	    	incorrectMatrixMultiplicationMethod();
	    }
    }
    else{
        incorrectFunction(argv[1]);                       // if the function argument is anything other than fullyconnected, activation, pooling, probability
        return 0;
    }


	return 0;
}

randommatrixgeneration.cpp

- For plotting and testing on various matrices we have written a file randommatrixgeneration.cpp
- This file has a function generateRandomMatrix which takes as input the dimension of the matrix that we have to generate and an upperLimit on entries of matrix. It returns the random matrix as a vector of vector
- The file calls this function to generate random input, weight, bias matrices of size 100*100 - 400*400
- These are then printed into the files inputMatrices.txt, weightMatrices.txt, biasMatrices.txt by using the function outputMatrix of inputoutput.cpp

inputoutput.cpp/ inputoutput.h
- This file has two functions for handling input output of matrices as vector of vector
- It has a function getMatrix to which given a file takes the matrix stored into the file in column major form, converts it into equivalent vector of vector and returns it
- It also has a function outputMatrix to which given a filename and a matrix as vector of vector, prints(appends) the matrix into the file in column major form

basicmultiplication.cpp/ basicmultiplication.h
- This file has a function basicMult to which given an input,weight,bias matrix it computes the result of product of input,weight and addition of bias to product
- The algorithm used is the simple o(n^3) one with only one thread working

basicmultiplicationtest.cpp
- It generates input, weight, bias matrices from inputMatrices.txt, weightMatrices.txt, biasMatrices.txt and then calls basicMult function on each of them.
- The time of multiplication(with addition of bias) on each matrix is printed in basicMultBox.dat file

latency.cpp
- It has two functions each of which takes a vector of floats and returns the mean and std of values of the vector
- These two are called from main on the .dat files (files containing time) for each of the implementation and the correpsonding outputs are printed on the console

fullyconnectedpthread.cpp/fullyconnectedpthread.h
- This files has pthread based multiplication of matrices followed by addition of bias
- PTHREAD IMPLEMENTATION - 
	-> A function with return type void* is created
	-> The arguments to this function is two matrices matrix1, matrix2, resultant matrix(result of multiplication)(passed by reference), and the startRow and endRow
	-> The startRow and endRow indicate which rows of matrix1 are to be be multiplied by *all* columns of matrix2 to get corresponding rows of resultant matrix
	-> The matrix1 is divided into 4 almost equal parts(by rows), then 4 pthreads are created each of which will do multiplication of their correspoding rows
	-> A function fullyConnectedPthread is created which takes input,weight,bias matrices and does all the tasks of dividing matrices, creating threads, adding bias by calling subsequent functions

pthreadtest.cpp
- It generates input, weight, bias matrices from inputMatrices.txt, weightMatrices.txt, biasMatrices.txt and then calls fullyConnnectedPthread function on each of them.
- The time of multiplication( with addition of bias) is printed in pthreadMultBox.dat

mkltest.cpp
- It generates input, weight, bias matrices(as an array of floats, storing elements in column major form) from inputMatrices.txt, weightMatrices.txt, biasMatrices.txt and then does multiplication and addition via cblass_segm  on each(each of 301 triple of matrices) of them.
- The resultant time for each matrix is noted in a file name mklMultBox.dat

openblastest.cpp
- It generates input, weight, bias matrices(as an array of floats, storing elements in column major form) from inputMatrices.txt, weightMatrices.txt, biasMatrices.txt and then does multiplication and addition via cblass_segm  on each(each of 301 triple of matrices) of them.
- The resultant time for each matrix is noted in a file name mklMultBox.dat

- 

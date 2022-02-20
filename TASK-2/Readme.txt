HELPER/MATRIX-MULTIPLICATION/DATA-GENERATING FILES

randommatrixgeneration.cpp

- For plotting and testing on various matrices we have written a file randommatrixgeneration.cpp
- This file has a function generateRandomMatrix which takes as input the dimension of the matrix that we have to generate and an upperLimit on entries of matrix. It returns the random matrix as a vector of vector
- The file calls this function to generate random input, weight, bias matrices of size 100*100 - 400*400
- These are then printed into the files inputMatrices.txt, weightMatrices.txt, biasMatrices.txt by using the function outputMatrix of inputoutput.cpp
- This file is also used to make matrices of size 2, 20, 50, 100, 150, 200, which are then printed to m1.txt, m2.txt, m3.txt, m4.txt, m5.txt, m6.txt


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
- These two functions are called from main on the .dat files(corresponding to times on matrices of size 100*100 - 400*400) for each of the implementation and the correpsonding outputs are printed on the console

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

latenciesoversamesize.cpp
- It uses the 6 matrices corresponding to m1,m2,m3,m4,m5,m6.txt
- For each of the  matrices all the four implementations are tested 100 time
- The resulting latencies for each of the 100 run(for a given matrix and implementation) are printed into corresponding .dat files
- For example dat file m4mkl.dat contains the time required for each of the 100 runs of mkl implementation on the matrix m4
- With these times/latencies some values (-100 etc.) are also printed which just help in providing horizontal coordinates in the boxplot
- I have assumed that the same matrix to be used as input,weight and bias matrix(This does not affect the time of computation much)

meanstdsamesize.cpp 
- This file computes the mean and standard deviations for the 100 runs of a given matrix and given implementation
- These metrics are printed in the console with appropriate labels


MAIN FILE
main2.cpp
- This is the main cpp file which contains all the 3 implementation and is used for running any desired implementation on given input, weight, bias matrix and print the output in outputmatrix.txt via terminal
- The corresponding executable is ./yourcode.out
- Commandline to used - ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outmatrix.txt method
- method is - 'mkl', 'openblas', 'pthread'

SHELL SCRIPT FOR PLOTTING THE DATA AND DESCRIPTION OF PNG FILES
There are two shell scripts for plotting the latencies in png and eps format
- The first one is plot.sh
	-> This plots box plots for basicMultBox.dat, pthreadMultBox.dat, mklMultBox.dat, openBlasMultBox.dat
	-> These plot correspond to the time of one run for each method(mkl,openblas etc.) on a matrix having size between 100*100 - 400*400
	-> The output files generated by this are basicMultBoxPlot.png, basicMultBoxPlot.eps, openBlasMultBoxPlot.eps, openBlasMultBoxPlot.png, mklMultBoxPlot.eps, mklMultBoxPlot.png, pthreadMultBoxPlot.png, pthreadMultBoxPlot.eps
	-> To run this use bash plot.sh

- The second one is plot2.sh
	-> This plot box plots for each m1basicMult.dat,m1mkl.dat,m1openblas.dat,m1pthread.dat,m2mkl.dat and so on
	-> The output files are basicMult.png, basicMult.eps, pthread.png, pthread.eps, openblas.png, openblas.eps, mkl.png, mkl.eps
	-> Each file have 6 boxes, corresponding to the 6 different matrices (size - 2, 20, 50, 100, 150, 200)
	-> Each box corresponds to the time of 100 runs over a particular matrix and for a given method of implementation

- There is also a file CPU_Utilization.png which shows the utilization of various cores during pthread implementation


OBSERVATIONS AND INFERENCES
Cpu
	-> The CPU utilization while pthread shows that 4 cores out of the 8 cores are busy with % idle time as 15,16,19,30
	-> This observation is consistent with the fact that the pthread implementation makes 4 threads for computing the matrix

Latencies over 100 runs of the 6 matrices - 

Over matrix of size 2, 2
Basic implementation
Mean - 1.64621e-06 Std - 3.39959e-07
Pthread implementation
Mean - 7.92058e-05 Std - 2.0693e-05
Mkl implementation
Mean - 3.015e-08 Std - 6.52131e-09
Openblas implementation
Mean - 2.865e-08 Std - 2.8892e-09
Over matrix of size 20, 20
Basic implementation
Mean - 0.000223037 Std - 3.48045e-05
Pthread implementation
Mean - 0.000189945 Std - 6.67748e-05
Mkl implementation
Mean - 1.926e-08 Std - 1.80898e-09
Openblas implementation
Mean - 1.918e-08 Std - 7.26361e-10
Over matrix of size 50, 50
Basic implementation
Mean - 0.00205098 Std - 0.000157223
Pthread implementation
Mean - 0.000879766 Std - 0.000111321
Mkl implementation
Mean - 1.766e-08 Std - 1.56984e-09
Openblas implementation
Mean - 1.792e-08 Std - 2.41528e-09
Over matrix of size 100, 100
Basic implementation
Mean - 0.0147054 Std - 0.000743169
Pthread implementation
Mean - 0.0051761 Std - 0.000947854
Mkl implementation
Mean - 1.996e-08 Std - 2.31914e-09
Openblas implementation
Mean - 2.1e-08 Std - 2.69815e-09
Over matrix of size 150, 150
Basic implementation
Mean - 0.0468161 Std - 0.00110467
Pthread implementation
Mean - 0.0155877 Std - 0.000330575
Mkl implementation
Mean - 1.811e-08 Std - 1.59308e-09
Openblas implementation
Mean - 1.803e-08 Std - 6.23779e-10
Over matrix of size 200, 200
Basic implementation
Mean - 0.121737 Std - 0.00209082
Pthread implementation
Mean - 0.0401227 Std - 0.0047175
Mkl implementation
Mean - 2.537e-08 Std - 4.57964e-09
Openblas implementation
Mean - 2.679e-08 Std - 4.0331e-09



- The basicmultiplication is 2 as fast as pthread multiplication for matrix of size 2x2
- However for matrix of size 20x20 both of them have same time with pthread being slightly faster
- For matrices of size 100x100, 150x150, 200x200  pthread becomes almost 3 times fast than basicmultiplication
- The possible reason for this could be that the extra time required for creating, maintaining, joining 4 threads surpassed the benefit of dividing the work among different threads for small matrices
- However for larger size matrices the overall computation required for matrix multiplication was much higher as compared to that of creation and maintainence of threads, thereby making pthreads much faster

--ADD REASON FOR MKL OPENBLAS

Average and standard deviation for 1 run on matrices of size 100x100 - 400x400
Mean of basic implementation is 0.231583
Std of basic implementations is 0.199918
Mean of pthread implementation is 0.189399
Std of pthread implementations is 0.157551
Mean of mkl implementation is 0.00235257
Std of mkl implementations is 0.00509506
Mean of openblas implementation is 0.00193483
Std of openBlas implementations is 0.00460053

- Clearly for very large matrices pthread implementation is faster than basic multiplication
- The results also indicate that mkl and openblas are quite optimized libraries for matrix multiplication with a mean 100 times faster than basic multiplication
- Mkl and openblas have similar performance with openblas slighly ahead


IMPORTANT POINTS TO NOTE - 

-We have computed latencies and created boxplots in 2 ways 
	-> Doing one run for 301 matrices of size 100*100 - 400x400
	-> Doing 100 runs for 6 matrices of the following size - 2x2, 20x20, 50x50, 100x100, 150x150, 200x200

REFERENCES - 

- Referred to geek for geeks on how to get time of evaluation of a function using chrono
- Referred to mkl and openblas official documentation for installation and calling the functions with apt arguments
- Referred to some online tutorials for shell scripting and gnuplot
- Stackoverflow for handling error in code


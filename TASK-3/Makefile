yourcode.out: DNN.o classifier.o inputoutput.o helper.o softmax.o relu.o openblasmult.o main.cpp
	g++ DNN.o classifier.o helper.o softmax.o inputoutput.o relu.o openblasmult.o -I /OpenBLAS/include/ -L/OpenBLAS/lib -lopenblas -lpthread -lgfortran -fopenmp -m64 main.cpp -o yourcode.out

classifier.o: classifier.cpp
	g++ -c classifier.cpp
DNN.o: DNN.cpp
	g++ -c DNN.cpp
softmax.o: softmax.cpp
	g++ -c softmax.cpp
relu.o: relu.cpp
	g++ -c relu.cpp
openblasmult.o: openblasmult.cpp helper.o
	g++ -c openblasmult.cpp
helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

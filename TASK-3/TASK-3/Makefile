yourcode.out: main.cpp libaudio.so
	g++ -L/home/os/Desktop/COP290/TASK-3 -Wl,-rpath=/home/os/Desktop/COP290/TASK-3 -Wall -o yourcode.out main.cpp -laudio -I /OpenBLAS/include/ -L/OpenBLAS/lib -lopenblas -lpthread -lgfortran -fopenmp -m64
libaudio.so: libaudio.o inputoutput.o classifier.o DNN.o softmax.o relu.o openblasmult.o helper.o 
	g++ -shared -o libaudio.so inputoutput.o softmax.o relu.o DNN.o libaudio.o openblasmult.o classifier.o	
libaudio.o : libaudio.cpp 
	g++ -c -Wall -Werror -fpic libaudio.cpp
inputoutput.o: inputoutput.cpp
	g++ -c -Wall -Werror -fpic inputoutput.cpp
classifier.o: classifier.cpp
	g++ -c -Wall -Werror -fpic classifier.cpp
DNN.o: DNN.cpp
	g++ -c -Wall -Werror -fpic DNN.cpp
softmax.o: softmax.cpp
	g++ -c -Wall -Werror -fpic softmax.cpp
relu.o: relu.cpp
	g++ -c -Wall -Werror -fpic relu.cpp
openblasmult.o: openblasmult.cpp helper.o
	g++ -c -Wall -Werror -fpic openblasmult.cpp
helper.o: helper.cpp
	g++ -c -Wall -Werror -fpic helper.cpp 

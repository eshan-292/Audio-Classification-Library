all: pthreadtest.out basicmultiplicationtest.out randommatrixgeneration.out latency.out


pthreadtest.out: fullyconnectedpthread.o inputoutput.o pthreadtest.cpp
	g++ inputoutput.o helper.o fullyconnectedpthread.o pthreadtest.cpp -pthread -o pthreadtest.out

fullyconnectedpthread.o: fullyconnectedpthread.cpp
	g++ -c fullyconnectedpthread.cpp

randommatrixgeneration.out: inputoutput.o randommatrixgeneration.cpp
	g++ inputoutput.o helper.o randommatrixgeneration.cpp -o randommatrixgeneration.out

basicmultiplicationtest.out: basicmultiplication.o basicmultiplicationtest.cpp
	g++ basicmultiplication.o basicmultiplicationtest.cpp -o basicmultiplicationtest.out

inputoutput.o: inputoutput.cpp helper.o
	g++ -c inputoutput.cpp

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

basicmultiplication.o: basicmultiplication.cpp
	g++ -c basicmultiplication.cpp -o basicmultiplication.o

latency.out: latency.cpp 
	g++ latency.cpp -o latency.out

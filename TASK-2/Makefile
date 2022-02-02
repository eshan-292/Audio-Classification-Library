
yourcode.out: fullyconnected.o helper.o main.cpp
	g++ fullyconnected.o helper.o main.cpp -o yourcode.out

fullyconnected.o: fullyconnected.cpp
	g++ -c fullyconnected.cpp -o fullyconnected.o -pthread

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

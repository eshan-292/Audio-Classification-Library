
yourcode.out: helper.o main2.cpp
	g++ helper.o main2.cpp -o yourcode.out -pthread

helper.o: helper.cpp
	g++ -c helper.cpp -o helper.o

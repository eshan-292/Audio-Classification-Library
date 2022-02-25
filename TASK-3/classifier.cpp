#include <iostream>
#include <fstream>

//#include "classfier.h"

using namespace std;



void classify(float* probabilities, int size, string outputFile){
  string keywords[12] =  {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};

  ofstream outputStream;
  outputStream.open(outputFile, ios_base::app);
    float prob[size] ;
    for(int i=0;i<size;i++){
        prob[i]=probabilities[i] ;
    }
    float maxi = probabilities[0] ;
    int curri=0 ;
    //The case when probabilities are equal yet to be handled
    int ansind[3], j=0 ;
    //Iterating thrice to find the top three probabilities
    for(int k=0;k<3;k++){
    curri=0, maxi=prob[0] ;
    //Iterating over the probabilities array to find the max probability
    for(int i=0;i<size;i++){
        if(prob[i]>maxi){
            maxi=prob[i] ;
            curri=i ;
        }
    }
    ansind[j]=curri ;       //saving the index of max probability
    j++ ;
    prob[curri]=0 ;         //dumping the max probability , so that the next maximum can be calculated in the next iteration
    }
    outputStream << keywords[ansind[0]] << " " << keywords[ansind[1]] << " " << keywords[ansind[2]] << " " << probabilities[ansind[0]] << " " << probabilities[ansind[1]] << " " << probabilities[ansind[2]] << endl;
}

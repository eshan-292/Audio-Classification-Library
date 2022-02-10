#include "helper.h"
#include <iostream>
using namespace std;

void incorrectFunction(string functionName){			// if the second argument in command line(other than ./yourcode.out) is anything other than fullyconnected
	cout<<"The following is a wrong function name - "<<functionName<<"\n";
	cout<<"The following are the possible functions - \n";
	cout<<"fullyconnected\n";
}

void insufficientArguments(){			// if the number of arguments in command line are less than what they should be 
	cout<<"More number of arguments are required\n";
}

void incorrectMatrixMultiplicationMethod(){
	cout<<"For matrix multiplication the possible methods are - 'pthread', 'mkl', 'openblas'";
}

bool canBeConvertedToInt(string s){		// checks if a given string can be converted to an integer
	for(int i=0;i<s.size();i++){
		if(i==0 && (s[i]=='+'|| s[i]=='-'|| (s[i]>='0' && s[i]<='9'))){	// first character of string should be +,- or anyinteger
			continue;
		}
		else if(s[i]>='0' && s[i]<='9'){// characters other than first character should be between '0' and '9'
			continue;
		}
		else{
			return false;				// if a violation is there return false
		}
	}
	return true;						// if all the characters follow the restrictions return true
}


bool canBeConvertedToFloat(string s){   // checks if a given string can be converted to a floating point number
	int dotcount=0;						// to store the number of occurences of decimal point(can be atmost one)
	for(int i=0;i<s.size();i++){
		if(s[i]=='.' && dotcount==0){	// if decimal point occurs(.) it should be the only one 
			dotcount++;					// to check that no more. occurs
			continue;
		}
		if(i==0 && (s[i]=='+'|| s[i]=='-'|| (s[i]>='0' && s[i]<='9'))){ // first character of string should be +,- or anyinteger
			continue;
		}
		else if((s[i]>='0' && s[i]<='9')){// characters other than first character should be between '0' and '9'
			continue;
		}
		else{
			return false;				  // if a violation is there return false
		}
	}
	return true;                          // if a violation is there return false
}
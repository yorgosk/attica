/*
File: main.cpp
Purpose: The main function for our project
*/
#include "header.h"

int N, NSegs, K ,Percent;

int main(int argc, char* argv[]){
	/* take command line arguments, evaluate and assign them */
	if(argc != 5){
		cout << "ERROR! Wrong number of arguments." << endl;
		return -1;
	}
	srand(time (NULL));
	N = atoi(argv[1]);
	NSegs = atoi(argv[2]);
	K = atoi(argv[3]);
	Percent = atoi(argv[4]);// / 100.0;	// percentage, remember ;-)
	if(N < 0 || NSegs < 0 || K < 0 || Percent < 0 || Percent > 100){
		cout << "ERROR! Arguments can't have negative values. They must be equal to zero or above! Also, Percent (4th argument) should not be greater than 100 !" << endl;
		return -2;
	}
	/* create highway */
	attica A;
	cout << endl;
	/* operate highway, as many times as argument 1 dictates */
	for(int i = 1; i <= N; i++){
		cout<<"----------------------------------------------------------------------------------OPERATE "<<i<<endl;
		A.operate();
	}
	cout << endl;

	return 0;
}

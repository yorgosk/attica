/*
File: attica.cpp
Purpose: attica class member functions' definitions
*/
#include "header.h"
/* highway constructor */
attica::attica(){
	sL = new segmentList();						// create list of highway segments
	cars = sL->get_number_of_cars();
	cout << "Attica Highway has just been created, and has " << cars << " cars!" << endl << endl;	// highway construction message
	cout << "Highway is operating" << endl << endl;							// we are ready to go!
}
/* highway destructor */
attica::~attica(){
	cout << "Attica Highway is about to be destroyed" << endl;	// highway destruction message
	delete sL;		// call segment list's destructor (destroy each highway's segment)
}
/* operate highway */
void attica::operate(){
	/* various operations */
	sL->operate();
	sL->prepare();
	sL->print();
	cars = sL->get_number_of_cars();
	/* how many cars in the highway right now */
	cout << endl << "Highway has: " << cars << " cars" << endl;
}

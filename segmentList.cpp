/*
File: segmentList.cpp
Purpose: segment and segmentList classes member functions' definitions
*/
#include "header.h"
/* segment class constructor */
segmentList::segment::segment(const int i) : id(i), kapa(K) {
	entr = new entrance(id, rand()%10 + 1); 				// create an entrance with a random in [1, 10] number of tolls
	cout << "Give max vehicle capacity for segment no." << id << ": ";
	while(!(cin>>MAXVEHICLES)){				// read max vehicles number, until you have a valid input
			cin.clear();
			cin.ignore(10000,'\n');
			cout<<" ERROR! Your input wasn't an integer! Try again: ";
	}

	VEHICLENUM = rand()%MAXVEHICLES + 1; 			// VEHICLENUM in [1, MAXVEHICLES]
	list = new vehicleList(VEHICLENUM, id);		// we initialize them with readiness = false
	next = NULL;							// there's currently no next segment
	prev = NULL;							// there's currently no previous segment
	cout << "A segment with id " << id << " has just been created!" << endl;	// segment construction message
}
/* segment class destructor */
segmentList::segment::~segment(){
	cout << endl << "Segment with id " << id << " is about to be destroyed" << endl;	// segment destruction message
	delete entr;			// destroy segment's entrance
	cout << endl << "\t\t\t\t\t\t\t\tSegments ";
	delete list;			// delete segment's vehicleList
	delete next;			// call next segment's destructor
}
/* vehicles enter a segment */
int segmentList::segment::enter(){
	if(VEHICLENUM >= MAXVEHICLES) return 0 ;  // dont enter if there is no space
	int counter = 0, elec_counter = 0, empl_counter = 0;
	bool is_elec;
	vehicle  *temp;
	cout << "Enter!" << endl;
	int tollnum = 1;  //for every toll if there is enough room car enters
	while((VEHICLENUM < MAXVEHICLES) && (temp = entr->enter(is_elec,tollnum))){
		list->pushFront(temp);
		cout<<"ENTER FROM TOLL "<<tollnum<<endl;
		tollnum++;
		counter++;
		if(is_elec) elec_counter++;    ///we are counting the number of empolyer tolls and the numer of
		else empl_counter++;//of electronic tolls in order to "break;" if we reach number K
		if((empl_counter == kapa) || (elec_counter == 2*kapa)) break;
		refreshVEHICLENUM();          // we refresh the number of the vehicles
	}
	if((empl_counter == kapa) || (elec_counter == 2*kapa)){
		cout << "\t\t\t\tMaximum vehicles entered in segment: " << id << " and that occured at " << ((empl_counter == kapa) ? "employee":"electronic") << " tolls!!!" << endl;
		kapa++;
	}else kapa--;   //we decrease K if the number of vehicles that entered is smalles than me maxnumber
	if(counter < entr->get_number_of_cars()){
		return 1;
	}
	list->print(); // we print the vehicle list in order to watch how the highway works
	return 0;
}
/* vehicles exit a segment */
void segmentList::segment::exit(){
	list->exit(id); 				//exit function destroyes a vehicle
	refreshVEHICLENUM();   // we refresh the number of the vehicles
}
/* vehicles pass from a segment to it's next */
int segmentList::segment::pass(){
	int counter = 0;
	cout << "\t\t\t\t\t\t\tPass for segment " << id << endl;
	if(!prev){		//if there is no previous segment to pass vehicles we return
		cout << "First segment has no previous segment to pass vehicles" << endl;
		return 0;
	}
	//synarthsh pou epistrefei vehicle * kai to kanei insert sto vehicle list tou epomenou
	vehicle *temp;
	while((VEHICLENUM) < (MAXVEHICLES) && ((temp = prev->list->pass(prev->id)) != NULL)){ // oso yparxoun aytokinhta me destination epomeno segment na synexizei
//while there is enough space for more vehicles we pass vehicles from the previous segment to the current
		list->pushFront(temp);
		prev->refreshVEHICLENUM(); 	 // we refresh the number of the vehicles of the previous segment
		refreshVEHICLENUM(); // we refresh the number of the vehicles of the current segment
		counter++;
	}
	if((VEHICLENUM) >= (MAXVEHICLES)) cout << "\t\t\t DEN XWRNE ALLA vehicle max = " <<MAXVEHICLES << endl;
	list->print();			//printing the vehicle list
	if(counter < list->get_num_of_ready()) return 1;
	cout << "End of PASS" << endl;
	return 0;
}
/* print segment */
void segmentList::segment::print() const {
	cout << "Printing segment with id " << id << endl;
	list->print(); // print list of vehicles
}
/* get current number of vehicles in the segment */
int segmentList::segment::get_no_of_vehicles() const {
	return VEHICLENUM;
}
/* operate a segment */
void  segmentList::segment::operate(){
	cout << endl << "Exit for segment with id : " << id << " MAXVEHICLES " << MAXVEHICLES << endl << endl;
	exit();
	cout << endl << "Pass for segment with id : " << id << " MAXVEHICLES " << MAXVEHICLES << endl << endl;
	int pa = pass();
	cout << endl << "Enter for segment with id  : " << id << " MAXVEHICLES " << MAXVEHICLES << endl << endl;;
	int en = enter();
	if(en){//An o arithmos twn oxhmatwn pou eiserxontai se ena tmhma  einai mikroteros
//apo to plithos twn oxhmatwn pou perimenoun sthn eisodo
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Kathysterhseis sthn eisodo tou kombou : "<<id<<endl;
		if(pa){
			//An epipleon o arithmos twn oxhmatwn  poy metakinountai metaksy twn tmhmatwn poy syndeontai
//me ton kombo einai mikroteros	apo ayta pou einai ready na metakinhthoun
			cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||  Kathysterhseis meta ton kombo : "<<id<<endl;
		}
	}
	else{
		//an den isxyei kati apo ta parapanw
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Tyreitai tis apostaseis asfaleias sto tmhma meta ton kombo : "<<id<<endl;
	}
	cout << "Segment with id : " << id << " has " << VEHICLENUM<< " cars" << endl;

	entr->more_vehicles();	//prosthetoume vehicles sta vehiclelist twn toll ths entrance
}
/* check if a segment is empty */
bool segmentList::segment::is_empty() const{
	return (VEHICLENUM == 0);
}
/* refresh the current number of vehicles in the segment */
void segmentList::segment::refreshVEHICLENUM(){
	VEHICLENUM = list->get_noOfVehicles();
}
/* segmentList class constructor */
segmentList::segmentList(){
	head = NULL;							// list has currently no head
	tail = NULL;							// list has currently no tail
	for(int i = 1; i <= NSegs; i++){	// for as much segments as requested
		segment *temp = new segment(i);	// construct the segment
		pushBack(temp);									// push it in the back of the segment's list
	}
	cout << "A segmentList has just been created!" << endl;	// segmentList construction message
}
/* segmentList class destructor */
segmentList::~segmentList(){
		cout << endl << "Segment List is about to be destroyed" << endl;	// segmentList destruction message
		delete head;	// destroy list's head (triggers the destruction of the whole list)
}
/* insert a segment in the end of the segmentList */
void segmentList::pushBack(segment* &x){
	if(!tail) head = x;		// if the list is empty (no tail = no node), then the new node is also the head node
	else tail->next = x;	// tail's next node is the new node
	x->prev = tail;				// new node's previous node is the current tail
	tail = x;							// the new tail is our new node
}
/* print segmentList */
void segmentList::print() const {
	segment *temp = head;					// temporary pointer to the list's head
	while(temp){									// while you can iterate the list
		temp->print();							// print each segment
		temp = temp->next;					// go to the next segment
	}
}
/* get number of cars in the segmentList */
int segmentList::get_number_of_cars() const{
	int counter = 0;
	segment *temp = head;					// temporary pointer to the list's head
	while(temp){									// while you can iterate the list
		counter += temp->get_no_of_vehicles();	// count each segment's vehicles
		temp = temp->next;					// go to the next segment
	}
	return counter;								// return the counted number
}
/* operate segmentList */
void segmentList::operate(){
	segment *temp = tail;					// temporary pointer to the list's tail
	while(temp){									// while you can iterate the list (backwards)
		temp->operate();						// prepare each segment
		temp = temp->prev;					// go to the previous segment
	}
}
/* prepare cars in the segmentList (changing readiness status) */
void segmentList::prepare(){
	cout << "\t\t\t\t\t\t\t\tPREPARE" << endl;
	segment* temp = head;					// temporary pointer to the list's head
	while(temp){									// while you can iterate the list
		temp->list->prepare();			// prepare each segment's vehicleList
		temp = temp->next;					// go to the next segment
	}
}
/* refresh the current number of vehicles in all the segments */
void segmentList::refresh_VEHICLENUMS(){
	segment* temp = head;					// temporary pointer to the list's head
	while(temp){									// while you can iterate the list
		temp->refreshVEHICLENUM();	// refresh each segment's current number of vehicles
		temp = temp->next;					// go to the next segment
	}
}

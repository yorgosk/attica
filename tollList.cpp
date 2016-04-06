/*
File: tollList.cpp
Purpose: toll struct and tollList class member functions' definitions
*/
#include "header.h"
/* toll struct constructor */
tollList::toll::toll(int i, int entrID) : id(i), entr_id(entrID) {
  int x = rand()%2;   // random number 0 or 1
  is_electronic = x;  // if x==0 then false, if x==1 then true
  next = NULL;        // no next node
  waitline = NULL;    // no waitline at that moment
  waitline = new vehicleList(rand()%5+1, entr_id, true);  // construct a waitline
  cout << "An " << (is_electronic ? "electronic" : "employee") << " toll with id: " << id << " has just been created!" << endl; // toll's construction message
}
/* toll struct destructor */
tollList::toll::~toll(){
  cout << "An " << (is_electronic ? "electronic":"employee") << " toll with id: " << id << " is about to be destroyed" << endl; // toll's destruction message
  delete waitline;  // destroy toll's waitline
  delete next;      // destroy next toll
  next = NULL;      // no next toll
  waitline = NULL;  // no waitline
}
/* get number of vehicles waiting to enter */
int tollList::toll::get_number_of_cars() const {
    return waitline->get_noOfVehicles();
}
/* add more vehicles to the waitline */
void tollList::toll::more_vehicles(){
	cout<<"\t\t\t\t\t\t\t\tPROSTHESH EPIPLEON OXHMATWN STO DIODIO : "<<id <<"TOU SEGMENT : "<< entr_id<<endl;
	waitline->more_vehicles(entr_id);  // add more vehicles to the waitline
	waitline->print();                 // print waitline
}
/* tollList class constructor */
tollList::tollList(int identity) : id(identity) {
  head = NULL;               // there is no head (no actual list) at this moment
  numOfTolls = rand()%5 + 1; // o arithmos diodiwn ths kathe listas diodiwn einai anamesta sta {1,5}
  for(int i = 1; i <= numOfTolls; i++){ // for the number of tolls
      toll *temp = new toll(i, id);     // create a toll
      pushFront(temp);                  // push it to the tolls' list
  }
  cout << "Toll list with id: " << id << " has just been created!" << endl; // tollList construction message
}
/* tollList class destructor */
tollList::~tollList(){
  cout << "Toll list with id: " << id << " is about to be destroyed" << endl; // tollList destruction message
  delete head;  // destroy the head of the list (triggers the actual destruction of the list)
}
/* extract a vehicle (which is gonna enter the highway) */
vehicle* tollList::enter(bool &is_elec, int &tollnum){
  toll *temp = head;  // a temporary pointer to the head of the list
  vehicle *pointer;
  if(tollnum > numOfTolls){  // An ftasoume sto teylaiyteo na ksanagyrisoume sto prwto
    cout << "KSANAPAEI STO PRWTO TOLL numoftolls: " << numOfTolls << endl;
    tollnum = 1;    // go back to the first toll
  }
  while(tollnum != temp->id) temp = temp->next; // while we haven't reached the toll that we want, iterate the list

  while((temp) && !(pointer = temp->waitline->pop())){ //shmainei oti to sygekrimenno toll den exei kanena amaksi ready
    temp = temp->next;  // tote pame sto epomeno toll
  }
  if(temp) is_elec = temp->is_electronic; // to know if the vehicle comes from an electronic toll
  return pointer; // return the (pointer to the) vehicle
}
/* add toll to the tollList */
void tollList::pushFront(toll* &x){
  x->next = head;			// to kathe antikeimeno pou kanoume insert mpainei sthn arxi
  head = x;
}
/* get number of vehicles waiting at the tolls */
int tollList::get_number_of_cars() const {
  toll *temp = head;  // temporary pointer to the head of the list
  int counter = 0;
  while(temp){
    counter += temp->get_number_of_cars();  // we count the number of vehicles waiting at the tolls
    temp = temp->next;                      // while iterating the tollList
  }
  return counter;     // we return what we counted
}
/* get number of tolls with employees */
int tollList::get_employee_tolls() const {
  int counter = 0;
  toll* temp = head;  // temporary pointer to the head of the list
  while(temp){        // we iterate the tollList
    if(!(temp->is_electronic)) ++counter; // count the employee tolls
    temp = temp->next;    // go to the next toll
  }
  return counter;     // we return what we counted
}
/* get number of electronic tolls */
int tollList::get_electronic_tolls() const {
  int counter = 0;
  toll* temp = head;  // temporary pointer to the head of the list
  while(temp){        // we iterate the tollList
    if(temp->is_electronic) ++counter; // count the electronic tolls
    temp = temp->next;    // go to the next toll
  }
  return counter;     // we return what we counted
}
/* add more vehicles to the waitlines */
void tollList::more_vehicles(){
	toll* temp = head ;  // temporary pointer to the head of the list
	while(temp){         // we iterate the tollList
		temp->more_vehicles();  // add more vehicles to temp's waitLine
		temp = temp->next;      // go to the next toll
	}
}

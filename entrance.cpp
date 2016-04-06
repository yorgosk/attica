/*
File: entrance.cpp
Purpose: entrance class member functions' definitions
*/
#include "header.h"
/* entrace's constructor */
entrance::entrance(int i, int tnum) : id(i), noOfTolls(tnum) {
  tL = new tollList(id);      // create the list of the entrance's tolls
  cout << "An entrance with id: " << id << " has just been created!" << endl; // entrance's construction message
}
/* entrance's destructor */
entrance::~entrance(){
  cout << "An entrance is about to be destroyed" << endl; // entrance's destruction message
  delete tL;    // call the destructor of the entrance's list of tolls
}
/* a vehicle is popped from an entrance's vehicleList (to enter the highway) */
vehicle* entrance::enter(bool &is_elec,int & tollnum){
  return tL->enter(is_elec,tollnum);
}
/* get number of vehicles waiting at tolls */
int entrance::get_number_of_cars() const {
  return tL->get_number_of_cars();
}
/* get entrance's ID */
int entrance::get_id() const {
 	return id;
}
/* add more vehicles to the entrance's tolls */
void entrance::more_vehicles(){
	tL->more_vehicles();
}

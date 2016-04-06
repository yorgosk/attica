/*
File: vehicleList.cpp
Purpose: vehicle struct and vehicleList class member functions' definitions
*/
#include "header.h"
/* vehicle struct constructor */
vehicle::vehicle(int i, int curr_segm, bool j) : destination(i), curr_segment(curr_segm), ready(j) {
  next = NULL;    // initialize next and...
  prev = NULL;    // ...previous nodes as NULL
  cout << "A vehicle with destination : " << destination << " and status " << (ready ? "ready":"not ready") << " has just been created!" << endl;  // vehicle construction message
}
/* vehicle struct destructor */
vehicle::~vehicle(){
  cout << "A vehicle with destination: "<< destination <<" with current_segment  :"<<curr_segment <<" and status " << (ready ? "ready":"not ready") << " is about to be destroyed" << endl;
  delete next;  // call next node's destructor
}
/* vehicle print function */
void vehicle::print() const {
  cout << "Vehicle with destination: " << destination <<" with current_segment :"<<curr_segment <<" and status " << (ready ? "ready":"not ready") << endl;
}
/* vehicleList class constructor */
vehicleList::vehicleList(int n, int current_segment, bool toll) : noOfVehicles(0) { // ton metrame meta ton noOfVehicles
  if(toll) curr_segment = -1;
  else curr_segment = current_segment;
  int dest;       // a vehicle's destination
  head = NULL;    // initialize list's head as NULL
  vehicle *temp;  // a temporary pointer to a vehicle
  for(int i = 1; i <= n; i++){  // create n vehicles and push them inside the list
    dest = rand()%(NSegs-current_segment+1) + current_segment; // vehicle, rationally, wants to go to a destination in [current_segment, NSegs]
    temp = new vehicle(dest, curr_segment);     // create a new vehicle
    pushFront(temp);              // push it in the vehicleList
  }
  cout << "A vehicle list has just been created!" << endl;  // vehicleList construction message
}
/* vehicleList class destructor */
vehicleList::~vehicleList(){
  cout << "Vehicle List is about to be destroyed" << endl;  // vehicleList destruction message
  delete head;  // call list's head destructor
}
/* print vehicleList */
void vehicleList::print() const {   // ( created, mainly for debugging reasons)
  cout << "Printing vehicleList ...." << endl;
  vehicle *temp = head;   // we start from the list's head
  while(temp){            // while temp != NULL (while we haven't reached the end of the list)
    temp->print();        // print the pointed vehicle
    temp = temp->next;    // point to the next vehicle
  }
}
/* push vehicle in the (front of the) list */
void vehicleList::pushFront(vehicle * &x){
  x->curr_segment = curr_segment; // vehicle *x is currently in the same segment with it's vehicleList
  if(head) head->prev = x;  // if there is a head, our (new) node is gonna be it's previous
  x->next = head;			      // new node's next node is going to be the current head
  head = x;                 // our new node
  noOfVehicles++;           // increase the number of list's vehicles
}
/* pop a vehicle out of the list (from the beginning of the list) */
vehicle* vehicleList::pop(){
  if(!head) return NULL;      		// empty list, nothing to be popped
  vehicle *temp = head;           // we pop from the front of the list
  if(head->next) head->next->prev = NULL; // if head is not the only node, it's next node will have no previous node
  head = head->next;              // new head is current head's next node
  temp->next = NULL;              // extracted node has no next...
  temp->prev = NULL;              // ...or previous nodes
  noOfVehicles--;                 // decreade the number of list's vehicles
  return temp;                    // pop node (essentially return it)
}
/* how many vehicles we have on this list */
int vehicleList::get_noOfVehicles(){
  return noOfVehicles;
}
/* extract vehicle from a list (to be passed into another) */
vehicle* vehicleList::pass(int segment_id){
  if(!head){              // if the list is empty
		return NULL;
	}
  vehicle *temp = head;   // temporary pointer to the head of the list
  vehicle *out = NULL;    // we currently have no vehicle to exit
  while(temp){            // we iterate the vehicleList
    if((temp->destination > segment_id) && (temp->ready)){ // if we find one that's ready and it has as a destination the segment where we are, it should exit
      if(head == temp){   // if temp points where head points
        if(head){         // if head, actually, points somewhere
          head = head->next;  // we go to it's next
        }
      }
      if(temp->next){         // if there is a next
        temp->next->prev = temp->prev; // next's previous is temp's previous
      }
      if(temp->prev){         // if there is a previous
        temp->prev->next = temp->next;  // previous' next is temp's next
      }
      out = temp;             // temp is about to pass
      temp = temp->next;      // temp points to the next VehicleList's node (next vehicle)
      out->next = NULL;       // out has no more a next...
      out->prev = NULL;       // ...nor a prev
      out->ready = false;     // and it's not ready anymore
      noOfVehicles--;         // we have one less vehicle to the VehicleList
      break;                  // there is no need to keep iterating, so we stop
    }
    else temp = temp->next;   // temp points to the next VehicleList's node (next vehicle)
  }
  return out;                 // return the vehicle that passes
}
/* a vehicle exits this list */
int vehicleList::exit(int dest){
  int counter = 0;
  vehicle *temp = head;   // temporary pointer to the head of the list
  vehicle *out;
  while(temp){            // we iterate the vehicleList
    if((temp->destination == dest) && (temp->ready)){ // if we find one that's ready and it has as a destination the segment where we are, it should exit
      counter++;          // we count how many vehicles exit
      if(head == temp){   // if temp points where head points
        if(head){         // if head, actually, points somewhere
          head = head->next;  // we go to it's next
        }
      }
      if(temp->next){         // if there is a next
        temp->next->prev = temp->prev; // next's previous is temp's previous
      }
      if(temp->prev){         // if there is a previous
        temp->prev->next = temp->next;  // previous' next is temp's next
      }
      out = temp;             // temp is about to exit
      temp = temp->next;      // temp points to the next VehicleList's node (next vehicle)
      out->next = NULL;       // out has no more a next...
      out->prev = NULL;       // ...nor a prev
      delete out;	            // exit
      out = NULL;             // we don't have any vehicle to exit anymore
      noOfVehicles--;         // we have one less vehicle to the VehicleList
    }
    else temp = temp->next;   // temp points to the next VehicleList's node (next vehicle)
  }
  if(!head){                  // if VehicleList is now empty
  	cout << "\nDiagraftikan OLA\n";
  }
  return counter;             // we return how many vehicles exited
}
/* set a percentage of vehicles ready to exit */
void vehicleList::prepare(){
  noOfVehicles = get_noOfVehicles();  // how many vehicles we currently have on the vehicleList
  int  i = 0, toBePrepared = (noOfVehicles*Percent)/100.0;  // we calculate how many vehicles we have to prepare
  vehicle* temp = head;   // temporary pointer to the head of the list
  while(temp && i < toBePrepared){  // we iterate the list if we still have vehicles to prepare
    temp->ready = true;             // we prepare the vehicle
    i++;                            // we have prepared one more vehicle
    temp = temp->next;              // we go to the next vehicle
  }
}
/* how many vehicles are ready */
int vehicleList::get_num_of_ready() const {
    vehicle *temp = head;   // start counting from the head
    int counter = 0;
    while(temp){            // iterate list
      if(temp->ready) counter++;  // if a vehicle is ready, increase counter by 1
      temp = temp->next;          // go to the next vehicle
    }
    return counter;
}
/* add more vehicles to this list */
void vehicleList::more_vehicles(int current_segment){
	int x = rand()%3+1; 		 // we add 1-3 vehicles
	for(int i = 1; i <= x; i++){
		int dest = rand()%(NSegs-current_segment+1) + current_segment; // vehicle, rationally, wants to go to a destination in [current_segment, NSegs]
		vehicle *temp = new vehicle(dest, -1);  // create a new vehicle, for a waitLine, in a toll
		pushFront(temp);                    // push it in the list
	}
}

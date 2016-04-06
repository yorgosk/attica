/*
File: header.h
Purpose: The header file for our project
*/
#ifndef __HEADER__
#define __HEADER__

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

extern int N, NSegs, K, Percent;

struct vehicle{
	vehicle *next;		// next vehicle
	vehicle *prev;		// previous vehicle
	int destination; 	// (id) number of destination-segment
	int curr_segment;	// (id) number of current segment
	bool ready; 			// readiness status
	vehicle(int, int, bool j = false);	// vehicle struct constructor
	~vehicle();										// vehicle struct destructor
	void print() const;						// vehicle print function
};

class vehicleList{
	vehicle *head;		// list's head
	int noOfVehicles;	// number of vehicles (in this list)
	int curr_segment;	// (id) number of current segment
public:
	vehicleList(int, int, bool toll = false);	// vehicleList class constructor
	~vehicleList();														// vehicleList class destructor
	void print() const;												// print vehicleList
	void pushFront(vehicle* &);								// push vehicle in the (front of the) list
	int get_noOfVehicles();										// how many vehicles we have on this list
	vehicle* pop();														// pop a vehicle out of the list (from the beginning of the list)
	int exit(int);														// a vehicle exits this list
	vehicle* pass(int);												// extract vehicle from a list (to be passed into another)
	void prepare();														// set a percentage of vehicles ready to exit
	int get_num_of_ready() const;							// how many vehicles are ready
	void more_vehicles(int );									// add more vehicles to this list
};

class tollList{
	struct toll{
		int id;									// toll's id
		int entr_id;						// entrance's id
		bool is_electronic;			// is the toll electronic (true) or not (false)
		int noOfWaiting;				// how many vehicles are waiting
		vehicleList* waitline;	// list of the vehicles that are waiting to enter
		toll *next;							// next toll
		void more_vehicles();		// add more vehicles to the waitline
		int get_number_of_cars() const;	// get number of vehicles waiting to enter
		toll(int, int);					// toll struct constructor
		~toll();								// toll struct destructor
	};
	int numOfTolls;		// number of tolls in the tollList
	toll *head;				// list's head
	int id;						// list's id
public:
	tollList(int);		// tollList class constructor
	~tollList();			// tollList class destructor
	int get_number_of_cars() const;		// get number of vehicles waiting at the tolls
	vehicle* enter(bool &,int &);			// extract a vehicle (which is gonna enter the highway)
	void pushFront(toll* &);					// add toll to the tollList
	int get_employee_tolls() const;		// get number of tolls with employees
	int get_electronic_tolls() const;	// get number of electronic tolls
	void more_vehicles();							// add more vehicles to the waitlines
};

class entrance{
	int id;					// entrance's ID
	int noOfTolls;	// genika ari8mos diodiwn
	tollList *tL;		// list of entrance's tolls
public:
	entrance(int, int);			// entrace's constructor
	~entrance();						// entrance's destructor
	vehicle* enter(bool &,int & );	// a vehicle is popped from an entrance's vehicleList (to enter the highway)
	int get_number_of_cars() const;	// get number of vehicles waiting at tolls
	int get_id() const;							// get entrance's ID
	void more_vehicles();						// add more vehicles to the entrance's tolls
};

class segmentList{
	class segment{
	public:
		////////////////////////
		int id;									// segment's id
		vehicleList *list;			// a list of the vehicles that move inside a segment
		entrance *entr;					// segment's entrance
		int MAXVEHICLES;				// maximum number of vehicles that can fit into this segment
		int VEHICLENUM;					// number of vehicles inside this segment
		int kapa;								// K for this specific segment
		segment* next;					// next segment
		segment* prev;					// previous segment
		////////////////////////
		segment(int);						// segment class constructor
		~segment();							// segment class destructor
		int enter();						// vehicles enter a segment
		void exit();						// vehicles exit a segment
		int pass();							// vehicles pass from a segment to it's next
		void print() const;			// print segment
		int get_no_of_vehicles() const;	// get current number of vehicles in the segment
		void operate();					// operate a segment
		bool is_empty() const;	// check if a segment is empty
		void refreshVEHICLENUM();	// refresh the current number of vehicles in the segment
	};
	segment *head;						// head of the segmentList
	segment *tail;						// tails of the segmentList
	int noOfSegments;					// number of segments in the segmentList
public:
	segmentList();						// segmentList class constructor
	~segmentList();						// segmentList class destructor
	void operate();						// operate segmentList
	void pushBack(segment* &);	// insert a segment in the end of the segmentList
	void print() const;				// print segmentList
	int get_number_of_cars() const;	// get number of cars in the segmentList
	void prepare();							// prepare cars in the segmentList (changing readiness status)
	void refresh_VEHICLENUMS();	// refresh the current number of vehicles in all the segments
};

class attica{
	segmentList *sL;	// list of the highway segments
	int cars;					// number of cars in the highway
public:
	attica();					// highway constructor
	~attica();				// highway destructor
	void operate();		// operate highway
};

#endif

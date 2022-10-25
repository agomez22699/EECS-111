#ifndef __TYPES_P2_H
#define __TYPES_P2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

#define EMPTY        0
#define WOMENPRESENT 1
#define MENPRESENT   2

class Person
{

	int gender; // 0: male 1: female
	std::string str_gender;
	struct timeval t_create;
	struct timeval t_start;
	struct timeval t_end;
	long time_to_stay_ms;

	unsigned long order;
	unsigned long use_order;

public:
	Person();
	
	void set_gender(int data);
	int get_gender(void);

	void set_order(unsigned long data);
	unsigned long get_order(void);

	void set_use_order(unsigned long data);
	unsigned long get_use_order(void);

	void set_time(long data);

	unsigned long acquire_time(void);

	int ready_to_leave(void);


	void start(void);
	void complete(void);
};
// Class for the restroom
// You may need to add more class member variables and functions
class Restroom {
	int status;
	int number;
	int switchStat;
	int summation;
	int countMen;
	int countWomen;
	// You need to define the data structure to
    // save the information of people using the restroom
	// You can probebly use Standard Template Library (STL) vector
public:
	Restroom(){
		status = EMPTY;
		countMen = 0;
		countWomen = 0;
		summation = 0;
		switchStat = 0;
	}
	vector<Person> que_vector; 
	vector<Person> restroom_vector;

	void set_input(int data);
	int get_input(void);

	// You need to use this function to print the Restroom's status
	void print_status(void);
	void set_status(int data);
	int get_status(void);

	// Call by reference
	// This is just an example. You can implement any function you need
	void add_person(Person& p);
	void remove_person(int a);
	void status_changed(Person& p);

	void woman_wants_to_enter(Person& p);
	void man_wants_to_enter(Person& p);
	void woman_leaves(Person& p);
	void man_leaves(Person& p);
};
#endif
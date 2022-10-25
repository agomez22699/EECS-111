#include "types_p2.h"
#include "utils.h"



void Person::set_gender(int data) { gender = data; }
int Person::get_gender(void)      { return gender; }

void Person::set_order(unsigned long data) { order = data; }
unsigned long Person::get_order(void)      { return order; }

void Person::set_use_order(unsigned long data) { use_order = data; }
unsigned long Person::get_use_order(void)      { return use_order; }

void Person::set_time(long data) { time_to_stay_ms = data; }
unsigned long Person::acquire_time(void){return time_to_stay_ms;}
int Person::ready_to_leave(void) {
	struct timeval t_curr;
	gettimeofday(&t_curr, NULL);

	if (get_elasped_time(t_start, t_curr) >= time_to_stay_ms) { return 1; }
	else { return 0; }
}

void Person::start(void) {
	gettimeofday(&t_start, NULL);
	printf("(%lu)th person enters the restroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_start));
}

void Person::complete(void) {
	gettimeofday(&t_end, NULL);
	printf("(%lu)th person comes out of the restroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_end));
	printf(" - (%lu) milliseconds after using the restroom\n", get_elasped_time(t_start, t_end));
}

Person::Person() {gettimeofday(&t_create, NULL);}

void Restroom::set_input(int data){number = data;}
int Restroom::get_input(void) {return number;}
void Restroom::set_status(int data){status = data;}
int Restroom::get_status(void){return status;}

// You need to use this function to print the Restroom's status
void Restroom::print_status(void) {
	if(status == 1){
		cout<<"(WomanPresent): Total: "<<summation<<" (Men: "<<countMen<<", Women: "<<countWomen<<")"<<endl;
	}
	else if (restroom_vector.size() == 0 || status == 0){
		cout<<"(Empty): Total: "<<summation<<" (Men: "<<countMen<<", Women: "<<countWomen<<")"<<endl;
	}
	else {
		cout<<"(MenPresent): Total: "<<summation<<" (Men: "<<countMen<<", Women: "<<countWomen<<")"<<endl;
	}
}

// Call by reference
// This is just an example. You can implement any function you need
void Restroom::add_person(Person& p) {
	int size;

	restroom_vector.push_back(p);

	size = restroom_vector.size() - 1;
	restroom_vector[size].start();

	if(p.get_gender() == 0){
		countMen = countMen + 1;
		summation = summation + 1;
	}
	else{
		countWomen = countWomen + 1;
		summation = summation + 1;
	}
}

void Restroom::remove_person(int a){
	if(restroom_vector[a].get_gender() == 0){
		status_changed(restroom_vector[a]);

		countMen = countMen - 1;
		summation = summation - 1;

		restroom_vector.erase(a + restroom_vector.begin());

		Person reg = restroom_vector[a];

		man_leaves(reg);
	}
	else{
		status_changed(restroom_vector[a]);

		countWomen = countWomen - 1;
		summation = summation - 1;

		restroom_vector.erase(a + restroom_vector.begin());

		Person reg = restroom_vector[a];
		woman_leaves(reg);

	}

	if(restroom_vector.size() == 0){
		set_status(0);
	}
}

void Restroom::status_changed(Person& p){
	int tempy;
	tempy = status;

	if(restroom_vector.size() == 0){
		status = 0;
	}
	else {
		if(p.get_gender() == 0){
			status = MENPRESENT;
		}
		else{
			status = WOMENPRESENT;
		}
	}

	if(status == tempy){
		switchStat = 0;
	}
	else{
		switchStat = 1;
	}
}

void Restroom::woman_wants_to_enter(Person& p){
	if(p.get_gender() == 1 && status == WOMENPRESENT){
		cout<<"[Queue] Send (Woman) into the restroom (Stay "<< p.acquire_time()<< "ms), Status:";	
	}
	else if(p.get_gender() == 1 && status == EMPTY){
		cout<<"[Queue] Send (Man) into the restroom (Stay "<<p.acquire_time()<<"ms), Status: ";
	}
	print_status();
	add_person(que_vector[0]);
}

void Restroom::man_wants_to_enter(Person& p){
	if(p.get_gender() == 0 && status == MENPRESENT){
		cout<<"[Queue] Send (Man) into the restroom (Stay "<<p.acquire_time()<< "ms), Status:";
	}
	else if(p.get_gender() == 0 && status == EMPTY){
		cout << "[Queue] Send (Man) into the restroom (Stay " << p.acquire_time() << "ms), Status: ";
	}
	print_status();
	add_person(que_vector[0]);
}

void Restroom::woman_leaves(Person& p){
	if(switchStat == 1){
	cout<< "[Restroom] (Woman) left the restroom. Status is changed, Status is ";	
	}
	else {
		cout<<"[Restroom] (Woman) left the restroom. Status is ";
	}
	print_status();
}

void Restroom::man_leaves(Person& p){
	if(switchStat == 1){
	cout<<"[Restroom] (Man) left the restroom. Status is changed, Status is ";	
	}
	else{
		cout<<"[Restroom] (Man) left the restroom. Status is ";
	}
	print_status();
}
#include "p2_threads.h"
#include "utils.h"
using namespace std;

extern struct timeval t_global_start;
extern Restroom stallVar;
extern pthread_mutex_t mutex;

void *newPerson(void *parameter){
	struct timeval cTime;
	srand(time(NULL));
	int summation;
	int numberMen;
	int numberWomen;
	summation = 2 * stallVar.get_input();
	numberMen = stallVar.get_input();
	numberWomen = numberMen;
	for (int a = 0; summation > a; a++){
		int t;
		t = 3 + (rand() % 10);
		Person personVar;
		if(numberWomen == 0){
			personVar.set_gender(0);
		}
		else if (numberMen == 0){
			personVar.set_gender(1);
		}
		else {
			int temp = rand() % 2;
			personVar.set_gender(temp);
		}
		//we want to order personVar
		personVar.set_order(1 + a);

		if (10 < t){
			int tempy;
			tempy = t - 10;
			t = t - tempy;
		}
		//we want to have a time between 3 and 10ms
		personVar.set_time(t);
		if( personVar.get_gender() == 1 ){
			numberWomen = numberWomen - 1;
		}
		else{
			numberMen = numberMen - 1;
		}
		// we are locking the thread
		pthread_mutex_lock(&mutex);
		//we are going to push the person down the waiting vector
		stallVar.que_vector.push_back(personVar);
		//we are unlokcing the thread
		pthread_mutex_unlock(&mutex);
		//sleep between 1 and 5 ms
		usleep(MSEC((1 + rand() % 5)));
	}
	//we want to end the thread
	pthread_exit(0);
}

void *enterStall(void *parameter){
	struct  timeval cTime;
	srand(time(NULL));
	int isMoving = 0;
	int counter = 0;
	int summation;
	summation = 2 * stallVar.get_input();

	while(summation != isMoving){
		if(stallVar.que_vector.size() != 0){
			pthread_mutex_lock(&mutex);
			gettimeofday(&cTime, NULL);
			if(stallVar.que_vector[0].get_gender() == 0){
				if(stallVar.get_status() != WOMENPRESENT){
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					stallVar.man_wants_to_enter(stallVar.que_vector[0]);
					counter = counter + 1;
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					cout<<"[Restroom] (Man) goes into the restroom, State is ";
					stallVar.status_changed(stallVar.que_vector[0]);
					stallVar.print_status();
					stallVar.que_vector.erase(stallVar.que_vector.begin());
					isMoving = isMoving + 1;
				}
			}

			else{
				if(stallVar.get_status() != MENPRESENT){
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					stallVar.woman_wants_to_enter(stallVar.que_vector[0]);
					counter = counter + 1;
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					cout<<"[Restroom] (Women) goes into the restroom, State is ";
					stallVar.status_changed(stallVar.que_vector[0]);
					stallVar.print_status();
					stallVar.que_vector.erase(stallVar.que_vector.begin());
					isMoving = isMoving + 1;
				}
			}
			pthread_mutex_unlock(&mutex);
		}
	}
	pthread_exit(0);
}

void *leaveStall(void *parameter){
	struct timeval cTime;
	int summation;
	summation = 2 * stallVar.get_input();

	while(summation != 0){
		for (int a = 0; stallVar.restroom_vector.size() > a; a++){
			if(stallVar.restroom_vector[a].ready_to_leave()){
				pthread_mutex_lock(&mutex);
				gettimeofday(&cTime, NULL);
				if(stallVar.restroom_vector[a].get_gender() == 0){
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					stallVar.remove_person(a);
					summation = summation - 1;
					a = a - 1;
				}
				else{
					cout<<"["<<get_elasped_time(t_global_start, cTime)<<"ms]";
					stallVar.remove_person(a);
					summation = summation - 1;
					a = a - 1;
				}

				pthread_mutex_unlock(&mutex);
			}

		}
	}
	pthread_exit(0);
}
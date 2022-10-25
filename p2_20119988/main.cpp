#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "types_p2.h"
#include "p2_threads.h"
#include "utils.h"

pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
Restroom stallVar;
struct timeval t_global_start;

int main(int argc, char** argv)
{
	int number;
	// This is to set the global start time
	gettimeofday(&t_global_start, NULL);
	// we want to have 3 threads
	pthread_t tid[2];
	int status = 0;
	int work = 0;

	if (argc != 2){
		cout << "[ERROR] Expecting 1 argument, but got (X)." <<endl;
		cout << "[USAGE] p2_exec <number>"<<endl;
		return 0;
	}
	else if(argc == 2){
		number = atoi(argv[1]);
	} 

	stallVar.set_input(number);

	// this thread is responisble for making new People
	if (pthread_create(&tid[0], NULL, newPerson, NULL)){
		fprintf(stderr, "Error in making 'newPerson' thread \n");
	}
	else if (pthread_create(&tid[1], NULL, enterStall, NULL)){
		fprintf(stderr, "Error in making 'moveInside' thread \n");
	}
	else if (pthread_create(&tid[2], NULL, leaveStall, NULL)){
		fprintf(stderr, "Error in making the 'leaveStall' thread \n");
	}

for ( int a = 0; 3 > a; a++){
	if (pthread_join(tid[a], NULL)){
		fprintf(stderr, "Error in joining threads \n");
		}
	}
	return 0;
}
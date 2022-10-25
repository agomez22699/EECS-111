#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <iostream>
using std::ios;
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <pthread.h>
#include <unistd.h>
#include <string.h>
using std::string;
#include <vector>
using std::vector;
using std::copy;
#include <sstream>
using std::stringstream;
#include<iomanip>

#include "p1_threads.h"
void get_statistics(std::string class_name[], int num_processes, int num_threads);

#endif

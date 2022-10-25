#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/syscall.h> 
#include <iostream>
#include<sys/types.h>
#include <string.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

#include "p1_process.h"

typedef struct {
	char studentID[16];
	double grade;
}studentDictionary;

typedef struct {
	int threadVAL;
	int first;
	int last;
	studentDictionary *studentINFO;
}mergeSort_Parameters;


bool comparisonCheck(studentDictionary left, studentDictionary right);

typedef bool(*cFunction)(studentDictionary, studentDictionary);

void merge(int min, int middle, int max,studentDictionary oldArray[], cFunction compare);

void* merge_Sort(void* arg);

#endif

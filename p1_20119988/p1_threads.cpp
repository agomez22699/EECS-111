/* Adrian Gomez
SID:20119988
EECS 111
Lab 1
5/3/2021
p1_threads.cpp
*/
#include "p1_threads.h"
// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function

 bool comparisonCheck(studentDictionary left, studentDictionary right){

       return right.grade > left.grade; 
}

 void merge(int min, int middle, int max, studentDictionary oldArray[], cFunction compare){   
    //declarations of variables
     int k;
     int newMin;
     int newMiddle;
     newMiddle = middle;
     newMin = min;
     k = 0;

    //copying new array info
     studentDictionary* newArray = new studentDictionary[max - min];

    //if the array is not properly formed, do not run merge sort
     if (min >= middle) {
         return;
    }
    else if (oldArray == NULL){
        return;
    }
    else if (middle >= max){
        return;
    }
  
    //if the array is properly formatted, perform a comparison check
    while (middle > newMin && max > newMiddle) {

        if (compare(oldArray[newMin],  oldArray[newMiddle])){ 

            memcpy(k + newArray, newMiddle + oldArray , sizeof(studentDictionary));

            ++newMiddle;//increment
        }
        else{

            memcpy(k + newArray , newMin + oldArray , sizeof(studentDictionary));

            ++newMin; //increment
        }
        ++k; //increment 
    }

    //left side of the array
    if (newMin < middle){

        memcpy(newArray + k, oldArray + newMin, sizeof(studentDictionary)*(middle-newMin));

    }
    //right side of the array
    else if (newMiddle < max){
        memcpy(newArray + k, oldArray + newMiddle, sizeof(studentDictionary)*(max-newMiddle));
    }
 
    //final memory operation
    memcpy(oldArray + min, newArray, sizeof(studentDictionary)*(max-min));
 
    //de allocate the array
    delete [] newArray;
    //clear the data from the memory of the array 
    newArray = NULL;
 }
 
void* merge_Sort(void* arg){
    //declariations of variables
    int min;
    int max;
    int tVAL;

    //get the values for structure
    mergeSort_Parameters *pointer = (mergeSort_Parameters*)arg;
    studentDictionary* oldArray = pointer -> studentINFO;
    min = pointer -> first;
    max = pointer -> last;
    tVAL = pointer -> threadVAL;

   if(1 + min < max) {
    pthread_t tid0;
    pthread_t tid1; 
    int middle;
    int value_0;
    int value_1;
    tid0 = tid1 = value_0 = value_1 = -1;
    middle = (min + max) / 2;

    mergeSort_Parameters *pointer_0 = new mergeSort_Parameters;
    pointer_0 -> first = min; // assign the min value to the first value
    pointer_0 -> last = middle; // assign the last value to the middle
    pointer_0 -> studentINFO = oldArray; // transfer the array
    pointer_0 -> threadVAL = tVAL-2; //decreases the thread counter

    mergeSort_Parameters *pointer_1 = new mergeSort_Parameters;
    pointer_1 -> first = middle; // assign the middle value to the first value
    pointer_1 -> last = max; // assign the last value to the max
    pointer_1 -> studentINFO = oldArray;// transfer the array
    pointer_1 -> threadVAL = tVAL-2; //decreases the thread counter

    if(0 <tVAL){
        value_0 = pthread_create(&tid0, NULL, merge_Sort, pointer_0);
    } 
    else{merge_Sort(pointer_0);}

    if(1 < tVAL){ value_1 = pthread_create(&tid1, NULL, merge_Sort, pointer_1);} 
    else {merge_Sort(pointer_1);}

    if(value_0 == 0){pthread_join(tid0, NULL);}
    if(value_1 == 0){ pthread_join(tid1, NULL);}
    
    merge(min, middle, max, oldArray, comparisonCheck);
   }
   }
/* Adrian Gomez
SID:20119988
EECS 111
Lab 1
5/3/2021
p1_process.cpp
*/

#include "p1_process.h"

double medianAlgorithm(studentDictionary *array, int capacity){
	double average;
	average = 0;
	int z;
	z = capacity/2;
	double tempy;
	tempy = 0;

	if(0 >= capacity) {return average;}
	else if(capacity % 2 == 0){
		tempy = ((array[z].grade + array[z-1].grade)/2);
		return tempy;
	}
	else{
		tempy = array[capacity/2].grade;
		return tempy;
	}
}

double averageAlgorithm(studentDictionary *array, int capacity){

	int x;
	double temp;
	double average;
	average = 0;
	temp = 0;

	if(0 >= capacity){return average;}

	for(int x = 0; x < capacity; x++){
		average += array[x].grade;
	}

	temp = average/capacity;

	return temp;
}


double s_deviationAlgorithm(studentDictionary *array, double average, int capacity){
	int v;
	double summation;
	summation = 0;
	double tempo;
	tempo = 0;

	if(0 >= capacity){return 0.0;}

	for(v = 0; capacity > v; v++){
		summation += (array[v].grade-average)*(array[v].grade-average);
	}

	tempo = sqrt(summation/capacity);
	return tempo;
}

void fileHelper(string sortedOutput, string statsOutput, int capacity, studentDictionary *array){
		double middle;
		double deviation;
		double average;
		ofstream out_file_stream;

		out_file_stream.open(sortedOutput.c_str(), ios::out);
		out_file_stream << "Rank" << ',' << "Student ID" << ',' << "Grade" <<endl;
		out_file_stream.setf (out_file_stream.showpoint);
		out_file_stream.precision(10); 
		out_file_stream.setf(ios::fixed); 
		
		int t = 0;
		for(int t = 0; capacity > t; t++){
		 out_file_stream << 1+t <<','<< array[t].studentID << ',' <<array[t].grade << endl;
		}
	 	out_file_stream.close();


		average = averageAlgorithm(array, capacity);
		middle = medianAlgorithm(array, capacity);
		deviation = s_deviationAlgorithm(array, average, capacity);


		out_file_stream.open(statsOutput.c_str(), ios::out);
		out_file_stream<< "Average" << ',' << "Median" << ',' << "Std. Dev" <<endl;
		out_file_stream.setf (out_file_stream.showpoint);
		out_file_stream.precision(3); 
		out_file_stream.setf(ios::fixed); 
		out_file_stream<<average <<','<<middle<<','<<deviation<<endl;
		out_file_stream.close();
		delete[] array;
}


void cProcess(string fName[], int num_threads, int fileNo){

	printf("Child process is created. (pid: %d)\n", getpid());

	int u;

	for(u = 0; fileNo > u; u++){

		vector<studentDictionary> vectorGradeInfo;
		string lVar;
		string stringVar = string("./input/") + fName[u] + string(".csv");
		int capacity;

		ifstream inFile(stringVar.c_str(), ios::in);
		getline(inFile, lVar);

		while(getline(inFile, lVar)){

			stringstream stStream(lVar);
			string t_string[2];
			studentDictionary studentVar;

			for(int b = 0; b < 2; b++) {getline(stStream, t_string[b], ',');}

			memset(studentVar.studentID, 0, sizeof(studentVar.studentID));
			memcpy(studentVar.studentID, t_string[0].c_str(), t_string[0].length());
			studentVar.grade = atof(t_string[1].c_str());
			vectorGradeInfo.push_back(studentVar);
		}

		capacity=vectorGradeInfo.size();
		studentDictionary *array = new studentDictionary[capacity];
		std::copy(vectorGradeInfo.begin(), vectorGradeInfo.end(), array);
		
		pthread_t thread_id;
		mergeSort_Parameters *pointerMerge = new mergeSort_Parameters;
		pointerMerge -> first = 0; 
		pointerMerge -> last = capacity;
		pointerMerge -> studentINFO = array;
		pointerMerge -> threadVAL = num_threads-1;

		pthread_create(&thread_id, NULL, merge_Sort, (void*)pointerMerge);
		pthread_join(thread_id, NULL);
		delete pointerMerge;

		string sortedOutput = string("./output/")+fName[u]+string("_sorted.csv");
		string statsOutput = string("./output/")+fName[u]+string("_stats.csv");
		fileHelper(sortedOutput, statsOutput, capacity, array);
	}
	printf("Child process is terminated. (pid: %d)\n", getpid());
	exit(0);
}


void get_statistics(string class_name[], int num_processes, int num_threads) {
	int tempVar2 = num_processes + 1;
	int *filesCount = new int[tempVar2];
	int progress;
	// You need to create multiple processes here (each process
	// handles at least one file.)
	
	
	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 
	
	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.

	for(int p = 0; num_processes > p; p++){filesCount[p+1] = 5 / num_processes;}
	for(int e = 0 ; e < 5 % num_processes; e++){filesCount[e+1]++;}
	filesCount[0] = 0;
	
	for(int i = 1; i <= num_processes; i++){
		int tempy;

		if((tempy = fork()) == 0){
			cProcess(filesCount[i - 1] + class_name, num_threads, filesCount[i]);
			exit(0);
		} 
		else if(tempy < 0){
			printf("Fork was not created successfully\n");
			return;
		}
	}
	while(wait(&progress) > 0);
}
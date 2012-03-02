#include "Job.h"
#include <cstddef>
#include <stdio.h>
#include <iostream>
using namespace std;

Job::Job():size(0),opCount(0), curOp(0), ops(NULL) {

}

Job::~Job() {
	delete [] ops;
}

void Job::set(int i, int s){
	id = i;
	size = s;
	ops = new Operation[s];
}


int Job::addOp(int m, int d){
	if(opCount >= size)
		return -1;
	ops[opCount].machine = m;
	ops[opCount].duration = d;
	++opCount;
	return 0;
}

Operation * Job::current() {
	return &ops[curOp];
}

int Job::moveOn() {
	if(curOp >= size)
		return -1;
	++curOp;
	return 0;
}

int Job::isFinished() {
	if(curOp >= size)
		return 1;
	return 0;
}

void Job::printSolution() {
	char word[20];
	for(int i = 0; i < size; ++i) {
		sprintf(word, "%-3d %-4d", ops[i].machine,ops[i].start);
		cout << word;
	}
	cout << endl;
}

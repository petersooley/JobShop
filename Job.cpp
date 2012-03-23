#include "Job.h"
#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Job::Job():size(0),opCount(0), curOp(0), nextStart(0), ops(NULL) {

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

int Job::scheduleCurOp(int opStart) {
	ops[curOp].start = opStart;
	nextStart = opStart + ops[curOp++].duration;
	return 0;
}
void Job::unschedulePrevOp() {
	// curOp is pointing to the next op to-be-scheduled,
	// so go back to the last scheduled op and unschedule it
	// by setting it's start to -1.
	ops[--curOp].start = -1;

	// When curOp is 0, no ops have been scheduled
	// so we can start as early as 0
	if(curOp == 0)
		nextStart = 0;

	// If we have ops scheduled, the earliest we can
	// start is at the end of the latest scheduled job
	else
		nextStart = ops[curOp - 1].start + ops[curOp - 1].duration;

}

int Job::isFinished() {
	if(curOp >= size)
		return 1;
	return 0;
}

void Job::printSolution() {
	cout << getSolution();
}
string Job::getSolution() {
	ostringstream solution;
	char word[20];
	for(int i = 0; i < size; ++i) {
		sprintf(word, "%-3d %-4d", ops[i].machine,ops[i].start);
		solution << word;
	}
	solution << endl;
	return solution.str();
}

int Job::getCurOpDuration() {
	return ops[curOp].duration;
}
int Job::getCurOpMachine() {
	return ops[curOp].machine;
}

int Job::getNextStart() {
	return nextStart;
}


#include "JobScheduler.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

JobScheduler::JobScheduler() {

}

JobScheduler::JobScheduler(string in):jobs(NULL) {

	ifstream inf(in.c_str());
	if(inf.fail()) {
		cout << "Could not open " << in << endl;
		exit(1);
	}
	inf >> numJobs;
	inf >> numMachs;

	jobs = new Job[numJobs];
	machines = new Machine[numMachs];

	for(int i = 0; i < numJobs; ++i)
		jobs[i].set(i,numMachs);

	int machine;
	int duration;
	int job = 0;
	int ops = 0;
	while(inf.good()) {
		inf >> machine;
		inf >> duration;
		jobs[job].addOp(machine, duration);
		++ops;
		if(ops % numMachs == 0)
			++job;
	}

	inf.close();
}

JobScheduler::~JobScheduler() {
	delete [] jobs;
	delete [] machines;
}

void JobScheduler::printSolution(string output) {

	// eventually we'll print this into the actual output file

	for(int i = 0; i < numJobs; ++i) {
		jobs[i].printSolution();
	}
}

int JobScheduler::findSchedule() {
	return schedule();
}

int JobScheduler::schedule() {
	// See if there are still operations available
	int stillHaveOps = 0;
	for(int a = 0; a < numJobs; ++a) {
		if(!jobs[a].isFinished()) {
			stillHaveOps = 1;
			break;
		}
	}
	// If we're done, return the score. The machine with the
	// longest duration of ops running on it.
	if(!stillHaveOps) {
		int score = 0;
		int current;
		for(int b = 0; b < numMachs; ++b) {
			current = machines[b].score();
			score = current > score ? current : score;
		}
		return score;
	}
	

	return 0;
}

int main(int argc, char*argv[]) {
	if(argc != 3) {
		cout << "Usage: ./JobScheduler <input_file> <output_file>\n";
		exit(1);
	}

	JobScheduler js(argv[1]);
	int score = 0;
	score = js.findSchedule();
	js.printSolution(argv[2]);

	return 0;
}

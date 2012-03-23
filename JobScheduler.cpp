#include "JobScheduler.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
using namespace std;

JobScheduler::JobScheduler() {

}

JobScheduler::JobScheduler(string in):bestScore(MAX),currentScore(0),jobs(NULL),machines(NULL){

	ifstream inf(in.c_str());
	if(inf.fail()) {
		cout << "Could not open " << in << endl;
		exit(1);
	}
	inf >> numJobs;
	inf >> numMachs;

	jobs = new Job[numJobs];
	machines = new int[numMachs];

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

	opCount = ops - 1;
	inf.close();
}

JobScheduler::~JobScheduler() {
	delete [] jobs;
	delete [] machines;
}

void JobScheduler::printSolution(string output) {

	// eventually we'll print this into the actual output file

	cout << solution << endl;
	cout << "Score: " << bestScore << endl;
}

int JobScheduler::doSchedule() {

	schedule();
	return bestScore;
}

int JobScheduler::schedule() {
	// If we're done, return the score which is the machine with the
	// longest duration of ops running on it.
	if(opCount == 0)
		return currentScore - 1;
	
	for(int c = 0; c < numJobs; ++c) {
		if(jobs[c].isFinished())
			continue;

		int jobNextStart = jobs[c].getNextStart();
		int curOpMachine = jobs[c].getCurOpMachine();
		int curOpDuration = jobs[c].getCurOpDuration();
		int machineNextStart = machines[curOpMachine];
		int opStart = machineNextStart > jobNextStart ? machineNextStart : jobNextStart;

		// DO
		jobs[c].scheduleCurOp(opStart);
		machines[curOpMachine] = opStart + curOpDuration;
		--opCount;
		int oldCurrentScore = currentScore;
		if(machines[curOpMachine] > currentScore) {
			currentScore = machines[curOpMachine];
		}

		int score = schedule();
		if(score != -1 && score < bestScore) {
			bestScore = score;
			saveState();
		}


		// UNDO
		jobs[c].unschedulePrevOp();
		machines[curOpMachine] = machineNextStart;
		currentScore = oldCurrentScore;
		++opCount;
	}

	return bestScore;
}

void JobScheduler::saveState() {
	ostringstream out;
	for(int i = 0; i < numJobs; ++i)
		out << jobs[i].getSolution();
	solution = out.str();
}

int main(int argc, char*argv[]) {
	if(argc != 3) {
		cout << "Usage: ./JobScheduler <input_file> <output_file>\n";
		exit(1);
	}

	JobScheduler js(argv[1]);
	js.doSchedule();
	js.printSolution(argv[2]);


	return 0;
}

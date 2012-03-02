#include "JobScheduler.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Job.h"
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
}

void JobScheduler::printSolution(string output) {

	// eventually we'll print this into the actual output file

	for(int i = 0; i < numJobs; ++i) {
		jobs[i].printSolution();
	}
}

int main(int argc, char*argv[]) {
	if(argc != 3) {
		cout << "Usage: ./JobPrinter <input_file> <output_file>\n";
		exit(1);
	}

	JobScheduler js(argv[1]);
	js.printSolution(argv[2]);

	return 0;
}

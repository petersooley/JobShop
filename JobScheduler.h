#ifndef JOBSCHEDULER_H_
#define JOBSCHEDULER_H_

#include <string>
#include "Job.h"
using namespace std;

class JobScheduler {
	public:
		JobScheduler();
		JobScheduler(string input);
		~JobScheduler();

		void printSolution(string output);
	private:
		int numJobs;
		int numMachs;
		Job * jobs;
};

#endif

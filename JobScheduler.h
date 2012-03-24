#ifndef JOBSCHEDULER_H_
#define JOBSCHEDULER_H_

#include <string>
#include "Job.h"
#include "Machine.h"
using namespace std;

class JobScheduler {
	public:
		JobScheduler();
		JobScheduler(string input);
		~JobScheduler();

		void printSolution(string output);
		int schedule();
	private:
		int numJobs;
		int numMachs;
		int bestScore;
		int numOps;
		int opCount;
		int currentScore;
		int bestIdleTime;
		int currentIdleTime;
		string solution;
		static const int MAX = 1000000;
		// An array of jobs
		Job * jobs;
		// An array to keep track of each
		int * machines;
		void saveState();
};

#endif

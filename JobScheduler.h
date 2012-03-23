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
		int doSchedule();
	private:
		int numJobs;
		int numMachs;
		int bestScore;
		int numOps;
		int opCount;
		int currentScore;
		string solution;
		static const int MAX = 10000;
		// An array of jobs
		Job * jobs;
		// An array to keep track of each
		int * machines;
		int schedule();
		void saveState();
};

#endif

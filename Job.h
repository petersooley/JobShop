#ifndef JOB_H_
#define JOB_H_

#include <string>
using namespace std;

struct Operation {
	int job;
	int machine;
	int duration;
	int start;
};

class Job {
	public:
		Job();
		~Job();

		void set(int id, int size);

		// Operations added to this job must be added in
		// sequential order.
		// -1 if ops array is full
		int addOp(int machine, int duration);

		// Schedule the current op to start at nextStart
		// and then move curOp forward.
		// -1 if you can't move on anymore
		int scheduleCurOp(int machineNextStart);
		void unschedulePrevOp();

		// 1 if finished, 0 if not
		int isFinished();

		void printSolution();
		string getSolution();

		int getCurOpDuration();
		int getCurOpMachine();
		int getNextStart();


	private:
		int id;
		int size;
		int opCount;
		int curOp;
		int nextStart;
		Operation * ops;
};

#endif

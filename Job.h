#ifndef JOB_H_
#define JOB_H_

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

		// Get a reference to the current operation in the list
		Operation * getReady();

		// Move on to the next operation, so that current() returns
		// a new operation.
		// -1 if you can't move on anymore
		int moveForward();
		void moveBackward();

		// 1 if finished, 0 if not
		int isFinished();

		void printSolution();

	private:
		int id;
		int size;
		int opCount;
		int curOp;
		Operation * ops;
};

#endif

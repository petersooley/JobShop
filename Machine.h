#ifndef MACHINE_H_
#define MACHINE_H_

#include "Job.h"

class Machine {
	public:
		Machine();
		~Machine();
		void addOp(Operation * op);
		void removeOp(Operation * op);
		// time until completion of all assigned operations
		int score();
	private:
		int nextStart;
};

#endif

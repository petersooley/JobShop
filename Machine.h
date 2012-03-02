#ifndef MACHINE_H_
#define MACHINE_H_

#include "Job.h"

class Machine {
	public:
		Machine();
		~Machine();
		void addOp(Operation * op);
	private:
		int nextStart;
};

#endif

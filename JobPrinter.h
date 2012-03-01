#ifndef __JOBPRINTER_H__
#define __JOBPRINTER_H__

#include <string>
using namespace std;

struct OpNode {
	OpNode(const int j, const int s, const int d, const int m);
	int job;
	int start;
	int duration;
	int machine;
	OpNode * next;
};

class JobPrinter {
	public:
		JobPrinter();
		JobPrinter(string input, string output);
		~JobPrinter();
		void print();

	private:
		OpNode * head;
		int nummachs;
		int numjobs;
		int lastSec;
		int addOperation(const int job, const int start, const int duration, const int machine);
		string pad(const int num);
		string pad(const char * s);
};


#endif

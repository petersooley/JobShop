#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "JobPrinter.h"

OpNode::OpNode(const int j, const int s, const int d, const int m) {
	job = j;
	start = s;
	duration = d;
	machine = m;
}


JobPrinter::JobPrinter() : head(NULL){

}

JobPrinter::JobPrinter(string input, string output) : head(NULL) {
	ifstream inf(input.c_str());
	ifstream outf(output.c_str());
	if(inf.fail()) {
		cout << "Could not open " << input << endl;
		exit(1);
	}
	if(outf.fail()) {
		cout << "Could not open " << output << endl;
		exit(1);
	}
	inf >> numjobs;
	inf >> nummachs;

	int machine1;
	int machine2;
	int start;
	int duration;
	int job = 0;
	int ops = 0;

	while(inf.good() && outf.good() && job < numjobs) {
		inf >> machine1;
		outf >> machine2;
		if(machine1 != machine2) {
			cout << "Error: input and output files don't match.\n";
			exit(1);
		}
		inf >> duration;
		outf >> start;

		if(!addOperation(job, start, duration, machine1)) {
			exit(1);
		}
		++ops;
		if(ops % nummachs == 0)
			++job;
	}

	inf.close();
	outf.close();
}

JobPrinter::~JobPrinter() {
	OpNode * grave;
	while(head) {
		grave = head;
		head = head->next;
		delete grave;
	}
}

/**
 * Inserts operations into a linked list sorted by start times. If two operations,
 * run at the same time and they aren't on the same machine, then sort them by machine.
 */
int JobPrinter::addOperation(const int job, const int start, const int duration, const int machine) {

	OpNode * data = new OpNode(job, start, duration, machine);

	if(!head) {
		head = data;
		head->next = NULL;
		return 1;
	}

	int mystart = head->start;
	int mymach = head->machine;
	if(mystart == start && mymach == machine) {
		cout << "Error can't run simultaneous operations on one machine.\n";
		exit(0);
	}
	if(mystart >= start) {
		data->next = head;
		head = data;
		lastSec = start + duration;
		return 1;
	}

	OpNode * previous = head;
	OpNode * current = head->next;
	while(current) {
		mystart = current->start;
		mymach = current->machine;
		if(mystart == start && mymach == machine) {
			cout << "Error can't run simultaneous operations on one machine.\n";
			exit(0);
		}
		if(mystart == start) {
			if(mymach < machine) {
				previous = current;
				current = current->next;
				continue;
			}
			else {
				previous = data;
				data->next = current;
				return 1;
			}
		}
		else if(mystart < start) {
			previous = current;
			current = current->next;
			continue;
		}
		previous->next = data;
		data->next = current;

		return 1;
	}

	previous->next = data;
	data->next = NULL;
	lastSec = start + duration;

	return 1;
}

void JobPrinter::print() {


	for(int i = 0; i < nummachs; ++i)
		cout << pad(i);
	cout << endl;

	cout << "  ";
	for(int j = 0; j < nummachs; ++j)
		cout << pad("-----");
	cout << endl;

	OpNode * current = head;
	for(int k = 0; k < 5; ++k) {
		cout << pad(" ");
		for(int l = 0; l < nummachs; ++l) {
			if(current->machine == l) {
				cout << pad(current->job);
				current= current->next;
			}
			else {
				cout << pad(" ");
			}
			cout << endl;
		}
	}


	OpNode * cur = head;
	while(cur) {
		cout << "Job " << cur->job
			<< ", machine "<< cur->machine
			<< ", start " << cur->start <<endl;
		cur = cur->next;
	}


}

string JobPrinter::pad(const int num) {
	char word[200];
	sprintf(word, "%8d",num);
	return word;
}

string JobPrinter::pad(const char* s) {
	char word[200];
	sprintf(word, "%8s",s);
	return word;
}



int main(int argc, char * argv[]) {

	if(argc != 3) {
		cout << "Usage: ./JobPrinter <input_file> <output_file>\n";
		exit(1);
	}

	JobPrinter jp(argv[1], argv[2]);
	jp.print();

	return 0;

}

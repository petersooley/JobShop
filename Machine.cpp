#include "Machine.h"

Machine::Machine():nextStart(0) {
}

Machine::~Machine() {
}

void Machine::addOp(Operation * op) {
	op->start = nextStart;
	nextStart += op->duration;
}
void Machine::removeOp(Operation * op) {
	op->start = -1;
	nextStart -= op->duration;
}

int Machine::score() {
	return nextStart - 1;
}

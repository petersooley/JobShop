#include "Machine.h"

Machine::Machine():nextStart(0) {
}

Machine::~Machine() {
}

void Machine::addOp(Operation * op) {
	op->start = nextStart;
	nextStart += op->duration;
}

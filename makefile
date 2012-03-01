CC = g++
CFLAGS = -g -Wall -c

OBJS = JobPrinter.o

JobPrinter: $(OBJS)
	$(CC) -o JobPrinter $(OBJS)

JobPrinter.o: JobPrinter.cpp
	$(CC) $(CFLAGS) JobPrinter.cpp JobPrinter.h

all: JobPrinter

clean:
	rm -f JobPrinter *.o *.gch

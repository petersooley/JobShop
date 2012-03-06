CC = g++
CFLAGS = -g -Wall -c

# JobPrinter...
#JobPrinter: JobPrinter.o
#	$(CC) -o JobPrinter JobPrinter.o

#JobPrinter.o: JobPrinter.cpp
#	$(CC) $(CFLAGS) JobPrinter.cpp JobPrinter.h

# JobScheduler...
OBJS = Job.o Machine.o JobScheduler.o

JobScheduler: $(OBJS)
	$(CC) -o JobScheduler $(OBJS)

JobScheduler.o: JobScheduler.cpp
	$(CC) $(CFLAGS) JobScheduler.cpp JobScheduler.h

Job.o: Job.cpp
	$(CC) $(CFLAGS) Job.cpp Job.h

Machine.o: Machine.cpp
	$(CC) $(CFLAGS) Machine.cpp Machine.h


all: JobPrinter JobScheduler

clean:
	rm -f JobScheduler JobPrinter *.o *.gch

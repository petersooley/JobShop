#!/usr/bin/python

import sys
import re
import os

if (len(sys.argv) != 2):
	print "usage: python genJobs.py <jobsSourceFile>"
	sys.exit(1);

sourcef = open(sys.argv[1], 'r')

pluses = re.compile("\+\+\+\+*");
ascii = re.compile("[A-Za-z]+");
line = sourcef.readline()
while(line != ''):
	if(pluses.search(line)):
		inputf = open("input.txt", 'w')
		while(True):
			next = sourcef.readline()
			if(pluses.search(next)):
				break
			if(ascii.search(next)):
				continue
			if(line == ""):
				continue	
			inputf.write(next)
		outputf = open("output.txt", 'w')
		os.system("./JobScheduler input.txt output.txt")
		sys.stdout.write("\n")
		inputf.close()
		outputf.close()
	line = sourcef.readline()

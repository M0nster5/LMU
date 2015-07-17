import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
import os
import sys
#open text file

def findAverage(file):
	count =0;
	s = 0;
	averages = []
	nums = []
	for line in file:
		if line == '\n':
			averages.append(s/count)
			count=0
			s = 0
		else:
			nums = line.split(" ")
			count+=1
			s += float(nums[1])

	print np.mean(averages)
print "How many simulations would you like to compare?"
numSimulation = int(raw_input())
print "performing simulations"
for i in range(0,numSimulation):
	os.system("./GillespieAlgorithm")
	file = open("outputBT.txt",'r')
	#put columns 0, 1, 2 in variables t, x, y
	findAverage(file)
	file.close
	file = open("outputC.txt",'r')
	findAverage(file)
	file.close



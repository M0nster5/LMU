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
	# plt.plot(averages,"ro")
	# plt.plot(500,np.mean(averages),"bo",ms=10)
	print np.mean(averages)
	return (averages)
print "How many simulations would you like to compare?"
numSimulation = int(raw_input())
print "performing simulations"
for i in range(0,numSimulation):
	plt.figure("Binary vs Composition "+str(i+1))
	print "running simulation",i+1
	os.system("./GillespieAlgorithm")
	file = open("outputBT.txt",'r')
	#put columns 0, 1, 2 in variables t, x, y
	bt = findAverage(file)
	file.close
	file = open("outputC.txt",'r')
	c = findAverage(file)
	file.close
	plt.plot(bt,"ro",c,"bo",alpha=.2)
	plt.plot(500,np.mean(bt),"ko",ms=50,alpha=.5)
	plt.plot(500,np.mean(c),"wo",ms = 50,alpha=.5)
plt.show()
	






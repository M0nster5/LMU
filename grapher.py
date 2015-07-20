import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
import os
#open text file
os.system("./GillespieAlgorithm")
file = open("outputBT.txt",'r')
#put columns 0, 1, 2 in variables t, x, y
tBT,xBT  = np.loadtxt(file, usecols=(0, 1), unpack=True)
file.close()
file = open("outputC.txt",'r')
tC,xC  = np.loadtxt(file, usecols=(0, 1), unpack=True)
evenT = np.linspace(0,5,len(tBT))
cmap = cm.jet
fig = plt.figure(1)
a = fig.add_subplot(211)
a.scatter(tBT,xBT,c=evenT,cmap=cmap, alpha = .05)
evenT = np.linspace(0,5,len(tC))
b = fig.add_subplot(212)
b.scatter(tC,xC,c=evenT,cmap=cmap, alpha = .05)
# plt.xlabel("Time")
# plt.ylabel("Position")
plt.show()

import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
#open text file
file = open("output.txt",'r')
#put columns 0, 1, 2 in variables t, x, y
t,x  = np.loadtxt(file, usecols=(0, 1), unpack=True)
evenT = np.linspace(0,5,len(t))
cmap = cm.jet
fig = plt.figure(1)
fig.clf()
ax = fig.add_subplot(1,1,1)
ax.scatter(t,x,c=evenT,cmap=cmap, alpha = .1)
# plt.xlabel("X")
# plt.ylabel("Y")
plt.show()
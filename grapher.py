import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

file = open("output.txt",'r')
t, x, y = np.loadtxt(file, usecols=(0, 1, 2), unpack=True)
evenT = np.linspace(0,5,len(t))
cmap = cm.jet
fig = plt.figure(1)
fig.clf()
ax = fig.add_subplot(1,1,1)
ax.scatter(x,y,c=evenT,cmap=cmap)
plt.xlabel("X")
plt.ylabel("Y")
plt.show()
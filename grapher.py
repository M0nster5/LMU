import matplotlib.pyplot as plt
import numpy as np

file = open("output.txt",'r')
t, p = np.loadtxt(file, usecols=(0, 2), unpack=True)
plt.plot(t,p)
plt.xlabel("Time")
plt.ylabel("Position")
plt.show()
# Import needed libraries
import matplotlib.pyplot as plt
import numpy as np

from qbstyles import mpl_style
mpl_style(dark=True)

# Define functios from the exercise
def f(x):
    return x**2 + x**4

def fp(x):
    return 2*x + 4*x**3

def fpa(x):
    h = .000001;
    return (f(x+h) - f(x))/(x+h-x)


# Create the values for the x axis
x = np.linspace(-10, 10, 1000)

# Plot the values of both functions using .5 as w
#plt.plot(x, f(x), color='#0099ff', label = "f")
#plt.plot(x, fpa(x), color='#0099ff', label = "f' (aproximate)")
plt.plot(x, fp(x), color='#0099ff', label = "f'")

cl = ["red", "yellow"]
its = [-2.9697, -2.18744, -1.58884, -1.12596, -0.764856, -0.485526, -0.281654, -0.150469, -0.0768641, -0.0386565]
#its = [-0.984108, -0.400997, -0.0192214, 0.213613, 0.32538, 0.36007, 0.364914, 0.365097, 0.365098]
#its = [-2.96969, -2.18743, -1.58883, -1.12595, -0.764844, -0.485512, -0.281642, -0.150459, -0.076856, -0.0386498]

for i in range(len(its)-1):
    plt.plot([its[i], its[i+1]], [fpa(its[i]), 0], color=cl[i%2], alpha=0.7)

#for p in its:
#    plt.plot(p, f(p), 'bo', color="#e00000")

plt.legend()
plt.show()


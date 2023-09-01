# Import needed libraries
import matplotlib.pyplot as plt
import numpy as np

from qbstyles import mpl_style
mpl_style(dark=True)

# Define functios from the exercise
def f1(x):
    return x**2

def f2(x):
    return (x-2)**2


# Create the values for the x axis
x = np.linspace(-10, 10, 1000)

# Plot the values of both functions using .5 as w
plt.plot(x, .5*f1(x) + .5*f2(x), color='#00b81f', label = ".5*f1 + .5*f2")
plt.plot(1, .5*f1(1) + .5*f2(1), 'ro', label='minimum')
plt.plot(x, f1(x), color='#e00000', label="f1", linestyle = 'dashed', linewidth = .6)
plt.plot(x, f2(x), color='#0099ff', label="f2", linestyle = 'dashed', linewidth = .6)
plt.legend()
plt.show()


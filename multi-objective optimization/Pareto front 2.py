# Import needed libraries
import matplotlib.pyplot as plt
import numpy as np
import matplotlib

from matplotlib import cm
from matplotlib.ticker import LinearLocator

from qbstyles import mpl_style

# Define the 2 functions from the exercise
def f1(x1, x2):
    return -10*np.exp(-0.2*np.sqrt(x1**2+x2**2))

def f2(x1, x2):
    return abs(x1)**.8 + 5*np.sin(x1**3) + abs(x2)**.8 + 5*np.sin(x2**3)

# Create a matplotlib 3D axis to plot the functions on
fig = plt.figure(figsize = (10,10), facecolor="#122229")
ax = fig.add_subplot(111, projection='3d') 

x1 = x2 = np.arange(-5, 5, 0.1)
x1, x2 = np.meshgrid(x1, x2)

# Calculate values for z axis
z = .5*f1(x1, x2) + .5*f2(x1, x2)


# Plot the surface
surf = ax.plot_surface(x1, x2, z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=True)

# Plot minimum point
ax.scatter(-1.13908154, -1.13908154, .5*f1(-1.13908154, -1.13908154) + .5*f2(-1.13908154, -1.13908154), color="green", label="mínimo")

# Set limits to x,y and z axis so it looks better
ax.set_xlim(x1.min() - 1, x1.max() + 1)
ax.set_ylim(x2.min() - 1, x2.max() + 1)
ax.set_zlim(z.min()  - 1, z.max()  + 1)

# Set the panel colors as transparent so it looks nicer
ax.xaxis.set_pane_color((1.0, 1.0, 1.0, 0))
ax.yaxis.set_pane_color((1.0, 1.0, 1.0, 0))
ax.zaxis.set_pane_color((1.0, 1.0, 1.0, 0))

# Errase uneded axis lines
ax.xaxis.line.set_alpha(0)
ax.yaxis.line.set_color("white")
ax.zaxis.line.set_color("white")

# Set tick colors as white so it looks nice with the darck bg
ax.tick_params(axis='x', colors='white') 
ax.tick_params(axis='y', colors='white')  
ax.tick_params(axis='z', colors='white') 

# Set the bg color to a dark one
ax.set_facecolor("#122229")

# Set the starting viewing angle of the graph
ax.view_init(5, 45)

# Show the plot
plt.legend()
plt.show()

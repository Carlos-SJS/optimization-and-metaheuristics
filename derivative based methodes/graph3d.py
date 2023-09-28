# Import needed libraries
import matplotlib.pyplot as plt
import numpy as np
import matplotlib

from matplotlib import cm
from matplotlib.ticker import LinearLocator

from mpl_toolkits.mplot3d import Axes3D

from qbstyles import mpl_style

# Define the 2 functions from the exercise
def f(x1, x2):
    return x1**2-2*x1 + x2**2

# Create a matplotlib 3D axis to plot the functions on
fig = plt.figure(figsize = (10,10), facecolor="#122229")
ax = fig.add_subplot(111, projection='3d', computed_zorder=False) 

x1 = x2 = np.arange(-5, 5, 0.1)
x1, x2 = np.meshgrid(x1, x2)

# Calculate values for z axis
z = f(x1, x2)


# Plot the surface
surf = ax.plot_surface(x1, x2, z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=True, alpha=.7)

ix1 = [-2.08333, -0.703829, -0.145371, -0.00922529, -4.2164e-005, -8.88865e-010, -8.88865e-010, -8.88865e-010, -8.88865e-010, -8.88865e-010]
ix2 = [-2.5, -1.25, -0.625, -0.3125, -0.15625, -0.078125, -0.0390625, -0.0195312, -0.00976562, -0.00488281]

ix1 = [4.03226, 3.46837, 2.5425, 2.19861, 2.03931, 2.00349, 2.00007, 2, 2]
ix2 = [3.33333, 2.85714, 1.53846, 1, 0.606061, 0.377358, 0.232558, 0.143885, 0.0888889, 0.0549451]

#fig = plt.figure(1)
#ax = fig.add_subplot(111, fig=fig, projection='3d', computed_zorder=False) 
for i in range(len(ix1)):
    ax.scatter(ix1[i], ix2[i], f(ix1[i], ix2[i]), 'o', color = "red", alpha=1)

# Plot minimum point
#ax.scatter(-1.13908154, -1.13908154, .5*f1(-1.13908154, -1.13908154) + .5*f2(-1.13908154, -1.13908154), color="green", label="mínimo")

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
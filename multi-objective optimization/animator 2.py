# The same as in "pareto front 2.py" but many times

import matplotlib.pyplot as plt
import numpy as np
import matplotlib

from matplotlib import cm
from matplotlib.ticker import LinearLocator

from qbstyles import mpl_style

def f1(x1, x2):
    return -10*np.exp(-0.2*np.sqrt(x1**2+x2**2))



def f2(x1, x2):
    return abs(x1)**.8 + 5*np.sin(x1**3) + abs(x2)**.8 + 5*np.sin(x2**3)

x1 = x2 = np.arange(-5, 5, 0.1)
x1, x2 = np.meshgrid(x1, x2)
st = 0.05
for i in range(21):
    w1 = st*i
    w2 = 1-w1

    plt.close()
        
    fig = plt.figure(figsize = (10,10), facecolor="#122229")
    ax = fig.add_subplot(111, projection='3d') 

    # Load and format data
    z = w1*f1(x1, x2) + w2  *f2(x1, x2)

    # Plot the surface
    surf = ax.plot_surface(x1, x2, z, cmap=cm.coolwarm,
                        linewidth=0, antialiased=True)
    
    ix = z.argmin()

    ax.scatter(x1[ix%100, int(ix/100)], x2[ix%100, int(ix/100)], z[ix%100, int(ix/100)], color="red", label=f"minimum ≈ {round(z[ix%100, int(ix/100)], 2) : .2f}\nx1 = {round(x1[ix%100, int(ix/100)], 2):.2f}, x2 = {round(x2[ix%100, int(ix/100)], 2):.2f}")

    plt.plot(-100, -100, -100, color='#00b81f', label = f"w1 = {w1:.2f}, w2 = {w2:.2f}")

    ax.set_xlim(x1.min() - 1, x1.max() + 1)
    ax.set_ylim(x2.min() - 1, x2.max() + 1)
    ax.set_zlim(-11, 16)

    ax.xaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.yaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.zaxis.set_pane_color((1.0, 1.0, 1.0, 0))

    ax.xaxis.line.set_alpha(0)
    ax.yaxis.line.set_color("white")
    ax.zaxis.line.set_color("white")

    ax.tick_params(axis='x', colors='white') 
    ax.tick_params(axis='y', colors='white') 
    ax.tick_params(axis='z', colors='white') 

    ax.set_facecolor("#122229")
    ax.view_init(5, 45)
    plt.legend()
    plt.savefig(f"ej2/plt{i}.png")
    
for i in range(1, 20):
    w1 = 1 - i*st
    w2 = 1-w1

    plt.close()
        
    fig = plt.figure(figsize = (10,10), facecolor="#122229")
    ax = fig.add_subplot(111, projection='3d') 

    z = w1*f1(x1, x2) + w2  *f2(x1, x2)

    # Plot the surface.
    surf = ax.plot_surface(x1, x2, z, cmap=cm.coolwarm,
                        linewidth=0, antialiased=True)
    
    ix = z.argmin()
    ax.scatter(x1[ix%100, int(ix/100)], x2[ix%100, int(ix/100)], z[ix%100, int(ix/100)], color="red", label=f"minimum ≈ {round(z[ix%100, int(ix/100)], 2) : .2f}\nx1 = {round(x1[ix%100, int(ix/100)], 2):.2f}, x2 = {round(x2[ix%100, int(ix/100)], 2):.2f}")


    plt.plot(-100, -100, -100, color='#00b81f', label = f"w1 = {w1:.2f}, w2 = {w2:.2f}")

    ax.set_xlim(x1.min() - 1, x1.max() + 1)
    ax.set_ylim(x2.min() - 1, x2.max() + 1)
    ax.set_zlim(-11, 16)

    ax.xaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.yaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.zaxis.set_pane_color((1.0, 1.0, 1.0, 0))

    ax.xaxis.line.set_alpha(0)
    ax.yaxis.line.set_color("white")
    ax.zaxis.line.set_color("white")

    ax.tick_params(axis='x', colors='white')
    ax.tick_params(axis='y', colors='white')
    ax.tick_params(axis='z', colors='white') 

    ax.set_facecolor("#122229")
    ax.view_init(5, 45)
    plt.legend()
    plt.savefig(f"ej2/plt{i+20}.png")
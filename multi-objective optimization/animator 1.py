# The same as in "pareto front 1.py" but many times

import matplotlib.pyplot as plt
import numpy as np

from qbstyles import mpl_style
mpl_style(dark=True)

def f1(x):
    return x**2

def f2(x):
    return (x-2)**2

#plt.style.use('dark_background')

x = np.linspace(-10, 10, 1000)
print(min(.5*f1(x) + .5*f2(x)))

st = 0.05
for i in range(21):
    w1 = st*i
    w2 = 1-w1

    z = w1*f1(x) + w2*f2(x)
    ix = z.argmin()

    plt.clf()

    plt.plot(x, z, color='#00b81f', label = f"w1 = {w1:.2f}, w2 = {w2:.2f}")
    #plt.plot(x[ix], z[ix], 'ro', label='minimum')
    plt.plot(x[ix], z[ix], 'ro', label=f"minimum ≈ {round(z[ix], 2) : .2f}\nx1 = {round(x[ix], 2):.2f}")
    plt.plot(x, f1(x), color='#e00000', label="f1", linestyle = 'dashed', alpha=.7, linewidth = .6)
    plt.plot(x, f2(x), color='#0099ff', label="f2", linestyle = 'dashed', alpha=.7, linewidth = .6)
    plt.legend()
    plt.savefig(f"ej1/plt{i}.png")

for i in range(1, 20):
    w1 = 1 - i*st
    w2 = 1-w1

    z = w1*f1(x) + w2*f2(x)
    ix = z.argmin()

    plt.clf()

    plt.plot(x, z, color='#00b81f', label = f"w1 = {w1:.2f}, w2 = {w2:.2f}")
    #plt.plot(x[ix], z[ix], 'ro', label='minimum')
    plt.plot(x[ix], z[ix], 'ro', label=f"minimum ≈ {round(z[ix], 2) : .2f}\nx1 = {round(x[ix], 2):.2f}")
    plt.plot(x, f1(x), color='#e00000', label="f1", linestyle = 'dashed', alpha=.7, linewidth = .6)
    plt.plot(x, f2(x), color='#0099ff', label="f2", linestyle = 'dashed', alpha=.7, linewidth = .6)
    plt.legend()
    plt.savefig(f"ej1/plt{i+20}.png")

import pylab
import os

def film(u, dt=0.01):
    line, = pylab.plot(pylab.array([0.0, 0.0]), pylab.array([0, 0]))
    pylab.xlim(-1.0, 1.0); pylab.ylim(-1.1, 0.1) 
    for i in range(u.shape[0]):
        line.set_data(pylab.array([0.0, u[i, 2]]), pylab.array([0.0, u[i, 3]]))
        pylab.draw()
        os.system('sleep '+str(dt))

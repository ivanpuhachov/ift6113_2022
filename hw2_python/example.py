import meshplot as mp
import numpy as np
import os
import igl
import scipy as sp

mp.offline()

inputfile = "../input/bunny.obj"

v, f = igl.read_triangle_mesh(inputfile)

eigenvectors = np.random.rand(*v.shape)

if not(os.path.isdir("plots/")):
	os.mkdir("plots/")

p = mp.plot(v, f, c=eigenvectors[:,0], return_plot=True, filename='plots/test.html')


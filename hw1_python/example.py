from trimesh import TriMesh
import meshplot as mp
import numpy as np
import os
import argparse

def subdivision_method(inputTrimesh):
	print("No subdivision implemented")
	return inputTrimesh

if __name__=="__main__":
	parser = argparse.ArgumentParser(description="Run subdivision")
	parser.add_argument("--input", "-i", default="../input/cube.obj", help="path to input .obj")
	parser.add_argument("-n", default=3, type=int, help="number of iterations to perform")
	args = parser.parse_args()

	inputfile = args.input
	number_of_iterations = args.n

	print(f"I parced arguments!\n input file: {inputfile}\n n_iterations: {number_of_iterations}\n")

	mesh = TriMesh.FromOBJ_FileName(inputfile)

	os.makedirs("plots/", exist_ok=True)
	os.makedirs("output/", exist_ok=True)

	print("Saving a plot")
	mp.offline()
	p = mp.plot(mesh.vs, mesh.faces, c=mesh.vs[:,0], return_plot=True, filename='plots/test.html')

	for iteration in range(number_of_iterations):
		mesh = subdivision_method(mesh)

	mesh.write_OBJ("output/test_output.obj")
	print("Done")
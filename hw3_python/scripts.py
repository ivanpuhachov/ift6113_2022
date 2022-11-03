import scipy
import numpy as np
import igl


def load_mesh(path):
    return igl.read_triangle_mesh(path)


def compute_laplacian(v,f):
    return igl.cotmatrix(v, f)


def compute_massmatrix(v,f):
    """see https://libigl.github.io/libigl-python-bindings/igl_docs/"""
    return igl.massmatrix(v,f, type=1)


def compute_eigenv_sparse(mat, near_point=0):
    return scipy.sparse.linalg.eigsh(mat, k=20, sigma=near_point)
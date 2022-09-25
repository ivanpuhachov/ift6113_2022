
This code was melted together from [libigl-example-project](https://github.com/libigl/libigl-example-project) and [half-edge date structure by Yotam Gingold](https://github.com/yig/halfedge) and provided as a reference. 

**Remark**: This code might not be optimal, but it gets the work done.

# Usage
Provide short description on how to run your code from command line.

## Prerequisites
Refer to libigl-tutorial for details: [libigl.github.io/tutorial/](https://libigl.github.io/tutorial/) and [libigl/libigl-example-project](https://github.com/libigl/libigl-example-project)

We will use libigl in the future assignments, while here we simply utilize its mesh visualization. Libigl is a header-only library for geometry processing.

Some pre-requisites ubuntu:
```bash
sudo apt-get install git build-essential cmake libx11-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev libxmu-dev libblas-dev libxinerama-dev libxcursor-dev
```
See [libigl tutorial](https://libigl.github.io/tutorial/) and [libigl example project](https://github.com/libigl/libigl-example-project).

## Build
```c
mkdir build
cd build
cmake ..
make
./example
```

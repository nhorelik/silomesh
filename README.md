silomesh
========

Python interface to create simple silo meshes from user data for visualization in Visit, Paraview, etc.

![Alt text](/doc/img/3dcore.png "Output example")

Dependencies
============

SWIG, Python2.7, and SILO 4.8 compiled with HDF5

On ubuntu, these are satisfied with:

* sudo apt-get install swig
* sudo apt-get install python2.7-dev
* sudo apt-get install libsilo-dev
* sudo apt-get install libhdf5-openmpi-dev

For quick viewing you can use ParaView (http://www.paraview.org/).  Make sure to download the latest version from their website, as the SILO file reader may not be included in the version packaged for your system (silomesh is tested on ParaView version 3.98.1).

Installation
============

* python setup.py build
* python setup.py install

Use the Python distutils options to customize the install location.

If the SILO and HDF5 includes and libraries are not in standard locations, it will be necessary to modify a few paths in setup.py to locate them.

Usage
=====

See the scripts in the examples directory.  The general flow is to

1. Initialize a SILO database
2. Initialize a mesh
3. Initialize a mesh variable
4. Populate the mesh varible positions with data
5. Finalize the mesh variable
6. Finalize the mesh
7. Finalize the SILO database to write everything to disk

Multiple meshes can be added to the same database, and multiple variables can be added to each mesh.  Each mesh or variable must be finalized before the next mesh or variable is worked on.

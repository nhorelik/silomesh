#!/usr/bin/env python

"""
setup.py file for distributing silomesh

If the silo library is not in a standard location for your system, modify and
use the library_dirs and include_dirs options to the Extension.

"""

from distutils.core import setup, Extension

import os

silomesh_module = Extension('_silomesh',
                             sources=['silomesh.i',
                                      'silomesh.c'],
                             libraries=['siloh5','hdf5'],
                             library_dirs=[
                             '/home/nhorelik/silo/silo-4.8-bsd/lib',
                             '/home/nhorelik/hdf5/install/lib'],
                             include_dirs=[
                             '/home/nhorelik/silo/silo-4.8-bsd/include',
                             '/home/nhorelik/hdf5/install/inlcude']
                             )

setup (name = 'silomesh',
       version = '0.1',
       author      = "Nick Horelik",
       description = '''Python interface to create simple silo meshes from user data for visualization in Visit, Paraview, etc.''',
       ext_modules = [silomesh_module],
       py_modules = ['silomesh'],
       packages = [''],
       )

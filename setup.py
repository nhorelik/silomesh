#!/usr/bin/env python

"""
setup.py file for distributing silomesh


"""

from distutils.core import setup, Extension

import os

silomesh_module = Extension('_silomesh',
                             sources=['silomesh.i',
                                      'silomesh.c'],
                             )

setup (name = 'silomesh',
       version = '0.1',
       author      = "Nick Horelik",
       description = '''Python interface to create simple silo meshes from user data for visualization in Visit, Paraview, etc.''',
       ext_modules = [silomesh_module],
       py_modules = ['silomesh'],
       packages = [''],
       )

#!/usr/bin/env python

import silomesh as sm

silo_filename = 'test.silo'
xdim,ydim,zdim = (50, 50, 50)             # dimension of mesh in each direction
lowx,lowy,lowz = (0.0, 0.0, 0.0)          # lower left point of mesh
highx,highy,highz = (50.0, 100.0, 300.0)  # upper right point of mesh

sm.init_silo(silo_filename)
sm.init_mesh('meshname1',xdim,ydim,zdim,lowx,lowy,lowz,highx,highy,highz)

sm.init_var('x')
for x in range(xdim):
  for y in range(ydim):
    for z in range(zdim):
      sm.set_value(float(x+1),x+1,y+1,z+1)
sm.finalize_var()

sm.init_var('y')
for x in range(xdim):
  for y in range(ydim):
    for z in range(zdim):
      sm.set_value(float(y+1),x+1,y+1,z+1)
sm.finalize_var()

sm.init_var('z')
for x in range(xdim):
  for y in range(ydim):
    for z in range(zdim):
      sm.set_value(float(z+1),x+1,y+1,z+1)
sm.finalize_var()
sm.finalize_mesh()

# can initialize as many other meshes and vars as needed before finalizing the file

sm.finalize_silo()



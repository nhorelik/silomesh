#!/usr/bin/env python

import silomesh as sm

silo_filename = 'test.silo'
xdim = 5
ydim = 5
zdim = 5
lowx = 0.0
lowy = 1.0
lowz = -10.0
wx = 1.0
wy = 2.0
wz = 3.7

sm.init_silo(silo_filename)
sm.init_mesh('meshname1',xdim,ydim,zdim,lowx,lowy,lowz,wx,wy,wz)

sm.init_var('varname1')
k = 0
for x in range(xdim):
  for y in range(xdim):
    for z in range(xdim):
      sm.set_value(k,x+1,y+1,z+1)
      k += 1
sm.finalize_var()

sm.init_var('varname2')
sm.finalize_var()

sm.finalize_mesh()

# can add as many other meshes as needed

sm.finalize_silo()
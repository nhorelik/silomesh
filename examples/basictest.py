#!/usr/bin/env python

import silomesh as sm

silo_filename = 't.silo'
xdim = 5
ydim = 5
zdim = 5
sm.init_silo(silo_filename)
sm.init_mesh('meshname',xdim,ydim,zdim)
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
sm.finalize_silo()

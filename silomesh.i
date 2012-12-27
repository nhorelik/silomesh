/* silomesh.i */
%module silomesh
%{
  extern void init_mesh(char* filename);
%}

extern void init_mesh(char* filename);

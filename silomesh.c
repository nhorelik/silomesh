#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <silo.h>


/* Function Declarations */

void init_silo(char* filename);
void init_mesh(char* mname, int n_x, int n_y, int n_z,
               float low_x, float low_y, float low_z,
               float width_x, float width_y, float width_z);
void init_var(char* vname);
void set_value(float val, int ix, int iy, int iz);
void finalize_var(void);
void finalize_mesh(void);
void finalize_silo(void);

extern void set_err(const char *msg);

/* Global Variables */

bool            activeSilo = false;
bool            activeMesh = false;
bool            activeVar = false;

char            msg[256];

// silo vars
DBfile          *dbfile;

// mesh vars
char            *meshname;
int             dims[3];
int             n_x,n_y,n_z;
int             n_cells;

// mesh variable vars
char            *varname;
float           *mesh_data;

/* Functions */

void init_silo(char* filename)
{

  if (activeSilo) {
    set_err("SILO file already initialized! Must call finalize_silo before"
            " initializing another file.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }

  // Initializae SILO database and abort on any errors
  DBShowErrors(DB_ABORT, NULL);
  dbfile = DBCreate(filename, DB_CLOBBER, DB_LOCAL, NULL, DB_HDF5);
  
  activeSilo = true;
}


void init_mesh(char* mname, int nx, int ny, int nz,
               float low_x, float low_y, float low_z,
               float high_x, float high_y, float high_z)
{
  
  float     *x,*y,*z;
  int       ix,iy,iz;
  float     *coords[3];
  float     width_x, width_y, width_z;
 
  if (!activeSilo) {
    set_err("No active silo file! Must call init_silo first.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }
  
  if (activeMesh) {
    set_err("Mesh already initialized! Must call finalize mesh before"
            " initializing another one.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }
  
  meshname = strdup(mname);

  n_x = nx; n_y = ny; n_z = nz;
  
  // find mesh widths
  width_x = (high_x - low_x) / (float) n_x;
  width_y = (high_y - low_y) / (float) n_y;
  width_z = (high_z - low_z) / (float) n_z;
  
  // setup dimensions and rectilinear coordinates
  n_cells = n_x*n_y*n_z;  
  dims[0] = n_x+1; dims[1] = n_y+1; dims[2] = n_z+1; // dims of coords
  x = malloc(sizeof(float)*(n_x+1));
  y = malloc(sizeof(float)*(n_y+1));
  z = malloc(sizeof(float)*(n_z+1));
  for (ix=0; ix<=n_x; ix++) x[ix] = low_x+width_x*(float)ix;
  for (iy=0; iy<=n_y; iy++) y[iy] = low_y+width_y*(float)iy;
  for (iz=0; iz<=n_z; iz++) z[iz] = low_z+width_z*(float)iz;
  coords[0] = x; coords[1] = y; coords[2] = z;

  // add mesh to datafile  
  DBPutQuadmesh(dbfile, meshname, NULL, coords, dims, 3, DB_FLOAT, DB_COLLINEAR, NULL);
  free(x); free(y); free(z);
  
  // dims will be used for variables, so needs to match with number of zones
  dims[0] = n_x; dims[1] = n_y; dims[2] = n_z;
  
  activeMesh = true;
  
}


void init_var(char* vname)
{

  int i;

  if (!activeMesh) {
    set_err("No active mesh! Must call init_mesh first.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }
  
  if (activeVar) {
    set_err("Variable already initialized! Must call finalize_var before"
            " initializing another one.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }

  varname = strdup(vname);

  // initialize the data array
  mesh_data = malloc(sizeof(float)*n_cells);
  for (i=0; i<n_cells; i++) mesh_data[i] = 0.0;
  
  activeVar = true;
}


void set_value(float val, int ix, int iy, int iz)
{
  int k;

  if (!activeVar) {
    set_err("No active variable! Must call init_var first.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }

  k = (iz-1)*n_x*n_y + (iy-1)*n_x + (ix-1);
  if (k > n_cells || k < 0) {
    sprintf(msg,"Indices (%i,%i,%i) out of range (1-%i,1-%i,1-%i).",ix,iy,iz,n_x,n_y,n_z);
    set_err(msg);
    return;
  }
  mesh_data[k] = val;
  
}



void finalize_var(void)
{

  if (!activeMesh) {
    set_err("No active mesh! Must call init_mesh first.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }

  DBPutQuadvar1(dbfile, varname, meshname, mesh_data, dims, 3, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
  free(mesh_data);
  
  free(varname);
  
  activeVar = false;
}


void finalize_mesh(void)
{
  if (!activeSilo) {
    set_err("No active silo file! Must call init_silo first.");
    if (meshname) free(meshname); if (varname) free (varname);
    return;
  }

  free(meshname);
  
  activeMesh = false;
}


void finalize_silo(void)
{
  DBClose(dbfile);
  
  activeSilo = false;
}

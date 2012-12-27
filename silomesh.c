#include <stdio.h>
#include <silo.h>

/* Function Declarations */

// functions exposed to python via SWIG
void init_mesh(char* filename);

/* Global Variables */

DBfile          *dbfile;

/* Functions */

void init_mesh(char* filename)
{
  
  int             driver = DB_HDF5;

  // Abort on any errors
  DBShowErrors(DB_ABORT, NULL);

  dbfile = DBCreate(filename, 0, DB_LOCAL, "armisilo mesh", driver);
  
  DBClose(dbfile);
  
}

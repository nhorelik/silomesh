/* silomesh.i */
%module silomesh
%{
  extern void init_silo(char* filename);
  extern void init_mesh(char* mname, int n_x, int n_y, int n_z,
                        float low_x, float low_y, float low_z,
                        float width_x, float width_y, float width_z);
  extern void init_var(char* vname);
  extern void set_value(float val, int ix, int iy, int iz);
  extern void finalize_var(void);
  extern void finalize_mesh(void);
  extern void finalize_silo(void);
  
  /* Exception helpers */
  static int swig_c_error_num = 0;
  static char swig_c_err_msg[256];

  const char* err_occurred(void)
  {
      if (swig_c_error_num) {
          swig_c_error_num = 0;
          return (const char*)swig_c_err_msg;
      }
      return NULL;
  }

  void set_err(const char *msg)
  {
      swig_c_error_num = 1;
      strncpy(swig_c_err_msg, msg, 256);
  }
%}

%exception {
    const char *err;
    $action
    err = err_occurred();
    if (err) {
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}

extern void init_silo(char* filename);
extern void init_mesh(char* mname, int n_x, int n_y, int n_z,
                      float low_x, float low_y, float low_z,
                      float width_x, float width_y, float width_z);
extern void init_var(char* vname);
extern void set_value(float val, int ix, int iy, int iz);
extern void finalize_var(void);
extern void finalize_mesh(void);
extern void finalize_silo(void);

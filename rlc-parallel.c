#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <math.h>
#define PIE 3.14159265
#define RR 20000.0
#define LL (47.0/1000)
#define CC (47.0/1000000000)
#define IS 5.0

int func(double t, const double y[], double f[],
	 void *params){
  (void)(t); /* avoid unused parameter warning */
  double mu = *(double *)params;
  f[0] = (IS - (1.0/RR)*y[0] -LL*y[1])/CC;
  f[1] = y[0]/(LL*LL);
  return GSL_SUCCESS;
}

int jac(double t, const double y[], double *dfdy,
     double dfdt[], void *params){

  (void)(t); /* avoid unused parameter warning */
  double mu = *(double *)params;
  gsl_matrix_view dfdy_mat
    = gsl_matrix_view_array (dfdy, 2, 2);
  gsl_matrix * m = &dfdy_mat.matrix;
  gsl_matrix_set(m, 0, 0,  1.0/(LL*LL));
  gsl_matrix_set(m, 0, 1,          0.0);
  gsl_matrix_set(m, 1, 0, -1.0/(CC*RR));
  gsl_matrix_set(m, 1, 1,       -LL/CC);
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;
  return GSL_SUCCESS;
}

int main (void) {
  double mu = 0.0;
  gsl_odeiv2_system sys ={func, jac, 2, &mu};
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new(&sys,
				  gsl_odeiv2_step_rk8pd,
                                  1e-6, 1e-6, 0.0);
  int i;
  double t = 0.0, t1 = 1.0;
  double y[2] = { 0.0, 10.0 };
  double omegazero = 1.0/sqrt(LL*CC);

  for (i = 1; i <= 50000; i++) {
      double ti = i * t1 / 10000000.0;
      int status = gsl_odeiv2_driver_apply(d, &t, ti, y);

      if (status != GSL_SUCCESS) {
          printf ("error, return value=%d\n", status);
          break;
      }
      if(i%100==0){
	printf ("%.5e %.5e %.5e\n", omegazero*t/PIE,
		y[0], y[1]*LL);
      }
  }

  gsl_odeiv2_driver_free (d);
  return 0;
}

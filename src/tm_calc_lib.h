/*
   -	tm_calc.h --
   -		This header declares structures and
   -		functions that store and manipulate
   -		time values.  See tm_calc (3).
   -	
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved
   .
   .	Please address questions and feedback to dev0@trekix.net.
   .
   .	$Revision: $ $Date: $
 */

#ifndef _TMCALC_H_
#define _TMCALC_H_

double tm_resoln(int, int, int, int, int, double);
double tm_caltojul(int, int, int, int, int, double);
int tm_jultocal(double, int *, int *, int *, int *, int *, double *);

#endif

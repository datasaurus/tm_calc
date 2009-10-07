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
   .	$Revision: 1.5 $ $Date: 2009/10/01 22:15:22 $
 */

#ifndef _TMCALC_H_
#define _TMCALC_H_

double Tm_Resoln(int, int, int, int, int, double);
double Tm_CalToJul(int, int, int, int, int, double);
int Tm_JulToCal(double, int *, int *, int *, int *, int *, double *);

#endif

/*
 - tm_calc.h --
 -	This header declares structures and functions that store and
 -	manipulate time values.
 - 
   Copyright (c) 2009 Gordon D. Carrie.  All rights reserved.

   Licensed under the Open Software License version 2.1

   Please address questions and feedback to dev0@trekix.net.

   @(#) $Id: tm_calc_lib.h,v 1.2 2009/07/08 21:44:48 gcarrie Exp $
 */

#ifndef _TMCALC_H_
#define _TMCALC_H_

double tm_resoln(int, int, int, int, int, double);
double tm_caltojul(int, int, int, int, int, double);
int tm_jultocal(double, int *, int *, int *, int *, int *, double *);

#endif

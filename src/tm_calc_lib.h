/*
 - tm_calc.h --
 -	This header declares structures and functions that store and
 -	manipulate time values.
 - 
   Copyright (c) 2009 Gordon D. Carrie.  All rights reserved.

   Licensed under the Open Software License version 2.1

   Please address questions and feedback to dev0@trekix.net.

   @(#) $Id: $
 */

#ifndef _TMCALC_H_
#define _TMCALC_H_

/* Time instant as a Julian day and seconds since midnight */
struct tm_jul {
    int   day;		/* Julian day */
    double second;	/* Seconds since midnight */
};

/* Global functions */
struct tm_jul tm_julset(int, double);
struct tm_jul tm_caltojul(int, int, int, int, int, double);
void tm_jultocal(struct tm_jul, int *, int *, int *, int *, int *, double *);
void tm_incr(struct tm_jul *, double);
int tm_cmp(struct tm_jul, struct tm_jul);
double tm_diff(struct tm_jul, struct tm_jul);

#endif

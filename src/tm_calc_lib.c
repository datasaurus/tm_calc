/*
   -	tm_calc_lib.c --
   -		This file defines functions for manipulate date and times
   -	
   .	Copyright (c) 2009 Gordon D. Carrie
   .	All rights reserved
   .
   .	Please send feedback to user0@tkgeomap.org
   .
   .	Reference for calendar computations:
   .		Henry F. Fliegel and Thomas C. Van Flandern
   .		Letters to the editor: a machine algorithm for
   .			processing calendar dates.
   .		Communications of the ACM archive
   .		Volume 11 , Issue 10 (October 1968) Page: 657 ISSN:0001-0782 
   .
   .	$Revision: 1.7 $ $Date: 2009/10/01 21:43:46 $
 */

#include <math.h>
#include "err_msg.h"
#include "tm_calc_lib.h"

double tm_resoln(int y, int mo, int d, int h, int mi, double s)
{
    double j1, j2;

    j1 = tm_caltojul(y, mo, d, h, mi, s);
    j2 = nextafter(j1, j1 + 1);
    return (j2 - j1) * 86400.0;
}

double tm_caltojul(int year, int month, int day,
	int hour, int minute, double second)
{
    return (1461 * (year + 4800 + (month - 14) / 12)) / 4
	+ (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
	- (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4
	+ day - 32075 + hour / 24.0 + minute / 1440.0 + second / 86400.0 - 0.5;
}

int tm_jultocal(double julday, int *year, int *month,
	int *day, int *hour, int *minute, double *second)
{
    double iday, fday;
    int l, n, i, j;		/* Intermediaries */
    double ihour, fhour, imin, fmin;

    julday += 0.5;
    fday = modf(julday, &iday);
    if (iday > INT_MAX) {
	err_append("Julian date too big for integer arithmetic.");
	return 0;
    }
    l = (int)iday + 68569;
    n = (4 * l) / 146097;
    l = l - (146097 * n + 3) / 4;
    i = (4000 * (l + 1)) / 1461001;
    l = l - (1461 * i) / 4 + 31;
    j = (80 * l) / 2447;
    *day = l - (2447 * j) / 80;
    l = j / 11;
    *month = j + 2 - (12 * l);
    *year = 100 * (n - 49) + i + l;

    fhour = modf(fday * 24.0, &ihour);
    *hour = (int)ihour;
    fmin = modf(fhour * 60.0, &imin);
    *minute = (int)imin;
    *second = fmin * 60.0;
    return 1;
}

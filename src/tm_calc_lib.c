/*
   -	tm_calc_lib.c --
   -		This file defines functions for manipulate date and times
   -	
   .	Copyright (c) 2011, Gordon D. Carrie. All rights reserved.
   .	
   .	Redistribution and use in source and binary forms, with or without
   .	modification, are permitted provided that the following conditions
   .	are met:
   .	
   .	    * Redistributions of source code must retain the above copyright
   .	    notice, this list of conditions and the following disclaimer.
   .
   .	    * Redistributions in binary form must reproduce the above copyright
   .	    notice, this list of conditions and the following disclaimer in the
   .	    documentation and/or other materials provided with the distribution.
   .	
   .	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   .	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   .	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   .	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   .	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   .	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   .	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   .	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   .	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   .	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   .	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	Reference for calendar computations:
   .		Henry F. Fliegel and Thomas C. Van Flandern
   .		Letters to the editor: a machine algorithm for
   .			processing calendar dates.
   .		Communications of the ACM archive
   .		Volume 11 , Issue 10 (October 1968) Page: 657 ISSN:0001-0782 
   .
   .	$Revision: 1.12 $ $Date: 2011/09/22 18:29:47 $
 */

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include "tm_calc_lib.h"

double Tm_CalToJul(int year, int month, int day,
	int hour, int minute, int second)
{
    return (1461 * (year + 4800 + (month - 14) / 12)) / 4
	+ (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
	- (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4
	+ day - 32075 + hour / 24.0 + minute / 1440.0 + second / 86400.0 - 0.5;
}

int Tm_JulToCal(double julday, int *year, int *month,
	int *day, int *hour, int *minute, int *second)
{
    double iday, fday;		/* Integer and fractional part of julday */
    int l, n, i, j;		/* Intermediaries */

    julday += 0.5;
    fday = modf(julday, &iday);
    if (iday > INT_MAX) {
	fprintf(stderr, "Julian day iday too big for integer arithmetic.");
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

    /*
       Round fday to nearest second and extract hour and minute
     */

    *second = fday * 86400 + 0.5;
    *minute = *second / 60;
    *second = *second - *minute * 60;
    *hour = *minute / 60;
    *minute = *minute - *hour * 60;
    return 1;
}

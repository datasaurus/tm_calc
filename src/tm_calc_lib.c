/*
 - tm_calc_lib.c --
 -	This file defines functions for manipulate date and times
 - 
   Copyright (c) 2009 Gordon D. Carrie

   Licensed under the Open Software License version 2.1

   Please send feedback to user0@tkgeomap.org

   Reference for calendar compuations:
	Henry F. Fliegel and Thomas C. Van Flandern
	Letters to the editor: a machine algorithm for processing calendar dates
	Communications of the ACM archive
	Volume 11 , Issue 10 (October 1968) Page: 657 ISSN:0001-0782 

   $Revision: $ $Date: $
 */

#include <math.h>
#include "tm_calc_lib.h"

struct tm_jul tm_julset(int day, double second)
{
    struct tm_jul jul;

    jul.day = day;
    jul.second = second;
    return jul;
}

struct tm_jul tm_caltojul(int year, int month, int day,
	int hour, int minute, double second)
{
    struct tm_jul jul;		/* Return value */

    jul.day =   (1461 * (year + 4800 + (month - 14) / 12)) / 4
	+ (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
	- (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4
	+ day - 32075;
    jul.second = 3600.0 * hour + 60.0 * minute + second;
    return jul;
}

void tm_jultocal(struct tm_jul jul, int *year, int *month,
	int *day, int *hour, int *minute, double *second)
{
    int l, n, i, j;		/* Intermediaries */
    int h, m;			/* Hour, minute */
    int s;			/* Second */
    double fsec;

    l = jul.day + 68569;
    n = (4 * l) / 146097;
    l = l - (146097 * n + 3) / 4;
    i = (4000 * (l + 1)) / 1461001;
    l = l - (1461 * i) / 4 + 31;
    j = (80 * l) / 2447;
    *day = l - (2447 * j) / 80;
    l = j / 11;
    *month = j + 2 - (12 * l);
    *year = 100 * (n - 49) + i + l;

    s = floor(jul.second);
    fsec = jul.second - s;
    h = s / 3600;
    s %= 3600;
    m = s / 60;
    s %= 60;
    if (h > 23) {
	*day += h / 24;
	h %= 24;
    }
    *hour = h;
    *minute = m;
    *second = s + fsec;
}

void tm_incr(struct tm_jul *jul, double ds)
{
    int d;
    double s;

    s = jul->second + ds;
    d = floor(s / 86400.0);
    jul->day += d;
    jul->second = s - d * 86400.0;
}

int tm_cmp(struct tm_jul jul1, struct tm_jul jul2)
{

    jul1 = tm_julset(jul1.day, jul1.second);
    jul2 = tm_julset(jul2.day, jul2.second);
    if (jul1.day > jul2.day) {
	return 1;
    }
    if (jul1.day < jul2.day) {
	return -1;
    }
    if (jul1.second > jul2.second) {
	return 1;
    }
    if (jul1.second < jul2.second) {
	return -1;
    }
    return 0;
}

double tm_diff(struct tm_jul jul1, struct tm_jul jul2)
{

    jul1 = tm_julset(jul1.day, jul1.second);
    jul2 = tm_julset(jul2.day, jul2.second);
    return (jul1.day - jul2.day) * 86400.0 + jul1.second - jul2.second;
}

/*
   -	tm_calc.c --
   -		This file defines an application that does
   -		time calculations.
   -	
   .	Copyright (c) 2008 Gordon D. Carrie
   .	All rights reserved
   .
   .	Please send feedback to dev0@trekix.net
   .
   .	$Revision: 1.10 $ $Date: 2010/03/04 15:51:38 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err_msg.h"
#include "alloc.h"
#include "str.h"
#include "tm_calc_lib.h"

/* Application name and subcommand name */
char *cmd, *cmd1;

/* Callback functions.  There should be one for each subcommand. */
typedef int (callback)(int , char **);
callback resoln_cb;
callback caltojul_cb;
callback jultocal_cb;

/* Number of subcommands */
#define NCMD 3

/* Array of subcommand names */
char *cmd1v[NCMD] = {"resoln", "caltojul", "jultocal"};

/* Array of subcommand callbacks. cb1v[i] is the callback for cmd1v[i] */
callback *cb1v[NCMD] = {resoln_cb, caltojul_cb, jultocal_cb};

int main(int argc, char *argv[])
{
    int i;
    int rslt;

    /* Ensure minimum command line */
    cmd = argv[0];
    if (argc < 2) {
	fprintf(stderr, "Usage: %s subcommand [subcommand_options ...]\n", cmd);
	exit(1);
    }
    cmd1 = argv[1];

    /* Search cmd1v for cmd1.  When match is found, evaluate the associated
     * callback from cb1v. */
    for (i = 0; i < NCMD; i++) {
	if (strcmp(cmd1v[i], cmd1) == 0) {
	    rslt = (cb1v[i])(argc - 1, argv + 1);
	    if ( !rslt ) {
		fprintf(stderr, "%s %s failed.\n", cmd, cmd1);
		fprintf(stderr, "%s\n", Err_Get());
		break;
	    } else {
		break;
	    }
	}
    }
    if (i == NCMD) {
	fprintf(stderr, "%s: No option or subcommand named %s\n", cmd, cmd1);
	fprintf(stderr, "Subcommand must be one of: ");
	for (i = 0; i < NCMD; i++) {
	    fprintf(stderr, "%s ", cmd1v[i]);
	}
	fprintf(stderr, "\n");
    }
    return !rslt;
}
int resoln_cb(int argc, char *argv[])
{
    char *yr_s, *mo_s, *dy_s, *hr_s, *mi_s, *sc_s;
    int yr, mo, dy, hr, mi;
    double sc;
    int da;
    char *fmt;

    /* Ensure minimum command line */
    if (argc < 7) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" [-f format] year month day hour minute second\n");
	return 0;
    }
    fmt = "%lf\n";
    da = 0;
    if (strcmp(argv[1], "-f") == 0) {
	fmt = Str_Esc(argv[2]);
	da = 2;
    }
    yr_s = argv[1 + da];
    mo_s = argv[2 + da];
    dy_s = argv[3 + da];
    hr_s = argv[4 + da];
    mi_s = argv[5 + da];
    sc_s = argv[6 + da];

    /* Get values from command line arguments */
    if (sscanf(yr_s, "%d", &yr) != 1) {
	Err_Append("Expected integer value for year, got ");
	Err_Append(yr_s);
	return 0;
    }
    if (sscanf(mo_s, "%d", &mo) != 1) {
	Err_Append("Expected integer value for month, got ");
	Err_Append(mo_s);
	return 0;
    }
    if (sscanf(dy_s, "%d", &dy) != 1) {
	Err_Append("Expected integer value for day, got ");
	Err_Append(dy_s);
	return 0;
    }
    if (sscanf(hr_s, "%d", &hr) != 1) {
	Err_Append("Expected integer value for hour, got ");
	Err_Append(hr_s);
	return 0;
    }
    if (sscanf(mi_s, "%d", &mi) != 1) {
	Err_Append("Expected integer value for minute, got ");
	Err_Append(mi_s);
	return 0;
    }
    if (sscanf(sc_s, "%lf", &sc) != 1) {
	Err_Append("Expected float value for second, got ");
	Err_Append(sc_s);
	return 0;
    }

    /* Send result */
    printf(fmt, Tm_Resoln(yr, mo, dy, hr, mi, sc));
    return 1;
}

int caltojul_cb(int argc, char *argv[])
{
    char *yr_s, *mo_s, *dy_s, *hr_s, *mi_s, *sc_s;
    int yr, mo, dy, hr, mi;
    double sc;
    int da;
    char *fmt;

    /* Ensure minimum command line */
    if (argc < 7) {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append(" [-f format] year month day hour minute second\n");
	return 0;
    }
    fmt = "%lf\n";
    da = 0;
    if (strcmp(argv[1], "-f") == 0) {
	fmt = Str_Esc(argv[2]);
	da = 2;
    }
    yr_s = argv[1 + da];
    mo_s = argv[2 + da];
    dy_s = argv[3 + da];
    hr_s = argv[4 + da];
    mi_s = argv[5 + da];
    sc_s = argv[6 + da];

    /* Get values from command line arguments */
    if (sscanf(yr_s, "%d", &yr) != 1) {
	Err_Append("Expected integer value for year, got ");
	Err_Append(yr_s);
	return 0;
    }
    if (sscanf(mo_s, "%d", &mo) != 1) {
	Err_Append("Expected integer value for month, got ");
	Err_Append(mo_s);
	return 0;
    }
    if (sscanf(dy_s, "%d", &dy) != 1) {
	Err_Append("Expected integer value for day, got ");
	Err_Append(dy_s);
	return 0;
    }
    if (sscanf(hr_s, "%d", &hr) != 1) {
	Err_Append("Expected integer value for hour, got ");
	Err_Append(hr_s);
	return 0;
    }
    if (sscanf(mi_s, "%d", &mi) != 1) {
	Err_Append("Expected integer value for minute, got ");
	Err_Append(mi_s);
	return 0;
    }
    if (sscanf(sc_s, "%lf", &sc) != 1) {
	Err_Append("Expected float value for second, got ");
	Err_Append(sc_s);
	return 0;
    }

    /* Send result */
    printf(fmt, Tm_CalToJul(yr, mo, dy, hr, mi, sc));
    return 1;
}

int jultocal_cb(int argc, char *argv[])
{
    int yr, mo, dy, hr, mi;
    double sc;
    char *fmt;
    char *j_s;
    double j;

    /* Ensure minimum command line */
    if ( argc == 2 ) {
	fmt = "%02d %02d %02d %02d %02d %04.1lf\n";
	j_s = argv[1];
    } else if ( argc == 4 && strcmp(argv[1], "-f") == 0 ) {
	fmt = Str_Esc(argv[2]);
	j_s = argv[3];
    } else {
	Err_Append("Usage: ");
	Err_Append(cmd);
	Err_Append(" ");
	Err_Append(cmd1);
	Err_Append("[-f format] julian_day\n");
	return 0;
    }

    /* Get Julian date from command line argument */
    if (sscanf(j_s, "%lf", &j) != 1) {
	Err_Append("Expected float value for Julian day, got ");
	Err_Append(j_s);
	return 0;
    }

    /* Send result */
    if (Tm_JulToCal(j, &yr, &mo, &dy, &hr, &mi, &sc)) {
	printf(fmt, yr, mo, dy, hr, mi, sc);
	return 1;
    } else {
	return 0;
    }
}

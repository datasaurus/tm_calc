/*
 - tm_calc.c --
 - 	This file defines an application that does time calculations.
 -
   Copyright (c) 2008 Gordon D. Carrie
   Licensed under the Open Software License version 3.0
  
   Please send feedback to dev0@trekix.net

   $Revision: $ $Date: $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err_msg.h"
#include "tm_calc_lib.h"

/* Application name and subcommand name */
char *cmd, *cmd1;

/* Callback functions.  There should be one for each subcommand. */
typedef int (callback)(int , char **);
callback julset_cb;

/* Number of subcommands */
#define NCMD 1

/* Array of subcommand names */
char *cmd1v[NCMD] = {"julset"};

/* Array of subcomand callbacks. cb1v[i] is the callback for cmd1v[i] */
callback *cb1v[NCMD] = {julset_cb};

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
		fprintf(stderr, "%s\n", err_get());
		break;
	    } else {
		break;
	    }
	}
    }
    if (i == NCMD) {
	fprintf(stderr, "%s: No option or subcommand named %s\n", cmd, cmd1);
    }
    return !rslt;
}

int julset_cb(int argc, char *argv[])
{
    char *d_s, *s_s;		/* Strings from command line */
    int d; double s;		/* Values from command line */
    struct tm_jul j;

    /* Ensure minimum command line */
    if (argc != 3) {
	err_append("Usage: ");
	err_append(cmd);
	err_append(" ");
	err_append(cmd1);
	err_append(" days seconds\n");
	return 0;
    }
    d_s = argv[1];
    s_s = argv[2];

    /* Get values from command line arguments */
    if (sscanf(d_s, "%d", &d) != 1) {
	err_append("Expected integer value for day, got ");
	err_append(d_s);
	return 0;
    }
    if (sscanf(s_s, "%lf", &s) != 1) {
	err_append("Expected float value for seconds, got ");
	err_append(s_s);
	return 0;
    }

    /* Send result */
    j = tm_julset(d, s);
    printf("%d %f\n", j.day, j.second);
    return 1;
}

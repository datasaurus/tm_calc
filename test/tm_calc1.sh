#!/bin/sh
#
#- tm_calc1.sh --
#-	This test application tests conversion functions defined in tm_calc_lib.c.
#-
# Copyright (c) 2009 Gordon D. Carrie
# All rights reserved
#
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.3 $ $Date: 2009/09/25 21:33:14 $
#
########################################################################

echo "
tm_calc.sh --

This test application tests conversion functions defined in tm_calc_lib.c.
See tm_calc_lib (3) and tm_calc (1) for more information.

Usage suggestions:
./tm_calc.sh 2>&1 | less
To save temporary files:
env RM=: ./tm_calc.sh 2>&1 | less

Copyright (c) 2009 Gordon D. Carrie
All rights reserved

################################################################################
"

if ! (cd src;make) > /dev/null
then
    echo "make failed"
    exit 1
fi
export PATH=$PWD/src:$PATH

# Run the tests
echo "test1: converting calendar date time to Julian day"
if [ `tm_calc caltojul -f '%.2f\n' 2009 07 10 00 00 00` = "2455022.50" ]
then
    echo "tm_calc produced correct output."
    result1=success
else
    echo "tm_calc produced bad output!"
    result1=fail
fi
echo "test1 result = $result1
Done with test1

################################################################################
"

echo "test2: converting Julian day to calendar date"
j=`tm_calc jultocal -f '%04d %02d %02d %02d %02d %04.1f\n' 2455022.50`
if [ "$j" = "2009 07 10 00 00 00.0" ]
then
    echo "tm_calc produced correct output."
    result2=success
else
    echo "tm_calc produced bad output!"
    result2=fail
fi
echo "test2 result = $result2
Done with test2

################################################################################
"

(cd src;make clean > /dev/null)

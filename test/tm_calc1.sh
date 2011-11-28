#!/bin/sh
#
#- tm_calc1.sh --
#-	This test application tests conversion functions defined in tm_calc_lib.c.
#-
# Copyright (c) 2011, Gordon D. Carrie. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#     * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Please send feedback to dev0@trekix.net
#
# $Revision: 1.4 $ $Date: 2010/10/02 01:29:44 $
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

#- Makefile --
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
#
# Please send feedback to dev0@trekix.net

# Where to install things
PREFIX=${HOME}/local
BINDIR=${PREFIX}/bin
MAN1DIR=${PREFIX}/man/man1
MAN3DIR=${PREFIX}/man/man3

CFLAGS = -std=c99 -O2 -Wall -Wmissing-prototypes
#LFLAGS = -L/usr/local/lib -lefence -lm
LFLAGS = -lm
EXECS = tm_calc 
MAN1 = ../man/man1/tm_calc.1

all : ${EXECS}

install : ${EXECS}
	mkdir -p ${BINDIR}
	cp ${EXECS} ${BINDIR}
	mkdir -p ${MAN1DIR}
	cp ${MAN1} ${MAN1DIR}

OBJ = tm_calc_app.o tm_calc_lib.o str.o alloc.o
tm_calc : ${OBJ}
	cc ${CFLAGS} -o tm_calc ${OBJ} ${LFLAGS}

tm_calc_lib.o : tm_calc_lib.c tm_calc_lib.h
	cc ${CFLAGS} -c tm_calc_lib.c

alloc.o : alloc.c alloc.h
	cc ${CFLAGS} -c alloc.c

str.o : str.c str.h
	cc ${CFLAGS} -c str.c

clean :
	rm -f ${EXECS} *core*  *.o *.ps *.out

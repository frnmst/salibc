#!/usr/bin/make -f

#
# Makefile
#
# Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
#                                            <franco.masotti@student.unife.it>
#
# This file is part of salibc.
#
# salibc is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# salibc is distributed in the hope that it will be
# useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with salibc.  If not, see <http://www.gnu.org/licenses/>.
#


# Macros.
CC = /usr/bin/gcc

DEPS = salibc.h
CFLAGS = -Wall -Wextra -Wpedantic -Werror -march=native -O0
LIBS = -lm -lrt
CSTANDARD = -std=c99
DEFFLAG =

INDENT_OPTS = -nbad -bap -nbc -bbo -bl -bli2 -bls -ncdb -nce -cp1 -cs -di2 -ndj -nfc1-nfca -hnl -i2 -ip5 -lp -pcs -psl -nsc -nsob
SPLINT_OPTS = -usereleased -compdef -preproc

EXECUTABLES = salibc.out
PRG_OBJFILES = salibc.o salibc_test.o

# Targets
default : salibc

all : main

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) $(CSTANDARD) $(LIBS) $(DEFFLAG) -c -o $@ $<

indent:
	@echo "Indenting all files..."
	@./indent.sh "$(INDENT_OPTS)" "$(SPLINT_OPTS)" "$(PRG_OBJFILES)"
	@echo "Done."

clean:
	@echo "Removing object files..."
	@rm -fv *.o $(EXECUTABLES)
	@echo "Object files removed."

target salibc: override DEFFLAG = -DSALIBC_TEST
salibc: salibc.o salibc_test.o
	@$(CC) -o $@.out $^
	@echo "$(CC) $(CFLAGS) $(CSTANDARD) $(LIBS) -DFSALIBC_TEST -o $@.out"

doxygen:
	@doxygen doxy.conf

# to protect files with the following names, the .PHONY rule is used
.PHONY: default all clean indent $(EXECUTABLES)

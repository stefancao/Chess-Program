##################################################
#
# Makefile for the simple GTK example
# author: Weiwei Chen (updates by Rainer Doemer)
# initial version: 01/22/13 EECS22L Winter 2013
# patched version: 01/14/15 EECS22L Winter 2015
#
##################################################

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS) 

OPTS	= -g
AR 	= ar rc
RANLIB	= ranlib

PROJECT	= Chesstro

all: $(PROJECT)

Chesstro.o: Chesstro.c Constants.h
	gcc -c Chesstro.c $(INC) $(OPTS) -o Chesstro.o

Rules.o: Rules.c Rules.h
	gcc -c Rules.c $(INC) $(OPTS) -o Rules.o

AI.o: AI.c
	gcc -c AI.c $(INC) $(OPTS) -o AI.o


libFilter.a: Rules.o
	$(AR) libFilter.a Rules.o
	$(RANLIB) libFilter.a

Chesstro: Chesstro.o libFilter.a AI.o 
	gcc Chesstro.o  -lFilter -L.  $(LIBS) $(OPTS) -o Chesstro

clean:
	rm -rf *.o $(PROJECT)

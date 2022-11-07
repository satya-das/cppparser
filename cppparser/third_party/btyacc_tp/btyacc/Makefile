#
# Makefile for BtYacc.
#

VERSION       = 3-0

DEST	      = .

HDRS	      = defs.h mstring.h

CFLAGS	      = -g -Wall -Wstrict-prototypes -Wmissing-prototypes

LDFLAGS	      = -static

LIBS	      =

CC	      = gcc
LINKER	      = gcc
# LINKER      = cl
# CC	      = cl

MAKEFILE      = Makefile

OBJS	      = closure.o dtor.o error.o lalr.o lr0.o main.o mkpar.o	\
		output.o mstring.o reader.o readskel.o skeleton.o	\
		symtab.o verbose.o warshall.o

PRINT	      = pr -f -l88

PROGRAM	      = btyacc

SRCS	      = closure.c dtor.c error.c lalr.c lr0.c main.c mkpar.c	\
		output.c mstring.c reader.c readskel.c skeleton.c	\
		symtab.c verbose.c warshall.c

OTHERS	      = README README.BYACC \
		Makefile btyaccpa.ske push.skel empty.y skel2c manpage	\
		makefile.dos skeleton.c

TEST_GEN      = test/*.tab.c test/*.code.c test/*.tab.h test/*.output	\
		test/*.o test/a.out test/tmp.txt

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		$(LINKER) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LIBS)

clean:;		rm -f $(OBJS) $(TEST_GEN)

clobber:;	rm -f $(OBJS) $(PROGRAM)

distclean:;	rm -f $(OBJS) $(PROGRAM) skeleton.c *.zip *.gz $(TEST_GEN) \
		test/faillog.txt

depend:;	mkmf -f $(MAKEFILE) PROGRAM=$(PROGRAM) DEST=$(DEST)

index:;		ctags -wx $(HDRS) $(SRCS)

install:	$(PROGRAM)
		cp $(PROGRAM).exe /bin

oldinstall:	$(PROGRAM)
		@echo Installing $(PROGRAM) in $(DEST)
		install -s $(PROGRAM) $(DEST)

listing:;	$(PRINT) Makefile $(HDRS) $(SRCS) | lpr

lint:;		lint $(SRCS)

program:        $(PROGRAM)

tags:           $(HDRS) $(SRCS)
		ctags $(HDRS) $(SRCS)

dist:		tar zip

tar:
		rm -f btyacc.tar btyacc.tar.gz
		tar cvf btyacc.tar $(OTHERS) $(SRCS) $(HDRS) test/*.y
		gzip -9 btyacc.tar
		mv btyacc.tar.gz btyacc-$(VERSION).tar.gz

zip:
		zip btyacc.zip $(OTHERS) $(SRCS) $(HDRS) test/*.y
		mv btyacc.zip btyacc-$(VERSION).zip

skeleton.c: btyaccpa.ske skel2c
		@echo "/*" >$@
		@echo "** This file generated automatically from $<" >>$@
		@echo "*/" >>$@
		@echo >>$@
		awk -f skel2c btyaccpa.ske >>$@

test: program
		@cd test; CC=$(CC) ./runtests

etags TAGS:
		etags *.c *.h

help:
	@echo "A simple 'make' will build btyacc"
	@echo "'make test' will run some automated regression tests"

.PHONY: all clean clobber distclean depend index install oldinstall listing lint program dist tar zip test help

###
closure.o: defs.h
dtor.o: defs.h
error.o: defs.h
lalr.o: defs.h
lr0.o: defs.h
main.o: defs.h
mkpar.o: defs.h
mstring.o: mstring.h
output.o: defs.h
reader.o: defs.h mstring.h
readskel.o: defs.h
skeleton.o: defs.h
symtab.o: defs.h
verbose.o: defs.h
warshall.o: defs.h

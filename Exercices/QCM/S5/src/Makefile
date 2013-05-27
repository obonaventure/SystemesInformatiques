####################################################################
#
#  Makefile for assembler
#  OB, Feb 2013
#
####################################################################

CC=~/local/clang+llvm-3.2-x86_64-apple-darwin11/bin/clang

CFLAGS=-target i386 -S -Wdisabled-optimization -O0  -fverbose-asm

all:
	@for file in *.c ; do \
	($(CC) $(CFLAGS) $${file}; ) ; done
	@for file in *.c ; do \
	($(CC)  $${file}; ) ; done

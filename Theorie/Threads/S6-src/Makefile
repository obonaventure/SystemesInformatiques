#
# Makefile for source code
#
# Builds all .c files, assuming they are all independant and runs them
# to collect the output on stdout
#
# Automatically builds some of the examples to be included in the text
#

GCC	= gcc

CFLAGS = -Wall -std=c99
LDFLAGS = -lpthread

ASMFLAGS = -Wall -std=c99 -O0 -fverbose-asm -fno-stack-protector -m32 -S

CFILES := $(patsubst %.c,%.exe,$(wildcard *.c))
ASMFILES := $(patsubst %.c,%.s,$(wildcard *.c))
OUTPUT := $(patsubst %.c,%.out,$(wildcard *.c))


all: ${CFILES} ${OUTPUT}

%.s: %.c
	@echo compiling $<
	$(GCC) $(ASMFLAGS)  $<

%.exe: %.c
	@echo compiling $<
	$(GCC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.out: %.exe
	rm -f $@
	@echo executing $<
	./$< >$@


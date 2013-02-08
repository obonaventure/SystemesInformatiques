EXEC=test
CFLAGS=-I$HOME/local/include -Wall -Werror
LDFLAGS=-L$HOME/local/lib -lcunit
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: exec

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

exec: $(EXEC)
	@LD_LIBRARY_PATH=$HOME/local/lib ./$(EXEC) 

.PHONY: exec


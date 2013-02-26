BIN=crypt
CFLAGS=-Wall -Werror
LDFLAGS=-lcrypt
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

.PHONY: clean all

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)